#include "readwritehelper.h"
#include "portNUMS_defined.h"
#include <stdio.h>
#include <string.h>
//void get_power(struct device, int);
//void get_variable(struct device, int);
//void set_power(struct device, int);
//void set_variable(struct device, int);
void get_power(struct device specs, int SD)
{ char * power;
  sprintf(power, "%d", specs.power); 
  writehelp(SD,power, strlen(power)+1);}

void get_variable(struct device specs, int SD)
{
  char * message="power is off. turn power on to get data\n";
  if(specs.power == 1)
    {
      printf("i'm inside if");
      char * var;
      sprintf(var, "%d", specs.variable);
      writehelp(SD, var, strlen(var)+1);
    }
  else
    writehelp(SD,message ,strlen(message)+1); 
}

void set_power(struct device specs, int p,int SD)
{ specs.power=p;
  char * s;
  sprintf(s,"power is now: %d\n", specs.power);
  write(SD,s,strlen(s)+1);
}

void set_variable(struct device specs, int SD)
{
  char *input;
  char *message="enter new number:";
  int intinput;
  writehelp(SD, message, strlen(message)+1);
  readhelp(SD, input, 10);
  intinput=atoi(input);
  printf("INT changed: %d \n", intinput);
  specs.variable=intinput;
}
void takecommands(char * command, struct device specs, int SD)
{
  if(strcmp(command, "GET_POWER")==0)
    {
      get_power(specs,SD);
    }
  else if(strcmp(command, "GET_TEMP")==0 | strcmp(command, "GET_WATT")==0 | strcmp(command, "GET_CHANNEL")==0)
    {
      get_variable(specs,SD);
    }
  else  if(strcmp(command, "SET_POWER_ON")==0)
    {
      set_power(specs,1,SD);
    }
  else  if(strcmp(command, "SET_POWER_OFF")==0)
    {
      set_power(specs,0,SD);
    }
  else if(strcmp(command, "SET_TEMP")==0 | strcmp(command, "SET_WATT")==0 | strcmp(command, "SET_CHANNEL")==0)
    {
      set_variable(specs,SD);
    }
  else
    {char * message="invalid command \n";
      write(SD,message , strlen(message)+1);
    }
}
