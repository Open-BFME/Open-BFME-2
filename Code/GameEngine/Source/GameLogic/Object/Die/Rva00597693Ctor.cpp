// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00597693@@QAE@PAX@Z @0x00597693 128B: ctor with EH prolog building Rva00506B1B at +0xc and three Vector_base<BfmeE16> at +0x18/+0x24/+0x30 via rowed 0x00506B1B and 0x00211E58; caller 0x004EC4B7
#include <vector>

struct BfmeE16 { float x, y, z, w; };

struct EmptyBase
{
	EmptyBase() {}
	~EmptyBase();
};

class BaseA
{
public:
	virtual void v0();
	int m_04;
	int m_08;
	BaseA() : m_04(1), m_08(2) {}
};

class Rva00506B1B
{
public:
	Rva00506B1B();
	virtual void v0();
	virtual void v1();
	bool m_04;
};

class Rva00597693 : public BaseA, public EmptyBase, public Rva00506B1B
{
public:
	virtual void v2();
	Rva00597693(void *p);
private:
	void *m_14;
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_vec18;
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_vec24;
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_vec30;
	int m_3c;
};

Rva00597693::Rva00597693(void *p)
	: BaseA()
	, Rva00506B1B()
	, m_14(p)
	, m_vec18(_STL::allocator<BfmeE16>())
	, m_vec24(_STL::allocator<BfmeE16>())
	, m_vec30(_STL::allocator<BfmeE16>())
	, m_3c(0)
{
}
