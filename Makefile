#########################################################
#
# Makefile: 	By default, builds executable "lzw"
#		from your main and your lzwLib library.
#
#		Also includes a clean target and a
#		target named "tar" which will clean
#		your lzwLib library directory and
#		make a .tar.gz file of it for submission.
#
#	You should feel free to modify this Makefile
#	to suit your needs, however, be sure to maintain
#	your ability to make the .tar.gz file correctly.
#
#	Original Author:	Dick Lang
#

LZWLIB=lzwLib
TARFILE=assignment1

CFLAGS=-c -g -std=c99 -Wall -pedantic -I$(LZWLIB)/include

lzw: main.o $(LZWLIB)/liblzw.a
	gcc -g -L$(LZWLIB) main.o -o lzw -llzw

main.o: main.c $(LZWLIB)/include/lzw.h
	gcc $(CFLAGS) main.c

$(LZWLIB)/liblzw.a:
	cd $(LZWLIB) && make liblzw.a

clean:
	rm -f lzw main.o $(TARFILE).tar $(TARFILE).tar.gz
	cd $(LZWLIB) && make clean

tar: clean
	tar cvf $(TARFILE).tar $(LZWLIB)
	gzip $(TARFILE).tar
