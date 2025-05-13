#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"


/* ���û�����ɫ */
#define WHITE           0xFFFF      /* ��ɫ */
#define BLACK           0x0000      /* ��ɫ */
#define RED             0xF800      /* ��ɫ */
#define GREEN           0x07E0      /* ��ɫ */
#define BLUE            0x001F      /* ��ɫ */ 
#define MAGENTA         0xF81F      /* Ʒ��ɫ/�Ϻ�ɫ = BLUE + RED */
#define YELLOW          0xFFE0      /* ��ɫ = GREEN + RED */
#define CYAN            0x07FF      /* ��ɫ = GREEN + BLUE */


typedef struct 
{
   volatile uint16_t REG;
   volatile uint16_t RAM;
    
}lcd_struct;

#define LCD_BASE        ((0x60000000 + (0x4000000 * (4 - 1))) | (((1 << 6) * 2) -2))
#define LCD             ((lcd_struct *) LCD_BASE)

void write_regno(volatile uint16_t regno)
{
     regno = regno;    
    LCD->REG = regno;
}

void write_reg(uint16_t regno, uint16_t data)
{
    LCD->REG = regno;
    LCD->RAM = data;
}

void write_data(volatile uint16_t data)
{
     data = data;  
    LCD->RAM = data;
}

void lcd_opt_delay(uint32_t i)
{
    while (i--); /* ʹ��AC6ʱ��ѭ�����ܱ��Ż�,��ʹ��while(1) __asm volatile(""); */
}

uint16_t read_data()
{
    volatile uint16_t ram;  /* ��ֹ���Ż� */
    lcd_opt_delay(2);
    ram = LCD->RAM;
    return ram;
}

/**
 * @brief       NT35310�Ĵ�����ʼ������ 
 * @param       ��
 * @retval      ��
 */
void nt35310_reginit(void)
{
    write_regno(0xED);
    write_data(0x01);
    write_data(0xFE);

    write_regno(0xEE);
    write_data(0xDE);
    write_data(0x21);

    write_regno(0xF1);
    write_data(0x01);
    write_regno(0xDF);
    write_data(0x10);

    /* VCOMvoltage */
    write_regno(0xC4);
    write_data(0x8F);  /* 5f */

    write_regno(0xC6);
    write_data(0x00);
    write_data(0xE2);
    write_data(0xE2);
    write_data(0xE2);
    write_regno(0xBF);
    write_data(0xAA);

    write_regno(0xB0);
    write_data(0x0D);
    write_data(0x00);
    write_data(0x0D);
    write_data(0x00);
    write_data(0x11);
    write_data(0x00);
    write_data(0x19);
    write_data(0x00);
    write_data(0x21);
    write_data(0x00);
    write_data(0x2D);
    write_data(0x00);
    write_data(0x3D);
    write_data(0x00);
    write_data(0x5D);
    write_data(0x00);
    write_data(0x5D);
    write_data(0x00);

    write_regno(0xB1);
    write_data(0x80);
    write_data(0x00);
    write_data(0x8B);
    write_data(0x00);
    write_data(0x96);
    write_data(0x00);

    write_regno(0xB2);
    write_data(0x00);
    write_data(0x00);
    write_data(0x02);
    write_data(0x00);
    write_data(0x03);
    write_data(0x00);

    write_regno(0xB3);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);

    write_regno(0xB4);
    write_data(0x8B);
    write_data(0x00);
    write_data(0x96);
    write_data(0x00);
    write_data(0xA1);
    write_data(0x00);

    write_regno(0xB5);
    write_data(0x02);
    write_data(0x00);
    write_data(0x03);
    write_data(0x00);
    write_data(0x04);
    write_data(0x00);

    write_regno(0xB6);
    write_data(0x00);
    write_data(0x00);

    write_regno(0xB7);
    write_data(0x00);
    write_data(0x00);
    write_data(0x3F);
    write_data(0x00);
    write_data(0x5E);
    write_data(0x00);
    write_data(0x64);
    write_data(0x00);
    write_data(0x8C);
    write_data(0x00);
    write_data(0xAC);
    write_data(0x00);
    write_data(0xDC);
    write_data(0x00);
    write_data(0x70);
    write_data(0x00);
    write_data(0x90);
    write_data(0x00);
    write_data(0xEB);
    write_data(0x00);
    write_data(0xDC);
    write_data(0x00);

    write_regno(0xB8);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);

    write_regno(0xBA);
    write_data(0x24);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);

    write_regno(0xC1);
    write_data(0x20);
    write_data(0x00);
    write_data(0x54);
    write_data(0x00);
    write_data(0xFF);
    write_data(0x00);

    write_regno(0xC2);
    write_data(0x0A);
    write_data(0x00);
    write_data(0x04);
    write_data(0x00);

    write_regno(0xC3);
    write_data(0x3C);
    write_data(0x00);
    write_data(0x3A);
    write_data(0x00);
    write_data(0x39);
    write_data(0x00);
    write_data(0x37);
    write_data(0x00);
    write_data(0x3C);
    write_data(0x00);
    write_data(0x36);
    write_data(0x00);
    write_data(0x32);
    write_data(0x00);
    write_data(0x2F);
    write_data(0x00);
    write_data(0x2C);
    write_data(0x00);
    write_data(0x29);
    write_data(0x00);
    write_data(0x26);
    write_data(0x00);
    write_data(0x24);
    write_data(0x00);
    write_data(0x24);
    write_data(0x00);
    write_data(0x23);
    write_data(0x00);
    write_data(0x3C);
    write_data(0x00);
    write_data(0x36);
    write_data(0x00);
    write_data(0x32);
    write_data(0x00);
    write_data(0x2F);
    write_data(0x00);
    write_data(0x2C);
    write_data(0x00);
    write_data(0x29);
    write_data(0x00);
    write_data(0x26);
    write_data(0x00);
    write_data(0x24);
    write_data(0x00);
    write_data(0x24);
    write_data(0x00);
    write_data(0x23);
    write_data(0x00);

    write_regno(0xC4);
    write_data(0x62);
    write_data(0x00);
    write_data(0x05);
    write_data(0x00);
    write_data(0x84);
    write_data(0x00);
    write_data(0xF0);
    write_data(0x00);
    write_data(0x18);
    write_data(0x00);
    write_data(0xA4);
    write_data(0x00);
    write_data(0x18);
    write_data(0x00);
    write_data(0x50);
    write_data(0x00);
    write_data(0x0C);
    write_data(0x00);
    write_data(0x17);
    write_data(0x00);
    write_data(0x95);
    write_data(0x00);
    write_data(0xF3);
    write_data(0x00);
    write_data(0xE6);
    write_data(0x00);

    write_regno(0xC5);
    write_data(0x32);
    write_data(0x00);
    write_data(0x44);
    write_data(0x00);
    write_data(0x65);
    write_data(0x00);
    write_data(0x76);
    write_data(0x00);
    write_data(0x88);
    write_data(0x00);

    write_regno(0xC6);
    write_data(0x20);
    write_data(0x00);
    write_data(0x17);
    write_data(0x00);
    write_data(0x01);
    write_data(0x00);

    write_regno(0xC7);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);

    write_regno(0xC8);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);

    write_regno(0xC9);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);

    write_regno(0xE0);
    write_data(0x16);
    write_data(0x00);
    write_data(0x1C);
    write_data(0x00);
    write_data(0x21);
    write_data(0x00);
    write_data(0x36);
    write_data(0x00);
    write_data(0x46);
    write_data(0x00);
    write_data(0x52);
    write_data(0x00);
    write_data(0x64);
    write_data(0x00);
    write_data(0x7A);
    write_data(0x00);
    write_data(0x8B);
    write_data(0x00);
    write_data(0x99);
    write_data(0x00);
    write_data(0xA8);
    write_data(0x00);
    write_data(0xB9);
    write_data(0x00);
    write_data(0xC4);
    write_data(0x00);
    write_data(0xCA);
    write_data(0x00);
    write_data(0xD2);
    write_data(0x00);
    write_data(0xD9);
    write_data(0x00);
    write_data(0xE0);
    write_data(0x00);
    write_data(0xF3);
    write_data(0x00);

    write_regno(0xE1);
    write_data(0x16);
    write_data(0x00);
    write_data(0x1C);
    write_data(0x00);
    write_data(0x22);
    write_data(0x00);
    write_data(0x36);
    write_data(0x00);
    write_data(0x45);
    write_data(0x00);
    write_data(0x52);
    write_data(0x00);
    write_data(0x64);
    write_data(0x00);
    write_data(0x7A);
    write_data(0x00);
    write_data(0x8B);
    write_data(0x00);
    write_data(0x99);
    write_data(0x00);
    write_data(0xA8);
    write_data(0x00);
    write_data(0xB9);
    write_data(0x00);
    write_data(0xC4);
    write_data(0x00);
    write_data(0xCA);
    write_data(0x00);
    write_data(0xD2);
    write_data(0x00);
    write_data(0xD8);
    write_data(0x00);
    write_data(0xE0);
    write_data(0x00);
    write_data(0xF3);
    write_data(0x00);

    write_regno(0xE2);
    write_data(0x05);
    write_data(0x00);
    write_data(0x0B);
    write_data(0x00);
    write_data(0x1B);
    write_data(0x00);
    write_data(0x34);
    write_data(0x00);
    write_data(0x44);
    write_data(0x00);
    write_data(0x4F);
    write_data(0x00);
    write_data(0x61);
    write_data(0x00);
    write_data(0x79);
    write_data(0x00);
    write_data(0x88);
    write_data(0x00);
    write_data(0x97);
    write_data(0x00);
    write_data(0xA6);
    write_data(0x00);
    write_data(0xB7);
    write_data(0x00);
    write_data(0xC2);
    write_data(0x00);
    write_data(0xC7);
    write_data(0x00);
    write_data(0xD1);
    write_data(0x00);
    write_data(0xD6);
    write_data(0x00);
    write_data(0xDD);
    write_data(0x00);
    write_data(0xF3);
    write_data(0x00);
    write_regno(0xE3);
    write_data(0x05);
    write_data(0x00);
    write_data(0xA);
    write_data(0x00);
    write_data(0x1C);
    write_data(0x00);
    write_data(0x33);
    write_data(0x00);
    write_data(0x44);
    write_data(0x00);
    write_data(0x50);
    write_data(0x00);
    write_data(0x62);
    write_data(0x00);
    write_data(0x78);
    write_data(0x00);
    write_data(0x88);
    write_data(0x00);
    write_data(0x97);
    write_data(0x00);
    write_data(0xA6);
    write_data(0x00);
    write_data(0xB7);
    write_data(0x00);
    write_data(0xC2);
    write_data(0x00);
    write_data(0xC7);
    write_data(0x00);
    write_data(0xD1);
    write_data(0x00);
    write_data(0xD5);
    write_data(0x00);
    write_data(0xDD);
    write_data(0x00);
    write_data(0xF3);
    write_data(0x00);

    write_regno(0xE4);
    write_data(0x01);
    write_data(0x00);
    write_data(0x01);
    write_data(0x00);
    write_data(0x02);
    write_data(0x00);
    write_data(0x2A);
    write_data(0x00);
    write_data(0x3C);
    write_data(0x00);
    write_data(0x4B);
    write_data(0x00);
    write_data(0x5D);
    write_data(0x00);
    write_data(0x74);
    write_data(0x00);
    write_data(0x84);
    write_data(0x00);
    write_data(0x93);
    write_data(0x00);
    write_data(0xA2);
    write_data(0x00);
    write_data(0xB3);
    write_data(0x00);
    write_data(0xBE);
    write_data(0x00);
    write_data(0xC4);
    write_data(0x00);
    write_data(0xCD);
    write_data(0x00);
    write_data(0xD3);
    write_data(0x00);
    write_data(0xDD);
    write_data(0x00);
    write_data(0xF3);
    write_data(0x00);
    write_regno(0xE5);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x02);
    write_data(0x00);
    write_data(0x29);
    write_data(0x00);
    write_data(0x3C);
    write_data(0x00);
    write_data(0x4B);
    write_data(0x00);
    write_data(0x5D);
    write_data(0x00);
    write_data(0x74);
    write_data(0x00);
    write_data(0x84);
    write_data(0x00);
    write_data(0x93);
    write_data(0x00);
    write_data(0xA2);
    write_data(0x00);
    write_data(0xB3);
    write_data(0x00);
    write_data(0xBE);
    write_data(0x00);
    write_data(0xC4);
    write_data(0x00);
    write_data(0xCD);
    write_data(0x00);
    write_data(0xD3);
    write_data(0x00);
    write_data(0xDC);
    write_data(0x00);
    write_data(0xF3);
    write_data(0x00);

    write_regno(0xE6);
    write_data(0x11);
    write_data(0x00);
    write_data(0x34);
    write_data(0x00);
    write_data(0x56);
    write_data(0x00);
    write_data(0x76);
    write_data(0x00);
    write_data(0x77);
    write_data(0x00);
    write_data(0x66);
    write_data(0x00);
    write_data(0x88);
    write_data(0x00);
    write_data(0x99);
    write_data(0x00);
    write_data(0xBB);
    write_data(0x00);
    write_data(0x99);
    write_data(0x00);
    write_data(0x66);
    write_data(0x00);
    write_data(0x55);
    write_data(0x00);
    write_data(0x55);
    write_data(0x00);
    write_data(0x45);
    write_data(0x00);
    write_data(0x43);
    write_data(0x00);
    write_data(0x44);
    write_data(0x00);

    write_regno(0xE7);
    write_data(0x32);
    write_data(0x00);
    write_data(0x55);
    write_data(0x00);
    write_data(0x76);
    write_data(0x00);
    write_data(0x66);
    write_data(0x00);
    write_data(0x67);
    write_data(0x00);
    write_data(0x67);
    write_data(0x00);
    write_data(0x87);
    write_data(0x00);
    write_data(0x99);
    write_data(0x00);
    write_data(0xBB);
    write_data(0x00);
    write_data(0x99);
    write_data(0x00);
    write_data(0x77);
    write_data(0x00);
    write_data(0x44);
    write_data(0x00);
    write_data(0x56);
    write_data(0x00);
    write_data(0x23);
    write_data(0x00);
    write_data(0x33);
    write_data(0x00);
    write_data(0x45);
    write_data(0x00);

    write_regno(0xE8);
    write_data(0x00);
    write_data(0x00);
    write_data(0x99);
    write_data(0x00);
    write_data(0x87);
    write_data(0x00);
    write_data(0x88);
    write_data(0x00);
    write_data(0x77);
    write_data(0x00);
    write_data(0x66);
    write_data(0x00);
    write_data(0x88);
    write_data(0x00);
    write_data(0xAA);
    write_data(0x00);
    write_data(0xBB);
    write_data(0x00);
    write_data(0x99);
    write_data(0x00);
    write_data(0x66);
    write_data(0x00);
    write_data(0x55);
    write_data(0x00);
    write_data(0x55);
    write_data(0x00);
    write_data(0x44);
    write_data(0x00);
    write_data(0x44);
    write_data(0x00);
    write_data(0x55);
    write_data(0x00);

    write_regno(0xE9);
    write_data(0xAA);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);

    write_regno(0x00);
    write_data(0xAA);

    write_regno(0xCF);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);

    write_regno(0xF0);
    write_data(0x00);
    write_data(0x50);
    write_data(0x00);
    write_data(0x00);
    write_data(0x00);

    write_regno(0xF3);
    write_data(0x00);

    write_regno(0xF9);
    write_data(0x06);
    write_data(0x10);
    write_data(0x29);
    write_data(0x00);

    write_regno(0x3A);
    write_data(0x55);  /* 66 */

    write_regno(0x11);
    delay_ms(100);
    write_regno(0x29);
    write_regno(0x35);
    write_data(0x00);

    write_regno(0x51);
    write_data(0xFF);
    write_regno(0x53);
    write_data(0x2C);
    write_regno(0x55);
    write_data(0x82);
    write_regno(0x2c);
}



/* LCD��Ҫ������ */
typedef struct
{
    uint16_t width;     /* LCD ��� */
    uint16_t height;    /* LCD �߶� */
    uint16_t id;        /* LCD ID */
    uint16_t gramcmd;   /* ��ʼдgramָ�� */
    uint16_t setxcmd;   /* ����x����ָ�� */
    uint16_t setycmd;   /* ����y����ָ�� */
}_lcd;

_lcd lcd_params;


void set_region(uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end)
{
    write_regno(lcd_params.setxcmd);
    write_data(x_start >> 8);
    write_data(x_start);
    write_data(x_end >> 8);
    write_data(x_end);
    
    write_regno(lcd_params.setycmd);
    write_data(y_start >>8);
    write_data(y_start);
    write_data(y_end >>8);
    write_data(y_end);
}

void init_display()
{
    
    lcd_params.setxcmd = 0x2A;
    lcd_params.setycmd = 0x2B;
    lcd_params.gramcmd = 0x2C; 
    lcd_params.width = 320;
    lcd_params.height = 480;
     
   //���÷��� 
    write_reg(0x36,0);  
    
}



void pre_gram_write()
{
    write_regno(lcd_params.gramcmd);
}


void lcd_fill_region(uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end , uint16_t color)
{
    set_region(x_start,x_end,y_start,y_end);
    
    pre_gram_write();
    for(uint32_t index = 0; index < (( x_end - x_start + 1) * (y_end - y_start +1) );index++ )
    {
        write_data(color);
        
    }
}


SRAM_HandleTypeDef lcd_handle;
void my_lcd_init()
{
     
    //����ʱ��ʹ��
     __HAL_RCC_FSMC_CLK_ENABLE();
    
    __GPIOB_CLK_ENABLE();
    __GPIOD_CLK_ENABLE();
    __GPIOE_CLK_ENABLE();
    __GPIOF_CLK_ENABLE();
    __GPIOG_CLK_ENABLE();
    
    GPIO_InitTypeDef gpio_init;
    gpio_init.Pin =  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |GPIO_PIN_14 | GPIO_PIN_15;
    gpio_init.Mode = GPIO_MODE_AF_PP;
    gpio_init.Pull = GPIO_PULLUP;
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio_init.Alternate = GPIO_AF12_FSMC;
    HAL_GPIO_Init(GPIOD,&gpio_init);
    
    gpio_init.Pin =  GPIO_PIN_7| GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |GPIO_PIN_12 |GPIO_PIN_13 |GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE,&gpio_init);
    
    gpio_init.Pin = GPIO_PIN_12;
    HAL_GPIO_Init(GPIOF,&gpio_init);
    HAL_GPIO_Init(GPIOG,&gpio_init);
    
    //��������
    gpio_init.Pin = GPIO_PIN_15;
    gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(GPIOB,&gpio_init);
    
    
    lcd_handle.Instance = FSMC_NORSRAM_DEVICE;
    lcd_handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
    lcd_handle.Init.NSBank = FSMC_NORSRAM_BANK4;                        /* ʹ��NE4 */
    lcd_handle.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;     /* ��ַ/�����߲����� */
    lcd_handle.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;    /* 16λ���ݿ�� */
    lcd_handle.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;       /* �洢��дʹ�� */
    lcd_handle.Init.ExtendedMode = FSMC_EXTENDED_MODE_ENABLE;           /* ��дʹ�ò�ͬ��ʱ�� */
    
    
    FSMC_NORSRAM_TimingTypeDef fsmc_read_handle;
    FSMC_NORSRAM_TimingTypeDef fsmc_write_handle;
   /* FSMC��ʱ����ƼĴ��� */
    fsmc_read_handle.AddressSetupTime = 15;           /* ��ַ����ʱ��(ADDSET)Ϊ15��fsmc_ker_ck(1/168=6)��6*15=90ns */
    fsmc_read_handle.AddressHoldTime = 0;            /* ��ַ����ʱ��(ADDHLD) ģʽA��û���õ� */
    fsmc_read_handle.DataSetupTime = 60;                /* ���ݱ���ʱ��(DATAST)Ϊ60��fsmc_ker_ck=6*60=360ns */
                                                        /* ��ΪҺ������IC�Ķ����ݵ�ʱ��,�ٶȲ���̫��,�����Ǹ�������оƬ */
    fsmc_read_handle.AccessMode = FSMC_ACCESS_MODE_A;   /* ģʽA */
    
    /* FSMCдʱ����ƼĴ��� */
    fsmc_write_handle.AddressSetupTime = 9;             /* ��ַ����ʱ��(ADDSET)Ϊ9��fsmc_ker_ck=6*9=54ns */
    fsmc_write_handle.AddressHoldTime = 0;           /* ��ַ����ʱ��(ADDHLD) ģʽA��û���õ� */
    fsmc_write_handle.DataSetupTime = 9;                /* ���ݱ���ʱ��(DATAST)Ϊ9��fsmc_ker_ck=6*9=54ns */
                                                        /* ע�⣺ĳЩҺ������IC��д�ź���������Ҳ��50ns */
    fsmc_write_handle.AccessMode = FSMC_ACCESS_MODE_A;  /* ģʽA */
    
    HAL_SRAM_Init(&lcd_handle, &fsmc_read_handle, &fsmc_write_handle);
    
    //�������ʱ
    delay_ms(50);
    
    //����LCD����
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);
   
    write_regno(0xD4);
    lcd_params.id = read_data();  /* dummy read */
    lcd_params.id = read_data();  /* ����0x01 */
    lcd_params.id = read_data();  /* ����0x53 */
    lcd_params.id <<= 8;
    lcd_params.id |= read_data(); /* �������0x10 */
    
    
   
     
    nt35310_reginit();
    
    printf("lcd id is %x\n",lcd_params.id);
    
    if(lcd_params.id == 0x5310)
    {
        fsmc_write_handle.AddressSetupTime = 1;
        fsmc_write_handle.DataSetupTime = 1;
        FSMC_NORSRAM_Extended_Timing_Init(lcd_handle.Extended,&fsmc_write_handle,lcd_handle.Init.NSBank,lcd_handle.Init.ExtendedMode);
        
    }
     
    init_display();
    lcd_fill_region(0,200,0,200, YELLOW);

}