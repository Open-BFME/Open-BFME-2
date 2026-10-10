// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
//
// ?rva00494C81@Rva00494C81@@QAEXHHHHH@Z @0x00494C81 165B ret 0x14.
// Sub-object (this = owner + 0x20) callback of the WeaponModeSpecialPower
// update family: kind 5 walks the 104 flag bits of the record's BitFlags<104>
// (rowed count 0x0028F6EB) and sets each as an object weapon-set flag, any other
// kind locks the weapon slot; then the record name is applied as an attribute
// modifier (rowed 0x0028EA91), the wake frame is set from the record, the
// owner flag +0x18 is raised, slot 15 is called with 1.0f and the object's
// FiringTracker cools down (rowed 0x004DEC88). Layout and call evidence from
// retail bytes; the owner class name is not proven, so the neutral address name
// stays. The record pointer is re-read through a volatile view after every
// callee because retail reloads it (the owner stores it at this - 0x1C).
#include "ascii_string.h"

enum WeaponSlotType
{
	SLOT_0 = 0
};
enum WeaponLockType
{
	LOCK_2 = 2
};
enum WeaponSetType
{
	SET_0 = 0
};
enum UpdateSleepTime
{
	SLEEP_0 = 0
};

template <int N> class BitFlags
{
public:
	int count() const;
	unsigned int m_words[(N + 31) / 32];
};

class Rva00494C81;

class FiringTracker
{
	friend class Rva00494C81;
	void coolDown(bool forceReset);
};

class Object
{
public:
	bool setWeaponLock(WeaponSlotType slot, WeaponLockType lock);
	void setWeaponSetFlag(WeaponSetType flag);
	bool addAttributeModifierToPool(const AsciiString &name, int value);
	char m_pad[0x240];
	FiringTracker *m_notify;
};

class UpdateModule
{
	friend class Rva00494C81;

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime when);
};

class Record
{
public:
	char m_pad[0x18];
	AsciiString m_name;
	int m_field1c;
	int m_kind;
	BitFlags<104> m_flags;
};

class Sub
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15(float amount);
};

class Rva00494C81
{
public:
	void rva00494C81(int, int, int, int, int);

private:
	char m_pad0[4];
	Sub m_sub;
	char m_pad8[0x10];
	unsigned char m_flag18;
};

void Rva00494C81::rva00494C81(int, int, int, int, int)
{
	Record *rec = *(Record *volatile *)((char *)this - 0x1c);
	int kind = rec->m_kind;
	Object *obj = *(Object **)((char *)this - 0x18);
	if (kind != 5) {
		obj->setWeaponLock((WeaponSlotType)kind, LOCK_2);
	} else if (rec->m_flags.count() != 0) {
		for (int i = 0; i < 0x68; ++i) {
			if ((*(Record *volatile *)((char *)this - 0x1c))->m_flags.m_words[(unsigned)i >> 5] & (1u << (i & 31)))
				obj->setWeaponSetFlag((WeaponSetType)i);
		}
	}
	rec = *(Record *volatile *)((char *)this - 0x1c);
	AsciiString *name = &rec->m_name;
	if (name->isEmpty() == 0)
		obj->addAttributeModifierToPool(*name, rec->m_field1c);
	rec = *(Record *volatile *)((char *)this - 0x1c);
	((UpdateModule *)((char *)this - 0x20))->setWakeFrame(obj, (UpdateSleepTime)rec->m_field1c);
	m_flag18 = 1;
	m_sub.s15(1.0f);
	obj->m_notify->coolDown(true);
}
