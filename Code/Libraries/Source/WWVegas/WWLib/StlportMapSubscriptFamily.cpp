// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// STLport map<AsciiString, T>::operator[] (124 bytes: lower_bound, key
// compare, default-constructed pair, hinted insert) for three AsciiString
// maps whose hinted map::insert is already rowed. Each is a masked-byte twin
// of the rowed map<AsciiString, TreeHintPayload002A1D9D>::operator[] at
// 0x002A57BD (stlport_rb_tree_hint_002a57bd.cpp, whose recipe and flags
// these are); its insert REL32 reads the rowed insert of exactly this map:
//
//   operator[]  insert      mapped view (insert's unit)
//   0x002C6F8C  0x002C6EC3  TreeHintPayload001F8ACB (stlport_rb_tree_hint_002c6c93.cpp)
//   0x00411A4B  0x00411319  TreeHintPayload00410B17 (stlport_rb_tree_hint_00410eab.cpp)
//   0x004E368A  0x004E2EBC  TreeHintPayload004E2257 (stlport_rb_tree_hint_004e2aab.cpp)
//
// The mapped values are 4-byte views default-constructed to zero, as the
// retail bodies store; lower_bound folds into the ICF twin at 0x00221B8D.
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()
#include <map>
#include "ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
struct TreeHintPayload001F8ACB { int m_val; TreeHintPayload001F8ACB() : m_val(0) {} TreeHintPayload001F8ACB(const TreeHintPayload001F8ACB &o) : m_val(o.m_val) {} };
typedef _STL::pair<const AsciiString, TreeHintPayload001F8ACB> TreeHintPair001F8ACB;
typedef _STL::map<AsciiString,TreeHintPayload001F8ACB,_STL::less<AsciiString >,_STL::allocator<TreeHintPair001F8ACB> > MapSubscript001F8ACB;
template TreeHintPayload001F8ACB &MapSubscript001F8ACB::operator[](const AsciiString &);

struct TreeHintPayload00410B17 { int m_val; TreeHintPayload00410B17() : m_val(0) {} TreeHintPayload00410B17(const TreeHintPayload00410B17 &o) : m_val(o.m_val) {} };
typedef _STL::pair<const AsciiString, TreeHintPayload00410B17> TreeHintPair00410B17;
typedef _STL::map<AsciiString,TreeHintPayload00410B17,_STL::less<AsciiString >,_STL::allocator<TreeHintPair00410B17> > MapSubscript00410B17;
template TreeHintPayload00410B17 &MapSubscript00410B17::operator[](const AsciiString &);

struct TreeHintPayload004E2257 { int m_val; TreeHintPayload004E2257() : m_val(0) {} TreeHintPayload004E2257(const TreeHintPayload004E2257 &o) : m_val(o.m_val) {} };
typedef _STL::pair<const AsciiString, TreeHintPayload004E2257> TreeHintPair004E2257;
typedef _STL::map<AsciiString,TreeHintPayload004E2257,_STL::less<AsciiString >,_STL::allocator<TreeHintPair004E2257> > MapSubscript004E2257;
template TreeHintPayload004E2257 &MapSubscript004E2257::operator[](const AsciiString &);
