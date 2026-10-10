// cl: /MD /Oy- /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva004E61C8@@UAE@XZ @0x004E61C8 105B: dtor stores vtable calls 0x4E5D6E deletes +0xc virtual result vector auto frees +0x10 base SubsystemInterface
#include <vector>

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	char m_pad04[4];
	class AsciiStringMember
	{
	public:
		~AsciiStringMember();
	} m_member08;
};

class Rva004E5D6E
{
public:
	void rva004E5D6E();
};

struct Rva004E61C8Inner
{
	virtual void *v0(int x);
};

void __cdecl operator delete(void *p);

class Rva004E61C8 : public SubsystemInterface
{
public:
	virtual ~Rva004E61C8();
private:
	Rva004E61C8Inner *m_c; // +0xc
	_STL::vector<void *, _STL::allocator<void *> > m_vec; // +0x10
	int m_1c;
	int m_20;
	int m_24;
};

Rva004E61C8::~Rva004E61C8()
{
	((Rva004E5D6E *)this)->rva004E5D6E();
	void *p;
	if (m_c != 0)
		p = m_c->v0(0);
	else
		p = 0;
	::operator delete(p);
	m_c = 0;
}
