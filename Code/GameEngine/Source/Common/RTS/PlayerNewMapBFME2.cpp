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
public: char pad[0x1B4]; AsciiString name1B4; AsciiString name1B8;
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
class Player {
public:
 char pad0[0x34]; PlayerTemplate *playerTemplate;
 char pad38[0x2DC-0x38]; PlayerAI *ai;
 char pad2E0[0x2EC-0x2E0]; Team *team;
 char pad2F0[0x3BC-0x2F0]; W3DBridge enableView;
 char pad4D0[0x6F0-0x4D0]; ObjectID startingObject;
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