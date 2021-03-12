#include <stdio.h>

#include "./ddcLib/ddcDef.h"
#include "./ddcLib/ddcPrint.h"
#include "./ddcLib/ddcString.h"
#include "./ddcLib/ddcSocket.h"

#include "./args.h"
#include "./file.h"
#include "./utils.h"
#include "./send.h"
#include "./receive.h"

int main(int argc, char** argv)
{
	read_args(argc, argv);
	if (args_if_def(make_constant_ddString("-r")))
	{
		tmf_receive(false);
	}
	else if (args_if_def(make_constant_ddString("-rc")))
	{
		tmf_receive(true);
	}
	else if (args_if_def(make_constant_ddString("-s")))
	{
		tmf_send(false);
	}
	else if (args_if_def(make_constant_ddString("-sc")))
	{
		tmf_send(true);
	}
	return 0;
}
