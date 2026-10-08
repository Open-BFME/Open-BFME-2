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
class RegionAwardDispute {
    unsigned char opaque[8];
    _STL::vector<Rva002E2903Player*> records;
public:
    int rva004FBE7A();
    int GetResolvableBy();
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
