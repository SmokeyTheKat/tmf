#ifndef __tmf_receive_h__
#define __tmf_receive_h__

#include "./args.h"
#include "./utils.h"

void tmf_receive(char repeat)
{
	int port = 5273;
	if (args_if_def(make_constant_ddString("-p")))
		port = ddString_to_int(args_get_value(make_constant_ddString("-p")));
	struct dsocketServer sck = make_dsocketServer(port);
	if (dsocketServer_bind(&sck))
		ddError("unable to bind server");
	dsocketServer_start_listen(&sck);
	do
	{
		int client = dsocketServer_listen(&sck);
		char reply[1024] = {0};
		dsocketServer_receive(sck, client, reply, 1024);
		if (cstring_compare(reply, "cready"))
		{
			dsocketServer_send(sck, client, "sready", 6);
			buffer_clear(reply, 1024);
			dsocketServer_receive(sck, client, reply, 1024);
			long data_length = ddString_to_int(make_constant_ddString(reply));
			ddString data = make_ddString_capacity("", data_length);
			dsocketServer_send(sck, client, "sgood", 5);
			long pos = 0;
			while (pos < data_length)
			{
				dsocketServer_receive(sck, client, reply, 1024);
				ddString_push_back(&data, make_constant_ddString_length(reply, 1024));
				dsocketServer_send(sck, client, "sgood", 5);
				pos += 1024;
			}
			data.length = data_length;
			data.cstr[data.length] = 0;
			ddPrintf("finished receiving\n");
			write_file(args_get_value(make_constant_ddString("__TARGET_FILE")).cstr, data);
		}
		else ddError("unable to confirm connection");
	} while (repeat);
}

#endif
