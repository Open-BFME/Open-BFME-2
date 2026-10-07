// ??4BfmeAssignRecord28@@QAEAAU0@ABU0@@Z at RVA 0x003F6388, 43 bytes.
// The packet pins the identity from three caller bodies. Its stores and calls
// establish a 4-byte field followed by vector subobjects at offsets 4 and 16;
// the record's field meanings and element layouts remain structural inference.
// cl: /I. /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva003F5FD0Record { Rva003F5FD0Record(); Rva003F5FD0Record(const Rva003F5FD0Record&); ~Rva003F5FD0Record(); Rva003F5FD0Record& operator=(const Rva003F5FD0Record&); char bytes[48]; };
namespace _STL { template<> void _Construct<Rva003F5FD0Record, Rva003F5FD0Record>(Rva003F5FD0Record*, const Rva003F5FD0Record&); }
struct Rva0021C21BElement { char bytes[4]; };

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
