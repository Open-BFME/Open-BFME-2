// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE /G7 /D_STLP_USE_STATIC_LIB
// stlport
// WB 0x0104CD00 names LivingWorldBattle::GetResolutionOptions; retail
// 0x003F4FD4..0x003F5192 supplies the complete 446-byte body. Both images
// establish the resolution flags, adjacent-region stride 24 and member
// offsets below. The address-derived types are prefix views, not recovered
// original class names. No BFME1 donor supplies this War of the Ring logic.
// The inline manager accessor preserves the original expression evaluation
// and MSVC 7.1 register allocation. The tutorial getter uses its existing
// verified member owner at 0x002B256E.
#include <vector>

class GameLogic;
extern GameLogic *TheGameLogic;
class GameInfo;
extern GameInfo *TheGameInfo;
class SkirmishGameInfo;
extern SkirmishGameInfo *TheSkirmishGameInfo;
class Rva00210C66CmpBoolField { public: bool get() const; };
class Rva002B254F { public: int rva002B254F(); };
class Rva002B256E { public: void *rva002B256E(); };
class Rva003F44A9 { public: bool rva003F44ED(); };
class Rva002E071E { public: int rva002E0BC0(int); };
class Rva0020E89C;
class Rva0020EAF6View { public: Rva0020E89C *rva0020EAF6(int); };
struct Rva003F4FD4LogicView {
    char pad00[0x98];
    void *player;
    char pad9C[0xB0 - 0x9C];
    Rva0020EAF6View *manager;
    Rva0020EAF6View *getManager() const { return manager; }
};
struct Rva003F4FD4GameLogicView { char pad00[0x114]; int mode; };
struct Rva003F4FD4GameInfoView { char pad00[0x7C]; int kind; };
struct AdjacentRegion { char pad00[8]; int id; char pad0C[0x18 - 0xC]; };
struct Rva003F4FD4Region {
    char pad00[0xA9];
    bool special;
    char padAA[0x12C - 0xAA];
    int id;
    char pad130[0x1A8 - 0x130];
    std::vector<AdjacentRegion> adjacent;
    std::vector<AdjacentRegion> &getAdjacent() { return adjacent; }
};
struct Rva003F4FD4OwnedRegion { char pad00[0x13C]; int playerID; };
struct Rva003F4E07Player { char pad00[0x14]; int id; };
class LivingWorldBattle;
class Rva003F4FD4Tutorial {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13();
    virtual int slot14(LivingWorldBattle *);
};
class Rva002BA8F1Logic { public: int rva002B5256(bool); };
class LivingWorldLogic {
public:
    bool WillPlayerBeEliminatedIfHeOrSheLosesThisRegion(int, int);
};
extern LivingWorldLogic *TheLivingWorldLogic;

class LivingWorldBattle {
public:
    struct BattlePlayer { Rva003F4E07Player *m_player; };
    int GetResolutionOptions();
    void *rva003F4DEE(void *);
    int rva003F4831();
private:
    char pad00[0x24];
    Rva003F4FD4Region *region24;
};

int LivingWorldBattle::GetResolutionOptions()
{
    if ((unsigned char)((Rva002B254F *)TheLivingWorldLogic)->rva002B254F())
        return ((Rva003F4FD4Tutorial *)((Rva002B256E *)TheLivingWorldLogic)->rva002B256E())->slot14(this);
    Rva003F4FD4Region *region = region24;
    if (!region) return 0;
    Rva003F4FD4GameInfoView *info = 0;
    GameLogic *gameLogic = TheGameLogic;
    if (((Rva00210C66CmpBoolField *)gameLogic)->get())
        info = (Rva003F4FD4GameInfoView *)TheGameInfo;
    else if (((Rva003F4FD4GameLogicView *)gameLogic)->mode != 3)
        info = (Rva003F4FD4GameInfoView *)TheSkirmishGameInfo;
    if (region->special) return 8;
    int flags = 0;
    if (info->kind != 2) flags = 2;
    bool mayRetreat = false;
    bool eliminated = false;
    void *localPlayer = ((Rva003F4FD4LogicView *)TheLivingWorldLogic)->player;
    BattlePlayer *player = localPlayer ? (BattlePlayer *)rva003F4DEE(localPlayer) : 0;
    if (player) {
        if (!((Rva003F44A9 *)player)->rva003F44ED()) mayRetreat = false;
        else {
            std::vector<AdjacentRegion> *adjacent = &region->getAdjacent();
            for (unsigned i = 0; i < adjacent->size(); ++i) {
                Rva0020E89C *owned = ((Rva003F4FD4LogicView *)TheLivingWorldLogic)->getManager()->rva0020EAF6((*adjacent)[i].id);
                if (owned && (unsigned char)((Rva002E071E *)player->m_player)->rva002E0BC0(((Rva003F4FD4OwnedRegion *)owned)->playerID)) {
                    mayRetreat = true;
                    break;
                }
            }
        }
        int regionID = region24->id;
        int playerID = player->m_player->id;
        if (TheLivingWorldLogic->WillPlayerBeEliminatedIfHeOrSheLosesThisRegion(playerID, regionID)) eliminated = true;
        if (mayRetreat && !eliminated) flags |= 4;
    }
    if (info->kind != 1) {
        if (((Rva003F4FD4GameLogicView *)TheGameLogic)->mode == 0) flags |= 8;
        else {
            int count = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B5256(false);
            if (rva003F4831() == count) flags |= 8;
            else flags |= 2;
        }
    }
    return flags;
}
