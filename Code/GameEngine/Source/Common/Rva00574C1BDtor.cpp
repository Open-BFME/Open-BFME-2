// cl: /O1 /MD /EHsc
// ??1Rva00574C1B@@UAE@XZ retail 0x00574C1B 83B
// Two-base dtor: own vptrs C6E4A4 (+0) and C6E4C0 (+0x10); under EH state 1
// the +0x10 subobject is unregistered from the list at +4 of the owner held
// at +0x14 through the rowed ?rva002B7250@Rva002B7250 0x002B7250; the second
// base's inline dtor restores C6E360 and the pinned first-base dtor
// ??1Rva005746AF@@UAE@XZ 0x005746D2 runs. Names address-derived.

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *who);
};

struct Rva00574C1BOwner
{
	int m_00;
	Rva002B7250 m_list; // +0x04
};

class Rva005746AF
{
public:
	virtual ~Rva005746AF();

private:
	unsigned char m_pad04[0x10 - 4];
};

class Rva00574C1BSecond
{
public:
	virtual ~Rva00574C1BSecond() {}

protected:
	Rva00574C1BOwner *m_owner; // +0x04 in this base, +0x14 overall
};

class Rva00574C1B : public Rva005746AF, public Rva00574C1BSecond
{
public:
	virtual ~Rva00574C1B();
};

Rva00574C1B::~Rva00574C1B()
{
	m_owner->m_list.rva002B7250((CreateAHeroData *)static_cast<Rva00574C1BSecond *>(this));
}
