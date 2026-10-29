// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??4Rva001FFEE9@@QAEAAV0@ABV0@@Z @0x001FFEE9 81B
// Copy-assign with 0x10 pad then int plus two UnicodeString via rowed set plus custom plus1C via pinned 0x1FFD6B plus tail ints/byte; base 5B ICF via pinned placeholder 0x1FD28E; 8B pad20 unproven gap; UnicodeString 4B for plus18.
class FXParticleSystem
{
public:
	template <int N> class CategoryModuleInfo
	{
	public:
		CategoryModuleInfo &operator=(const CategoryModuleInfo &that);
	};
};
struct Rva001FFD6BRecord;
#include <vector>

namespace _STL {
// Bind the assignment to the kept vector copy-assignment worker.
template <> vector<Rva001FFD6BRecord, allocator<Rva001FFD6BRecord> > &vector<Rva001FFD6BRecord, allocator<Rva001FFD6BRecord> >::operator=(const vector<Rva001FFD6BRecord, allocator<Rva001FFD6BRecord> > &that);
}
typedef _STL::vector<Rva001FFD6BRecord, _STL::allocator<Rva001FFD6BRecord> > Rva001FFD6BRecordVector;
// UnicodeString is StringBase<WideChar>; its set is the inherited
// StringBase<unsigned short>::set, the row at 0x00037150 the calls land on.
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"
class Rva001FFEE9
{
public:
	Rva001FFEE9 &operator=(const Rva001FFEE9 &that);
private:
	char m_pad00[0x10];
	int m_10;
	UnicodeString m_14;
	UnicodeString m_18;
	char m_1C[4];
	char m_pad20[8];
	int m_28;
	int m_2C;
	unsigned char m_30;
};
Rva001FFEE9 &Rva001FFEE9::operator=(const Rva001FFEE9 &that)
{
	*(FXParticleSystem::CategoryModuleInfo<0> *)this = *(const FXParticleSystem::CategoryModuleInfo<0> *)&that;
	m_10 = that.m_10;
	m_14.set(that.m_14);
	m_18.set(that.m_18);
	*(Rva001FFD6BRecordVector *)&m_1C = *(const Rva001FFD6BRecordVector *)&that.m_1C;
	m_28 = that.m_28;
	m_2C = that.m_2C;
	m_30 = that.m_30;
	return *this;
}