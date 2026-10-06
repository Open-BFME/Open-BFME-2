// cl: /MD /EHsc /DNDEBUG
//
// ??1Rva0050A7AD@@UAE@XZ retail 0x0050A7AD 56B dtor with filter.
// Evidence: member dtor 0x00360D26 at +0x160; base dtor 0x00507823; caller deleting 0x0050A791.
class Rva00360D26Member
{
public:
	~Rva00360D26Member();
private:
	int m_x;
};

class Rva00507823
{
public:
	virtual ~Rva00507823();
private:
	unsigned char m_pad[0x128 - 4];
};

class __declspec(novtable) Rva0050A7AD : public Rva00507823
{
public:
	virtual ~Rva0050A7AD();
	void *Rva0050A791Release(unsigned int flags);
private:
	char m_pad128[0x160 - 0x128];
	Rva00360D26Member m_160;
};

Rva0050A7AD::~Rva0050A7AD()
{
}

// Retail [0x0050A791..0x0050A7AD) calls this owner's recovered destructor
// directly; flag bit zero then controls scalar operator delete at 0x0002FD60.
// This address-derived method names the observed release behavior without
// asserting the original compiler-generated deleting-destructor symbol.
void *Rva0050A7AD::Rva0050A791Release(unsigned int flags)
{
	this->Rva0050A7AD::~Rva0050A7AD();
	if (flags & 1) ::operator delete(this);
	return this;
}
