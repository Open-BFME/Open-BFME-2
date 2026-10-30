// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?parse@AreaPolygonBase@@QAEXAAVDataChunkInput@@H@Z, retail 0x0030BAF8, 143 bytes.
// Holder vector swap via DataChunkInput readInt/readReal plus flag at +0x24.
// Evidence: prev 0x0030BAA0 same holder same flags; caller 0x0030BB87 forwards DataChunkInput plus 1; callees readInt 0x00306E78 readReal 0x00306E56 reserve 0x0030B876 push_back 0x00539A2E swap 0x00567ECD.
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
struct BfmeE8 { float x; float y; };
// bfme link decl-only begin
// The rowed body calls the 8-byte push_back 0x00539A2E
// (stlport_vector_e8_allocate_copy.cpp); this unit's /EH copy of its
// _M_insert_overflow is not retail's 0x00057C80, so it emits neither.
namespace _STL { template <> void vector<BfmeE8, allocator<BfmeE8> >::push_back(BfmeE8 const &); }
// Likewise reserve 0x0030B876, whose _M_allocate_and_copy copy here is not retail's.
namespace _STL { template <> void vector<BfmeE8, allocator<BfmeE8> >::reserve(unsigned int); }
// bfme link decl-only end
struct BfmeE12 { int a[3]; };
class DataChunkInput
{
public:
	int readInt();
	float readReal();
};
struct AreaPolygonBounds { float v[4]; };
struct AreaPolygonBase
{
	_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > m_points;
	AreaPolygonBounds m_bounds;
	float m_1c;
	float m_20;
	bool m_dirty;
	void parse(DataChunkInput &file, int unused);
};
void AreaPolygonBase::parse(DataChunkInput &file, int unused)
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
	(((_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > *)&m_points)->swap(*(_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > *)&tmp));
	m_dirty = true;
}
