/* pst2john
 *
 * Modified readpst.c (Part of the LibPST project)
 * Written by David Smith (dave.s@earthcorp.com) */

#include "define.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *output_dir = ".";
int output_type_mode = 0xff;	// Default to all.
pst_file pstfile;
char *default_charset = NULL;

char *fname = NULL;

void process_file(char *filename)
{
	pst_item *item = NULL;
	pst_desc_tree *d_ptr;
	fname = filename;

	time_t now = time(NULL);
	srand((unsigned) now);
	output_type_mode = 0;
	
	RET_DERROR(pst_open(&pstfile, fname, default_charset), 1,
	    ("Error opening File\n"));
	RET_DERROR(pst_load_index(&pstfile), 2, ("Index Error\n"));

	pst_load_extended_attributes(&pstfile);

	d_ptr = pstfile.d_head;	// first record is main record
	item = pst_parse_item(&pstfile, d_ptr, NULL);
	if (!item || !item->message_store) {
		DEBUG_RET();
		DIE(("Could not get root record\n"));
	}
	pst_close(&pstfile);
}

int main(int argc, char *const *argv)
{
	int i;
	if(argc < 2) {
		fprintf(stderr, "Usage: %s <.pst file(s)>\n", argv[0]);
		exit(1);
	}
	for(i = 1; i < argc; i++) {
		process_file(argv[i]);
	}

	return 0;
}

void version()
{
	DEBUG_ENT("version");
	printf("ReadPST / LibPST v%s\n", VERSION);
#if BYTE_ORDER == BIG_ENDIAN
	printf("Big Endian implementation being used.\n");
#elif BYTE_ORDER == LITTLE_ENDIAN
	printf("Little Endian implementation being used.\n");
#else
#  error "Byte order not supported by this library"
#endif
	DEBUG_RET();
}

