// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ICF twin of ??4Rva0051F87B@@QAEAAV0@ABV0@@Z (0x0051F972,
// Rva0051F87BAssign.cpp): the element of the STLport sweep at 0x0051FC54 is
// the same 0x50-byte record, and its assignment is that body. Same flags
// and layout as the owner.
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"
// Suppress this TU's non-retail copy of ??4?$vector@URva0026F4F4Element@@V?$allocator@URva0026F4F4Element@@@_STL@@@_STL@@QAEAAV01@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0026F4F4Element;
namespace _STL { template <> vector<Rva0026F4F4Element,allocator<Rva0026F4F4Element> > & vector<Rva0026F4F4Element,allocator<Rva0026F4F4Element> >::operator=(vector<Rva0026F4F4Element,allocator<Rva0026F4F4Element> > const &); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@URva0051F7ADRecord@@V?$allocator@URva0051F7ADRecord@@@_STL@@@_STL@@IAEX:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0051F7ADRecord;
namespace _STL { template <> void vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> >::_M_clear(); }
// Suppress this TU's non-retail copy of ??$_M_allocate_and_copy@PBURva0051F7ADRecord@@@?$vector@URva0051F7ADRecord@@V?$allocator@U:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0051F7ADRecord;
namespace _STL { template <> template <> Rva0051F7ADRecord * vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> >::_M_allocate_and_copy<Rva0051F7ADRecord const *>(unsigned int,Rva0051F7ADRecord const *,Rva0051F7ADRecord const *); }
// Suppress this TU's non-retail copy of ??4?$vector@URva0051F7ADRecord@@V?$allocator@URva0051F7ADRecord@@@_STL@@@_STL@@QAEAAV01@AB:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0051F7ADRecord;
namespace _STL { template <> vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> > & vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> >::operator=(vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> > const &); }
// Suppress this TU's non-retail copy of ??$__copy@PBURva0051F7ADRecord@@PAU1@H@_STL@@YAPAURva0051F7ADRecord@@PBU1@0PAU1@ABUrandom_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0051F7ADRecord;
namespace _STL { template <> Rva0051F7ADRecord * __copy<Rva0051F7ADRecord const *,Rva0051F7ADRecord *,int>(Rva0051F7ADRecord const *,Rva0051F7ADRecord const *,Rva0051F7ADRecord *,random_access_iterator_tag const &,int *); }

class Rva0051F6DF
{
public:
	Rva0051F6DF &operator=(const Rva0051F6DF &other);
private:
	char m_data[12];
};

struct Rva0051F7ADRecord
{
	char bytes[12];
};
// vector<Rva0051F7ADRecord>::operator= is rowed at 0x0051F7AD
// (AptTimeLine.cpp); declared only, so this unit emits no copy of it
// nor of the _Destroy and __uninitialized_copy it would pull in.
namespace _STL { template <> vector<Rva0051F7ADRecord, allocator<Rva0051F7ADRecord> > &vector<Rva0051F7ADRecord, allocator<Rva0051F7ADRecord> >::operator=(const vector<Rva0051F7ADRecord, allocator<Rva0051F7ADRecord> > &); }

struct Rva0026F4F4Element
{
	unsigned words[1];
};

struct Rva0051FC54Element
{
public:
	virtual ~Rva0051FC54Element();
	Rva0051FC54Element &operator=(const Rva0051FC54Element &other);
private:
	UnicodeString m_04;
	int m_08;
	AsciiString m_0C;
	int m_10;
	Rva0051F6DF m_14;
	_STL::vector<Rva0051F7ADRecord, _STL::allocator<Rva0051F7ADRecord> > m_20;
	_STL::vector<Rva0026F4F4Element, _STL::allocator<Rva0026F4F4Element> > m_2C;
	_STL::vector<Rva0026F4F4Element, _STL::allocator<Rva0026F4F4Element> > m_38;
	_STL::vector<Rva0026F4F4Element, _STL::allocator<Rva0026F4F4Element> > m_44;
};

Rva0051FC54Element &Rva0051FC54Element::operator=(const Rva0051FC54Element &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_20 = other.m_20;
	m_2C = other.m_2C;
	m_38 = other.m_38;
	m_44 = other.m_44;
	return *this;
}
