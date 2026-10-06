// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0040394A@@QAE@XZ @0x0040394A 22B
// Default ctor: default-constructs the 12B vector at +8 through the rowed
// Vector_base<BfmeE16> ctor 0x00211E58; scalars at +0/+4 are left alone.
// Evidence: caller 0x004045B4 builds a 20B record at ebp-0x20, fills int at
// +0 and float at +4 after this call, then assigns a vector<AsciiString>
// over +8 and pushes the record into the stride-0x14 Rva00403927 array.
// Member is spelled vector<BfmeE16> so the implicit base call mangles to
// the rowed callee name; element width is irrelevant to these bytes since
// the base ctor only zeroes three pointers. Honest Rva owner name: no
// vtable or export proves the class.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva0040394A
{
public:
	Rva0040394A();
private:
	int m_00;
	int m_04;
	_STL::vector<BfmeE16> m_vec;
};

Rva0040394A::Rva0040394A()
{
}
