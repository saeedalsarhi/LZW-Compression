#include <stdlib.h>
#include <dict.h>
#include <stdio.h>

/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHOR:        Saeed AlSarhi
 */

Dict *newDict(unsigned int hashSize){
    Dict *r = malloc(sizeof(Dict));
    r->size = hashSize;
    r->hashTable = calloc(hashSize, sizeof(Entry *));
    return r;
}

void deleteEntry(Entry *entry){ //recusrsive function to delete all what entry is pointing to.
    if (entry == NULL){
        return;
    }
    deleteEntry(entry->next);
    deleteSequence(entry->data); //free all the sequences
    free(entry);                 // then free the entire entry
}

void deleteDictDeep(Dict *dict){
    for (int i = 0; i < dict->size; i++){
        if (dict->hashTable[i] != NULL){
            deleteEntry(dict->hashTable[i]);
        }
    }
    free(dict->hashTable);
    free(dict);
}

unsigned int hash(Sequence *sequence){ //this is a burnstein hash as discribed in class
    unsigned int h = 5138;
    for (int i = 0; i < sequence->size; i++){
        h = 33 * h ^ sequence->data[i];
    }
    return h;
}

bool searchDict(Dict *dict, Sequence *key, unsigned int *code){
    unsigned int i = hash(key) % dict->size; //used mod to make sure that i dosn't become huge
    Entry *entry = dict->hashTable[i];
    while (entry != NULL){
        if (identicalSequences(key, entry->data)){
            *code = entry->code;
            return true;
        }
        entry = entry->next;
    }
    return false;
}

void insertIntoDict(Dict *dict, Sequence *key, unsigned int code){
    unsigned int i = hash(key) % dict->size; //used mod to make sure that i dosn't become huge
    Entry *entry = malloc(sizeof(Entry));
    entry->code = code;
    entry->next = dict->hashTable[i];
    entry->data = key;
    dict->hashTable[i] = entry;
}
