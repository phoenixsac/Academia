#include "utilities.h"
#include <string.h>

void clear_buff(char* buff_to_clr){
    memset(buff_to_clr, 0, sizeof(buff_to_clr));
}

void str_cpy(char *dest, char *src) {
    while (*src != '\n') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}
