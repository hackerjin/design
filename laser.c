#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/of_gpio.h>
#include <linux/semaphore.h>
#include <linux/timer.h>
#include <linux/irq.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/platform_device.h>
#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/miscdevice.h>


struct laser_dev
{
    dev_t dev_no;
    struct class* cls;
    int gpio;
    struct cdev cdev;
    struct mutex lock;
};

static int open(struct inode * node, struct file * f)
{
    f->private_data = container_of(node->i_cdev , struct laser_dev, cdev);
}

static ssize_t write(struct file * f, const char __user * user_buf, size_t len, loff_t * off)
{
    struct laser_dev* laser_dev = f->private_data;


    //加锁，防止同一个文件不同使用者同时控制gpio口
    mutex_lock(&laser_dev->lock);

    uint8_t temp;
    copy_from_user(&temp,user_buf,1);
    gpio_set_value(laser_dev->gpio,temp);

    mutex_unlock(&laser_dev->lock);
    return 0;
}


static int release(struct inode * node, struct file * f)
{


    return 0;
}

static struct of_device_id match_table[] = 
{
    {.compatible = "dotlaser"},
    {.compatible = "crosslaser"},
    {}
};

static struct file_operations fops = {
    .open = open,
    .write = write,
    .release = release,
};



static int probe(struct platform_device * pdev)
{
    struct device* dev = &pdev->dev;

    //获取匹配id
    struct of_device_id *match_id = of_match_device(match_table, dev);

    //分配驱动结构体
    struct laser_dev* laser_dev = devm_kzalloc(dev,sizeof(struct laser_dev) ,GFP_KERNEL);
    
    //绑定，后续在remove使用
    platform_set_drvdata(pdev,laser_dev);


    
    alloc_chrdev_region(&laser_dev->dev_no,0,1,"laser");

    cdev_init(&laser_dev->cdev,&fops);
    cdev_add(&laser_dev->cdev,laser_dev->dev_no,1);

    laser_dev->cls =  class_create(THIS_MODULE, match_id->compatible);
    device_create(laser_dev->cls,dev ,laser_dev->dev_no,NULL,match_id->compatible);

    laser_dev->gpio =  of_get_named_gpio(dev->of_node,"laser-gpios",0);
    devm_gpio_request(laser_dev->gpio,match_id->compatible);
    gpio_direction_output(laser_dev->gpio,1);

    mutex_init(laser_dev->lock);
    return 0;
}



static int remove(struct platform_device * pdev)
{

    struct laser_dev* laser_dev = platform_get_drvdata(pdev);
    cdev_del(&laser_dev->cdev);				/*  删除cdev */
	unregister_chrdev_region(laser_dev->dev_no, 1); /* 注销设备号 */
	device_destroy(laser_dev->cls, laser_dev->dev_no);
	class_destroy(laser_dev->cls);
	return 0;

}



static struct platform_driver laser_driver = 
{
    .driver = 
    {
        .of_match_table = match_table,
        .owner = THIS_MODULE,
        .name = "laser",
    },
    .probe = probe,
    .remove = remove,

};


module_platform_driver(laser_driver);
MODULE_DESCRIPTION("laser driver");
MODULE_AUTHOR("design");
MODULE_LICENSE("GPL v2");