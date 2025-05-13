#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"

//0-3扇区的长度都是16k
#define SECTOR0_BASE 0x08000000
#define SECTOR1_BASE 0x08004000
#define SECTOR2_BASE 0x08008000
#define SECTOR3_BASE 0x0800C000
//4扇区是64k
#define SECTOR4_BASE 0x08010000
//5扇区及以后是128k
#define SECTOR5_BASE 0x08020000
#define SECTOR6_BASE 0x08040000
#define SECTOR7_BASE 0x08060000
#define SECTOR8_BASE 0x08080000
#define SECTOR9_BASE 0x080A0000
#define SECTOR10_BASE 0x080C0000
#define SECTOR11_BASE 0x080E0000

uint32_t flash_read_word(uint32_t addr)
{
    return *((volatile uint32_t*)(addr));
    
}
void flash_read(uint32_t base_addr, uint32_t * buf, uint32_t len)
{
    for(int i = 0; i< len;i++)
    {
        
        buf[i]  = *((volatile uint32_t*)(base_addr + i*4));
        
    }
}

uint8_t get_flash_sector(uint32_t addr)
{
    if(addr < SECTOR1_BASE)
        return 0;
    else if(addr < SECTOR2_BASE)
        return 1;
    else if(addr < SECTOR3_BASE)
        return 2;
    else if(addr < SECTOR4_BASE)
        return 3;
    else if(addr < SECTOR5_BASE)
        return 4;
    else if(addr < SECTOR6_BASE)
        return 5;
    else if(addr < SECTOR7_BASE)
        return 6;
    else if(addr < SECTOR8_BASE)
        return 7;
    else if(addr < SECTOR9_BASE)
        return 8;
    else if(addr < SECTOR10_BASE)
        return 9;
    else if(addr < SECTOR11_BASE)
        return 10;
    else
        return 11;
}

void flash_write(uint32_t base_addr, uint32_t* buf,uint32_t len)
{
    if( base_addr % 4 != 0 || base_addr < SECTOR0_BASE  || base_addr + len*4 > SECTOR11_BASE + 0x20000)
    {
        printf("地址不合法\n");
        return;
    }
    
    FLASH_EraseInitTypeDef erase_init;
    erase_init.Banks = FLASH_BANK_1;
    erase_init.NbSectors = 1;
    erase_init.TypeErase = FLASH_TYPEERASE_SECTORS;
    erase_init.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    
    uint32_t erase_err;
    
    HAL_FLASH_Unlock();
    FLASH->ACR &= ~(1 << 10);
    
   
    for(uint32_t i = 0; i < len; i++)
    {
        //此种情况下需要清除此地址所在的扇区，为后续数据的写入作准备
        if(flash_read_word(base_addr + i*4) != 0xFFFFFFFF)
        {
            erase_init.Sector = get_flash_sector(base_addr + i*4);
            HAL_FLASHEx_Erase(&erase_init,&erase_err);
        }
        FLASH_WaitForLastOperation(50000);
    }
    
    for(uint32_t i = 0; i < len; i++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD ,base_addr + i*4,buf[i]);
    }
    
    FLASH->ACR |= 1 << 10;
    HAL_FLASH_Lock();
    
}
