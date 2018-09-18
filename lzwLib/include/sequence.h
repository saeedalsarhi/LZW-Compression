#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <stdbool.h>

/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHORS:       Saeed AlSarhi and Dick Lang
 */

/***********************************************************************
 
 Sequence:
 ---------
 
     Module representing character strings of arbritrary length, where
     the characters can be any 8-bit integer value, including zero.
 
     The module supports creating and deleting sequences, writing them
     to some destination, copying and appending a character and comparing
     them for equality.
 
     Consider this interface to be a starting point or a suggestion for
     your code design. Modify it as needed, but obey good object-oriented
     design principles.
 
 ***********************************************************************/

typedef struct _sequence {
    
    unsigned char *data;
    unsigned int size;

} Sequence;

/* newSequence:
     Create and return a newSequence object with its first and only character equal
     to firstByte. It can be noted that there is no need to support a Sequence that
     has zero characters.  All Sequences used by LZW have at least one character. */
Sequence* newSequence(unsigned char firstByte);

/* deleteSequence:
     Free all heap memory associated with sequence. */
void deleteSequence(Sequence* sequence);

/* copySequenceAppend:
     Create and return a new Sequence object where the new object contains
     all the characters of sequence, but with addByte appended to its end. */
Sequence* copySequenceAppend(Sequence* sequence, unsigned char addByte);

/* outputSequence:
     Write the characters in sequence (in sequential order) using the given
     writeFunc() and its context data. */
void outputSequence(Sequence* sequence,
                    int (*writeFunc)(unsigned char c, void* context), void* context);

/* identicalSequences:
     Return true if a and b contain exactly the same characters in the
     same order, false otherwise. */
bool identicalSequences(Sequence* a, Sequence* b);

#endif
