// cl: /DNDEBUG /MD
//
// ??1HorseHordeContain@@UAE@XZ, retail 0x00476653, 87 bytes.
// Slot evidence: ??_G at 0x00476730 (ContainModuleDeletingDtors) calls here.
// Restores 11 vptrs (+0x00 +0x0C +0x10 +0x20 +0x24 +0x28 +0x2C +0x30 +0x34
// +0xFC +0x11C) then tail-jumps to pinned ??1HordeContain@@UAE@XZ at
// 0x0046F901. Low nine match TransportContainDtor ten-vptr pattern (B0-B8)
// and HordeContain base 0x0046F901 (nine shared); derived overrides at +0
// +0x20 +0x11C. No member teardown, no EH. TransportContainDtor precedent.
class Thing;
class ModuleData;
class Object;

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

class HFC { public: virtual void hfc(); private: unsigned char m_pad[0x20 - 4]; };
class HLC { public: virtual void hlc(); };

class HordeContain : public OpenContain, public HFC, public HLC
{
public:
	virtual ~HordeContain();
};

class HorseHordeContain : public HordeContain
{
public:
	virtual ~HorseHordeContain();
};

HorseHordeContain::~HorseHordeContain()
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
