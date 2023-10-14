//utilities.h
#ifndef UTILITIES_H
#define UTILITIES_H

#include "utilities.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define SLEEP_TIMEOUT 2
#define RECORD_SIZE 5
#define CLEAR_BUFF_SIZE 1024

void clear_buff(char* buff_to_clr){
    memset(buff_to_clr, 0, CLEAR_BUFF_SIZE);
}

void str_cpy(char *dest, char *src) {
    while (*src != '\n') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void my_itoa(int num, char *str, int base) {
    int i = 0;
    while (num > 0) {
        int digit = num % base;
        str[i++] = digit + '0';
        num = num / base;
    }
    str[i] = '\0';

    // Reverse the string.
    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}


ssize_t read_line(int fd, void *buffer, size_t n)
{
    ssize_t numRead; /* # of bytes fetched by last read() */
    size_t totRead;  /* Total bytes read so far */
    char *buf;
    char ch;
    
    if (n <= 0 || buffer == NULL) {
        return -1;
    }

    buf = buffer; /* No pointer arithmetic on "void *" */
    totRead = 0;

    for (;;)
    {
        numRead = read(fd, &ch, 1);
        if (numRead == -1) {
            return -1; /* Some other error */
        } else if (numRead == 0) {                     /* EOF */
            if (totRead == 0) /* No bytes read; return 0 */
                return 0;
            else /* Some bytes read; add '\0' */
                break;
        } else { /* 'numRead' must be 1 if we get here */
            if (totRead < n - 1) { /* Discard > (n - 1) bytes */
                totRead++;
                *buf++ = ch;
            }
            if (ch == '\n')
                break;
        }
    }
    *buf = '\0';
    return totRead;
}



#endif
