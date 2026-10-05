// ?_M_insert_overflow@?$vector@URva003F5F89Record@@V?$allocator@URva003F5F89Record@@@_STL@@@_STL@@IAEXPAURva003F5F89Record@@ABU3@ABU__false_type@2@I_N@Z
// partial score=0.98 date=2026-10-05
// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Stock STLport 4.5.3 algorithm; native 003F6B24..003F6BDB ret14, stride28.
// Copy 003F62F5 and fill 003F631B both call Construct 003F62C8, which
// in turn calls 003F5F89. That constructor copies +0 as a scalar, constructs
// a twelve-byte member at +4 via 003F5B5B, and another at +16 via 0054878E.
// This contradicts the older BfmeStringRecord00111ACF {AsciiString first,...}
// view; its generic helper pins cannot establish this record's identity.
// Name only establishes the observed copy-ctor relationship, not Eva ownership.
#include <vector>
struct Rva003F5F89Record {
 char m_unported[28];
 Rva003F5F89Record(const Rva003F5F89Record &);
 ~Rva003F5F89Record();
};
namespace _STL {
template<> void _Construct<Rva003F5F89Record,Rva003F5F89Record>(Rva003F5F89Record *,const Rva003F5F89Record &);
}
template<> void _STL::vector<Rva003F5F89Record>::_M_clear();
template void _STL::vector<Rva003F5F89Record>::_M_insert_overflow(Rva003F5F89Record *,const Rva003F5F89Record &,const _STL::__false_type &,unsigned int,bool);
