#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>

int main(){
  
  int FDfromClient;
  int FDtoClient;
  char messageFromClient[256];//aka client pid
  char messageToClient[256];
  
  umask(0000);
  assert( mkfifo("commonServerPipe", 0666) == 0);// make common pipe

  FDfromClient=open("commonServerPipe", O_RDONLY);//connect to pipe
  read(FDfromClient,messageFromClient, 50);//read pid
  
  printf("messageFromClient: %s \n", messageFromClient);

  FDtoClient=open(messageFromClient /*pid name pipe*/, O_WRONLY);
  sprintf(messageToClient, "hello %s", messageFromClient);
  write(FDtoClient, messageToClient, strlen(messageToClient)+1);



  return 1;
}
