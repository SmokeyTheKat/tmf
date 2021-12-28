#include "sender.h"

#include "ddcSocket.h"

#include <stdio.h>
#include <string.h>

int sender_send(char* ip, int port, char* filename)
{
	char buffer[4096];
	struct dsocket_tcp_client client = make_dsocket_tcp_client(ip, port);

	if (dsocket_tcp_client_connect(&client) != 0)
		return 1;

	if (dsocket_tcp_client_receive(client, buffer, sizeof(buffer)) <= 0)
		return 1;

	if (strcmp(buffer, "send ready"))
		return 1;

	FILE* fp = fopen(filename, "r");

	if (fp == 0)
		return 1;

	int byte_count;
	while ((byte_count = fread(buffer, 1, sizeof(buffer), fp)) > 0)
		if (dsocket_tcp_client_send(client, buffer, byte_count) <= 0)
			break;

	fclose(fp);
	close(client.dscr);

	return 0;
}