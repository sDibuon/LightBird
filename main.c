#include "Http_Server.c"
#include "lib/Dict.c"


int main( int argc, char** argv )
{
    HashTable table;
    init_Hash_Table( &table, 5, 60.0 );

    insert_Hash_Table( &table, "ciao", "1234" );
    insert_Hash_Table( &table, "come", "4567" );
    insert_Hash_Table( &table, "stai", "7890" );
    insert_Hash_Table( &table, "megy", "####" );

    char buffer[100];

    scanf("%s", buffer);

    const char * value = search_Hash_Table( &table, buffer );

    if ( value == NULL ) {
        puts("Nessun valore trovato");
    } else {
        printf(" %s -> %s\n", buffer, value);
    }

    del_Hash_Table( &table );
    return 0;
}