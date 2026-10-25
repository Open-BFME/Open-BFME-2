// Region-cost classification, native 0x007F7260..0x007F744F (495 bytes).
// WB 0x01057DF0 supplies structural corroboration, not an original class name.
// Native accesses establish record cost+24, region owner+13C, player anchors+1B8,
// logic players+8C and region manager+B0. The receiver identity stays opaque.
// Reconstructed from target evidence; no donor source.
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include "ascii_string.h"
#include <vector>

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class Rva0020E89C;
class Rva002E2903Player;
class Rva00318C32Ret;
class Rva00318C79Owner {
public:
    Rva00318C32Ret *rva00318C32();
};
class Rva002BA8F1Logic {
public:
    Rva002E2903Player *find(int, unsigned *);
    Rva002E2903Player *GetPlayerAtIndex(int);
};
class Rva0020EAF6View {
public:
    Rva0020E89C *rva0020EAF6(int);
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

struct RegionCostRecord {
    int region;
    char unmodelled04[0x20];
    float cost;
    int getRegion() const { return region; }
};
struct RegionOwnerView {
    char unmodelled00[0x13c];
    int owner;
};
struct RegionAnchorView {
    char unmodelled00[0x18];
    AsciiString name;
    char unmodelled1c[0x58];
    unsigned char flag74;
};
struct WorldPlayerRegionView {
    char unmodelled00[0x1b8];
    _STL::vector<RegionAnchorView *> anchors;
    const _STL::vector<RegionAnchorView *> &getAnchors() const { return anchors; }
};
struct WorldLogicRegionView {
    char unmodelled00[0x8c];
    _STL::vector<Rva002E2903Player *> players;
    char unmodelled98[0x18];
    Rva0020EAF6View *regions;
    Rva0020EAF6View *getRegions() const { return regions; }
};

class Rva003F7260 {
public:
    void rva003F7260(int *input);
    void *unknown00;
    int owner04;
    float otherNamed08, otherAny0c, ownNamed10, ownAny14, otherRegion18;
    RegionAnchorView *selected1c, *otherAny20, *ownNamed24;
    Rva0020E89C *neutral28;
    float neutral2c;
    Rva0020E89C *owned30;
    float owned34;
};

// ?rva003F7260@Rva003F7260@@QAEXPAH@Z
void Rva003F7260::rva003F7260(int *input)
{
    RegionCostRecord *cost = (RegionCostRecord *)input;
    const float &newCost = cost->cost;
    Rva0020E89C *region = ((WorldLogicRegionView *)TheLivingWorldLogic)
        ->getRegions()->rva0020EAF6(cost->getRegion());
    Rva002E2903Player *owner = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(owner04, 0);

    if (((RegionOwnerView *)region)->owner != owner04) {
        // Compiler scheduling adapter: retain each native owner-field access
        // rather than a common address temporary. Emits no instructions.
        _ReadWriteBarrier();
        if (otherRegion18 > newCost)
            otherRegion18 = newCost;
        if (((RegionOwnerView *)region)->owner == -1 && neutral2c > newCost) {
            neutral28 = region;
            neutral2c = newCost;
        } else if (((RegionOwnerView *)region)->owner != -1 && owned34 > newCost) {
            owned30 = region;
            owned34 = newCost;
        }
    }

    for (int p = 0; p < (int)((WorldLogicRegionView *)TheLivingWorldLogic)->players.size(); ++p) {
        Rva002E2903Player *player = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->GetPlayerAtIndex(p);
        WorldPlayerRegionView *view = (WorldPlayerRegionView *)player;
        const _STL::vector<RegionAnchorView *> &anchors = view->getAnchors();
        for (unsigned a = 0; a < anchors.size(); ++a) {
            if (((Rva00318C79Owner *)anchors[a])->rva00318C32() == (Rva00318C32Ret *)region) {
                RegionAnchorView *anchor = anchors[a];
                if (!anchor->name.isEmpty()) {
                    if (player == owner) {
                        if (ownNamed10 > newCost) {
                            ownNamed10 = newCost;
                            ownNamed24 = anchors[a];
                            if (ownAny14 > newCost)
                                ownAny14 = newCost;
                        }
                    } else {
                        if (otherNamed08 > newCost) {
                            otherNamed08 = newCost;
                            if (otherAny0c > newCost) {
                                otherAny0c = newCost;
                                otherAny20 = anchors[a];
                                selected1c = anchors[a];
                            }
                        }
                    }
                } else if (!anchor->flag74 && player == owner) {
                    if (ownAny14 > newCost) {
                        ownAny14 = newCost;
                        selected1c = anchors[a];
                    }
                }
            }
        }
    }
}
