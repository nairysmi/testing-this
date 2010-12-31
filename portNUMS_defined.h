#define light 8000;
#define oven 8020;
#define refrigerator 8030;
#define tv 8040;



struct device{
  char *name;
  int id;
  int power;//0=off 1=on
  int variable;//temperature, wattage, or channel
};

