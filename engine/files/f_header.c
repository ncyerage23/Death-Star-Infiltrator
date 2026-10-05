/*
 * f_header implementation
 *
 * Just reads/writes the NYHeader
 *
 */


/* ----- INCLUDES ----- */
#include "files/f_header.h"


/* ----- FUNCTIONS ----- */
int f_readHeader(FILE* fp, f_header* head)
{
	if (!fread(&head, 8, 1, fp)) {
		printf("Failed to read header.\n");
		return 0;
	}
	return 1;
}


int f_writeHeader(FILE* fp, f_header* head)
{
	if (!fp) {
		printf("File is null?\n");
		return 0;
	}
	fwrite(head, 8, 1, fp);
	return 1;
}




