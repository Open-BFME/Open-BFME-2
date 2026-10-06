// cl: /MD
// stlport
//
// ??0Rva002CEC0A@@QAE@XZ @0x002CEBEE 28B: ctor storing vtable 0x0080222C
// and constructing the vector member at +0x04 via the rowed empty
// Vector_base<BfmeE16> at 0x00211E58 (ICF-folded with the AsciiString
// spelling used by the dtor at 0x002CEC0A, clear at 0x002CEC34 and xfer at
// 0x002CED26). Same class as Rva002CEC0ADtor.cpp. Caller at 0x0022E53F
// proves a thiscall void ctor; honest address-class naming.
#include <vector>

struct BfmeE16
{
	float x, y, z, w;
};

class Rva002CEC0A
{
public:
	Rva002CEC0A();
	virtual ~Rva002CEC0A();

private:
	_STL::vector<BfmeE16> m_vec04;
};

Rva002CEC0A::Rva002CEC0A()
{
}
