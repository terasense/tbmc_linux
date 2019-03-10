/* 
 * (C) 2018-2019 TeraSense Inc. http://terasense.com/
 * All Rights Reserved
 *
 * Description: The memory mapped IO helper
 *
 * Author: Oleg Volkov olegv142@gmail.com
 */

#include <stdint.h>

uint32_t mm_peek(uint32_t volatile const* addr);

/*
 * The following functions return 0 on success, -1 in case the address is not properly aligned
 */
int mm_poke(uint32_t volatile* addr, uint32_t val);

int mm_read(uint32_t volatile const* addr, uint32_t* buff, unsigned word_cnt);

int mm_write(uint32_t volatile* addr, uint32_t const* buff, unsigned word_cnt);

int mm_write16(uint32_t volatile* addr, uint16_t const* buff, unsigned word_cnt);

