struct BfmeCsDWA
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv789.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: BfmeThingDWC::bfmeGoDWC 0x000387D0 (27B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.
{
	unsigned char m_bfmeHead[0x18];
};

// platformsdk
#include <windows.h>
#undef near
#undef far



// The critical section is the DebugCriticalSection the debug manager owns at
// 0x009E0884; this unit enters it through its byte view.
struct DebugCriticalSection;
extern DebugCriticalSection g_bfmeCsDWC;

struct BfmeThingDWC
{
	bool bfmeGoDWC();
	unsigned char m_bfmeHead[0x9df8];
	BfmeCsDWA m_bfmeCs;
};

bool BfmeThingDWC::bfmeGoDWC()
{
	InterlockedIncrement((LONG *)&m_bfmeCs);
	EnterCriticalSection((CRITICAL_SECTION *)&g_bfmeCsDWC);
	return false;
}

