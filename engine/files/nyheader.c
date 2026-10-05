/*
 * NYHeader implementation
 *
 * Just reads/writes the NYHeader
 *
 */


/* ----- INCLUDES ----- */
#include "files/nyheader.h"


/* ----- FUNCTIONS ----- */
int nyfile_readHeader(FILE* f, NYHeader* head)
{
	if (!fread(&head, 8, 1, f)) {
		printf("Failed to read header.\n");
		return 0;
	}
	return 1;
}


int nyfile_writeHeader(FILE* f, NYHeader* head)
{
	if (!f) {
		printf("File is null?\n");
		return 0;
	}
	fwrite(head, 8, 1, f);
	return 1;
}




