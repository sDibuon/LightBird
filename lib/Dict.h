#ifndef __DICT_H__
#define __DICT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define PERCENT_TO_DOUBLE(x) ((double)((double)x/(double)100))


typedef struct ListNode {
    char* key;
    char* value;
    struct ListNode* next;
} ListNode;


typedef struct {
    ListNode** buckets;
    unsigned int lenght;
    unsigned int capacity;
    double loadfactor;
} HashTable;


unsigned long long int djb2_hash( const char* string );


int init_Hash_Table( HashTable* table, unsigned int capacity, double loadfactor );


int del_Hash_Table( HashTable* table );


int update_Capacity_Hash_Table( HashTable* table );


const char* search_Hash_Table( HashTable* table, const char* key );


int insert_Hash_Table( HashTable* table, const char* key, const char* value );



#endif // __DICT_H__