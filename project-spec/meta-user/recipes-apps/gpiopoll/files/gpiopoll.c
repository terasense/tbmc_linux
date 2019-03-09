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
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>

int main(int argc, char **argv)
{
	char buff[128];
	char path[128] = {};
	struct pollfd fdset[1];
	int pin, fd;

	if (argc < 2) {
		fprintf(stderr, "GPI pin number argument missing\n");
		return -1;
	}

	pin = atoi(argv[1]);
	snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY | O_NONBLOCK );
	if (fd < 0) {
		fprintf(stderr, "Failed to open %s: %d (%s)\n", path, errno, strerror(errno));
		return -1;
	}

	fdset[0].fd = fd;
	fdset[0].events = POLLPRI;
	
	for (;;) {
		fdset[0].revents = 0;
		if (poll(fdset, 1, -1) < 0) {
			fprintf(stderr, "Failed to poll %s: %d (%s)\n", path, errno, strerror(errno));
			return -1;
		}
		if (fdset[0].revents & POLLPRI) {
			printf("*");
			fflush(stdout);
		} else {
			// Should not happen
			fprintf(stderr, "Returned %#x events\n", fdset[0].revents);
			return -1;
		}
		if (pread(fd, buff, sizeof(buff), 0) < 0) {
			fprintf(stderr, "Failed to read %s: %d (%s)\n", path, errno, strerror(errno));
			return -1;
		}
	}

	return 0;
}
