#pragma once
#ifndef MEMDUMP_H
#define MEMDUMP_H

#include <cstdio>
#include <cstdlib>
#include <string.h>

#define INFO    true //displays startup information
#define ADDRESS true //displays the starting address of the hex dump on the left
#define COLSIZE 16   //number of columns
#define ASCII   true //displays ascii characters on the right of the hex dump

bool memdump(const void* ptr, size_t bytes) {
	if (INFO == true) {
		printf("MEMORY DUMP\n");
		if (sizeof(void*) == 4)
			printf("Architecture:\t\tx86\n");
		else if (sizeof(void*) == 8)
			printf("Architecture:\t\tx64\n");
		else
			printf("Unknown architecture\n");
		printf("Virtual Start Address: \t0x%p\nBytes to read: \t\t%zu\n\n", ptr, bytes);
	}

	/*copy n bytes from ptr to dump*/
	unsigned char* dump = (unsigned char*)calloc(bytes, sizeof(char));
	if (dump == NULL)
		return false;
	memcpy(dump, ptr, bytes);

	for (size_t i = 0; i < bytes; i++) {

		if (ADDRESS == true && i % COLSIZE == 0)
			printf("0x%p\t", (char*)ptr + i);

		printf("%02X ", dump[i]);

		if (i % COLSIZE == COLSIZE - 1) {
			if (ASCII == true) {
				printf("\t");
				for (size_t j = i - COLSIZE + 1; j <= i; j++) {
					if (dump[j] == '\n' || dump[j] == '\r' || dump[j] == '\t')
						printf(" ");
					else
						printf("%c ", dump[j]);
				}
			}
			puts("");
		}

	}
	
	if (ASCII == true) {
		const unsigned int rest = bytes % COLSIZE;
		for (unsigned int i = 0; i < COLSIZE - rest; i++) {
			printf("   ");
		}
		printf("\t");
		for (size_t i = bytes - rest; i < bytes; i++) {
			if (dump[i] == '\n' || dump[i] == '\r' || dump[i] == '\t')
				printf(" ");
			else
				printf("%c ", dump[i]);
		}
	}
	puts("\n");

	free(dump);
	return true;
}

#endif
