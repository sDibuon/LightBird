#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PERCENT(x) ( (double)x / (double)100 )


#define LOFACTOR PERCENT(75)

typedef struct ListNode {
    char* key;
    char* value;
    struct ListNode* next;
} ListNode;

typedef struct {
    ListNode** buckets;
    int size;
    int capacity;
} HashTable;

typedef HashTable* Dict;
typedef ListNode* KeyValue;

unsigned int hash( const char* key, int module );

KeyValue Create_KeyValue( const char* key, const char* value );

void Delete_KeyValue( KeyValue* pair );

Dict Create_Dict( int capacity );

void Delete_Dict( Dict* dict );

int Insert_On_Dict( Dict* dict, KeyValue content );

int Update_Dict_Capacity( Dict* dict );

KeyValue Search_On_Dict( Dict* dict, const char* key );