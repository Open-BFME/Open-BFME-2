// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii_common /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /D_CRTIMP= /EHsc /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// stable_sort machinery over AsciiString* with less<AsciiString>.
//
// Open-BFME-1's Win32BIGFileSystem_loadBigFiles.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76) stable_sorts a vector of archive
// names. Compiled with the donor's flags plus /O1, four of the STLport bodies
// that sort emits place uniquely on unclaimed game.dat .text by masked
// whole-.text search, and ./build.sh reproduces them byte for byte. The
// BFME 2 caller is not recovered, so this unit carries no caller: an explicit
// instantiation of stable_sort emits the same instantiation chain.
#include "Common/AsciiString.h"
// codegen otherwise instantiates the min<int> COMDAT (one byte shape
// per TU flags); a file-static overload takes those calls instead so this
// TU emits no external copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const int &min(const int &a, const int &b)
{
    return b < a ? b : a;
}
}
#include <vector>
#include <algorithm>
// bfme link decl-only begin
// Retail's copy_backward call lands on 0x004F6FE1, rowed as
// copy_backward<TreeHintRef00217D4C *> (an ICF fold): forward to it with this call shape.
struct TreeHintRef00217D4C;
namespace _STL { template <> TreeHintRef00217D4C * copy_backward<TreeHintRef00217D4C *,TreeHintRef00217D4C *>(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *); }
namespace _STL { template <> __declspec(dllimport) __forceinline AsciiString * copy_backward<AsciiString *, AsciiString *>(AsciiString *a0, AsciiString *a1, AsciiString *a2)
{ return ((AsciiString * (__cdecl *)(AsciiString *,AsciiString *,AsciiString *))(TreeHintRef00217D4C * (__cdecl *)(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *))&copy_backward<TreeHintRef00217D4C *,TreeHintRef00217D4C *>)(a0, a1, a2); } }
// bfme link decl-only end

// Retail calls each of these helpers out of line at an address the ledger
// already rows under another spelling; each forwarder reaches that row with
// the call shape of the helper it replaces (generated from the retail REL32s).
#include "Rva004F9185Cmp.h"
struct TreeHintRef00217D4C;
namespace _STL { template <> TreeHintRef00217D4C * __lower_bound<struct TreeHintRef00217D4C *,struct TreeHintRef00217D4C,struct Rva004F9185Cmp,int>(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C const &,Rva004F9185Cmp,int *); }
namespace _STL { template <> TreeHintRef00217D4C * __merge_backward<struct TreeHintRef00217D4C *,struct TreeHintRef00217D4C *,struct TreeHintRef00217D4C *,struct Rva004F9185Cmp>(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,Rva004F9185Cmp); }
namespace _STL { template <> TreeHintRef00217D4C * __rotate<struct TreeHintRef00217D4C *,int,struct TreeHintRef00217D4C>(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,int *,TreeHintRef00217D4C *); }
namespace _STL { template <> TreeHintRef00217D4C * __upper_bound<struct TreeHintRef00217D4C *,struct TreeHintRef00217D4C,struct Rva004F9185Cmp,int>(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C const &,Rva004F9185Cmp,int *); }
TreeHintRef00217D4C * __cdecl Rva004F6E47Copy(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *);
TreeHintRef00217D4C * __cdecl Rva004F7308Merge(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *);
namespace _STL { template <> void swap<struct TreeHintRef00217D4C>(TreeHintRef00217D4C &,TreeHintRef00217D4C &); }
namespace _STL { template <> __declspec(dllimport) __forceinline AsciiString * __lower_bound<class AsciiString *,class AsciiString,struct _STL::less<class AsciiString>,int>(AsciiString * a0, AsciiString * a1, AsciiString const & a2, _STL::less<AsciiString> a3, int * a4)
{ return ((AsciiString * (__cdecl *)(AsciiString *,AsciiString *,AsciiString const &,_STL::less<AsciiString>,int *))(TreeHintRef00217D4C * (__cdecl *)(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C const &,Rva004F9185Cmp,int *))&_STL::__lower_bound<TreeHintRef00217D4C *,TreeHintRef00217D4C,Rva004F9185Cmp,int>)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline AsciiString * __merge_backward<class AsciiString *,class AsciiString *,class AsciiString *,struct _STL::less<class AsciiString> >(AsciiString * a0, AsciiString * a1, AsciiString * a2, AsciiString * a3, AsciiString * a4, _STL::less<AsciiString> a5)
{ return ((AsciiString * (__cdecl *)(AsciiString *,AsciiString *,AsciiString *,AsciiString *,AsciiString *,_STL::less<AsciiString>))(TreeHintRef00217D4C * (__cdecl *)(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,Rva004F9185Cmp))&_STL::__merge_backward<TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,Rva004F9185Cmp>)(a0, a1, a2, a3, a4, a5); } }
namespace _STL { template <> __declspec(dllimport) __forceinline AsciiString * __rotate<class AsciiString *,int,class AsciiString>(AsciiString * a0, AsciiString * a1, AsciiString * a2, int * a3, AsciiString * a4)
{ return ((AsciiString * (__cdecl *)(AsciiString *,AsciiString *,AsciiString *,int *,AsciiString *))(TreeHintRef00217D4C * (__cdecl *)(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,int *,TreeHintRef00217D4C *))&_STL::__rotate<TreeHintRef00217D4C *,int,TreeHintRef00217D4C>)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline AsciiString * __upper_bound<class AsciiString *,class AsciiString,struct _STL::less<class AsciiString>,int>(AsciiString * a0, AsciiString * a1, AsciiString const & a2, _STL::less<AsciiString> a3, int * a4)
{ return ((AsciiString * (__cdecl *)(AsciiString *,AsciiString *,AsciiString const &,_STL::less<AsciiString>,int *))(TreeHintRef00217D4C * (__cdecl *)(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C const &,Rva004F9185Cmp,int *))&_STL::__upper_bound<TreeHintRef00217D4C *,TreeHintRef00217D4C,Rva004F9185Cmp,int>)(a0, a1, a2, a3, a4); } }
namespace _STL { template <> __declspec(dllimport) __forceinline AsciiString * copy<class AsciiString *,class AsciiString *>(AsciiString * a0, AsciiString * a1, AsciiString * a2)
{ return ((AsciiString * (__cdecl *)(AsciiString *,AsciiString *,AsciiString *))(TreeHintRef00217D4C * (__cdecl *)(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *))&Rva004F6E47Copy)(a0, a1, a2); } }
namespace _STL { template <> __declspec(dllimport) __forceinline AsciiString * merge<class AsciiString *,class AsciiString *,class AsciiString *,struct _STL::less<class AsciiString> >(AsciiString * a0, AsciiString * a1, AsciiString * a2, AsciiString * a3, AsciiString * a4, _STL::less<AsciiString> a5)
{ return ((AsciiString * (__cdecl *)(AsciiString *,AsciiString *,AsciiString *,AsciiString *,AsciiString *,_STL::less<AsciiString>))(TreeHintRef00217D4C * (__cdecl *)(TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *,TreeHintRef00217D4C *))&Rva004F7308Merge)(a0, a1, a2, a3, a4, a5); } }
namespace _STL { template <> __declspec(dllimport) __forceinline void swap<class AsciiString>(AsciiString & a0, AsciiString & a1)
{ ((void (__cdecl *)(AsciiString &,AsciiString &))(void (__cdecl *)(TreeHintRef00217D4C &,TreeHintRef00217D4C &))&_STL::swap<TreeHintRef00217D4C>)(a0, a1); } }

// Retail's fill lands on 0x004F651D (rowed Rva004F651DFill). The tag argument is
// passed through a local so the caller's unused __false_type temporary stays
// un-zeroed, as it is when the callee's body is visible.
TreeHintRef00217D4C * __cdecl Rva004F651DFill(TreeHintRef00217D4C *,int,TreeHintRef00217D4C const *);
namespace _STL { template <> __declspec(dllimport) __forceinline AsciiString * __uninitialized_fill_n<AsciiString *,int,AsciiString>(AsciiString *a0, int a1, AsciiString const &a2, __false_type const &)
{ __false_type tag; return ((AsciiString * (__cdecl *)(AsciiString *,int,AsciiString const &,__false_type const &))(TreeHintRef00217D4C * (__cdecl *)(TreeHintRef00217D4C *,int,TreeHintRef00217D4C const *))&Rva004F651DFill)(a0, a1, a2, tag); } }
template void _STL::stable_sort<AsciiString *>(AsciiString *, AsciiString *);
// __rotate is forwarded above, so its swap_ranges (a row of this unit) is instantiated explicitly.
template AsciiString *_STL::swap_ranges<AsciiString *, AsciiString *>(AsciiString *, AsciiString *, AsciiString *);
