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

int main() {

  int FDtoServer;
  int FDfromSubServer;
  char message[255];
  char clientname[255];//aka pid #

  umask(0000);
  sprintf(clientname, "%d", getpid()); // sets the name to be the pid
  assert( mkfifo(clientname, 0666) == 0 );// make subserver pipe but idk what assert does

  FDtoServer=open("commonServerPipe", O_WRONLY); // connect to common to server pipe with write only abilities
  write(FDtoServer, clientname, strlen(clientname)+1);//send up a message so that it can connect subserver pipe
  FDfromSubServer=open(clientname, O_RDONLY); //open subserver pipe
  read(FDfromSubServer, message, 255); //read from subserver
  
  printf("message: %s ", message);
  



  return 1;
}
