// ??4BfmeAssignRecord28@@QAEAAU0@ABU0@@Z at RVA 0x003F6388, 43 bytes.
// The packet pins the identity from three caller bodies. Its stores and calls
// establish a 4-byte field followed by vector subobjects at offsets 4 and 16;
// the record's field meanings and element layouts remain structural inference.
// cl: /I. /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
// Suppress this TU's non-retail copy of ??4?$vector@URva003F5FD0Record@@V?$allocator@URva003F5FD0Record@@@_STL@@@_STL@@QAEAAV01@AB:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva003F5FD0Record;
namespace _STL { template <> vector<Rva003F5FD0Record,allocator<Rva003F5FD0Record> > & vector<Rva003F5FD0Record,allocator<Rva003F5FD0Record> >::operator=(vector<Rva003F5FD0Record,allocator<Rva003F5FD0Record> > const &); }
// Suppress this TU's non-retail copy of ??$__copy@PBURva003F5FD0Record@@PAU1@H@_STL@@YAPAURva003F5FD0Record@@PBU1@0PAU1@ABUrandom_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva003F5FD0Record;
namespace _STL { template <> Rva003F5FD0Record * __copy<Rva003F5FD0Record const *,Rva003F5FD0Record *,int>(Rva003F5FD0Record const *,Rva003F5FD0Record const *,Rva003F5FD0Record *,random_access_iterator_tag const &,int *); }

#include "../../../../GameEngine/Include/Common/Rva003F5FD0Record.h"
namespace _STL { template<> void _Construct<Rva003F5FD0Record, Rva003F5FD0Record>(Rva003F5FD0Record*, const Rva003F5FD0Record&); }
#include "Rva0021C21BElement.h"
namespace _STL {template<> vector<Rva0021C21BElement>& vector<Rva0021C21BElement>::operator=(const vector<Rva0021C21BElement>&);}


struct BfmeAssignRecord28 {
	unsigned int field;
	_STL::vector<Rva003F5FD0Record, _STL::allocator<Rva003F5FD0Record> > records;
	_STL::vector<Rva0021C21BElement, _STL::allocator<Rva0021C21BElement> > elements;
	BfmeAssignRecord28 &operator=(const BfmeAssignRecord28 &other);
};
 BfmeAssignRecord28 &BfmeAssignRecord28::operator=(const BfmeAssignRecord28 &other)
 {
	field = other.field;
	records = other.records;
	elements = other.elements;
	return *this;
 }
