#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"


void flash_write(uint32_t base_addr, uint32_t* buf,uint32_t len);
void flash_read(uint32_t base_addr, uint32_t * buf, uint32_t len);

int main(void)
{
    uint8_t len;
    uint16_t times = 0;
    
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
    delay_init(168);                        /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    led_init();                             /* 初始化LED */

    uint8_t cbuf[] = "i am hackerjin";
    uint8_t size =  sizeof(cbuf) /4 ;
    uint8_t read_buf[30];
    
    flash_write(0x08010000 ,(uint32_t*)cbuf, size);
    
    
    while(1)
    {
       HAL_Delay(300);
    }
}

