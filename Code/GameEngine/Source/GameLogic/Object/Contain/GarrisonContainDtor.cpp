// cl: /DNDEBUG /MD /EHsc
//
// ??1GarrisonContain@@UAE@XZ retail 0x00478067 128 bytes.
// GarrisonContain virtual destructor over pinned OpenContain base 0x00464692.
// Restores nine vtable slots at +0x00 +0x0C +0x10 +0x20 +0x24 +0x28 +0x2C +0x30 +0x34
// then destroys 120 Coord3D at +0x424 via eh vector destructor iterator
// through folded dtor at 0x000B3FD0 then calls base dtor.
// Donor BFME1 GarrisonContainDestructor Coord3D 3x40 at 0x3FC moved to 0x424 in BFME2.
// Identity via deleting wrapper 0x0047860D slot0 vtable 0x00C461F8
// and pool key 0x0047801C with GarrisonContain string.
// Layout from ctor 0x00477F06 array 0x424 count 0x78 size 0x0C and factory news 0x9E0.
// Shape follows CaveContainDtor ten-vptr plus FlightDeck RunwayInfo Coord3D array precedent.

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

GarrisonContain::~GarrisonContain()
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
