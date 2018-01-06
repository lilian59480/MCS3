#include "test_utils.h"

void test_strcrtonl () {
    
    // La valeur 
    char value[BUFF_MAX] = "Lorem\n ips\rum\r\n\n\r dolor\n\r sit\r amet\n\r.\n";
    
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "Lorem\n ips\num\n\n\n\n dolor\n\n sit\n amet\n\n.\n";
    
    strcrtonl (value);

    EXIT_IF_STRING_NOT_EQUAL(value,expected);
}

void test_strnltocr () {
    
    // La valeur 
    char value[BUFF_MAX] = "Lorem\n ips\rum\r\n\n\r dolor\n\r sit\r amet\n\r.\n";
    
    // La valeur que l'on doit obtenir
    char expected[BUFF_MAX] = "Lorem\r ips\rum\r\r\r\r dolor\r\r sit\r amet\r\r.\r";
    
    strnltocr (value);

    EXIT_IF_STRING_NOT_EQUAL(value,expected);
}

int main() {
    test_strcrtonl();
    
    test_strnltocr();
    
    return 0;
}

