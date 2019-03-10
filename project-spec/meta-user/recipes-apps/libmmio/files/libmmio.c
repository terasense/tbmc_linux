/* 
 * (C) 2018-2019 TeraSense Inc. http://terasense.com/
 * All Rights Reserved
 *
 * Description: The memory mapped IO helper
 *
 * Author: Oleg Volkov olegv142@gmail.com
 */

#include <mmio.h>

#define IS_ALIGNED(addr) (!((long)addr & (sizeof(*addr)-1)))

uint32_t mm_peek(uint32_t volatile const* addr)
{
	return *addr;
}

int mm_poke(uint32_t volatile* addr, uint32_t val)
{
	if (!IS_ALIGNED(addr))
		return -1;
	*addr = val;
	return 0;
}

int mm_read(uint32_t volatile const* addr, uint32_t* buff, unsigned word_cnt)
{
	if (!IS_ALIGNED(addr))
		return -1;
	for (; word_cnt; --word_cnt, ++buff) {
		*buff = *addr;
	}
	return 0;
}

int mm_write(uint32_t volatile* addr, uint32_t const* buff, unsigned word_cnt)
{
	if (!IS_ALIGNED(addr))
		return -1;
	for (; word_cnt; --word_cnt, ++buff) {
		*addr = *buff;
	}
	return 0;
}

int mm_write16(uint32_t volatile* addr, uint16_t const* buff, unsigned word_cnt)
{
	if (!IS_ALIGNED(addr))
		return -1;
	for (; word_cnt; --word_cnt, ++buff) {
		*addr = *buff;
	}
	return 0;
}
