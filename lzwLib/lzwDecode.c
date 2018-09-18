#include <sequence.h>
#include <bitStream.h>
#include <stdlib.h>
#include <lzw.h>

/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHOR:        Saeed AlSarhi
 */

bool lzwDecode(unsigned int bits, unsigned int maxBits,
               int (*readFunc)(void *context), void *readContext,
               int (*writeFunc)(unsigned char c, void *context), void *writeContext){

    int maxCode = (1 << maxBits) - 1;
    Sequence **T = calloc(maxCode, sizeof(Sequence));

    for (int i = 0; i < 256; i++){ //creating an array of sequences.
        T[i] = newSequence(i);
    }

    // Create BS
    BitStream *BS = openInputBitStream(readFunc, readContext);

    unsigned int nextCode = 256;
    unsigned int previousCode = 0;

    if (!readInBits(BS, bits, &previousCode)){
        closeAndDeleteBitStream(BS);
        return false;
    }
    outputSequence(T[previousCode], writeFunc, writeContext);
    int capacity = (1 << bits);

    if ((nextCode >= capacity) && (bits < maxBits)){
        bits++;
        capacity = (1 << bits);
    }
    unsigned int currentCode = 0;
    char C = -1;
    while (readInBits(BS, bits, &currentCode)){
        if (currentCode < nextCode){
            C = T[currentCode]->data[0];
        }else{
            C = T[previousCode]->data[0];
        }

        if (nextCode < maxCode){
            T[nextCode++] = copySequenceAppend(T[previousCode], C);
            if ((nextCode >= capacity) && (bits < maxBits)){
                bits++;
                capacity = (1 << bits);
            }
        }
        outputSequence(T[currentCode], writeFunc, writeContext);
        previousCode = currentCode;
    }
    closeAndDeleteBitStream(BS);
    for (int i = 0; i < maxCode; i++){
        deleteSequence(T[i]);
    }
    free(T);
    return true;
}
