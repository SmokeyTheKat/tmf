#ifndef __TMF_ARGS_H__
#define __TMF_ARGS_H__

#include <stdbool.h>

struct args;

void interrupt_args(int argc, char** argv);

struct args
{
	bool continuous;
	int mode;
	int port;
	char* ip;
	char* filename;
};

extern struct args args;

#endif