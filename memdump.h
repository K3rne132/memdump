#pragma once
#ifndef MEMDUMP_H
#define MEMDUMP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFO    1  // displays startup information
#define ADDRESS 1  // displays the starting address of the hex dump on the left
#define COLSIZE 16 // number of columns
#define ASCII   1  // displays ascii characters on the right of the hex dump

int memdump(const void* ptr, size_t bytes) {
	if (INFO) {
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
		return 0;
	memcpy(dump, ptr, bytes);

	for (size_t i = 0; i < bytes; i++) {
		if (ADDRESS && i % COLSIZE == 0)
			printf("0x%p\t", (char*)ptr + i);

		printf("%02X ", dump[i]);

		if (i % COLSIZE == COLSIZE - 1) {
			if (ASCII) {
				printf("\t");
				for (size_t j = i - COLSIZE + 1; j <= i; j++) {
					if (dump[j] >= 0x20 && dump[j] < 0x7F)
						printf("%c", dump[j]);
					else
						printf(".");
				}
			}
			puts("");
		}
	}
	
	if (ASCII) {
		const unsigned int rest = bytes % COLSIZE;
		for (unsigned int i = 0; i < COLSIZE - rest; i++) {
			printf("   ");
		}
		printf("\t");
		for (size_t i = bytes - rest; i < bytes; i++) {
			if (dump[i] >= 0x20 && dump[i] < 0x7F)
				printf("%c", dump[i]);
			else
				printf(".");
		}
	}
	puts("\n");

	free(dump);
	return 1;
}

int dump_to_file(const char* filename, const void* ptr, size_t bytes) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL)
		return 0;
	if (fwrite(ptr, sizeof(char), bytes, file) != bytes)
		return 0;
	fclose(file);
	return 1;
}

#endif
