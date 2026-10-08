// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/networkutil /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#define Matrix4x4 Matrix4  // BFME renamed it
// stlport

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// No defined global owns VA 0x00DD2DB4. data_xrefs has no row because this
// matched function has no Ghidra boundary; retail stores AX there, and the
// adjacent reader/incrementer confirms a 16-bit command ID. Retail bytes: 64 00.
unsigned short g_00DD2DB4 = 100;

// SeedNextCommandIDFromPlayerCount: BFME-only helper, no Zero Hour counterpart.
//
// Retail: 0x00581194, 20 bytes. mov eax,[esp+4]; add eax,0Ah; imul eax,eax,3E8h;
// mov word ptr [00DD2DB4h],ax; ret. (BFME1 donor b1 0x00682CF0 stores to
// 012BA084h; BFME2 moved the static.)
//
// 012BA084h is the exact address of NetworkUtil.cpp's GenerateNextCommandID()
// static UnsignedShort commandID (that function loads/increments the very same
// address -- three total .text xrefs to 012BA084h in the whole exe: this
// store, GenerateNextCommandID's load, and its increment). Zero Hour just
// initializes that static to a fixed 100/64000; BFME instead reseeds it here
// with a value derived from the player count. The sole caller is
// BFMEConnectionManager::attachPlayersFromGameInfo (0x00666610), which calls
// this immediately after fetching GameInfo's player count, before attaching
// any per-player slots -- i.e. once, at match-attach time.
// BFME2's copy of that static lives at 00DD2DB4h: the very next body in
// game.dat (0x5811A8: mov eax,[DD2DB4] / inc word ptr [DD2DB4] / ret) is
// GenerateNextCommandID loading and incrementing this same address, and the
// seeding store here is its only other xref.
void SeedNextCommandIDFromPlayerCount(Int numPlayers)
{
	g_00DD2DB4 = static_cast<unsigned short>((numPlayers + 10) * 1000);
}

// Retail: 0x005811A8, 13 bytes. mov eax,[00DD2DB4h]; inc word ptr [00DD2DB4h];
// ret -- the post-increment of BFME 1's NetworkUtil.cpp GenerateNextCommandID
// (b1 0x00682D10, same 13 bytes, its function-local `static UnsignedShort
// commandID = 100; return commandID++;`). BFME 2's counter is the file-scope
// g_00DD2DB4 above because the seeding store shares it. 24 matched call sites
// in ConnectionManager and the network command code call this address.
UnsignedShort GenerateNextCommandID()
{
	return g_00DD2DB4++;
}
