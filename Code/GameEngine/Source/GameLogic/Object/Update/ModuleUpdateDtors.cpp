// cl: /MD
//
// Opaque module destructors tail-calling Rva0044EF5E::~Rva0044EF5E at
// 0x00451F45 (pinned opaque intermediate base dtor; the derived module
// dtors re-store the vtable plus the +0x0C/+0x10/+0x20 consts, then
// tail-jump it). The base is modeled with its full 0x88 layout but its
// destructor is only declared here (defined nowhere -- it resolves via the
// pin), because a same-TU definition would capture the call locally instead
// of at the ledger address. Vtable values and consts are DIR32 auto-patches.
// Derived identities come from factory stub order (OCLUpdate,
// SupplyCenterDockUpdate); the base identity is unproven (opaque Rva name).
// CurseSpecialPower is named by its vtable 0x00C5F850: its ctor at 0x004CCD7F
// installs it, slot 0 is the ??_G at 0x004CCE30 and slot 4 is
// CurseSpecialPower's pool-key getter at 0x004CCDEB. One ledger row per destructor, landed one
// commit at a time. Each class also emits its scalar deleting destructor
// (vtable slot 0), claimed as its own row once the primary lands.

class Thing;
class ModuleData;

static int s_dummy0C;
static int s_dummy10;
extern "C" const void *const vtbl_00C552A4[9];

// Opaque 0x88-byte UpdateModule-derived intermediate; dtor resolves to the
// opaque pin at 0x00451F45. Protected slots mirror the retail stores.
class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();

protected:
	unsigned char m_pad0[8];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad1[0x20 - 0x14];
	const void *m_p20;
	unsigned char m_pad2[0x88 - 0x24];
};

class OCLUpdate : public Rva0044EF5E
{
public:
	virtual ~OCLUpdate();
};

OCLUpdate::~OCLUpdate()
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = vtbl_00C552A4;
}

class CurseSpecialPower : public Rva0044EF5E
{
public:
	virtual ~CurseSpecialPower();
};

CurseSpecialPower::~CurseSpecialPower()
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = vtbl_00C552A4;
}

class SupplyCenterDockUpdate : public Rva0044EF5E
{
public:
	virtual ~SupplyCenterDockUpdate();
};

SupplyCenterDockUpdate::~SupplyCenterDockUpdate()
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = vtbl_00C552A4;
}

class Rva00490D76 : public Rva0044EF5E
{
public:
	virtual ~Rva00490D76();
};

Rva00490D76::~Rva00490D76()
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = vtbl_00C552A4;
}

class Rva004921B0 : public Rva0044EF5E
{
public:
	virtual ~Rva004921B0();
};

Rva004921B0::~Rva004921B0()
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = vtbl_00C552A4;
}

extern "C" const void *const s_dummy20[9];
static int s_dummyEB30;
static int s_dummyE184;
static int s_dummyEB0C;

class Rva00492439 : public Rva0044EF5E
{
public:
	virtual ~Rva00492439();
};

Rva00492439::~Rva00492439()
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = s_dummy20;
}







class Rva00494F1B : public Rva0044EF5E
{
public:
	virtual ~Rva00494F1B();
};

Rva00494F1B::~Rva00494F1B()
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = vtbl_00C552A4;
}

// These two interface tables were previously represented by zero-filled
// dummy scalars. Preserve their provisional ledger names while supplying
// every native slot through its existing rowed code owner. Slot labels do
// not establish the original method identities (several bodies are folded).
extern "C" {
void __identifier("??1Region2D@@QAE@XZ")();
void __identifier("?rva004B0303@Rva004B0303@@UAEXXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ")();
void __identifier("?getRailedTransportDockUpdateInterface@RailedTransportDockUpdate@@UAEPAVRailedTransportDockUpdateInterface@@XZ")();
void __identifier("?getDie@DieModule@@UAEPAVDieModuleInterface@@XZ")();
void __identifier("?get@Rva004543A9LeaNegSbbField@@UBEHXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
}

// RVA 0x008562C8; 4 code pointers; followed immediately by the next table.
extern "C" const void *const s_dummy62C8[4] = {
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 0, RVA 0x000B3FD0
	(const void *)&__identifier("?rva004B0303@Rva004B0303@@UAEXXZ"), // slot 1, RVA 0x004B0303
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 2, RVA 0x000B3FD0
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 3, RVA 0x0047A699
};

// RVA 0x008562D8; 47 code pointers; the next native word is zero padding.
extern "C" const void *const s_dummy62D8[47] = {
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 0, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 1, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 2, RVA 0x000D43D0
	(const void *)&__identifier("?getRailedTransportDockUpdateInterface@RailedTransportDockUpdate@@UAEPAVRailedTransportDockUpdateInterface@@XZ"), // slot 3, RVA 0x004B01D9
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 4, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 5, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 6, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 7, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 8, RVA 0x000D43D0
	(const void *)&__identifier("?getDie@DieModule@@UAEPAVDieModuleInterface@@XZ"), // slot 9, RVA 0x002533D3
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 10, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 11, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 12, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 13, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 14, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 15, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 16, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 17, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 18, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 19, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 20, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 21, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 22, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 23, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 24, RVA 0x000D43D0
	(const void *)&__identifier("?get@Rva004543A9LeaNegSbbField@@UBEHXZ"), // slot 25, RVA 0x004543A9
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 26, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 27, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 28, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 29, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 30, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 31, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 32, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 33, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 34, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 35, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 36, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 37, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 38, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 39, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 40, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 41, RVA 0x000D43D0
	(const void *)&__identifier("?behaviorAnchor@BehaviorModuleInterface@@UAEIXZ"), // slot 42, RVA 0x000D43D0
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 43, RVA 0x0047A69C
	(const void *)&__identifier("??1Region2D@@QAE@XZ"), // slot 44, RVA 0x000B3FD0
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 45, RVA 0x0047A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 46, RVA 0x0047A69C
};

class Rva004B0164 : public Rva0044EF5E
{
public:
	virtual ~Rva004B0164();

private:
	const void *m_tail88;
};

Rva004B0164::~Rva004B0164()
{
	m_p0C = &s_dummy62D8;
	m_p10 = &s_dummy10;
	m_p20 = vtbl_00C552A4;
	m_tail88 = &s_dummy62C8;
}

class Rva004B29BE : public Rva0044EF5E
{
public:
	virtual ~Rva004B29BE();
};

Rva004B29BE::~Rva004B29BE()
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = vtbl_00C552A4;
}

class Rva004CC9BF : public Rva0044EF5E
{
public:
	virtual ~Rva004CC9BF();
};

Rva004CC9BF::~Rva004CC9BF()
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = vtbl_00C552A4;
}

class Rva004CDD39 : public Rva0044EF5E
{
public:
	virtual ~Rva004CDD39();
};

Rva004CDD39::~Rva004CDD39()
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = vtbl_00C552A4;
}

static int s_dummy52C8;
static int s_dummy5348;
static int s_dummyDF74;
extern "C"
{
	int s_dummyFD98;
}



class Rva004AE4E2 : public Rva0044EF5E
{
public:
	virtual ~Rva004AE4E2();
};

Rva004AE4E2::~Rva004AE4E2()
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = &s_dummy5348;
}



class Rva004CE03D : public Rva0044EF5E
{
public:
	virtual ~Rva004CE03D();
};

Rva004CE03D::~Rva004CE03D()
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = &s_dummyFD98;
}

extern "C"
{
	int s_dummy5198;
	int s_dummy5188;
}

class Rva004AD9B0 : public Rva0044EF5E
{
public:
	virtual ~Rva004AD9B0();

private:
	const void *m_tail88;
};

Rva004AD9B0::~Rva004AD9B0()
{
	m_p0C = &s_dummy62D8;
	m_p10 = &s_dummy10;
	m_p20 = &s_dummy5198;
	m_tail88 = &s_dummy5188;
}
