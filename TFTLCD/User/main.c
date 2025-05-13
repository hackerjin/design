#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"


void sram_init();


//����SRAMֱ�ӷ�������
#define SRAM_BASE_ADDR   (0X60000000 + (0X4000000 * 2))
uint16_t sram_buffer[500000] __attribute__((at(SRAM_BASE_ADDR)));

void sram_write(uint32_t addr, uint16_t data)
{
    *((volatile uint16_t*) (SRAM_BASE_ADDR + addr*2) )= data;   
}


void sram_read(uint32_t addr, uint16_t* buf)
{
    *buf = *((volatile uint16_t*) (SRAM_BASE_ADDR + addr*2));
    
}

void my_lcd_init();

int main(void)
{
    uint8_t x = 0;
    uint8_t lcd_id[12];
    
    HAL_Init();                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7);     /* ����ʱ��,168Mhz */
    delay_init(168);                        /* ��ʱ��ʼ�� */
    usart_init(115200);                     /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                             /* ��ʼ��LED */
    my_lcd_init();
    
    
   
    uint16_t buf;
    while (1)
    {
        
        delay_ms(1000);
    }
}
