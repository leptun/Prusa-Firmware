//uvlo.h
#ifndef _UVLO_H
#define _UVLO_H
#include "Configuration_prusa.h"
#ifdef UVLO_SUPPORT

#include <inttypes.h>

// These should be moved to uvlo.cpp once all UVLO code is moved there.
#include "Configuration.h"
#include "ConfigurationStore.h"

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
#define XVLO_CURRENT_POSITION (XVLO_MBL - 4*sizeof(float))
#define XVLO_AXIS_RELATIVE_MODES (XVLO_CURRENT_POSITION - 4*sizeof(bool))
#define XVLO_SAVED_TARGET (XVLO_AXIS_RELATIVE_MODES - 4*sizeof(float))
#define XVLO_LA_K (XVLO_SAVED_TARGET - sizeof(float))
#define XVLO_CONFIGURATION_STORE (XVLO_LA_K - sizeof(cs))
#define XVLO_EXTRUDER_MULTIPLIER (XVLO_CONFIGURATION_STORE - EXTRUDERS*sizeof(float))
#define XVLO_EXTRUDEMULTIPLY (XVLO_EXTRUDER_MULTIPLIER - sizeof(int))
#define XVLO_FEEDRATE (XVLO_EXTRUDEMULTIPLY - sizeof(uint16_t))
#define XVLO_TARGET_TEMPERATURE_BED (XVLO_FEEDRATE - sizeof(int))
#define XVLO_TARGET_TEMPERATURE (XVLO_TARGET_TEMPERATURE_BED - EXTRUDERS*sizeof(int))
#define XVLO_ACTIVE_EXTRUDER (XVLO_TARGET_TEMPERATURE - sizeof(uint8_t))
#define XVLO_FANSPEED (XVLO_ACTIVE_EXTRUDER - sizeof(int))
#define XVLO_FEEDMULTIPLY (XVLO_FANSPEED - sizeof(int))

extern void xflash_write(uint32_t addr, uint8_t* data, uint16_t cnt);
extern void uvlo_drain_reset();
extern void uvlo_clear();
extern void uvlo_init();


#endif //UVLO_SUPPORT
#endif //_UVLO_H
