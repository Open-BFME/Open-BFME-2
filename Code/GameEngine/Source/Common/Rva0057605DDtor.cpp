// cl: /MD /EHsc
// ??1Rva0057605D@@UAE@XZ retail 0x00575E9C 78B
// Two-base dtor: own vptrs C6E6A0 at +0 and C6E690 at +8; under EH state 1
// the body unregisters the +8 subobject from the list at +8 of the object
// held at +0xC through the rowed ?rva002B7250@Rva002B7250 0x002B7250; the
// inline base dtors then restore C77F44 (+8) and C6E60C (+0). Caller: rowed
// ??_GRva0057605D 0x005760B1. Names address-derived.

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *who);
};

struct Rva0057605DOwner
{
	unsigned char m_pad[8];
	Rva002B7250 m_list; // +0x08
};

class Rva0057605DBase
{
public:
	virtual ~Rva0057605DBase() {}

private:
	int m_04;
};

class Rva0057605DSecond
{
public:
	Rva0057605DSecond();
	virtual ~Rva0057605DSecond() {}

protected:
	Rva0057605DOwner *m_owner; // +0x04 in this base, +0x0C overall
};
// ??0Rva0057605DSecond@@QAE@XZ @0x002B251A 9B: the default constructor, storing the
// class's own vtable (VA 0x00C77F44) and returning this.
Rva0057605DSecond::Rva0057605DSecond()
{
}

class Rva0057605D : public Rva0057605DBase, public Rva0057605DSecond
{
public:
	virtual ~Rva0057605D();
};

Rva0057605D::~Rva0057605D()
{
	m_owner->m_list.rva002B7250((CreateAHeroData *)static_cast<Rva0057605DSecond *>(this));
}
