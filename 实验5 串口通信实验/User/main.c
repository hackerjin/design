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
    
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    delay_init(168);                        /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                             /* ��ʼ��LED */

    uint8_t cbuf[] = "i am hackerjin";
    uint8_t size =  sizeof(cbuf) /4 ;
    uint8_t read_buf[30];
    
    flash_write(0x08010000 ,(uint32_t*)cbuf, size);
    
    
    while(1)
    {
       HAL_Delay(300);
    }
}

