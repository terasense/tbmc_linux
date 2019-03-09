/*
* Copyright (C) 2013 - 2016  Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or (b) that interact
* with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in this
* Software without prior written authorization from Xilinx.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#define ADDR 0x43c00000

int main(int argc, char **argv)
{	
	int iters, devmem;
	uint32_t volatile * ptr, v;

	if (argc < 2) {
		printf("Usage: %s iters\n", argv[0]);
		return -1;
	}
	iters = atoi(argv[1]);
	devmem = open("/dev/mem",O_RDWR);
	if (devmem < 0) {
		printf("couldn't open /dev/mem. Are you root?\n");
		return -1;
	}
	ptr = mmap(0, 4096, PROT_READ, MAP_SHARED, devmem, ADDR);
	if (ptr == MAP_FAILED) {
		printf("map failed: %s\n", strerror(errno));
		close(devmem);
		return -1;
	}
	for (; iters > 0; iters -= 8) {
		v = *ptr; (void)v;
		v = *ptr; (void)v;
		v = *ptr; (void)v;
		v = *ptr; (void)v;
		v = *ptr; (void)v;
		v = *ptr; (void)v;
		v = *ptr; (void)v;
		v = *ptr; (void)v;
	}
	munmap((void*)ptr, 4096);
	close(devmem);
	return 0;
}
