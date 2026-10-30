// cl: /Ireference/shims/bfme2_ascii /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4Rva0031804D@@QAEAAV0@ABV0@@Z @0x0031804D (81B): copy-assign copying
// AsciiStrings at +0x4/+0x8 via pinned 0x000366F0, byte +0xC, 4B-POD vector
// at +0x10 via int pin at 0x0021C21B, byte +0x1C, int +0x20, NoCase pair
// vector at +0x24 via rowed 0x00317EBB. Same offsets as Rva00317F6F ctor
// 0x00317F6F; caller at 0x003181C1 unblocks 0x0031816C.
#include "ascii_string.h"
#include <vector>
#include <utility>

enum ScienceType
{
	SCIENCE_NONE = 0
};
struct NoCaseTreeValue4
{
	char m_body[4];
};
// Native 0x0021C21B is owned by the non-POD-traited four-byte record
// specialization in StlSweepW5Rva0021C21B.cpp. Preserve this caller's
// storage and argument ABI while naming the verified out-of-line provider.
struct Rva0021C21BElement { char bytes[4]; };
typedef _STL::vector<Rva0021C21BElement, _STL::allocator<Rva0021C21BElement> > RetailAssignVector;
namespace _STL {
template <> vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &
vector<Rva0021C21BElement, allocator<Rva0021C21BElement> >::operator=(
    const vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &);
}

typedef _STL::vector<_STL::pair<const AsciiString, NoCaseTreeValue4>, _STL::allocator<_STL::pair<const AsciiString, NoCaseTreeValue4> > > RetailNoCaseVector;
namespace _STL {
template <> RetailNoCaseVector &RetailNoCaseVector::operator=(const RetailNoCaseVector &);
}

class TerrainType
{
	friend class TerrainTypeCollection;
public:
	TerrainType();
	virtual ~TerrainType();
	TerrainType &operator=(const TerrainType &that);
	void friend_setName(AsciiString name);
private:
	AsciiString m_str04;
	AsciiString m_str08;
	unsigned char m_f0c;
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_v1;
	unsigned char m_f1c;
	TerrainType *m_next;
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_v2;
};
TerrainType &TerrainType::operator=(const TerrainType &that)
{
	m_str04 = that.m_str04;
	m_str08 = that.m_str08;
	m_f0c = that.m_f0c;
	*(RetailAssignVector *)&m_v1 = *(const RetailAssignVector *)&that.m_v1;
	m_f1c = that.m_f1c;
	m_next = that.m_next;
	*(RetailNoCaseVector *)&m_v2 = *(const RetailNoCaseVector *)&that.m_v2;
	return *this;
}
