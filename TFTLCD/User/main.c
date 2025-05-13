#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"


void sram_init();


//定义SRAM直接访问数组
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
    
    HAL_Init();                             /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);     /* 设置时钟,168Mhz */
    delay_init(168);                        /* 延时初始化 */
    usart_init(115200);                     /* 串口初始化为115200 */
    led_init();                             /* 初始化LED */
    my_lcd_init();
    
    
   
    uint16_t buf;
    while (1)
    {
        
        delay_ms(1000);
    }
}
