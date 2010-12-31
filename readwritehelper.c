#include "readwritehelper.h"
#include <stdio.h>
#include <string.h>


char * readhelp(int SD, char *string, int max)
{
  int counter=0;
  int error;
  char c;
  //printf("original string: %s\n", p);
  while (counter<=max && (error=read(SD,&c,1) != -1) )
    {
      //  printf(" c= %c and c int %d \n", c,(int)c);
      if (c==0)
	{ // printf("entered NULL segment");
	  //string[counter]=c;printf("done because end of string: %s\n", string);
	  return string;
	}
      else if(c=='\n')
	{ // printf("entered ENTER segment");
	  string[counter-1]=0;  // printf("done cuz of enter... string: %s\n", string);
	  return string;
	}
      else
	{
	  // printf("entered NORMAL segment");
	  // printf("character= %c and int value= %d \n", c,c);
	  string[counter]=c;
	  // printf("p: %s \n", string);
	  counter++;
	}

    }
  if (error==-1)
    printf("error in reading");
  // printf("done by other means\n");
  return string;
 
}

writehelp(int SD, char * string, int len)
{
  int counter=0;
  while(string[counter] && counter<=len)
    {
      // printf("string[counter]= %c \n", string[counter]);
      if( write(SD,&(string[counter]),1)!=1)
	printf("error in writing\n");
      counter++;
    }
 
}
