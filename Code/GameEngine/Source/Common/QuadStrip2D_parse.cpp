// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?parse@QuadStrip2D@@QAEXAAVDataChunkInput@@H@Z @0x00538A0B 165B
// Holder vector load via DataChunkInput readInt/readReal plus flag at +0x20.
// Evidence: prev 0x005388C2 holder copy same layout region+flag; callees readInt 0x00306E78 readReal 0x00306E56 reserve 0x00538839 push_back 0x00473F13 swap 0x00567ECD; precedent Rva0030BAF8Parse same recipe ret8.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "../../../Libraries/Include/Lib/BfmeE16.h"
struct BfmeFloat4Record00469C61
{
public:
	float x; // +0x00
	float y; // +0x04
	float z; // +0x08
	float w; // +0x0C
};
// reserve 0x00538839 and push_back 0x00473F13 are rowed in
// stlport_vector_float4_469c61.cpp. This unit's own copies of their callees
// (_M_allocate_and_copy, _M_insert_overflow, _Construct) were not retail's.
// Declare both only, so the calls bind to the rowed copies.
namespace _STL {
template <> void vector<BfmeFloat4Record00469C61, allocator<BfmeFloat4Record00469C61> >::reserve(size_t);
template <> void vector<BfmeFloat4Record00469C61, allocator<BfmeFloat4Record00469C61> >::push_back(const BfmeFloat4Record00469C61 &);
}
struct BfmeE12 { int a[3]; };
class DataChunkInput
{
public:
	int readInt();
	float readReal();
};
struct QuadStrip2D
{
	QuadStrip2D(const QuadStrip2D &other);
	void parse(DataChunkInput &file, int unused);
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec;
	char m_pad[0x20 - 12];
	bool m_20;
};
void QuadStrip2D::parse(DataChunkInput &file, int unused)
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
	m_20 = true;
}
