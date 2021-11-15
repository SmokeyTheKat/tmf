#include "args.h"

#include "tmf.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct args args = {
	.continuous=false,
	.mode=0,
	.port=1234,
	.ip="0.0.0.0",
	.filename=0,
};

void print_help(void)
{
	printf("tmf\n");
	printf("usage: tmf [-mode] [-options] targetfile\n");
	printf("modes:\n");
	printf("    -r              -    receive once\n");
	printf("    -s              -    send once\n");
	printf("options:\n");
	printf("    -i x.x.x.x      -    target ip\n");
	printf("    -p x            -    target port\n");
	printf("    -c              -    repeat operation continously\n");
	printf("docs: https://ddmo.xyz/projects/tmf/\n");
	exit(0);
}

void interrupt_args(int argc, char** argv)
{
	if (argc == 1) print_help();
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-i"))
		{
			args.ip = argv[i+1];
			i++;
		}
		else if (!strcmp(argv[i], "-p"))
		{
			args.port = atoi(argv[i+1]);
			i++;
		}
		else if (!strcmp(argv[i], "-r"))
		{
			args.mode = MODE_RECEIVE;
		}
		else if (!strcmp(argv[i], "-s"))
		{
			args.mode = MODE_SEND;
		}
		else if (!strcmp(argv[i], "-c"))
		{
			args.continuous = true;
		}
		else
		{
			args.filename = argv[i];
		}
	}
}