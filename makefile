echo: echo_client.c echo_server.c
	gcc -o serv echo_server.c
	gcc -o client echo_client.c
combo: server_takes_name.c readwritehelper.c portNUMS_defined.c state_calls.c
	gcc server_takes_name.c readwritehelper.c portNUMS_defined.c state_calls.c -I.