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
	virtual ~Rva00506B1B();
	virtual void b1();
	virtual void rva004EA33A();
private:
	unsigned char m_pad04[0x18 - 0x04];
};

class Rva004EA3B8 : public BaseA, public Rva00506B1B
{
public:
	virtual ~Rva004EA3B8();
	virtual void rva004EA33A();
private:
	_STL::vector<int> m_items24;			// +0x24
};

Rva004EA3B8::~Rva004EA3B8()
{
	rva004EA33A();
}
