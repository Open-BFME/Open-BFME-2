// ?rva00494C81@Rva00494C81@@QAEXHHHHH@Z
// partial score=0.98 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// class-gate: allow AsciiString address-only view for isEmpty.
//
// ?rva00494C81@Rva00494C81@@QAEXHHHHH@Z @0x00494C81 165B ret 0x14.
// Kind 5 walks the bit words at record+0x24. Otherwise the kind is a
// weapon-slot lock. Then the record name, wake frame, slot 15, and the
// +0x240 notify.

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

class AsciiString
{
public:
	bool isEmpty() const;
};

class BitFlags
{
public:
	int rva0028F6EB();
	unsigned int m_words[8];
};

class Rva004DEC88
{
public:
	void rva004DEC88(int flag);
};

class Object
{
public:
	bool setWeaponLock(WeaponSlotType slot, WeaponLockType lock);
	void setWeaponSetFlag(WeaponSetType flag);
	bool rva0028EA91(const AsciiString &name, int value);

	char m_pad[0x240];
	Rva004DEC88 *m_notify;
};

class Rva00494C81;

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
	char m_name[4];
	int m_field1c;
	int m_kind;
	BitFlags m_flags;
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
	} else if (rec->m_flags.rva0028F6EB() != 0) {
		for (int i = 0; i < 0x68; ++i) {
			int bit = 1 << (i & 31);
			Record *cur = *(Record *volatile *)((char *)this - 0x1c);
			if (cur->m_flags.m_words[(unsigned)i >> 5] & (unsigned)bit)
				obj->setWeaponSetFlag((WeaponSetType)i);
		}
	}
	rec = *(Record *volatile *)((char *)this - 0x1c);
	AsciiString *name = (AsciiString *)((char *)rec + 0x18);
	if (name->isEmpty() == 0)
		obj->rva0028EA91(*name, rec->m_field1c);
	rec = *(Record *volatile *)((char *)this - 0x1c);
	((UpdateModule *)((char *)this - 0x20))->setWakeFrame(obj, (UpdateSleepTime)rec->m_field1c);
	m_flag18 = 1;
	m_sub.s15(1.0f);
	obj->m_notify->rva004DEC88(1);
}
