// cl: /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva0053ED1A@@UAE@XZ @0x0053ED78 90B dtor installs vtables plus frees vector buffer plus secondary plus base via caller ??_G 0x0053EF12. Evidence: pin plus vtable slots plus rowed base SubsystemInterface plus twin-pinned secondary Rva005C6D4D at 0x005C6C7B plus rowed _free.
#include <vector>

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
private:
	char m_pad04[8];
};

class Rva005C6D4D
{
public:
	Rva005C6D4D();
	virtual ~Rva005C6D4D();
private:
	char m_pad04[0x38];
};

class Rva0053ED1A : public SubsystemInterface, public Rva005C6D4D
{
public:
	Rva0053ED1A();
	virtual ~Rva0053ED1A();
private:
	_STL::vector<int> m_at48;
	int m_at54;
	int m_at58;
};

Rva0053ED1A::~Rva0053ED1A()
{
}
