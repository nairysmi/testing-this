TCP UNIVERSAL REMOTE

Adam Yabroudi

DESCRIPTION:
A client connects to a central server over the internet and controls appliances through the central server. 


COMPILNG AND RUNNING:

1. In one terminal window type make central and then ./central.
2. In another terminal type make appliance. Then make as many appliances as you want by typing ./appliance "type" ID#.
	Types: light, refrigerator, tv, oven
	Possible IDS: 
		light-> 1-20
		refrigerator->1-10
		oven->1-10
		tv->1-20
3. Either on a seperate computer or in another terminal type make client. Then type ./client "IPAddress of the computer with the central server" 8080
4. In the client window type first a device name, space, device id, space and then a command.
	Commands:
		GET_POWER- gets the state of the power
		GET_WATT(light), GET_TEMP(refrigerator and oven), GET_CHANNEL(tv)- gets the state of the appropriate variable
		SET_POWER_ON- sets power to 1
		SET_POWER_OFF-sets power to 0
		SET_WATT(light), SET_TEMP(refrigerator and oven), SET_CHANNEL(tv)- sets variable only when appliance is on. Requests an input for new number

FEATURES:

3 part commands typed into the client are sent to the central server, rerouted appropriately to the appliance, states are changed or received, and the data is channeled back up to the client. 

Appliances run regardless of whether they are connected to the central server or not. Data is stored in the appliance so if a client disconnects and another comes on, the appliance will retain its last state. 

BUGS:

When compiling, lots of warnings. Not sure of how to remove them. 

TODO:

Allow for more capabilities and features. Maybe change the code to allow servers to be on different computers or maybe make appliances things other than terminals.
Also maybe figure out a way to store the appliance's states even when the appliance window is turned off. Another idea I had was to possibly create a possibility for having a timer to turn off the appliance at a certain time. 


FILES:

echo_client.c	   	The code to run client commands and connect to the central server.
central_server.c	The code to run the central server. Must be compiled before the client is compiled.
appliance.c		The code to run the appliances.
portNUMS_defined.c	Defines the values of appliance names and creates the struct for devices to hold states
portNUMS_defined.h
state_calls.c		Takes a string command and redirects it to a function. Writes from the appliance to the central server.
state_calls.h

makefile		Allows for three different compilings (make appliance, make client, make central).	


CREDITS:

Guidance from my Morgan Stanley mentor.
A pdf on sockets: rites.uic.edu/~solworth/sockets.pdf


