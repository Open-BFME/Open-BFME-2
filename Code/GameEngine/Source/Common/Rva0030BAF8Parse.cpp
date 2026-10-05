// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030BAF8@Rva0030BAF8@@QAEXAAVDataChunkInput@@H@Z, retail 0x0030BAF8, 143 bytes.
// Holder vector swap via DataChunkInput readInt/readReal plus flag at +0x24.
// Evidence: prev 0x0030BAA0 same holder same flags; caller 0x0030BB87 forwards DataChunkInput plus 1; callees readInt 0x00306E78 readReal 0x00306E56 reserve 0x0030B876 push_back 0x00539A2E swap 0x00567ECD.
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
struct BfmeE8 { float x; float y; };
struct BfmeE12 { int a[3]; };
class DataChunkInput
{
public:
	int readInt();
	float readReal();
};
struct Rva0030BAF8
{
	void rva0030BAF8(DataChunkInput &file, int unused);
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_vec;
	char m_pad[0x24 - 12];
	bool m_flag;
};
void Rva0030BAF8::rva0030BAF8(DataChunkInput &file, int unused)
{
	int count = file.readInt();
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > tmp;
	tmp.reserve(count);
	while (count > 0) {
		BfmeE8 e;
		e.x = file.readReal();
		e.y = file.readReal();
		tmp.push_back(e);
		--count;
	}
	(((_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > *)&m_vec)->swap(*(_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > *)&tmp));
	m_flag = true;
}
