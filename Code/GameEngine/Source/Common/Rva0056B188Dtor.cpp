// cl: /MD /EHsc
// ??1Rva0056B188@@UAE@XZ retail 0x0056B188 98B
// Own vptrs C6D3A8 (+0), C6D36C (+8, inside the first base) and C6D35C
// (+0x14, second base). Under EH state 1, when the owner at +0x18 is set the
// +0x14 subobject is unregistered from the list at +4 of that owner through
// the rowed ?rva002B7250@Rva002B7250 0x002B7250 and the pointer is cleared;
// the second base's inline dtor restores BC6F34 and the rowed first-base dtor
// ??1Rva0056AC26@@UAE@XZ 0x0056AC26 runs. Names address-derived.

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *who);
};

struct Rva0056B188Owner
{
	int m_00;
	Rva002B7250 m_list; // +0x04
};

class Rva0056AC26A
{
public:
	virtual ~Rva0056AC26A();

private:
	int m_04;
};

class Rva0056AC26B
{
public:
	virtual ~Rva0056AC26B();

private:
	int m_04;
	int m_08;
};

class Rva0056AC26 : public Rva0056AC26A, public Rva0056AC26B
{
public:
	virtual ~Rva0056AC26();
};

class Rva0056B188Second
{
public:
	virtual ~Rva0056B188Second() {}

protected:
	Rva0056B188Owner *m_owner; // +0x04 in this base, +0x18 overall
};

class Rva0056B188 : public Rva0056AC26, public Rva0056B188Second
{
public:
	virtual ~Rva0056B188();
};

Rva0056B188::~Rva0056B188()
{
	if (m_owner)
	{
		m_owner->m_list.rva002B7250((CreateAHeroData *)static_cast<Rva0056B188Second *>(this));
		m_owner = 0;
	}
}
