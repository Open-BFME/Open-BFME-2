// Reference: pristine STLport4.5.3. Address-derived opaque record ABI.
// Target boundary and literal pointer stride establish storage width only; no application identity inferred.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <stl/_algobase.h>
#include <vector>

struct Rva000B978ARecord { Rva000B978ARecord(); Rva000B978ARecord(const Rva000B978ARecord&); ~Rva000B978ARecord(); Rva000B978ARecord&operator=(const Rva000B978ARecord&); private: char bytes[24]; };
namespace _STL {template<> void _Construct<Rva000B978ARecord,Rva000B978ARecord>(Rva000B978ARecord*,const Rva000B978ARecord&);}
template Rva000B978ARecord *_STL::__copy(Rva000B978ARecord*,Rva000B978ARecord*,Rva000B978ARecord*,const _STL::random_access_iterator_tag&,int*);

// Native record assignment at0x000B68F0 is resolved by its actual name.
