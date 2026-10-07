// cl: /DNDEBUG /MD /EHsc /O1 /G7
//
// Target facts from the 75-byte interval at 0x0013132D: if this+0x10 is null
// it returns without touching the other fields. Otherwise it calls vtable
// slots +0x2C and +0x34 on that object and stores the results at +0x18 and
// +0x14, then clears +0x10. It next refreshes +0x24 and +0x20 through the same
// two slots on this+0x1C and clears +0x1C; when +0x1C is null it zeros both
// result fields. Owner identity and interface names remain unproven. The
// interface layout below only records the observed vtable offsets and returns.

class Rva0013132DInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual int slot2C() = 0;
	virtual void slot30() = 0;
	virtual int slot34() = 0;
};

class Rva0013132DTarget
{
public:
	void rva0013132D();

private:
	char m_pad00[0x10];
	Rva0013132DInterface *m_primary;
	int m_result14;
	int m_result18;
	Rva0013132DInterface *m_secondary;
	int m_result20;
	int m_result24;
};

void Rva0013132DTarget::rva0013132D()
{
	if (m_primary == 0) {
		return;
	}

	m_result18 = m_primary->slot2C();
	m_result14 = m_primary->slot34();
	m_primary = 0;
	if (m_secondary != 0) {
		m_result24 = m_secondary->slot2C();
		m_result20 = m_secondary->slot34();
		m_secondary = 0;
	} else {
		m_result24 = 0;
		m_result20 = 0;
	}
}
