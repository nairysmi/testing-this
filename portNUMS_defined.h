//DEFINES A VALUE TO APPLIANCE NAMES
#define light 8000;
#define oven 8020;
#define refrigerator 8030;
#define tv 8040;


//THE STRUCT HOLDING INFORMATION ON THE APPLIANCE
struct device{
  char *name;
  int id;
  int power;//0=off 1=on
  int variable;//temperature, wattage, or channel
};


//TAKES IN A NAME AND AN ID AND MAKES A PORT NUMBER OUT OF IT
//RETURNS PORT NUMBER
int portnumhelper(char *, int);
