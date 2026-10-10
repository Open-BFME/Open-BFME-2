// WorldBuilder 0x013137B0 names GetResolvableBy in LivingWorldRegionAwardDispute.cpp.
// The retail call graph and Ghidra extents prove 0x004FBED6 (184 B) and its
// unnamed count helper 0x004FBE7A (49 B). Players are the pointer values returned
// by the independently verified 0x002B51F8 lookup: id +0x14 and count gate +0x44.
// WB reports no humans when the count is zero; the helper name is still unknown.
// The dispute's vector is at +8. Its preceding fields and complete layout are
// deliberately opaque. GameSlot's host player id at +0x4C is read by both images.
// STLport 4.5.3 pointer find / __find are ordinary typed instantiations; their
// complete 27 / 103 B bodies and relocations fold to the established owners.
// cl: /O1 /G7 /arch:SSE
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <algorithm>
class Rva002E2903Player {
public:
    unsigned char opaque[0x14];
    int id;
    unsigned char gap[0x44-0x18];
    int field_44;
};
class Rva002BA8F1Logic { public: Rva002E2903Player* find(int, unsigned*); };
class LivingWorldLogic;
extern LivingWorldLogic* TheLivingWorldLogic;
class GameSlot { public: unsigned char opaque[0x4c]; int playerId; };
class GameInfo { public: const GameSlot* getConstSlot(int) const; };
extern GameInfo* TheGameInfo;
// The local player lookup (rowed 0x002B2B66) and the dispute's flag setter
// (rowed 0x004FBDB0), viewed under their row spellings.
class Rva002B2B66 { public: int rva002B2B66(); };
class Rva004FBDB0 { public: void rva004FBDB0(bool flag); };
class RegionAwardDispute {
    unsigned char opaque[8];
    _STL::vector<Rva002E2903Player*> records;
public:
    int rva004FBE7A();
    int GetResolvableBy();
    void rva004FC0AD(const Rva002E2903Player *player);
};
int RegionAwardDispute::rva004FBE7A() {
    int result = 0;
    for (unsigned i = 0; i < records.size(); ++i)
        if (records[i]->field_44 == 0) ++result;
    return result;
}

int RegionAwardDispute::GetResolvableBy() {
    if (records.empty()) return -1;
    int humanCount = rva004FBE7A();
    if (humanCount == 0) return records[0]->id;
    if (humanCount == 1) {
        for (unsigned i=0; i < records.size(); ++i)
            if (records[i]->field_44 == 0) return records[i]->id;
    } else {
        if (!TheGameInfo) return -1;
        const GameSlot* slot=TheGameInfo->getConstSlot(0);
        if (!slot) return -1;
        int id=slot->playerId;
        Rva002E2903Player* player=reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->find(id,0);
        if (!player) return -1;
        if (_STL::find(records.begin(), records.end(), player)==records.end()) return -1;
        return id;
    }
    return -1;
}

// ?rva004FC0AD@RegionAwardDispute@@QAEXPBVRva002E2903Player@@@Z, retail
// 0x004FC0AD..0x004FC0ED (64 bytes, RET 4): adds a disputant (the pinned
// pointer-vector push_back fold; the argument is copied to a temporary of
// the element type first) and tells the dispute (rowed 0x004FBDB0) whether
// the local player (rowed 0x002B2B66) is now the one who resolves it.
void RegionAwardDispute::rva004FC0AD(const Rva002E2903Player *player) {
    records.push_back((Rva002E2903Player *)player);
    int local = reinterpret_cast<Rva002B2B66 *>(TheLivingWorldLogic)->rva002B2B66();
    reinterpret_cast<Rva004FBDB0 *>(this)->rva004FBDB0(local == GetResolvableBy());
}
