//utilities.h
#ifndef UTILITIES_H
#define UTILITIES_H

void clear_buff(char *buff_to_clr);
void str_cpy(char *dest, char *src);
int get_locking(int fd, int recordno, int l_type);

#endif
