// cl: /DNDEBUG /MD
//
// ??0CitadelSlaughterHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0048059F, 91 bytes.
// CitadelSlaughterHordeContain behavior ctor over the rowed
// SlaughterHordeContain intermediate base (0x48034E, thing plus data):
// forwards both args to the base, clears the int at +0x9EC, then re-stores
// the primary vtable slot and eight secondary slots at +0x0C/+0x10/+0x20/
// +0x24/+0x28/+0x2C/+0x30/+0x34 (address-of TU-local dummies, DIR32-masked).
// The and-first uses the ThreatFinder barrier recipe. The rowed pool key at
// 0x480600 and ModuleData factory 0x24C100 prove the class; the rowed
// instance factory 0x24C0C5 (news 0x9F0) is the sole raw caller. Row
// supersedes the ctor pin.

class Thing;
class ModuleData;
class Xfer;
class DamageInfo;
class CitadelContainDieView;
enum ObjectID { INVALID_ID = 0 };
enum NameKeyType { NK_UNKNOWN = 0 };

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;
static int s_secondary20;
static int s_secondary24;
static int s_secondary28;
static int s_secondary2C;
static int s_secondary30;
static int s_secondary34;

// Rowed SlaughterHordeContain base; the inherited vptr occupies +0.
// Keep the seed TU's primary virtual slots and the ctor's proven secondary
// table offsets in one view. novtable on the derived class preserves retail
// ordering: clear +0x9EC, then explicitly install its primary/secondary tables.
class SlaughterHordeContain
{
public:
	SlaughterHordeContain(Thing *thing, const ModuleData *moduleData);
	virtual ~SlaughterHordeContain();

protected:
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);

public:
	virtual NameKeyType getModuleNameKey() const;

protected:
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_p20;
	const void *m_p24;
	const void *m_p28;
	const void *m_p2C;
	const void *m_p30;
	const void *m_p34;
	unsigned char m_pad38[0x9EC - 0x38];
};

class __declspec(novtable) CitadelSlaughterHordeContain : public SlaughterHordeContain
{
public:
	CitadelSlaughterHordeContain(Thing *thing, const ModuleData *moduleData);
	virtual ~CitadelSlaughterHordeContain();
	virtual NameKeyType getModuleNameKey() const;
	virtual void onDie(const DamageInfo*);
	CitadelContainDieView *contain() { return reinterpret_cast<CitadelContainDieView*>(reinterpret_cast<char*>(this)-8); }

protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_9EC; // +0x9EC, factory 0x0024C0C5 news 0x9F0
};

// ??0CitadelSlaughterHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x48059F
CitadelSlaughterHordeContain::CitadelSlaughterHordeContain(Thing *thing, const ModuleData *moduleData)
	: SlaughterHordeContain(thing, moduleData)
{
	m_9EC = INVALID_ID;
	_ReadWriteBarrier();
	*reinterpret_cast<const void **>(this) = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_p20 = &s_secondary20;
	m_p24 = &s_secondary24;
	m_p28 = &s_secondary28;
	m_p2C = &s_secondary2C;
	m_p30 = &s_secondary30;
	m_p34 = &s_secondary34;
}
