// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
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
#undef free
#pragma comment(linker, "/alternatename:?Rva00030830FreeAllocation@@YAXPAX@Z=_free")
namespace _STL {
template <> string &string::append(const char *);
template <> unsigned int &map<string, unsigned int>::operator[](const string &);
}
struct BfmePeerStats { unsigned char unknown[0x98]; std::map<std::string, unsigned int> group, staging; };
enum RoomType { TitleRoom, GroupRoom, StagingRoom };
class PeerThreadClass {
public: void trackStatsForPlayer(RoomType roomType, const char *nick, const char *key, const char *val);
private: std::string packStatKey(const char *nick, const char *key);
};
std::string PeerThreadClass::packStatKey(const char *nick, const char *key) {
    std::string s = nick;
    s.append(key);
    return s;
}
// ?trackStatsForPlayer@PeerThreadClass@@ present-unmatched
void PeerThreadClass::trackStatsForPlayer(RoomType roomType, const char *nick, const char *key, const char *val) {
    BfmePeerStats *state = reinterpret_cast<BfmePeerStats *>(this);
    switch (roomType) {
    case 1: state->group[packStatKey(nick, key)] = atoi(val); break;
    case 2: state->staging[packStatKey(nick, key)] = atoi(val); break;
    }
}
