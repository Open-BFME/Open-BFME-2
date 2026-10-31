// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Forwarders from an embedded sub-object to a rowed method of the object it
// sits in (add ecx, -N; jmp <method>, arguments passed through in place), the
// negative-offset form of the member forward ~PlayerPosition 0x0022D920
// (add ecx, 8; jmp). None has a direct caller (they sit in vtables or are
// out-of-line copies); the embedding classes are not recovered, so each view
// is address-named and reaches its owner by the proven offset.

typedef bool Bool;
enum WeaponSlotType { PRIMARY_WEAPON = 0 };
enum ObjectID { INVALID_ID = 0 };
struct LivingWorldArmy;

class TurretAI
{
public:
	Bool isWeaponSlotOnTurret(WeaponSlotType wslot) const;		// 0x004D81D7
};

class LivingWorldBattle
{
public:
	void RemoveArmy(LivingWorldArmy *army);					// 0x003F5647
};

class Rva004CBF9A
{
public:
	void clear();										// 0x004CBF9A
};

class Rva003F59FE;
class Rva0039851D;

class FoundationAIUpdate
{
	friend class Rva0039851D;
	void rva0045527A(ObjectID id);						// 0x0045527A
};

// --- 0x004D8717 (8B): the TurretAI sub-object at +4.
class Rva004D8717
{
public:
	Bool rva004D8717(WeaponSlotType wslot) const;
};

Bool Rva004D8717::rva004D8717(WeaponSlotType wslot) const
{
	return ((const TurretAI *)((const char *)this - 4))->isWeaponSlotOnTurret(wslot);
}

// --- 0x003F59FE (8B): the LivingWorldBattle sub-object at +4.
class Rva003F59FE
{
public:
	void rva003F59FE(LivingWorldArmy *army);
};

void Rva003F59FE::rva003F59FE(LivingWorldArmy *army)
{
	((LivingWorldBattle *)((char *)this - 4))->RemoveArmy(army);
}

// --- 0x004CC08D (8B): the Rva004CBF9A sub-object at +0xC.
class Rva004CC08D
{
public:
	void rva004CC08D();
};

void Rva004CC08D::rva004CC08D()
{
	((Rva004CBF9A *)((char *)this - 0xC))->clear();
}

// --- 0x0039851D (8B): the FoundationAIUpdate sub-object at +0x20.
class Rva0039851D
{
public:
	void rva0039851D(ObjectID id);
};

void Rva0039851D::rva0039851D(ObjectID id)
{
	((FoundationAIUpdate *)((char *)this - 0x20))->rva0045527A(id);
}

// --- 0x004FB128 (8B): an interface sub-object at +4 whose owner keeps the
// registry pointer at +0; forwards both arguments to the rowed lookup
// Rva004FB0C7Registry::rva004FB0C7 (0x004FB0C7, ret 8).
struct Rva004FAFF2;
class Rva004FB0C7Registry
{
public:
	Bool rva004FB0C7(int key, Rva004FAFF2 *out);
};

struct Rva004FB128Owner
{
	Rva004FB0C7Registry *m_registry;	// +0
};

class Rva004FB128
{
public:
	Bool rva004FB128(int key, Rva004FAFF2 *out);
};

Bool Rva004FB128::rva004FB128(int key, Rva004FAFF2 *out)
{
	return ((Rva004FB128Owner *)((char *)this - 4))->m_registry->rva004FB0C7(key, out);
}

// --- 0x0042C07B (8B) / 0x0043DA9D (8B): clear one flag byte (+0x94,
// +0x2C3); the shape of the rowed Reset bodies such as
// AABTreeIterator::Reset 0x0065D1C0.
class Rva0042C07B
{
public:
	void reset();
private:
	char m_pad00[0x94];
	bool m_94;
};

void Rva0042C07B::reset()
{
	m_94 = false;
}

class Rva0043DA9D
{
public:
	void reset();
private:
	char m_pad00[0x2C3];
	bool m_2C3;
};

void Rva0043DA9D::reset()
{
	m_2C3 = false;
}

// --- 0x004B96C4 (8B): the slot after onBuildComplete (0x004B96A9) in
// InheritUpgradeCreate's +0x10 interface table (VA 0x00C596EC): forwards to
// the pinned create work 0x004B959C on the primary this, the same call
// onBuildComplete tail-jumps.
class InheritUpgradeCreate
{
public:
	void rva004B959C();									// 0x004B959C (pinned)
};

class Rva004B96C4
{
public:
	void rva004B96C4();
};

void Rva004B96C4::rva004B96C4()
{
	((InheritUpgradeCreate *)((char *)this - 0x10))->rva004B959C();
}

// --- 0x004F68A8 (8B): assign the TreeHintRef member at +0x20 through the
// rowed TreeHintRef00217D4C::operator= 0x002174A4 (add ecx, 0x20; jmp), the
// positive-offset member forward of ~PlayerPosition 0x0022D920.
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);	// 0x002174A4
};

class Rva004F68A8
{
public:
	void rva004F68A8(const TreeHintRef00217D4C &ref);
private:
	char m_pad00[0x20];
	TreeHintRef00217D4C m_20;
};

void Rva004F68A8::rva004F68A8(const TreeHintRef00217D4C &ref)
{
	m_20 = ref;
}

// --- 0x004F68B0 (8B): clear the member at +0x20 through the rowed
// Rva002BED91::clear 0x002BED91 (add ecx, 0x20; jmp).
class Rva002BED91
{
public:
	void clear();										// 0x002BED91
};

class Rva004F68B0
{
public:
	void rva004F68B0();
private:
	char m_pad00[0x20];
	Rva002BED91 m_20;
};

void Rva004F68B0::rva004F68B0()
{
	m_20.clear();
}

// --- 0x004EC062 / 0x004EC06A (8B each): two forwards into the AI unit
// builder held at +0x38 of their owner (add ecx, 0x38; jmp), with the
// caller's argument in place: AIUnitBuilder::registerUnitFactory 0x00598431
// and the rowed map member 0x00598149 over the same sub-object.
class AIUnitBuilder
{
public:
	void registerUnitFactory(ObjectID id);				// 0x00598431
};

class Rva00598149
{
public:
	void rva00598149(void *p);							// 0x00598149
};

class Rva004EC062
{
public:
	void rva004EC062(ObjectID id);
	void rva004EC06A(void *p);
private:
	char m_pad00[0x38];
	AIUnitBuilder m_unitBuilder;
};

void Rva004EC062::rva004EC062(ObjectID id)
{
	m_unitBuilder.registerUnitFactory(id);
}

void Rva004EC062::rva004EC06A(void *p)
{
	((Rva00598149 *)&m_unitBuilder)->rva00598149(p);
}
