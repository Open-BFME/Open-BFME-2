// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// BFME1 6583b3c1 PeerThread.cpp supplies lookup-by-room semantics.
// Native38A63C/131 calls the rowed stat-key constructor and find389291,
// selects maps98/A4, returns the four-byte mapped value or zero.
// The unsigned map adopts the existing verified scalar model, while the
// reference return ABI interprets its four-byte bit pattern as int.
// /EHsc keeps native cleanup but removes the extra /GX unwind-state store.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdlib.h>
#undef _CRTIMP
#define _CRTIMP
void Rva00030830FreeAllocation(void *);
// Route inline string cleanup to the independently verified game allocator.
#define free Rva00030830FreeAllocation
#include <string>
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#undef free
#pragma comment(linker, "/alternatename:?Rva00030830FreeAllocation@@YAXPAX@Z=_free")
namespace _STL {
// Use the comparator in its existing verified owner.
// Native operator<388F39 compares four begin/end pointers through244FC only.
template <> bool operator< <char, char_traits<char>, allocator<char> >(const string &, const string &) throw();
template <> string &string::append(const char *);
}
struct BfmePeerStats { unsigned char unknown[0x98]; std::map<std::string, unsigned int> group, staging; };
enum RoomType { TitleRoom, GroupRoom, StagingRoom };
class PeerThreadClass {
public: int lookupStatForPlayer(RoomType, const char *, const char *);
private: std::string packStatKey(const char *nick, const char *key);
};
int PeerThreadClass::lookupStatForPlayer(RoomType roomType, const char *nick, const char *key) {
    std::string fullKey = packStatKey(nick, key);
    typedef std::map<std::string, unsigned int> StatMap;
    StatMap::const_iterator it;
    BfmePeerStats *state = reinterpret_cast<BfmePeerStats *>(this);
    switch (roomType) {
    case GroupRoom:
        it = state->group.find(fullKey);
        if (it != state->group.end()) return static_cast<int>(it->second);
        break;
    case StagingRoom:
        it = state->staging.find(fullKey);
        if (it != state->staging.end()) return static_cast<int>(it->second);
        break;
    }
    return 0;
}
