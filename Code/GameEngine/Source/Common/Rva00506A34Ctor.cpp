// cl: /MD
// stlport
// ??0Rva00506A34@@QAE@PAX@Z @0x00506A34 30B: holder ctor storing void* at +0
// then default vector<BfmeE16> at +4 via rowed Vector_base 0x00211E58 with
// one-byte stack allocator temp at [ebp+0xb]. Size 0x10 proven by new 0x10
// at caller 0x002C618F. Prev Rva00506A0C /O1 /MD next Rva00506B1B /O1 /MD.
// Honest address-derived name; BfmeE16 is the 16B stand-in from
// stlport_vector_e16_o1.cpp.
#include <vector>
struct BfmeE16 { float x; float y; float z; float w; };
class Rva00506A34
{
public:
	Rva00506A34(void *a);
private:
	void *m_00;
	_STL::vector<BfmeE16> m_04;
};

Rva00506A34::Rva00506A34(void *a)
	: m_00(a)
{
}
