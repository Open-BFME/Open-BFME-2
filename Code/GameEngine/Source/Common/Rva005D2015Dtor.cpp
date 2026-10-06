// cl: /O1 /MD /EHsc
// ??1Rva005D2015@@UAE@XZ retail 0x005D2015 58B
// Own vptr C75778; under EH state 0 the body unregisters this from the +4
// subobject of the object at +8 through the rowed
// ?rva002B7250@Rva002B7250 0x002B7250; the inline base dtor restores
// C6E350. Caller: rowed ??_G 0x005D204F. Names address-derived.

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *who);
};

struct Rva005D2015Owner
{
	int m_00;
	Rva002B7250 m_list; // +0x04
};

class Rva005D2015Base
{
public:
	virtual ~Rva005D2015Base() {}

private:
	int m_04;
};

class Rva005D2015 : public Rva005D2015Base
{
public:
	virtual ~Rva005D2015();

private:
	Rva005D2015Owner *m_owner; // +0x08
};

Rva005D2015::~Rva005D2015()
{
	m_owner->m_list.rva002B7250((CreateAHeroData *)this);
}
