// cl: /GS
// 0x007EB920 / 0x007EB9C0: FESL debug.cpp assert/error formatters. sprintf
// into a 0x180-byte stack buffer, fail if strlen >= sizeof(buf), emit vslot 1.

#include <stdio.h>
#include <string.h>

#include "../../Include/GameNetwork/Rva007EB810Diag.h"

extern int g_FeslDiagReporter;

#pragma intrinsic(strlen)

class Rva007EB8B0Log
{
public:
	virtual void v0();
	virtual void emit(char *buf);
	int assertFailed(const char *expr, const char *file, int line);
	int errorFrom(int code, const char *from, const char *file, int line);
};

int Rva007EB8B0Log::assertFailed(const char *expr, const char *file, int line)
{
	char buf[0x180];
	sprintf(buf, "assert '%.128s' at %.128s:%ld failed\n", expr, file, line);
	if (!(strlen(buf) < 0x180))
		((Rva007EB810Diag *)g_FeslDiagReporter)->fail(
			"strlen(buf) < sizeof(buf)",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\debug.cpp",
			137);
	emit(buf);
	return 0;
}

int Rva007EB8B0Log::errorFrom(int code, const char *from, const char *file, int line)
{
	char buf[0x180];
	if (code)
	{
		sprintf(buf, "error %d from '%.128s' at %.128s:%ld\n", code, from, file, line);
		if (!(strlen(buf) < 0x180))
			((Rva007EB810Diag *)g_FeslDiagReporter)->fail(
				"strlen(buf) < sizeof(buf)",
				"\\views\\feslbuild_main\\jabba\\fesl\\source\\debug.cpp",
				161);
		emit(buf);
	}
	return 0;
}

// ?g_FeslDiagReporter@@3HA: the data ledger's global at VA 0xe09fbc (the FESL
// diagnostic reporter pointer); users cast it to their Rva007EB810Diag view.
int g_FeslDiagReporter = 0;
