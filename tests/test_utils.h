#ifndef H_TESTS_TESTUTILS
#define H_TESTS_TESTUTILS

// Includes systèmes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <sys/wait.h>
#include <assert.h>

// Includes locaux
#include "../src/Utilitaires/utils.h"
#include "../src/Protocole/protocole.h"
#include "../src/Protocole/Requetes/requetes.h"
#include "../src/Protocole/Reponses/reponses.h"
#include "../src/Reseau/reseau.h"
#include "../src/main.h"

// Macros

#define EXIT_IF_FALSE(statement) assert( (statement) != FALSE );
#define EXIT_IF_TRUE(statement) assert( (statement) != TRUE );

#define EXIT_IF_NULL(statement) assert( (statement) != NULL );
#define EXIT_IF_NOT_NULL(statement) assert( (statement) == NULL );

#define EXIT_IF_EQUAL(statement,expected) assert( (statement) != (expected) );
#define EXIT_IF_NOT_EQUAL(statement,expected) assert( (statement) == (expected) );

#define EXIT_IF_STRING_EQUAL(statement,expected) assert( strcmp( (statement), (expected) ) != 0 );
#define EXIT_IF_STRING_NOT_EQUAL(statement,expected) assert( strcmp( (statement), (expected) ) == 0 );


#endif
