######################################
#
# Makefile: for building lzwLib.a
#
# source files are compiled and a library file created 
# which can be searched for static linking with 
# the instructor's testbed.
#
# You may need to change some of the following targets, 
# dependencies and productions if your source structure 
# deviates from my template structure.  Note the "clean"
# target at the end for removing all derived files. Both
# it and the "lzwLib.a" targets will be needed by the
# instructor's testbed build.
#

INCLUDE=include/
# do NOT modify these C flags! (you shouldn't want to!)
CFLAGS=-c -std=c99 -Wall -pedantic -I$(INCLUDE) -g

liblzw.a: lzwEncode.o lzwDecode.o sequence.o dict.o bitStream.o
	ar cru liblzw.a lzwEncode.o lzwDecode.o sequence.o dict.o bitStream.o
	ranlib liblzw.a

lzwEncode.o: lzwEncode.c $(INCLUDE)lzw.h $(INCLUDE)bitStream.h $(INCLUDE)dict.h $(INCLUDE)sequence.h
	gcc $(CFLAGS) lzwEncode.c

lzwDecode.o: lzwDecode.c $(INCLUDE)lzw.h $(INCLUDE)bitStream.h $(INCLUDE)dict.h $(INCLUDE)sequence.h
	gcc $(CFLAGS) lzwDecode.c

bitStream.o: bitStream.c $(INCLUDE)bitStream.h
	gcc $(CFLAGS) bitStream.c

dict.o: dict.c $(INCLUDE)dict.h $(INCLUDE)sequence.h
	gcc $(CFLAGS) dict.c

sequence.o: sequence.c $(INCLUDE)sequence.h
	gcc $(CFLAGS) sequence.c

clean:
	rm -f liblzw.a lzwEncode.o lzwDecode.o bitStream.o dict.o sequence.o