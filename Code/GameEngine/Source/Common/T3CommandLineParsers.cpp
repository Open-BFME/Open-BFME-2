// cl: -DNDEBUG -MD -EHs-c- -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME-1: BFME's own CommandLine.cpp option handlers.
//
// Every body here is an `Int parseXxx(char *args[], int num)` of the shape the
// Zero Hour CommandLine.cpp uses, and the already-matched rows in
// game/GameEngine/Source/Common/CommandLine.cpp (parseXRes, parseFullVersion,
// parseFPUPreserve) sit in the same run of addresses. The Zero Hour source
// cannot claim these, though: BFME's GlobalData is a different object, so the
// ZH header puts m_windowed at +0x20 where retail stores +0x29, and the ZH
// translation unit misses on member offsets alone. So GlobalData is rebuilt
// here from the offsets retail actually writes.
//
// One of those offset pairs is pinned by numbers rather than by shape: the pair
// (m_useFpsLimit at +0x1E, m_framesPerSecondLimit at +0x24) is written FALSE and
// 0x7530 = 30000 together, which is ZH parseNoFPSLimit verbatim.
//
// TheCommandLineFlags at [0x012A6FA0] is a BFME addition with no ZH counterpart:
// a bitmask of which switches were seen, OR-ed with one bit per handler.
//
// A handler takes EA's name where tools/ea_flagtable.py reads it from the
// CommandLineParam tables: retail's own (0x00EA6F40) pairs a flag with a body,
// BFME1 WorldBuilder's (0x00FBB788) pairs it with a body of identical effects,
// and Zero Hour's table pairs that flag with the name
// (targets/game/reverse/identity_evidence/00ea6f40-commandline-params.md).
// The rest are address-derived: their rows are Rva-prefixed and each carries
// the ZH handler it matches in shape where there is one.
//
// Dedicated TU: only the four placed bodies are defined; the donor's other
// twenty-four definitions are omitted. All four are the same shape -- `Int
// parseXxx(char *args[], int num)` reading atoi(args[1]) into a value global,
// mirroring it into a second global, OR-ing a bit into TheCommandLineFlags --
// and differ only in which globals they touch and which bit they set.
//
// Every offset below is one retail store; no name moves one. The named members
// are the offsets retail's own INI field table at 0x00C77018 gives a key to,
// joined to the upstream member that key writes -- so the offset is BFME's and
// only the vocabulary is Zero Hour's. That table independently reproduces the
// three offsets this file had already pinned by hand from the stores
// (m_useFpsLimit +0x1E, m_framesPerSecondLimit +0x24, m_windowed +0x29), which
// is what makes it safe to read the rest of it. A key BFME added and Zero Hour
// has no member for stays an offset name, with the key in its comment.

#include <stdlib.h>

typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
#include "../../Include/Common/GlobalData.h"

extern GlobalData *TheWritableGlobalData;				///< retail [0x012ED5C8]
extern unsigned int BFME2CommandFlags;					///< retail [0x012A6FA0]

extern bool g_flag12ED4D8;								///< retail [0x012ED4D8]
extern bool g_flag12ED4D9;								///< retail [0x012ED4D9]
extern bool g_flag12ED4DA;								///< retail [0x012ED4DA]
extern bool g_flag12ED4E8;								///< retail [0x012ED4E8]
extern bool g_flag12D6DA8;								///< retail [0x012D6DA8]

extern int TheDebugCRCFromFrame;
extern int TheDebugCRCUntilFrame;
extern Int g_value12A6F38;								///< retail [0x012A6F38]
extern Int g_value12A6FA8;								///< retail [0x012A6FA8]
extern Int g_value12A6FB0;								///< retail [0x012A6FB0]
extern Int g_value12A6FB4;								///< retail [0x012A6FB4]
// Defined here with the BFME2 image's initial values; these handlers are
// their only writers (GameLogicInit.cpp also reads the first).
Int g_value12A6F38 = -1;	///< BFME2 .data VA 0x00DC116C
Int g_value12A6FA8 = 0;		///< BFME2 .data VA 0x00DC1178
Int g_value12A6FB0 = 0;		///< BFME2 .data VA 0x00DC1180
Int g_value12A6FB4 = -1;	///< BFME2 .data VA 0x00DC1184
extern Int NET_CRC_INTERVAL; // native RVA 0x009BC800

// ?parseDebugCRCFromFrame@@YAHQAPADH@Z
Int parseDebugCRCFromFrame(char *args[], int num)
{
	if (num > 1)
	{
		Int value = atoi(args[1]);
		(*(Int *)&TheDebugCRCFromFrame) = value;
		BFME2CommandFlags |= 0x2000;
		g_value12A6FA8 = value;
	}
	return 2;
}

// ?parseDebugCRCUntilFrame@@YAHQAPADH@Z
Int parseDebugCRCUntilFrame(char *args[], int num)
{
	if (num > 1)
	{
		Int value = atoi(args[1]);
		(*(Int *)&TheDebugCRCUntilFrame) = value;
		BFME2CommandFlags |= 0x4000;
		g_value12A6FA8 = value;
	}
	return 2;
}

// ?parseNetCRCInterval@@YAHQAPADH@Z
Int parseNetCRCInterval(char *args[], int num)
{
	if (num > 1)
	{
		Int value = atoi(args[1]);
		NET_CRC_INTERVAL = value;
		BFME2CommandFlags |= 0x8000;
		g_value12A6FB0 = value;
	}
	return 2;
}

// ?Rva000613F0_parse@@YAHQAPADH@Z
Int Rva000613F0_parse(char *args[], int num)
{
	if (num > 1)
	{
		Int value = atoi(args[1]);
		if (value > 0)
		{
			g_value12A6F38 = value;
			g_value12A6FB4 = value;
		}
	}
	return 1;
}
