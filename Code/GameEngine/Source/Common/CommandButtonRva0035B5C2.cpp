// cl: /O1 /arch:SSE /G7 /MD /EHsc
// ?rva0035B5C2@CommandButton@@QAEXPAVObject@@_N@Z @0x0035B5C2 246B
// Banked attempt reverse/attempts/0x0035b5c2.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
// 0x0035B5C2 / 246 bytes. CommandButton ownership is inferred from adjacent
// getStance and the callers' shared this pointer. Field roles and render-data
// virtual slot are inferred from retail accesses; the method keeps an address name.

enum ObjectStatusTypes { STATUS_0035B5C2 = 0x17 };
enum KindOfType { KIND_0035B5C2_A = 0x91, KIND_0035B5C2_B = 0x92 };

class Rva0035B5C2RenderData
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual void slot6C(); virtual void slot70(); virtual void slot74();
	virtual void slot78(); virtual void slot7C(); virtual void slot80();
	virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98();
	virtual void slot9C(); virtual void slotA0(); virtual void slotA4();
	virtual void slotA8(); virtual void slotAC(); virtual void slotB0();
	virtual void slotB4(); virtual void slotB8(); virtual void slotBC();
	virtual void slotC0(); virtual void slotC4(); virtual void slotC8();
	virtual void slotCC(); virtual void slotD0(); virtual void slotD4();
	virtual void slotD8(); virtual void slotDC(); virtual void slotE0();
	virtual void slotE4(); virtual void slotE8();
	virtual bool matches();
};

class Object
{
public:
	Object *rva002931F5(bool arg);
	void *rva0028C197() const;
	bool testStatus(ObjectStatusTypes status) const;
	bool isKindOf(KindOfType kind) const;
};

class Rva0028B7AELeaGetter
{
public:
	void *get() const;
};

class Rva00331682Holder
{
public:
	bool test(const void *value) const;
};

struct Rva0035B5C2PointerRange
{
	void **begin;
	void **end;
	void **capacity;
	unsigned int size() const { return (unsigned int)(end - begin); }
};

class CommandButton
{
public:
	void rva0035B5C2(Object *object, bool value);

private:
	unsigned char m_pad00[0x14];
	int m_stance;
	unsigned char m_pad18[4];
	unsigned int m_flags;
	unsigned char m_pad20[0x64];
	int m_value84;
	int m_value88;
	int m_value8C;
	unsigned char m_objectFilter[4];
	unsigned char m_pad94[0x58];
	Rva0035B5C2PointerRange m_required;
	int m_padF8;
	int m_cachedAvailability;
};

void CommandButton::rva0035B5C2(Object *object, bool value)
{
	if (object == 0)
		return;
	if (m_required.size() < 2)
	{
		m_cachedAvailability = 0;
		return;
	}
	if (m_flags & 0x01000000)
	{
		Rva0028B7AELeaGetter *getter = (Rva0028B7AELeaGetter *)object;
		Rva00331682Holder *holder = (Rva00331682Holder *)getter->get();
		m_cachedAvailability = holder->test(m_objectFilter) != value;
		return;
	}
	if (m_flags & 0x02000000)
	{
		Object *target = object->rva002931F5(false);
		if (target)
		{
			Rva0035B5C2RenderData *data = (Rva0035B5C2RenderData *)target->rva0028C197();
			if (data)
				m_cachedAvailability = data->matches() == value;
		}
		return;
	}
	if (m_flags & 0x00800000)
	{
		if (m_stance != 0x23)
		{
			if (m_stance == 0x30)
				m_cachedAvailability = object->testStatus(STATUS_0035B5C2) == value;
		}
		else
		{
			if (object->isKindOf(KIND_0035B5C2_A))
				m_cachedAvailability = m_value88;
			else if (object->isKindOf(KIND_0035B5C2_B))
				m_cachedAvailability = m_value8C;
			else
				m_cachedAvailability = m_value84;
		}
	}
}
