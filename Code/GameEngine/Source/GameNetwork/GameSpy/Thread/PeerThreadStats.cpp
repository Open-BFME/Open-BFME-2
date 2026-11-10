// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// BFME1 6583b3c1 PeerThread.cpp supplies stat-key concatenation and room maps.
// Native38E0C4/173 selects maps98/A4 for room1/2, indexes by the concatenated
// nickname/key and stores imported atoi's four-byte result. The unsigned map
// scalar uses the independently verified retail subscript38E041; signedness
// of the stored bit pattern is not established by this write alone.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdlib.h>
#undef _CRTIMP
#define _CRTIMP
void Rva00030830FreeAllocation(void *);
// Route STL inline cleanup to the rowed game allocator, while atoi remains imported.
#define free Rva00030830FreeAllocation
#include <string>
#include <map>
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PADDV?$allocator@D@_STL@@@_STL@@QAEPADI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * _STL::_STLP_alloc_proxy<char *,char,_STL::allocator<char> >::allocate(unsigned int); }
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}
#undef free
namespace _STL {
template <> string &string::append(const char *);
template <> unsigned int &map<string, unsigned int>::operator[](const string &);
template <> vector<unsigned int>::vector(const vector<unsigned int> &);
}
enum RoomType { TitleRoom, GroupRoom, StagingRoom };
class GameLogic;
extern GameLogic *TheGameLogic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002034E9Host { public: bool rva002034E9(); };
class Rva002B31F2 {
public:
 void rva002B31F2(_STL::vector<unsigned int> *out);
};
class Rva0040DBA9 {
public:
 _STL::vector<unsigned int> rva0040DBA9();
};

// Ghidra [40DBA9,40DC1F)118B RET4, hidden vector result. Caller2401C0
// invokes this on GameLogic+184. The receiver is unused: this constructs
// an empty vector, conditionally fills it through the world pointer's
// 2B31F2 visitor, then returns a counted copy and frees the local allocation.
// The verified scalar copy2CFAB9 establishes four-byte elements; unsigned
// words preserve their bits without claiming the application's element type.
// No PeerThread identity is inferred from the compiled sibling lead.
_STL::vector<unsigned int> Rva0040DBA9::rva0040DBA9()
{
 _STL::vector<unsigned int> values;
 if (reinterpret_cast<Rva002034E9Host *>(TheGameLogic)->rva002034E9())
  reinterpret_cast<Rva002B31F2 *>(TheLivingWorldLogic)->rva002B31F2(&values);
 return values;
}
