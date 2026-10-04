// cl: -GF -Gy -MD -EHsc -GR -DNDEBUG -DWIN32 -D_WINDOWS /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI

//
// ??0Rva0078D270GameWindowHost@@QAE@XZ
// retail 0x00104F32, 65 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameClient/GUI/Rva0078D270GameWindowHostDtor.cpp
// (reference/open-bfme-1). The donor body is byte-identical to retail once
// relocations are masked (unique masked placement on unclaimed .text, donor
// recompiled /Os). Only the placed body is defined here; the donor's other
// definition (the destructor) is omitted.
//
class Gen0078D1C0Base
{
public:
	virtual ~Gen0078D1C0Base() {}
};

// Retail's member teardown at 0x0078D040 destroys the embedded object through
// 0x009409F0, whose own body installs vtable 0x0113CEAC and is matched in the
// ledger as ??1Render2DSentenceClass@@UAE@XZ (see
// targets/game/reverse/identity_evidence/009409f0-render2dsentence-dtor.md).
// Spelling the embedded type with its defining name is what makes this
// reference resolve; the destructor's virtualness already matches UAE@XZ.
class Render2DSentenceClass
{
public:
	virtual ~Render2DSentenceClass();

private:
	char m_unreconstructed[ 0xC8 ];
};

class Gen0078D1C0 : public Gen0078D1C0Base
{
public:
	Gen0078D1C0();
	virtual ~Gen0078D1C0() {}

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
	Gen0078D1C0 *m_embeddedPointer;
	char m_unreconstructed[ 0x210 ];
};

class Rva0078D270GameWindowHost : public GameWindow
{
public:
	Rva0078D270GameWindowHost();
	virtual ~Rva0078D270GameWindowHost();

private:
	Gen0078D1C0 m_embedded;
};

Rva0078D270GameWindowHost::Rva0078D270GameWindowHost()
{
	m_embeddedPointer = &m_embedded;
}
