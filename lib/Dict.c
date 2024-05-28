#include "Dict.h"

unsigned long long int djb2_hash( const char* string )
{
    unsigned long long int digest = 5381;

    for ( int i = 0 ; string[i] ; i++ ) {
        digest = ((digest << 5) + digest) + string[i];
    }

    return digest;
}


int init_Hash_Table( HashTable* table, unsigned int capacity, double loadfactor )
{
    table->buckets = calloc( capacity, sizeof(ListNode*) );
    if ( table->buckets == NULL ) {
        fprintf( stderr, "Memory allocation failed.\n" );
        return -1;
    }
    table->loadfactor = loadfactor;
    table->capacity = capacity;
    table->lenght = 0;

    return 0;
}

int del_Hash_Table( HashTable* table )
{
    for ( int i = 0 ; i < table->capacity ; i++ ) {
        ListNode* node = table->buckets[i];
        while ( node != NULL ) {
            void* next = node->next;
            free( node->key );
            free( node->value );
            free( node );
            node = next;
        }
    }
    free( table->buckets );
    return 0;
}


int insert_Hash_Table( HashTable* table, const char* key, const char* value )
{
    ListNode* new_node = malloc(sizeof(ListNode));
    if ( new_node == NULL ) {
        fprintf(stderr, "Memory allocation failed.\n");
        return -1;
    }

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = NULL;

    if ( new_node->key == NULL || new_node->value == NULL ) {
        fprintf( stderr, "Error allocate memory for keyvalue" );
        return -2;
    }

    unsigned int index = djb2_hash( key ) % table->capacity;

    new_node->next = table->buckets[ index ];
    table->buckets[ index ] = new_node;
    table->lenght++;

    double load_factor = (double)table->lenght / (double)table->capacity;

    if ( load_factor > PERCENT_TO_DOUBLE( table->loadfactor ) ) {
        if ( update_Capacity_Hash_Table( table ) != 0 ) {
            fprintf( stderr, "Error during updating of dict.\n" );
            return -1;
        }
    }

    return 0;
}

const char* search_Hash_Table( HashTable* table, const char* key )
{
    unsigned int index = djb2_hash( key ) % table->capacity;

    ListNode* node = table->buckets[index];

    while ( node != NULL ) {
        if ( strcmp( node->key, key ) == 0 )    return node->value;
        node = node->next;
    }

    return NULL;
}

int update_Capacity_Hash_Table( HashTable* table )
{
    HashTable old_hashtable = *table;

    if ( init_Hash_Table( table, old_hashtable.capacity * 2 ,old_hashtable.loadfactor ) == -1 ) {
        fprintf( stderr, "Error on creation of new dict to update the oldone.\n" );
        return -1;
    }

    for ( int i = 0 ; i < old_hashtable.capacity ; i++ ) {
        ListNode* node = old_hashtable.buckets[i];
        while ( node != NULL ) {
            void* cache = node->next;
            if ( insert_Hash_Table( table, node->key, node->value ) == -1 ) {
                fprintf( stderr, "Error insert data to table\n" );
                return -1;
            }
            node = cache;
        }
    }

    if ( del_Hash_Table( &old_hashtable ) == -1 ) {
        fprintf( stderr, "Error delete old table\n" );
        return -1;
    }

    return 0;
}