// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??1SlaughterHordeContain@@UAE@XZ, retail 0x004803FB, 118 bytes.
// Virtual dtor over vtable 0x00C48AA0 (slot 0 deleting dtor at 0x00480645
// calls this body). Restores nine vtable slots at +0x00 +0x0C +0x10 +0x20
// +0x24 +0x28 +0x2C +0x30 +0x34 (DIR32), destroys the AsciiString at +0x9E8
// through the pinned 0x00036410 dtor (single tracked member state 0), then
// calls the rowed GarrisonContain base dtor at 0x00478067. Layout from the
// rowed ctor 0x0048034E (HordeGarrisonContain base, m_9E4 int cleared, m_9E8
// cleared string null, factory 0x0024C036 news 0x9EC) over the GarrisonContain
// 0x9E0 shape (Coord3D array at +0x424). Shape follows GarrisonContainDtor
// (TU-local nine-base OpenContain chain with inline Coord3D, empty derived
// body, entry derived stores kept so no novtable).

class B0 { public: virtual void b0(); private: unsigned char m_pad[8]; };
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char m_pad[12]; };
class B3 { public: virtual void b3(); };
class B4 { public: virtual void b4(); };
class B5 { public: virtual void b5(); };
class B6 { public: virtual void b6(); };
class B7 { public: virtual void b7(); };
class B8 { public: virtual void b8(); private: unsigned char m_pad[0xC8 - 4]; };

class OpenContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
public:
	virtual ~OpenContain();
};

class Coord3D
{
public:
	~Coord3D();
	float x;
	float y;
	float z;
};

class GarrisonContain : public OpenContain
{
public:
	virtual ~GarrisonContain();
private:
	unsigned char m_padFC424[0x424 - 0xFC];
	Coord3D m_garrisonPoint[120];
	unsigned char m_tail[0x9E0 - 0x9C4];
};

#include "ascii_string.h"

class SlaughterHordeContain : public GarrisonContain
{
public:
	virtual ~SlaughterHordeContain();

private:
	int m_pad9E0; // +0x9E0 (Horde intermediate pad)
	int m_9E4; // +0x9E4
	AsciiString m_str9E8; // +0x9E8
};

SlaughterHordeContain::~SlaughterHordeContain()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?b1@B1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?b6@B6@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
