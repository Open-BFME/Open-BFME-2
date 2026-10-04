// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI

//
// ?createAptScreenInGameChat@@YGPAXPAX@Z
// retail 0x0041025D, 58 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameClient/GUI/AptScreenFactories.cpp
// (reference/open-bfme-1). The donor body is byte-identical to retail once
// relocations are masked (unique masked placement on unclaimed .text, donor
// recompiled /Os). Only the placed body is defined here; the donor's other
// 42 definitions are omitted.
//
// InGameChat.apt, retail 0x001050C0, object 0x2A4 bytes. The screen is
// described only by its size -- the factory body touches no member, so there
// is no layout to recover and none is invented. The constructor is called
// out-of-line, so only its retail address matters; it is pinned in
// reverse/symbols.csv at 0x0056DB9B.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/BfmeAptScreenBaseLayout.h
class BfmeAptScreenInGameChat
{
public:
	BfmeAptScreenInGameChat( void *context );

private:
	char m_unmodelled[ 0x2A4 ];
};

// ?createAptScreenInGameChat@@YGPAXPAX@Z
void * __stdcall createAptScreenInGameChat( void *context )
{
	return new BfmeAptScreenInGameChat( context );
}
