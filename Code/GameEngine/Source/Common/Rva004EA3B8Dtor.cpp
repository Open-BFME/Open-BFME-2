// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva004EA3B8@@UAE@XZ, retail 0x004EA3B8..0x004EA418 (96 bytes, EH): the
// destructor its rowed scalar deleting destructor 0x004EAB6E calls. The
// object has two bases: BaseA (vtable 0x00C62888, inline destructor) and
// Rva00506B1B at +0x0C (vtable 0x00C62894 in this class; its destructor is
// the pinned vtable store 0x00506B28). The body runs the class's override of
// the second base's slot 2 (0x004EA33A, not yet rowed; pinned), which MSVC
// calls on the +0x0C subobject; then the +0x24 vector is freed and both bases
// are torn down (EH states 2, 1, 0). WorldBuilder's twin (0x01381630) is
// unnamed, so the names stay address-derived.

#include <vector>

class BaseA
{
public:
	BaseA() : m_04(2), m_08(1) {}
	virtual void a0();
	virtual void a1();
	virtual ~BaseA() {}
private:
	int m_04;
	int m_08;
};

class Rva00506B1B
{
public:
	Rva00506B1B();
	virtual ~Rva00506B1B();
	virtual void b1();
	virtual void rva004EA33A();
private:
	bool m_04;
};

class Rva004EA3B8 : public BaseA, public Rva00506B1B
{
public:
	Rva004EA3B8(void *owner);
	virtual ~Rva004EA3B8();
	virtual void rva004EA33A();
	void rva004EA420();
private:
	void *m_owner14;						// +0x14
	int m_18;
	int m_1C;
	int m_20;
	_STL::vector<int> m_items24;			// +0x24
};

// ??0Rva004EA3B8@@QAE@PAX@Z, retail 0x004EAAF3..0x004EAB6E (123 bytes, EH,
// RET 4): BaseA (fields 2 and 1; EH state 0), the rowed Rva00506B1B
// constructor 0x00506B1B, the owner and the three scalar fields, both
// vtables, the vector (rowed _Vector_base<int> 0x00211E58; state 2), then the
// class's 0x004EA420 set-up (not yet rowed; pinned).
Rva004EA3B8::Rva004EA3B8(void *owner)
	: m_owner14(owner), m_18(0), m_1C(0), m_20(-1)
{
	rva004EA420();
}

Rva004EA3B8::~Rva004EA3B8()
{
	rva004EA33A();
}
