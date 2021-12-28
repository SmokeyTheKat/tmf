#include "receiver.h"

#include "ddcSocket.h"

#include <stdio.h>
#include <string.h>

int receiver_receive(int port, char* filename)
{
	struct dsocket_tcp_server server = make_dsocket_tcp_server(port);

	if (dsocket_tcp_server_bind(&server) != 0)
	{
		close(server.dscr);
		return 1;
	}
	if (dsocket_tcp_server_start_listen(&server) != 0)
	{
		close(server.dscr);
		return 1;
	}

	int client = dsocket_tcp_server_listen(&server);

	FILE* fp = fopen(filename, "w");
	if (fp == 0)
	{
		fclose(fp);
		close(server.dscr);
		return 1;
	}

	if (dsocket_tcp_server_send(server, client, "send ready", 10) <= 0)
	{
		close(server.dscr);
		fclose(fp);
		return 1;
	}

	char buffer[4096];

	int byte_count;
	while ((byte_count = dsocket_tcp_server_receive(server, client, buffer, sizeof(buffer))) > 0)
		fwrite(buffer, 1, byte_count, fp);

	fclose(fp);
	close(server.dscr);

	return 0;
}