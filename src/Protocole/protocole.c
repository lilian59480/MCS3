#include "protocole.h"

void strcrtonl (char* str)
{
    unsigned int i;

    for (i = 0; i < strlen (str); i += 1)
    {
        if (str[i] == '\r')
        {
            str[i] = '\n';
        }
    }
}

void strnltocr (char* str)
{
    unsigned int i;

    for (i = 0; i < strlen (str); i += 1)
    {
        if (str[i] == '\n')
        {
            str[i] = '\r';
        }
    }
}

