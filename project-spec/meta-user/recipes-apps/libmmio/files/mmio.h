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

/*
 * Try read data while optionally skipping leading zero data words. The routine reads 32 bit words from the given
 * address and then put them as 16 bit words to the buffer. If skipz is not zero it defines the number of
 * zero 32 bit words to skip before giving up and returning 0. Note that since the routine reads data by
 * 2 words at once it may read 1 more word than requested so the caller should provide the additional space
 * in the buffer. The routine returns the number of 16 bit data words read or -1 in case the address is
 * not properly aligned.
 */
int mm_read16_ex(uint32_t volatile const* addr, uint16_t* buff, unsigned word_cnt, unsigned skipz);
