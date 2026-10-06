// cl: /O1 /MD /EHsc
// ??1Rva005D1D38@@UAE@XZ retail 0x005D1D38 87B
// Two-base dtor: own vptrs C75734 (+0) and C7572C (+0xC); under EH state 1,
// when the owner at +0x14 is set, the +0xC subobject is unregistered from the
// list at +8 of that owner through the rowed ?rva002B7250@Rva002B7250
// 0x002B7250; the second base's inline dtor restores C75284 and the pinned
// first-base dtor ??1Rva005CCDDD@@UAE@XZ 0x005CCDDD runs. Caller: rowed ??_G
// 0x005D1DAF (vtable 0x00C75734). Names address-derived.

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *who);
};

struct Rva005D1D38Owner
{
	int m_00;
	int m_04;
	Rva002B7250 m_list; // +0x08
};

class Rva005CCDDD
{
public:
	virtual ~Rva005CCDDD();

private:
	int m_04;
	int m_08;
};

class Rva005D1D38Second
{
public:
	virtual ~Rva005D1D38Second() {}

protected:
	int m_04;
	Rva005D1D38Owner *m_owner; // +0x08 in this base, +0x14 overall
};

class Rva005D1D38 : public Rva005CCDDD, public Rva005D1D38Second
{
public:
	virtual ~Rva005D1D38();
};

Rva005D1D38::~Rva005D1D38()
{
	if (m_owner)
		m_owner->m_list.rva002B7250((CreateAHeroData *)static_cast<Rva005D1D38Second *>(this));
}
