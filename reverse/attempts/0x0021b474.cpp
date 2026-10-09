// ?BindHeroToObjectAndUpdate@CreateAHeroManager@@QAEXPAVObject@@@Z
// partial score=0.84 date=2026-10-09
// Scratch reconstruction: WB B7D7B0 names BindHeroToObjectAndUpdate;
// retail 21B474..21B5D6 supplies its complete 354-byte body and RET4 ABI.
// Existing GetHeroForPlayer proves GameSlot name34/hasHero60/hero64 and
// Player nameKey50. This body witnesses Object key74/modules244, manager
// local hero0C/upgrade190/selected1E0 and module secondary-view0C slot20.
// The returned interface's slot54 and hero slot10 signatures follow their
// native call sites; neutral slot names do not assert original identities.
// ConstructHeroBlingList and RegisterExperienceLevels are WB callee names,
// but their unrowed targets409A76/408150 remain unresolved in this bank.
// Best trial352B: index/slot register allocation and inline getHero mask
// scheduling differ. All data offsets and call/virtual-slot ABI are retained.
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE
#include "ascii_string.h"
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString &); };
extern NameKeyGenerator *TheNameKeyGenerator;
class UpgradeTemplate;
class UpgradeCenter { public: const UpgradeTemplate *findUpgrade(const AsciiString &) const; };
extern UpgradeCenter *TheUpgradeCenter;
class Player { public: char unknown00[0x50]; NameKeyType nameKey50; bool isLocalPlayer() const; void rva002ADAC3(const UpgradeTemplate *,int); };
class CreateAHeroData { public: void rva00408A55(); };
class Rva00406E47 { public: bool rva00406E47(int); };
class CreateAHeroHero {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C(); virtual void slot10(int);
    void ConstructHeroBlingList(); void RegisterExperienceLevels();
};
class HeroModuleResult { public: virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C(); virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C(); virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C(); virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C(); virtual void slot50(); virtual void slot54(); };
class HeroModuleView { public: virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C(); virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C(); virtual HeroModuleResult *slot20(); };
struct HeroModule { char unknown00[12]; HeroModuleView view0C; };
class Object { public: char unknown00[0x74]; int key74; char unknown78[0x244-0x78]; HeroModule **modules244; Player *getControllingPlayer() const; };
class GameSlot { public: char unknown00[0x34]; AsciiString name34; char unknown38[0x60-0x38]; bool hasHero60; char unknown61[3]; CreateAHeroHero hero64; const CreateAHeroHero *getHero() const { return hasHero60?&hero64:0; } };
class GameInfo { public: GameSlot *getSlot(int); };
extern GameInfo *TheGameInfo;
class CreateAHeroManager { public: void BindHeroToObjectAndUpdate(Object *); char unknown00[0x190]; AsciiString upgradeName190; char unknown194[0x1e0-0x194]; CreateAHeroHero *selected1E0; };
void CreateAHeroManager::BindHeroToObjectAndUpdate(Object *object) {
    if(!object) return;
    Player *player=0;
    CreateAHeroHero *hero;
    bool remember;
    if(TheGameInfo) {
        Player *controlling=object->getControllingPlayer();
        GameSlot *slot=0;
        for(unsigned i=0; slot==0 && i<8; ++i) {
            AsciiString name=TheGameInfo->getSlot(i)->name34;
            NameKeyType key=TheNameKeyGenerator->nameToKey(name);
            if(controlling->nameKey50==key) slot=TheGameInfo->getSlot(i);
        }
        hero=slot?const_cast<CreateAHeroHero *>(slot->getHero()):0;
        remember=controlling->isLocalPlayer() && hero;
        player=controlling;
    } else {
        hero=reinterpret_cast<CreateAHeroHero *>(reinterpret_cast<char *>(this)+0xc);
        remember=true;
    }
    if(!hero) return;
    hero->ConstructHeroBlingList();
    reinterpret_cast<CreateAHeroData *>(hero)->rva00408A55();
    reinterpret_cast<Rva00406E47 *>(hero)->rva00406E47(object->key74);
    hero->RegisterExperienceLevels();
    hero->slot10(0x2ff);
    if(player) player->rva002ADAC3(TheUpgradeCenter->findUpgrade(upgradeName190),1);
    if(remember) selected1E0=hero;
    for(HeroModule **module=object->modules244; *module; ++module) {
        HeroModuleResult *result=(*module)->view0C.slot20();
        if(result) result->slot54();
    }
}



