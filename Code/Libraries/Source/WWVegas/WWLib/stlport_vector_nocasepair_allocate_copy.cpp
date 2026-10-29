// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport

#pragma comment(linker, "/alternatename:?allocate@?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@_STL@@QBEPAU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@2@IPBX@Z=?allocate@?$allocator@UBfmeE8@@@_STL@@QBEPAUBfmeE8@@IPBX@Z")

// ??$_M_allocate_and_copy@PBU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@?$vector@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@@_STL@@IAEPAU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@1@IPBU21@0@Z @0x00317D5C 45B: vector allocate-and-copy for 8-byte NoCase pair via allocate 0x00523D6C plus uninitialized_copy 0x00317CF2. Evidence: retail calls rowed allocate plus dup_00317CF2 worker for CopyNoCasePair; caller 0x00317EBB assign path sar 3 stride 8; same 45B ebp-tag shape as 0x0040D077 and 0x000BC72B.
#include "ascii_string.h"
#include <vector>
#include <utility>
struct NoCaseTreeValue4
{
	char m_body[4];
};
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> CopyNoCasePair;
struct Rva00317CF2Element { char bytes[8]; bool operator<(const Rva00317CF2Element&)const; bool operator==(const Rva00317CF2Element&)const; };
void __cdecl Rva00317CA0Construct(void *, const void *);
namespace _STL
{
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva00317CF2Element, Rva00317CF2Element>(Rva00317CF2Element *__p, const Rva00317CF2Element &__val)
{ Rva00317CA0Construct(__p, &__val); }
// Preserve the separately rowed allocator and copy worker while using the
// library's vector, allocator, pair and tag definitions.
template <> CopyNoCasePair *allocator<CopyNoCasePair>::allocate(unsigned int, const void *) const;
template <> template <> CopyNoCasePair *
vector<CopyNoCasePair, allocator<CopyNoCasePair> >::_M_allocate_and_copy<const CopyNoCasePair *>(
    size_type n, const CopyNoCasePair *first, const CopyNoCasePair *last)
{
    pointer result = _M_end_of_storage.allocate(n);
    __false_type tag; // Empty dispatch tag; retail does not value-initialize storage.
    __uninitialized_copy(reinterpret_cast<const Rva00317CF2Element *>(first),
                         reinterpret_cast<const Rva00317CF2Element *>(last),
                         reinterpret_cast<Rva00317CF2Element *>(result), tag);
    return result;
}
}
