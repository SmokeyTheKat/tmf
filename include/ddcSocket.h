#ifndef __ddcSockets__
#define __ddcSockets__

#define __DSOCKET_BUFFER_SIZE 1024

#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

struct dsocket_tcp_client;
struct dsocket_tcp_server;

struct dsocket_tcp_server make_dsocket_tcp_server(int port);
int dsocket_tcp_server_bind(struct dsocket_tcp_server* sck);
int dsocket_tcp_server_start_listen(struct dsocket_tcp_server* sck);
int dsocket_tcp_server_listen(struct dsocket_tcp_server* sck);
int dsocket_tcp_server_send(struct dsocket_tcp_server sck, int client, const char* data, long length);
int dsocket_tcp_server_receive(struct dsocket_tcp_server sck, int client, char* buffer, long length);

struct dsocket_tcp_client make_dsocket_tcp_client(char* addr, int port);
void raze_dsocket_tcp_client(struct dsocket_tcp_client* sck);
int dsocket_tcp_client_connect(struct dsocket_tcp_client* sck);
int dsocket_tcp_client_send(struct dsocket_tcp_client sck, const char* data, long length);
int dsocket_tcp_client_receive(struct dsocket_tcp_client sck, char* buffer, long length);

struct dsocket_tcp_client
{
	int dscr;
	int port;
	struct sockaddr_in server;
	char* addr;
};

struct dsocket_tcp_server
{
	int dscr;
	int port;
	int opt;
	struct sockaddr_in server;
	int server_len;
};

#endif