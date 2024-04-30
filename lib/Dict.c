#include "Dict.h"

unsigned int hash( const char* key, int module )
{
    unsigned int digest = 0;
    for ( int i = 0 ; key[i] ; i++ ) {
        digest = (( digest * 31 ) + key[i]) % module;
    }
    return digest;
}

KeyValue Create_KeyValue( const char* key, const char* value )
{
    KeyValue new_node = malloc(sizeof(ListNode));
    if ( new_node == NULL ) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = NULL;

    return new_node;
}

void Delete_KeyValue( KeyValue* pair )
{
    free( (*pair)->key );
    free( (*pair)->value );
    free( *pair );
}

Dict Create_Dict( int capacity )
{
    Dict allocate = malloc( sizeof(HashTable) );
    if ( allocate == NULL ) {
        fprintf( stderr, "Memory allocation failed.\n" );
        return NULL;
    }

    allocate->buckets = calloc( capacity, sizeof(ListNode*) );
    if ( allocate->buckets == NULL ) {
        fprintf( stderr, "Memory allocation failed.\n" );
        free( allocate );
        return NULL;
    }

    allocate->capacity = capacity;
    allocate->size = 0;

    return allocate;
}

void Delete_Dict( Dict* dict )
{
    if ( *dict == NULL )     return;

    for ( int i = 0 ; i < (*dict)->capacity ; i++ ) {
        KeyValue node = (*dict)->buckets[i];
        while ( node != NULL ) {
            void* next = node->next;
            Delete_KeyValue( &node );
            node = next;
        }
    }

    free( *dict );
    *dict = NULL;
}

int Insert_On_Dict( Dict* dict, KeyValue content )
{
    if ( *dict == NULL )     return -1;

    unsigned int index = hash( content->key, (*dict)->capacity );

    content->next = (*dict)->buckets[index];
    (*dict)->buckets[index] = content;
    (*dict)->size++;

    if ( (double)(*dict)->size / (double)(*dict)->capacity > LOFACTOR ) {
        if ( Update_Dict_Capacity( dict ) != 0 ) {
            fprintf( stderr, "Error during updating of dict.\n" );
            return -1;
        }
    }

    return 0;
}

int Update_Dict_Capacity( Dict* dict )
{
    if ( *dict == NULL )    return -1;

    Dict new = Create_Dict( (*dict)->capacity * 2 );

    if ( new == NULL ) {
        fprintf( stderr, "Error on creation of new dict to update the oldone.\n" );
        return -1;
    }

    for ( int i = 0 ; i < (*dict)->capacity ; i++ ) {
        KeyValue node =  (*dict)->buckets[i];
        while ( node != NULL ) {
            void* cache = node->next;
            Insert_On_Dict( &new, node );
            node = cache;
        }
        (*dict)->buckets[i] = NULL;
    }

    Delete_Dict( dict );
    *dict = new;

    return 0;
}

KeyValue Search_On_Dict( Dict* dict, const char* key )
{
    unsigned int index = hash( key, (*dict)->capacity );

    KeyValue node = (*dict)->buckets[index];

    while ( node != NULL ) {
        if ( strcmp( node->key, key ) == 0 )    return node;
        node = node->next;
    }

    return NULL;
}

