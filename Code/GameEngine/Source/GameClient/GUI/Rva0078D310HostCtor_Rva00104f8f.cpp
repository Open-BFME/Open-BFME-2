// cl: -GF -Gy -MD -EHsc -GR -DNDEBUG -DWIN32 -D_WINDOWS /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI

//
// ??0Rva0078D310Host@@QAE@PAX@Z
// retail 0x00104F8F, 70 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameClient/GUI/Rva0078D310HostCtor.cpp
// (reference/open-bfme-1). The donor body is byte-identical to retail once
// relocations are masked (unique masked placement on unclaimed .text, donor
// recompiled /Os). The donor file carries this single definition, so the
// dedicated TU is that body verbatim.
//
class Gen0078D1C0
{
public:
	Gen0078D1C0();
};

class BfmeAptScreenBase
{
public:
	BfmeAptScreenBase( void *context );
	virtual ~BfmeAptScreenBase();

protected:
	Gen0078D1C0 *m_memberPointer;
	char m_unreconstructed[ 0x210 ];
};

class Rva0078D310Host : public BfmeAptScreenBase
{
public:
	Rva0078D310Host( void *context );
	virtual ~Rva0078D310Host();

private:
	Gen0078D1C0 m_member;
};

Rva0078D310Host::Rva0078D310Host( void *context )
	: BfmeAptScreenBase( context )
{
	m_memberPointer = &m_member;
}
