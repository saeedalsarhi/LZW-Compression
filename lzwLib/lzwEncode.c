#include <sequence.h>
#include <bitStream.h>
#include <dict.h>
#include <lzw.h>
#include <string.h>
#include <stdio.h>

/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHOR:        Saeed AlSarhi
 */

bool lzwEncode(unsigned int bits, unsigned int maxBits, int (*readFunc)(void *context), void *readContext,
               int (*writeFunc)(unsigned char c, void *context), void *writeContext){
    int dictSize = (1 << maxBits);
    Dict *dict = newDict(dictSize);

    for (int i = 0; i < 256; i++){
        Sequence *s = newSequence(i);
        insertIntoDict(dict, s, i);
    }

    int nextcode = 256;
    // read first byte
    int firstByte = readFunc(readContext);
    if (firstByte == -1)
        return false;

    // Create BS
    BitStream *BS = openOutputBitStream(writeFunc, writeContext);
    Sequence *W = newSequence(firstByte);
    char C = 0;
    int capacity = (1 << bits);
    unsigned int code;
    while ((C = readFunc(readContext)) != -1){
        Sequence *X = copySequenceAppend(W, C);
        if (searchDict(dict, X, &code)){
            //Sequence W is assigned Sequence X
            deleteSequence(W);
            W = X;
        }else{
            searchDict(dict, W, &code);
            outputBits(BS, bits, code);

            if (nextcode < dict->size){
                if ((nextcode >= capacity) && (bits < maxBits)){
                    bits++;
                    capacity = (1 << bits);
                }
                insertIntoDict(dict, X, nextcode);
                nextcode++;
            }
            deleteSequence(W);
            W = newSequence(C);
        }
    }
    searchDict(dict, W, &code);
    outputBits(BS, bits, code);
    deleteDictDeep(dict);
    deleteSequence(W);
    closeAndDeleteBitStream(BS);
    return true;
}
