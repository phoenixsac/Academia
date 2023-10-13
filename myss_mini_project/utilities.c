#include "utilities.h"
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define SLEEP_TIMEOUT 2
#define RECORD_SIZE 5


int get_locking(int fd, int recordno, int l_type){
    struct flock lock;
    if(l_type==0)
        lock.l_type=F_RDLCK;
    else if(l_type==2)
        lock.l_type=F_UNLCK;
    else if(l_type==1)
        lock.l_type=F_WRLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start = RECORD_SIZE*(recordno-1);;
    lock.l_len = RECORD_SIZE;
    lock.l_pid=getpid();

    if(fcntl(fd,F_SETLKW, &lock)==-1){
        perror("Error locking or releasing lock...");
        return -1;
    }
    return 0;
}

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

