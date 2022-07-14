#include <unistd.h>
#include <stdio.h>

ssize_t write(int fildes, const void *buf, size_t nbyte)
{
  printf("My Write!");
  return 0;
}
