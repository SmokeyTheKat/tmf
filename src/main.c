#include <stdio.h>

#include "tmf.h"
#include "args.h"
#include "sender.h"
#include "receiver.h"
#include <time.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	interrupt_args(argc, argv);
	if (args.mode == MODE_RECEIVE)
	{
		do
		{
			if (receiver_receive(args.port, args.filename) == 0)
				printf("receive successful\n");
			else
			{
				printf("receive failed\n");
				sleep(1);
			}
		} while (args.continuous);
	}
	else if (args.mode == MODE_SEND)
	{
		if (args.continuous)
		{
			while (1)
			{
				printf("[(send -> enter)(quit -> q)]");
				char c = getc(stdin);
				if (c == '\n')
				{
					if (sender_send(args.ip, args.port, args.filename) == 0)
						printf("send successful\n");
					else printf("send failed\n");
				}
				else if (c == 'q')
					return 0;
			}
		}
		else
		{
			if (sender_send(args.ip, args.port, args.filename) == 0)
				printf("send successful\n");
			else printf("send failed\n");
		}
	}
	return 0;
}