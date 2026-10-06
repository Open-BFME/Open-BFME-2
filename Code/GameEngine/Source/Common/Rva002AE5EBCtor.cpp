// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva002AE5EB@@QAE@XZ, retail 0x002AE5EB, 54 bytes.
// Ctor stores vtable 0x007FDDB4 at +0 (gate DIR32), int 100 at +4, zeros at
// +8/+14/+18/+1C, vector at +0x20 via rowed Vector_base BfmeE16 0x00211E58
// (allocator temp on esp), bool false at +0x2C. Members at +0xC/+0x10 left
// uninitialized. Called at +0x60 by the 576B parent ctor at 0x002B0F3C.
// BfmeE16 is the 16B stand-in from stlport_vector_e16_o1. Owner identity
// unproven, honest Rva name.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva002AE5EB
{
public:
	Rva002AE5EB();
	virtual ~Rva002AE5EB();
private:
	int m_04; // +0x04, 100
	void *m_08; // +0x08, 0
	int m_0C; // +0x0C, uninitialized
	int m_10; // +0x10, uninitialized
	void *m_14; // +0x14, 0
	void *m_18; // +0x18, 0
	void *m_1C; // +0x1C, 0
	_STL::vector<BfmeE16> m_20; // +0x20
	bool m_2C; // +0x2C, false
};

Rva002AE5EB::Rva002AE5EB()
	: m_04(100),
	  m_08(0),
	  m_14(0),
	  m_18(0),
	  m_1C(0),
	  m_20(_STL::allocator<BfmeE16>()),
	  m_2C(false)
{
}
