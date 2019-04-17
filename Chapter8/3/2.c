#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <unistd.h>

#define FIFO_FILE_PATH "output.txt"
#define BUFF_SIZE 256

int main()
{
  int i;
  int readFd;
  char buf[BUFF_SIZE];
  int size;

  //Read file
  if ( ( readFd=open(FIFO_FILE_PATH,O_RDONLY) ) == -1 ){
    perror("readfile open");
    exit(1);
  }

  //Output to stdout
  while ( (size=read(readFd, buf, BUFF_SIZE)) != 0 ){
    write(1, buf, size);
  }

  close(readFd);
  unlink(FIFO_FILE_PATH);


  return 0;
}