appliance: appliance.c readwritehelper.c portNUMS_defined.c state_calls.c
	gcc -o appliance appliance.c readwritehelper.c portNUMS_defined.c state_calls.c -I.
client: echo_client.c readwritehelper.c
	gcc -o client echo_client.c readwritehelper.c
central: central_server.c readwritehelper.c portNUMS_defined.c
	gcc -o central central_server.c readwritehelper.c portNUMS_defined.c