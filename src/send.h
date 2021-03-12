#ifndef __tmf_send_h__
#define __tmf_send_h__

#include <ddcKeyboard.h>
#include <ddcPrint.h>

#include "./args.h"
#include "./utils.h"

void tmf_send(char control)
{
	do
	{
		if (control)
		{
			ddPrintf("[(enter)(send)][(q)(quit)]");
			char c = ddKey_getch();
			if (c == 'q') exit(0);
		}
		ddString buffer = read_file(args_get_value(make_constant_ddString("__TARGET_FILE")).cstr);
		struct dsocketClient sck = make_dsocketClient("127.0.0.1", 5273);
		if (dsocketClient_connect(&sck))
			ddError("unable to connect to server");
		dsocketClient_send(sck, "cready", 6);
		char reply[1024] = {0};
		dsocketClient_receive(sck, reply, 1024);
		if (cstring_compare(reply, "sready"))
		{
			long pos = 0;
			ddString strlen = make_ddString_from_int(buffer.length);
			dsocketClient_send(sck, strlen.cstr, strlen.length);
			dsocketClient_receive(sck, reply, 1024);
			while (pos < buffer.length)
			{
				dsocketClient_send(sck, buffer.cstr+pos, 1024);
				dsocketClient_receive(sck, reply, 1024);
				pos += 1024;
			}
			ddPrintf("finished sending\n");
		}
		else ddError("unable to confirm connection");
	} while (control);
}

#endif
