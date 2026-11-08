// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// Retail 0038ADE2..0038AF29: aggregate teardown preceding the WB-named
// PeerThreadClass::pushStatsToRoom. Constructor38AAEB installs C1989C;
// Slot0 deleting wrapper38ADC6 calls this virtual destructor; table slot2
// is the rowed PeerThreadClass::Thread_Function.
// Native teardown proves lifetime members at54..490: eight strings atD0;
// two PlayerStatMap trees at98/A4; record dtors at278/298; ThreadClass base
// teardown last. All gaps derive from native member addresses. This is a
// destructor-only view: novtable suppresses the own-vptr reset absent from
// retail, following SkirmishGameInfoDtor.cpp's established virtual ABI pattern.
// STLport semantics: BFME1 donor0bef414b52a39a3ab1ec98dca60d8a214de4260e.
// Existing callee names are retained; opaque record names preserve uncertainty.
// Only destruction is used here. These views preserve STLport 4.5.3's
// three-word string/map storage without instantiating unrelated allocator
// helpers. The narrow string release is the already verified 14-byte body
// at 0x00142D70 (stlport_narrow_num_get_double.cpp); the real map destructor
// at 0x0038A5D1 is supplied by Rva0055011ACtor.cpp. Native parent accesses
// and its complete EH graph independently constrain all member offsets.
namespace _STL {
template <class T> class char_traits {};
template <class T> class allocator {};
template <class Char, class Traits = char_traits<Char>, class Alloc = allocator<Char> >
class basic_string {
    Char *m_start, *m_finish, *m_storageEnd;
public:
    __forceinline ~basic_string() { if (m_start) free(m_start); }
};
template <class T> struct less {};
template <class First, class Second> struct pair;
template <class Pair> struct _Select1st;
template <class Key, class Value, class Extract, class Compare, class Alloc>
class _Rb_tree {
    void *m_storage[3];
public:
    ~_Rb_tree();
};
template <class Key, class Value, class Compare = less<Key>,
    class Alloc = allocator<pair<const Key, Value> > >
class map {
    _Rb_tree<Key, pair<const Key, Value>, _Select1st<pair<const Key, Value> >,
        Compare, Alloc> m_tree;
public:
    ~map() {}
};
typedef basic_string<char> string;
}
namespace std = _STL;
#include <stdlib.h>
#include "../../../../../Libraries/Source/WWVegas/WWLib/ThreadClass.h"
struct BfmeOpaqueOwnedRecord492 { ~BfmeOpaqueOwnedRecord492(); char bytes[492]; };
struct Rva00388EAE { ~Rva00388EAE(); char bytes[12]; };
class __declspec(novtable) PeerThreadClass : public ThreadClass {
public: virtual ~PeerThreadClass();
 virtual void Thread_Function();
private:
 char gap50[4]; std::string s54,s60,s6c,s78;
 char gap84[0x14];
 std::map<std::string,int> m98,ma4;
 char gapb0[4]; std::string sb4;
 char gapc0[4]; std::string sc4;
 std::string names[8];
 char gap130[0x30]; std::string s160,s16c;
 char gap178[0x100]; Rva00388EAE record278;
 std::string s284; char gap290[8];
 BfmeOpaqueOwnedRecord492 record298; char gap484[12];
 std::string s490;
};
PeerThreadClass::~PeerThreadClass() {}

// Native unwind action 0x0078059A belongs to this destructor's complete
// EH graph. It destroys names[8] at owner+0xD0 with 12-byte stride, through
// the ordinary std::string member lifetime above. Its independent 24-byte
// boundary and compiler-emitted code/relocations are verified as a whole.
