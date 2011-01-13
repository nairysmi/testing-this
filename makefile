echo: echo_client.c echo_server.c
	gcc -o serv echo_server.c
	gcc -o client echo_client.c
combo: serv_with_pipe_up.c readwritehelper.c portNUMS_defined.c state_calls.c
	gcc serv_with_pipe_up.c readwritehelper.c portNUMS_defined.c state_calls.c -I.