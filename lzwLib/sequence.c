#include <stdlib.h>
#include <sequence.h>

/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHOR:        Saeed AlSarhi
 */

Sequence *newSequence(unsigned char firstByte){
    Sequence *s = malloc(sizeof(Sequence));
    s->size = 1;
    s->data = malloc(sizeof(char));
    *(s->data) = firstByte;
    return s;
}

void deleteSequence(Sequence *sequence){
    if (sequence == NULL){
        return;
    }
    free(sequence->data);
    free(sequence);
}

Sequence *copySequenceAppend(Sequence *sequence, unsigned char addByte){
    Sequence *r = malloc(sizeof(Sequence));
    r->size = sequence->size + 1;
    r->data = malloc(sizeof(char) * r->size);
    for (int i = 0; i < sequence->size; i++){
        r->data[i] = sequence->data[i];
    }
    r->data[sequence->size] = addByte;
    return r;
}

void outputSequence(Sequence *sequence, int (*writeFunc)(unsigned char c, void *context), void *context){
    for (int i = 0; i < sequence->size; i++){
        writeFunc(sequence->data[i], context);
    }
}

bool identicalSequences(Sequence *a, Sequence *b){
    if (a->size != b->size){
        return false;
    }
    for (int i = 0; i < a->size; i++){
        if (a->data[i] != b->data[i]){
            return false;
        }
    }
    return true;
}
