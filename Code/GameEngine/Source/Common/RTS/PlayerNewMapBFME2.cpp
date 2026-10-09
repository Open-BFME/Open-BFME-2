// cl: /DBFME_ASCII_KEEP_COPY_SET_BODY /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /MD /EHsc /DNDEBUG
// Target identity: WB 0x00C133C0 names Player::newMap (callgraph score 2;
// Player.cpp 1045). Retail 0x002B0D00..0x002B0E55 is ret0 and PlayerList
// vslot 15 calls it on each of twenty players. ZH Player.cpp:761 supplies
// the AI newMap semantic core; all additional control flow and offsets
// below are native BFME2 facts, rather than donor layout assumptions.
// Native fields: Player template +34, AI +2DC, team +2EC, starting ObjectID
// +6F0; template names +1B4/+1B8; ObjectID +74. The +9C0 option and GameInfo
// vslots 18..20 retain numeric names because their meanings are unproved.
// Hero init is independently named by WB 0x00C1C660 and Player.cpp's hero
// assertions at 4121..4144. The +3BC call uses the already verified setter
// ABI owned by W3DBridge::setEnabled at 0x0039B780: this does not establish
// that Player contains a bridge. enableView is only an accessed call view.
// The raw Object and BfmeGlob939D callees likewise retain existing owners.
// stlport
// initBuildableHeroes: native 0x002B0B96..0x002B0CB0, ret0, WB Player.cpp
// 4121..4144 explicitly asserts the hero names. Mode +114 == 3 selects
// template heroes +18C/+190; the other branch uses the living-world id
// +3AC, named extraction 0x002E2F44 and tracker +738. Keeping the template
// snapshot local matches native lifetime and register allocation.
// The local vector's D8-stride element uses its existing Rva002E2690Element
// destructor/constructor ABI. Its layout is only an opaque revival-record
// view, not a claim of EA's original record name. addRevivableUnit's rowed
// second argument is unused and typed int; native supplies this Player
// pointer in that four-byte slot. The already rowed addInitialBuildUnit
// call keeps its raw Rva0037F32F owner name pending canonical reconciliation.
#include <vector>
#include "ascii_string.h"
#include "../GameLogicObjectLookupView.h"
class BfmeGlob939D : public GameLogic { public: char bfmeCall939D(); };
extern GameLogic *TheGameLogic;
class Team;
struct CreateMask { unsigned int bits[4]; };
class ThingTemplate;
class ThingFactory {
public:
 const ThingTemplate *findTemplate(const AsciiString &name);
 Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool flag);
};
extern ThingFactory *TheThingFactory;
class Rva0028CBFD { public: void rva0028CBFD(); };
class Object { public: char pad[0x74]; ObjectID id; ObjectID getID() const { return id; } };
class PlayerTemplate {
public: char pad[0x18C]; AsciiString *heroBegin; AsciiString *heroEnd; char pad194[0x1B4-0x194]; AsciiString name1B4; AsciiString name1B8;
};
class PlayerAI {
public:
 virtual void slot00() = 0;
 virtual void slot01() = 0;
 virtual void slot02() = 0;
 virtual void slot03() = 0;
 virtual void slot04() = 0;
 virtual void slot05() = 0;
 virtual void newMap() = 0;
};
class GlobalData { public: char pad[0x9C0]; bool flag9C0; };
extern GlobalData *TheWritableGlobalData;
class GameInfo {
public:
#define SLOT(N) virtual void slot##N() = 0;
 SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
 SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17)
#undef SLOT
 virtual bool flag48() = 0;
 virtual bool flag4C() = 0;
 virtual bool flag50() = 0;
};
extern GameInfo *TheGameInfo;
class W3DBridge { public: void setEnabled(bool); char pad[0x114]; };
struct Rva002E2690Element { char bytes[0xD8]; ~Rva002E2690Element(); };
struct Rva002E2D10Record { char bytes[0xD8]; };
class Player;
class UnitRevivalTracker { public: void addRevivableUnit(const Rva002E2D10Record &,int); char bytes[0x14]; };
class Rva0037F32F { public: void rva0037F32F(const ThingTemplate *,Player *); };
class LivingWorldPlayer { public: void ExtractRevivalUnitDataForCurrentMap(_STL::vector<Rva002E2690Element> *); };
class Rva002E2903Player;
class Rva002BA8F1Logic { public: Rva002E2903Player *find(int,unsigned int *); };
extern Rva002BA8F1Logic *TheLivingWorldLogic;
class Rva0023C6A4 { public: bool rva00200084(); };
class Player {
public:
 char pad0[0x34]; PlayerTemplate *playerTemplate;
 char pad38[0x2DC-0x38]; PlayerAI *ai;
 char pad2E0[0x2EC-0x2E0]; Team *team;
 char pad2F0[0x3AC-0x2F0]; int livingWorldID; char pad3B0[0x3BC-0x3B0]; W3DBridge enableView;
 char pad4D0[0x6F0-0x4D0]; ObjectID startingObject; char pad6F4[0x738-0x6F4]; UnitRevivalTracker revival;
 void rva002A99FA();
 void initBuildableHeroes();
 void newMap();
};
void Player::newMap() {
 if (team && playerTemplate) {
  AsciiString name;
  if (((BfmeGlob939D *)TheGameLogic)->bfmeCall939D())
   name = playerTemplate->name1B8;
  else
   name = playerTemplate->name1B4;
  if (!name.isEmpty()) {
   const ThingTemplate *tmplate = TheThingFactory->findTemplate(name);
   if (!tmplate) return;
   CreateMask mask;
   memset(&mask,0,sizeof(mask));
   Object *obj = TheThingFactory->newObject(tmplate,team,&mask,false);
   startingObject = obj->getID();
   ((Rva0028CBFD *)obj)->rva0028CBFD();
  }
 }
 rva002A99FA();
 if (ai) ai->newMap();
 if (TheWritableGlobalData->flag9C0 ||
     (TheGameInfo && (TheGameInfo->flag48() || TheGameInfo->flag4C() || TheGameInfo->flag50())) ||
     (TheGameLogic && ((BfmeGlob939D *)TheGameLogic)->bfmeCall939D()))
  initBuildableHeroes();
 enableView.setEnabled(true);
}
void Player::initBuildableHeroes() {
 if (TheGameLogic->m_114 != 3) {
  if (livingWorldID == -1) return;
  LivingWorldPlayer *living = (LivingWorldPlayer *)TheLivingWorldLogic->find(livingWorldID,0);
  if (living) {
   _STL::vector<Rva002E2690Element> units;
   living->ExtractRevivalUnitDataForCurrentMap(&units);
   for (unsigned int i=0;i<units.size();++i)
    revival.addRevivableUnit(*(Rva002E2D10Record *)&units[i],(int)this);
  }
 } else {
  if (((Rva0023C6A4 *)TheGameLogic)->rva00200084()) return;
  const PlayerTemplate *pt = playerTemplate;
  if (!pt) return;
  int count = pt->heroEnd-pt->heroBegin;
  for (int i=0;i<count;++i) {
   const ThingTemplate *tmplate=TheThingFactory->findTemplate(pt->heroBegin[i]);
   if (tmplate) ((Rva0037F32F *)&revival)->rva0037F32F(tmplate,this);
  }
 }
}
