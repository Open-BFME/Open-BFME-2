// cl: /DNDEBUG /MD /EHsc /Oy-
//
// Debug::Command, retail 0x0003B640 (47 bytes, ret 4). Debug vtable (RVA
// 0x7BE810) slot 0x8C, the slot profile_cmd_run_result_functions.cpp calls
// with "profile.result file_csv".
//
// Zero Hour's body (a static there, `DFAIL_IF(!cmd) return;` then
// ExecCommand over the whole string). BFME2 makes it a virtual member that
// returns ExecCommand's bool and returns false for a null command. The
// ExecCommand body at 0x00039E20 returns bool too: its two exits load
// `xor al, al` and a saved byte into al before `ret 8`.


#include <string.h>

#include "../../../../GameEngine/Source/Common/debug.h"

// ?Command@Debug@@UAE_NPBD@Z
bool Debug::Command(const char *cmd)
{
	if (!cmd)
		return false;
	return ExecCommand(cmd, cmd + strlen(cmd));
}
