#ifndef __tmf_args_h__
#define __tmf_args_h__

#include <ddcPrint.h>

void print_help(void)
{
	ddPrint_cstring("tmf\n");
	ddPrint_cstring("usage: tmf [-MODE] [-OPTIONS...] file\n");
	ddPrint_cstring("modes:\n");
	ddPrint_cstring("	-r	-	receive once\n");
	ddPrint_cstring("	-rc	-	receive constantly\n");
	ddPrint_cstring("	-s	-	send once\n");
	ddPrint_cstring("	-sc	-	send on signal\n");
	ddPrint_cstring("options:\n");
	ddPrint_cstring("docs: https://ddmo.xyz/projects/tmf/\n");
	exit(0);
}

struct compilerArgs
{
	ddString name;
	ddString value;
};

struct compilerArgs cargs[1000];
sizet cargsCount = 0;

void read_args(int argc, char** argv)
{
	if (argc == 1) print_help();
	for (int i = 1; i < argc; i++)
	{
		ddString dsarg = make_ddString(argv[i]);
		if (ddString_compare_cstring(dsarg, "--help") || ddString_compare_cstring(dsarg, "-help"))
			print_help();
/*
		else if (ddString_compare_cstring(dsarg, "-o"))
		{
			cargs[cargsCount].name = dsarg;
			cargs[cargsCount++].value = make_ddString(argv[++i]);
		}
*/
		else if (dsarg.cstr[0] == '-')
		{
			cargs[cargsCount++].name = dsarg;
		}
		else if (dsarg.cstr[0] != '-')
		{
			cargs[cargsCount].name = make_constant_ddString("__TARGET_FILE");
			cargs[cargsCount++].value = dsarg;
		}
	}
}
ddString args_get_value(ddString name)
{
	for (sizet i = 0; i < cargsCount; i++)
	{
		if (ddString_compare(name, cargs[i].name)) return cargs[i].value;
	}
	return make_constant_ddString("ERROR");
}
bool args_if_def(ddString name)
{
	for (sizet i = 0; i < cargsCount; i++)
	{
		if (ddString_compare(name, cargs[i].name)) return true;
	}
	return false;
}

#endif
