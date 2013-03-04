dummy:
	@echo 'Run either "make pst2john-windows" OR "make pst2john-linux"'

pst2john-windows:
	gcc -Wall -Wno-char-subscripts -std=gnu99 pst2john.c libpst.c debug.c vbuf.c libstrfunc.c -liconv -o pst2john

pst2john-linux:
	gcc -Wall -std=gnu99 pst2john.c libpst.c debug.c vbuf.c libstrfunc.c -o pst2john
