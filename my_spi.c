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
#include <linux/i2c.h>
#include <linux/spi/spi.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#define NAME "icm20608"

#define WHO_AM_I 0x75

#define PWR_MGMT_1 0x6b
#define PWR_MGMT_2 0x6c

#define ACCEL_XOUT_H 0x3b
#define TEMP_OUT_H 0x41
#define GYRO_XOUT_H 0x43

#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define INT_STATUS 0x3A

static struct  miscdevice misc;
static struct spi_device* spi;

static int write_regs(uint8_t reg,uint8_t len, uint8_t* buf)
{

    struct spi_message spi_msg = {0};
    spi_message_init(&spi_msg);

    struct spi_transfer spi_trans = {0};

    uint8_t temp_buf[len+1];
    temp_buf[0] = reg & (~0x80);
    memcpy(&temp_buf[1],buf,len);
    spi_trans.len = len + 1;
    spi_trans.tx_buf = temp_buf;

    spi_message_add_tail(&spi_trans, &spi_message);
    
    return spi_sync(spi,&spi_msg);

}

static int read_regs(uint8_t reg,uint8_t len, uint8_t* buf)
{
    reg = reg  | 0x80;

    return spi_write_then_read(spi,&reg,1,buf,len);

}

static int open(struct inode * inode, struct file * f)
{

    return 0;

}

static int release(struct inode * inode, struct file * f);
{

    return 0;

}

static ssize_t read(struct file * f, char __user * user_buf, size_t len, loff_t * offset)
{
    //一次性读取14字节传感器数据
    int16_t temp_buf[7];

    read_regs(ACCEL_XOUT_H,14,temp_buf);
    
    copy_to_user(user_buf,temp_buf,14);

    return 14;
    
}



static struct file_operations  ops = 
{
    .open = open,
    .read = read,
    .release = release,
};


static int icm_probe(struct spi_device *spi_dev)
{
    spi = spi_dev;

    //申请icm连接的gpio中断

    //配置icm
    uint8_t val;
    val = 0x80;

    //只进行复位，不进行时钟设置，使用默认时钟设置
    write_regs(PWR_MGMT_1,1,&val);
    
    read_regs(WHO_AM_I,1,&val);

    if(val == 0xAF)
        printk("id is right\n");
    else
    {
        printk("id is not right\n);
        return -1;
    }


    //注册misc
    misc.fops = ops;
    misc.name = NAME;
    misc.minor = 99;
    misc.parent = spi->dev;
    
    misc_register(&misc);
    
    return 0;
}


static int  icm_remove(struct spi_device *spi)
{

    //取消中断

    misc_deregister(&misc);
    return 0;

}



static struct spi_driver  icm_driver= {
    .probe = icm_probe,
    .remove = icm_remove,
    .driver = 
    {
        .name = NAME,
        .owner = THIS_MODULE,
    }
    .id_table = {
        .name = NAME
    } ,
};

static int __init icm_init(void)
{
	return spi_register_driver(&icm_driver);
}

/*
 * @description	: 驱动出口函数
 * @param 		: 无
 * @return 		: 无
 */
static void __exit icm_exit(void)
{
	spi_unregister_driver(&icm_driver);
}


module_init(icm_init);
module_exit(icm_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("zuozhongkai");