// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <hash_map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }

struct Rva00212A16Record { char bytes[1]; };

// Retail 0x00212A16 resizes through 0x00212858, hashes the key through 0x00223149
// and allocates the node through 0x00212354, all rowed as Rva000427195 methods
// (Rva00212858Resize.cpp, PlayerXferStringMaps.cpp, Rva00212354NewNode.cpp; the
// same three calls as the rowed twin Rva000A7A63Insert.cpp). Instantiating
// _M_insert over this unit's record emitted non-retail resize/_M_bkt_num_key/
// _M_new_node copies and left the record's hash, copy ctor and dtor unresolved,
// so _M_insert is defined here as an explicit specialization that calls those rows.
class AsciiString;
#include "../../../../GameEngine/Include/GameLogic/Rva000427195.h"
namespace _STL {
typedef pair<Rva00212A16Record const, Rva00212A16Record> Rva00212A16Pair;
template <>
Rva00212A16Pair &hashtable<Rva00212A16Pair, Rva00212A16Record, hash<Rva00212A16Record>, _Select1st<Rva00212A16Pair>, equal_to<Rva00212A16Record>, allocator<Rva00212A16Pair> >::_M_insert(const value_type &obj)
{
    Rva000427195 *self = (Rva000427195 *)this;
    self->rva00212858(_M_num_elements._M_data + 1);
    const size_type n = self->bucketIndex((const AsciiString *)&obj);
    _Node *first = (_Node *)_M_buckets[n];
    _Node *tmp = (_Node *)self->rva00212354(&obj);
    tmp->_M_next = first;
    _M_buckets[n] = tmp;
    ++_M_num_elements._M_data;
    return tmp->_M_val;
}
}
