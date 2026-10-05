// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /MD /EHsc /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva00082EF5@@QAE@PAX@Z @0x00082EF5 117B: MI ctor with second base at +8 plus vector float bool plus list append and init call. Evidence: vtable stores plus vector base row plus append row plus pin 0x82D6A plus callers 0x82F81 0x8355E.
#include <vector>
struct BfmeE16 { float x, y, z, w; };

struct Rva002BA8F1Listener { char opaque[4]; };
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
};

class Rva00082D6A
{
public:
	void rva00082D6A();
};

class Rva00082EF5Second
{
public:
	Rva00082EF5Second() {}
	virtual ~Rva00082EF5Second();
};

class Rva00082EF5Base1
{
public:
	Rva00082EF5Base1() : m_04(0) {}
	virtual ~Rva00082EF5Base1() {}
	int m_04;
};

class Rva00082EF5 : public Rva00082EF5Base1, public Rva00082EF5Second
{
public:
	Rva00082EF5(void *mgr);
	virtual ~Rva00082EF5();
private:
	void *m_mgr0C;
	float m_flt10;
	_STL::vector<BfmeE16> m_vec14;
	bool m_flag20;
};

Rva00082EF5::Rva00082EF5(void *mgr)
	: Rva00082EF5Base1()
	, Rva00082EF5Second()
	, m_mgr0C(mgr)
	, m_flt10(0.0f)
	, m_vec14()
	, m_flag20(false)
{
	((Rva005A0B4CList *)((char *)mgr + 8))->append((Rva002BA8F1Listener *)((char *)this + 8));
	((Rva00082D6A *)this)->rva00082D6A();
}
