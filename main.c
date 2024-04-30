#include "lib/Http_Server.c"
#include "lib/Dict.c"


int main( int argc, char** argv )
{
    Http_Server server = Create_Http_Server( 55555 );
    Dict diz = Create_Dict( 10 );

    Delete_Dict( &diz );
    Delete_Http_Server( &server );
    return 0;
}