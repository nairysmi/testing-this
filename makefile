echo: echo_client.c echo_server.c
	gcc -o serv echo_server.c
	gcc -o client echo_client.c
combo: appliance.c readwritehelper.c portNUMS_defined.c state_calls.c
	gcc -o combo appliance.c readwritehelper.c portNUMS_defined.c state_calls.c -I.
client: echo_client.c readwritehelper.c
	gcc -o client echo_client.c readwritehelper.c
central: central_server.c readwritehelper.c portNUMS_defined.c
	gcc -o central central_server.c readwritehelper.c portNUMS_defined.c