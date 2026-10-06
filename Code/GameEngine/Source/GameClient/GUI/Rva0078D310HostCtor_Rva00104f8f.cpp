// cl: -GF -Gy -MD -EHsc -GR -DNDEBUG -DWIN32 -D_WINDOWS -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI

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
// ??0Rva000A2670@@QAE@PAX@Z @0x000A2670 24B unlock via base ctor row 0x00104F8F plus vtable g_00BC904C unblocks 0x0008F999 0x000A26F7 0x000A26C7
class Rva000A2670 : public Rva0078D310Host
{
public:
	Rva000A2670(void *context);
};
Rva000A2670::Rva000A2670(void *context) : Rva0078D310Host(context)
{
}
// ??0Rva000A2137@@QAE@PAX@Z @0x000A2137 24B evidence: base ctor row 0x00104F8F plus vtable g_00BC8FF4; callers 0x0008FAA8 in Rva0008FA81Create and 0x000A2186; LINK BONUS 232B for Rva0008F8EBFactories
class Rva000A2137 : public Rva0078D310Host
{
public:
	Rva000A2137(void *context);
};
Rva000A2137::Rva000A2137(void *context) : Rva0078D310Host(context)
{
}
