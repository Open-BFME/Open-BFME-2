// cl: /O1 /MD /EHsc
// ??1Rva005AFE3F@@UAE@XZ retail 0x005AFE3F 71B
// Own vptr C728B8; under EH state 0 the body unregisters this from the
// registry returned by the rowed getter ?Rva00381452Get 0x00381452 through the
// rowed ?rva002B7250@Rva002B7250 0x002B7250, clears +8/+0xC/+0x10, and the
// inline base dtor restores C6FFFC. Three derived dtors tail-call it.
// Names address-derived.

class CreateAHeroData;

int Rva00381452Get();

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *who);
};

class Rva005AFE3FBase
{
public:
	virtual ~Rva005AFE3FBase() {}

private:
	int m_04;
};

class Rva005AFE3F : public Rva005AFE3FBase
{
public:
	virtual ~Rva005AFE3F();

private:
	int m_08;
	int m_0C;
	int m_10;
};

Rva005AFE3F::~Rva005AFE3F()
{
	((Rva002B7250 *)Rva00381452Get())->rva002B7250((CreateAHeroData *)this);
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
}
