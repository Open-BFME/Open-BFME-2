// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00538A0B@Rva005388C2@@QAEXAAVDataChunkInput@@H@Z @0x00538A0B 165B
// Holder vector load via DataChunkInput readInt/readReal plus flag at +0x20.
// Evidence: prev 0x005388C2 holder copy same layout region+flag; callees readInt 0x00306E78 readReal 0x00306E56 reserve 0x00538839 push_back 0x00473F13 swap 0x00567ECD; precedent Rva0030BAF8Parse same recipe ret8.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
struct BfmeE16 { float x, y, z, w; };
struct BfmeFloat4Record00469C61 { float x, y, z, w; };
struct BfmeE12 { int a[3]; };
class DataChunkInput
{
public:
	int readInt();
	float readReal();
};
struct Rva005388C2
{
	void rva00538A0B(DataChunkInput &file, int unused);
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec;
	char m_pad[0x20 - 12];
	bool m_flag;
};
void Rva005388C2::rva00538A0B(DataChunkInput &file, int unused)
{
	int count = file.readInt();
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > tmp;
	((_STL::vector<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> > *)&tmp)->reserve(count);
	while (count > 0) {
		BfmeE16 e;
		e.x = file.readReal();
		e.y = file.readReal();
		e.z = file.readReal();
		e.w = file.readReal();
		((_STL::vector<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> > *)&tmp)->push_back(*(_STL::vector<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> >::value_type *)&e);
		--count;
	}
	((_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > *)&m_vec)->swap(*(_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > *)&tmp);
	m_flag = true;
}
