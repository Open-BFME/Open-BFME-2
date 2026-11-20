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
// text at 0x01075230 when TheDeepCRC at 0x012ED4E5 is already set.



extern unsigned int BFME2CommandFlags;
extern bool TheDeepCRC;	// 0x00A02D86 (Rva0023E7D9Clear.cpp)
extern bool TheLiteCRC;	// 0x00A02D87 (GameLogicInit.cpp)
#include "Common/INIException.h"

int bfmeSetupAPB(void)
{
	TheLiteCRC = true;
	BFME2CommandFlags |= 0x20000;
	if (TheDeepCRC)
	{
		throw INIException(3, "Do not specify both -deepCRC and -liteCRC in your commandline arguments.");
	}
	return 1;
}

// The paired deep-CRC handler at retail 0x003B9BA1 (63 bytes).
// The donor lite-CRC handler supplies the exception semantics; target writes
// select bit 0x10000 and the opposite mode flag. The descriptive name
// records that behavior, without asserting the original source spelling.
int bfmeSetupDeepCRC(void)
{
	TheDeepCRC = true;
	BFME2CommandFlags |= 0x10000;
	if (TheLiteCRC)
	{
		throw INIException(3, "Do not specify both -deepCRC and -liteCRC in your commandline arguments.");
	}
	return 1;
}
