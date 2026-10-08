// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x0028C428, 142B: an Object const predicate (thiscall, no args)
// in the attack-capability family. True when the template count at
// ThingTemplate+0x0C is at least 1, or when the entry from 0x0028AC4E passes
// its own count test (0x001E3E5C); otherwise when any of the six weapon slots
// of the weapon set at +0x330 (WeaponSet::getWeaponInWeaponSlot 0x002C7469)
// holds a weapon whose template index at +0x174 is non-negative, when the
// body module at +0x254 exposes an interface (slot 0x29) whose slot 0x0E
// accepts, or when the emotion tracker at +0x24C reports true (0x004B0EBC).
// Slot name not established: address-derived.

typedef int Int;

class ThingTemplate
{
public:
	unsigned char m_pad00[0x0C];
	Int m_count0C;
};

struct Rva0028AC4EEntry;

class Rva001E3E5C
{
public:
	bool rva001E3E5C() const;
};

class WeaponTemplate
{
public:
	unsigned char m_pad00[0x174];
	Int m_index174;
};

class Weapon
{
public:
	void *m_vtable;
	const WeaponTemplate *m_template;
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0,
	WEAPONSLOT_COUNT = 6
};

class WeaponSet
{
public:
	Weapon *getWeaponInWeaponSlot(WeaponSlotType slot) const;
};

class Rva0028C428Iface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v0a();
	virtual void v0b();
	virtual void v0c();
	virtual void v0d();
	virtual bool test();
};

class BodyModuleInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v0a();
	virtual void v0b();
	virtual void v0c();
	virtual void v0d();
	virtual void v0e();
	virtual void v0f();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v1a();
	virtual void v1b();
	virtual void v1c();
	virtual void v1d();
	virtual void v1e();
	virtual void v1f();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual Rva0028C428Iface *getIface();
};

class EmotionTrackerUpdate
{
public:
	bool rva004B0EBC();
};

class Object
{
public:
	const Rva0028AC4EEntry *rva0028AC4E() const;
	bool rva0028C428() const;

	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_pad08[0x24C - 0x08];
	EmotionTrackerUpdate *m_emotionTracker;
	unsigned char m_pad250[0x254 - 0x250];
	BodyModuleInterface *m_body;
	unsigned char m_pad258[0x330 - 0x258];
	WeaponSet m_weaponSet;
};

bool Object::rva0028C428() const
{
	if( m_template->m_count0C >= 1 )
		return true;

	const Rva0028AC4EEntry *entry = rva0028AC4E();
	if( entry && ((const Rva001E3E5C *)entry)->rva001E3E5C() )
		return true;

	for( Int i = 0; i < WEAPONSLOT_COUNT; ++i )
	{
		const Weapon *weapon = m_weaponSet.getWeaponInWeaponSlot( (WeaponSlotType)i );
		if( weapon && weapon->m_template && weapon->m_template->m_index174 >= 0 )
			return true;
	}

	BodyModuleInterface *body = m_body;
	if( body )
	{
		Rva0028C428Iface *iface = body->getIface();
		if( iface && iface->test() )
			return true;
	}

	if( m_emotionTracker && m_emotionTracker->rva004B0EBC() )
		return true;

	return false;
}
