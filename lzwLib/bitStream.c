#include <stdlib.h>
#include <bitStream.h>
#include <stdio.h>

/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHOR:        Saeed AlSarhi
 */

BitStream *openInputBitStream(int (*readFunc)(void *context), void *context){
    BitStream *r = malloc(sizeof(BitStream));
    r->input = true; //because it is reading then set input to true
    r->context = context;
    r->writeFunc = NULL; //set writeFunc to null because the function isnt writing anything
    r->readFunc = readFunc;
    r->buffer = 0;
    r->size = 0;
    return r;
}

BitStream *openOutputBitStream(int (*writeFunc)(unsigned char c, void *context), void *context){
    BitStream *r = malloc(sizeof(BitStream));
    r->input = false;
    r->context = context;
    r->writeFunc = writeFunc;
    r->readFunc = NULL;
    r->buffer = 0;
    r->size = 0;
    return r;
}

void closeAndDeleteBitStream(BitStream *bs){
    if ((!bs->input) && (bs->size > 0)){
        int byte = (bs->buffer << (CHAR_BITS - bs->size));
        bs->writeFunc(byte, bs->context);
    }
    free(bs);
}

void outputBits(BitStream *bs, unsigned int nBits, unsigned int code){

    bs->buffer = (bs->buffer << nBits) | code;
    bs->size += nBits;

    while (bs->size >= CHAR_BITS){
        bs->size -= CHAR_BITS;
        int byte = (bs->buffer >> bs->size);
        bs->writeFunc(byte, bs->context);
        bs->buffer = bs->buffer ^ (byte << bs->size);
    }
    ///////////////////////////////////// Phase 1 //////////////////////////////////////////////////////////////////////////
    // unsigned char MSB = (code >> 8) & 0xFF;  //get the most significant bit buy shiffting it to the right and & with 0xFF
    // unsigned char LSB = code & 0xFF; //get the least significant bit by & the code with 0xFF
    // bs->writeFunc(MSB, bs->context); //write MSB to context
    // bs->writeFunc(LSB, bs->context); //write LSB to context
}

bool readInBits(BitStream *bs, unsigned int nBits, unsigned int *code){

    while (bs->size < nBits){
        int byte = bs->readFunc(bs->context);
        if (byte == -1)
            return false;
        bs->buffer = (bs->buffer << CHAR_BITS) | byte;
        bs->size += CHAR_BITS;
    }
    bs->size -= nBits;
    *code = (bs->buffer >> bs->size);
    bs->buffer = bs->buffer ^ (*code << bs->size);
    return true;
////////////////////////////////// Phase 1 //////////////////////////////////////////////////
    // unsigned int LSB = bs->readFunc(bs->context);
    // unsigned int MSB = bs->readFunc(bs->context);
    // *code = (LSB<<8) | MSB;
}
