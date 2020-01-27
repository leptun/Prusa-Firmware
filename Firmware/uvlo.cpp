//uvlo.cpp

#include "uvlo.h"
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include "eeprom.h"
#include "w25x20cl.h"
#include "ConfigurationStore.h"
#include "Configuration_adv.h"
#include "system_timer.h"
#include "Marlin.h"
#include "pins.h"
#include "fastio.h"
#include "temperature.h"
#include "messages.h"
#include "language.h"
#include "ultralcd.h"
#include "backlight.h"
#include "planner.h"
#include "cardreader.h"
#include "stepper.h"
#include "tmc2130.h"
#include "cmdqueue.h"
#include "mesh_bed_leveling.h"
#include "mesh_bed_calibration.h"

#ifdef UVLO_SUPPORT

//This function is needed since a write page command can only affect one page at a time. Normally, if the value that is written overlaps two pages, the code will wrap to the beginning of the page, the second page remaining unaffected. This function splits the write command in case it is not alligned.
void xflash_write(uint32_t addr, uint8_t* data, uint16_t cnt)
{
    while (cnt>0)
    {
        uint16_t tempCount = min(cnt, ((addr | (XFLASH_PAGE_SIZE - 1)) - addr + 1));
        w25x20cl_wait_busy();
        w25x20cl_enable_wr();
        w25x20cl_page_program(addr, data, tempCount);
        cnt -=tempCount;
        addr+=tempCount;
        data+=tempCount;
    }
}

void uvlo_prepare_for_next_uvlo()
{
    //todo: Make the command respect the last XFLASH_UVLO block
    W25X20CL_SPI_ENTER();
    for (uint_least8_t i = 0; i < 1; i++)
    {
        w25x20cl_wait_busy();
        w25x20cl_enable_wr();
        w25x20cl_sector_erase(XVLO_TOP - 1 - i * XFLASH_SECTOR_SIZE);
    }
    printf_P(PSTR("uvlo_prepare_for_next_uvlo: OK\n"));
}

void uvlo_init()
{
    if (eeprom_read_byte((uint8_t*)EEPROM_UVLO) == 255) {
		eeprom_write_byte((uint8_t*)EEPROM_UVLO, 0);
        uvlo_prepare_for_next_uvlo();
	}
    DDRE &= ~(1 << 4); //input pin
    PORTE &= ~(1 << 4); //no internal pull-up

    //sensing falling edge
    EICRB |= (1 << 0);
    EICRB &= ~(1 << 1);

    //enable INT4 interrupt
    EIMSK |= (1 << 4);
}

#endif //UVLO_SUPPORT