// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Ireference/open-bfme-1/inputs/reference/shims/iniexception
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeSetupAPB.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: bfmeSetupAPB 0x003B9BE0 (64B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.

// ?bfmeSetupAPB@@YAHXZ 0x00061380
// The retail body updates g_bfmeFlagsAPB at 0x012A6FA0, marks the second CRC
// mode at 0x012ED4E6, and rejects the mode pair through the shared INIException
// text at 0x01075230 when g_bfmeOnAPB at 0x012ED4E5 is already set.

typedef unsigned int UnsignedInt;

extern unsigned int BFME2CommandFlags;
extern bool g_bfmeOnAPB;
extern bool g_bfmeDoneAPB;
#include "Common/INIException.h"

int bfmeSetupAPB(void)
{
	g_bfmeDoneAPB = true;
	BFME2CommandFlags |= 0x20000;
	if (g_bfmeOnAPB)
	{
		throw INIException(3, "Do not specify both -deepCRC and -liteCRC in your commandline arguments.");
	}
	return 1;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_bfmeFlagsAPB@@3IA=?BFME2CommandFlags@@3IA")
#pragma comment(linker, "/alternatename:?g_bfmeOnAPB@@3_NA=?g_Rva00A02D86@@3EA")
#pragma comment(linker, "/alternatename:?g_bfmeDoneAPB@@3_NA=?g_Rva00A02D87@@3EA")

// The paired deep-CRC handler at retail 0x003B9BA1 (63 bytes).
// The donor lite-CRC handler supplies the exception semantics; target writes
// select bit 0x10000 and the opposite mode flag. The descriptive name
// records that behavior, without asserting the original source spelling.
int bfmeSetupDeepCRC(void)
{
	g_bfmeOnAPB = true;
	BFME2CommandFlags |= 0x10000;
	if (g_bfmeDoneAPB)
	{
		throw INIException(3, "Do not specify both -deepCRC and -liteCRC in your commandline arguments.");
	}
	return 1;
}
