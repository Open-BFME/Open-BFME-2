// cl: -GF -Gy -MD -EHsc -DNDEBUG -DWIN32 -D_WINDOWS -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI

//
// ??0Rva0078D310Host@@QAE@XZ
// retail 0x00104F32, 65 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameClient/GUI/Rva0078D270GameWindowHostDtor.cpp
// (reference/open-bfme-1). The donor body is byte-identical to retail once
// relocations are masked (unique masked placement on unclaimed .text, donor
// recompiled /Os). Only the placed body is defined here; the donor's other
// definition (the destructor) is omitted.
//
#include "../../../../Libraries/Source/WWVegas/WW3D2/Render2DSentenceClass.h"

class Gen0078D1C0Base
{
public:
	virtual ~Gen0078D1C0Base() {}
};

// BFME 1 donor note: there the member teardown runs through 0x009409F0
// (??1Render2DSentenceClass). In BFME 2 the embedded object's destructor is the
// rowed ??1Rva00104DB0 0x00104DB0, declared out of line so this unit's unwind
// calls it instead of emitting an inline copy.

class Rva00104DB0 : public Gen0078D1C0Base
{
public:
	Rva00104DB0();
	virtual ~Rva00104DB0();

private:
	Render2DSentenceClass m_registry;
	char m_unreconstructed[ 0x0E ];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	GameWindow();

protected:
	virtual ~GameWindow();
	Rva00104DB0 *m_embeddedPointer;
	char m_unreconstructed[ 0x210 ];
};

class Rva0078D310Host : public GameWindow
{
public:
	Rva0078D310Host();
	virtual ~Rva0078D310Host();

private:
	Rva00104DB0 m_embedded;
};

Rva0078D310Host::Rva0078D310Host()
{
	m_embeddedPointer = &m_embedded;
}
