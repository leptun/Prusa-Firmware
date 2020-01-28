//uvlo.h
#ifndef _UVLO_H
#define _UVLO_H
#include "Configuration_prusa.h"
#ifdef UVLO_SUPPORT

#include <inttypes.h>

#define XFLASH_READ(valuePointer, xflash_address) do {w25x20cl_wait_busy(); w25x20cl_rd_data(xflash_address, (uint8_t*)&valuePointer, (uint16_t)sizeof(valuePointer));} while(0)
#define XFLASH_READ_WITH_SIZE(valuePointer, xflash_address, size) do {w25x20cl_wait_busy(); w25x20cl_rd_data(xflash_address, (uint8_t*)&valuePointer, (uint16_t)size);} while(0)
#define XFLASH_WRITE(valuePointer, xflash_address) xflash_write(xflash_address, (uint8_t*)&valuePointer, (uint16_t)sizeof(valuePointer))
#define XFLASH_WRITE_WITH_SIZE(valuePointer, xflash_address, size) xflash_write(xflash_address, (uint8_t*)&valuePointer, size)

#define XFLASH_PAGE_SIZE 256
#define XFLASH_SECTOR_SIZE 4096
#define XFLASH_TOP 262144

//table of addresses for saved and restored values for XVLO
#define XVLO_TOP XFLASH_TOP
#define XVLO_DIR_DEPTH (XVLO_TOP - 1*sizeof(uint8_t))
#define XVLO_DIRS_ARRAY (XVLO_DIR_DEPTH - 8*MAX_DIR_DEPTH*sizeof(char)) //all the directories filenames that construct the full path (8 chars long) from root till the file. The number of dirs is XVLO_DIR_DEPTH.
#define XVLO_FILENAME (XVLO_DIRS_ARRAY - 13*sizeof(char)) //full 8.3 filename string (max 13 bytes, can be less if filename is really short). Null terminated
#define XVLO_FILE_POSITION (XVLO_FILENAME - sizeof(uint32_t))
#define XVLO_MBL (XVLO_FILE_POSITION - (MESH_NUM_X_POINTS * MESH_NUM_Y_POINTS)*sizeof(float))

extern void xflash_write(uint32_t addr, uint8_t* data, uint16_t cnt);
extern void uvlo_prepare_for_next_uvlo();
extern void uvlo_init();


#endif //UVLO_SUPPORT
#endif //_UVLO_H
