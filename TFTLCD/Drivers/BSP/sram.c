#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"


SRAM_HandleTypeDef sram_handle;

void sram_init()
{
    //外设时钟使能
    __HAL_RCC_FSMC_CLK_ENABLE();
    __GPIOD_CLK_ENABLE();
    __GPIOE_CLK_ENABLE();
    __GPIOF_CLK_ENABLE();
    __GPIOG_CLK_ENABLE();
    
    GPIO_InitTypeDef gpio_init;
    gpio_init.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_12 |GPIO_PIN_13 |GPIO_PIN_14 | GPIO_PIN_15;
    gpio_init.Mode = GPIO_MODE_AF_PP;
    gpio_init.Pull = GPIO_NOPULL;
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init.Alternate = GPIO_AF12_FSMC;
    HAL_GPIO_Init(GPIOF,&gpio_init);
    
    gpio_init.Pin =  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |GPIO_PIN_12 |GPIO_PIN_13 |GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOD,&gpio_init);
    
    gpio_init.Pin =  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |GPIO_PIN_12 |GPIO_PIN_13 |GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE,&gpio_init);
    
    gpio_init.Pin =  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3  |GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_10 ;
    HAL_GPIO_Init(GPIOG,&gpio_init);
    
    sram_handle.Instance = FSMC_NORSRAM_DEVICE;
    sram_handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
    sram_handle.Init.NSBank = FSMC_NORSRAM_BANK3;
    sram_handle.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
    sram_handle.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
    sram_handle.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
    sram_handle.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
    sram_handle.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
    sram_handle.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
    
    
    FSMC_NORSRAM_TimingTypeDef timing;
    timing.AccessMode = FSMC_ACCESS_MODE_A;
    timing.AddressHoldTime = 0x00;
    timing.AddressSetupTime = 0x02;
    timing.DataSetupTime = 0x08;
    HAL_SRAM_Init(&sram_handle,&timing,&timing);
}