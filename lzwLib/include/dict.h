#ifndef DICT_H
#define DICT_H
#include <stdbool.h>
#include "sequence.h"

/*
 COURSE:        CS 360 Spring 2018
 ASSIGNMENT:    1
 AUTHORS:       Saeed ALSarhi and Dick Lang
 */

/***********************************************************************
 
 Dict:
 -----
 
     Module representing a dictionary (hash table) for storing and
     retrieving integer symbol codes using a Sequence as a key.
 
     Dictionaries may be created and deleted.  Sequences can be inserted
     into the dictionary, along with their assigned code.  Sequences can
     be searched for and their code obtained. There is no limit (other
     than available heap memory) to the number of Sequence/code pairs
     that may be stored in a Dictionary.
 
     Consider this interface to be a starting point or a suggestion for
     your code design. Modify it as needed, but obey good object-oriented
     design principles.
 
 ***********************************************************************/
typedef struct _entry {

    Sequence *data;
    unsigned int code;
    struct _entry *next;

} Entry;

typedef struct _dict {
    
    unsigned int size;
    Entry **hashTable;

} Dict;

/*  newDict:
     Create a new Dict with hashSize "buckets" and return a pointer to it */
Dict* newDict(unsigned int hashSize);

/*  deleteDictDeep:
     Free dict heap memory along with all of its contents */
void deleteDictDeep(Dict* dict);

/*  searchDict:
     Search dict for key, if found, return true, otherwise false.
     If code is non-null and key is found, set *code to the key's assigned code */
bool searchDict(Dict* dict, Sequence* key, unsigned int* code);

/*  insertIntoDict:
     Insert key into dict and assign code as its associated value.
     (It is assumed that key is NOT already present in dict) */
void insertIntoDict(Dict* dict, Sequence* key, unsigned int  code);

#endif
