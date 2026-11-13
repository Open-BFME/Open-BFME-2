// cl: /DBFME_ASCII_KEEP_COPY_SET_BODY /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G7 /MD /EHsc /DNDEBUG
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
// view, not a claim of EA's original record name. addRevivableUnit's
// second argument is this Player (unused by the rowed body).
#include <vector>
#include "ascii_string.h"
#include "../GameLogicObjectLookupView.h"
#include "../../../Include/Common/BfmeGlob939D.h"
extern GameLogic *TheGameLogic;
class Team;
struct CreateMask { unsigned int bits[4]; };
class ThingTemplate;
enum ObjectID; class ThingFactory {
public:
 const ThingTemplate *findTemplate(const AsciiString &name);
 Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, ObjectID flag);
};
extern ThingFactory *TheThingFactory;
#include "../../../Include/Common/Rva0028CBFD.h"
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
#include "../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
#include "../../../Include/GameNetwork/GameInfo.h"
extern GameInfo *TheGameInfo;
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DBridge.h"
#include "../../../Include/Common/Rva002E2690Element.h"
// Cleanup belongs to the existing 63-byte vector destructor provider at
// 0x002B0B32. Declare that specialization so this TU emits no divergent
// allocator/deallocation COMDAT copies for the accessed D8 record view.
namespace _STL { template<> vector<Rva002E2690Element>::~vector(); }
struct Rva002E2D10Record { char bytes[0xD8]; };
class Player;
#include "../../../Include/Common/UnitRevivalTracker.h"
#include "../../../Include/GameLogic/LivingWorldPlayer.h"
class Rva002E2903Player;
#include "../../../Include/GameLogic/Rva002BA8F1Logic.h"
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "../../../Include/Common/Rva0023C6A4.h"
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
   const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(name);
   if (!thingTemplate) return;
   CreateMask mask;
   memset(&mask,0,sizeof(mask));
   Object *obj = TheThingFactory->newObject(thingTemplate,team,&mask,(ObjectID)0);
   startingObject = obj->getID();
   ((Rva0028CBFD *)obj)->rva0028CBFD();
  }
 }
 rva002A99FA();
 if (ai) ai->newMap();
 if (TheWritableGlobalData->field09C0 ||
     (TheGameInfo && (TheGameInfo->isSkirmish() || TheGameInfo->isMultiPlayer() || TheGameInfo->isSandbox())) ||
     (TheGameLogic && ((BfmeGlob939D *)TheGameLogic)->bfmeCall939D()))
  initBuildableHeroes();
 enableView.setEnabled(true);
}
void Player::initBuildableHeroes() {
 if (TheGameLogic->m_114 != 3) {
  if (livingWorldID == -1) return;
  LivingWorldPlayer *living = (LivingWorldPlayer *)((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(livingWorldID,0);
  if (living) {
   _STL::vector<Rva002E2690Element> units;
   living->ExtractRevivalUnitDataForCurrentMap(&units);
   for (unsigned int i=0;i<units.size();++i)
    revival.addRevivableUnit(*(Rva002E2D10Record *)&units[i],this);
  }
 } else {
  if (((Rva0023C6A4 *)TheGameLogic)->rva00200084()) return;
  const PlayerTemplate *pt = playerTemplate;
  if (!pt) return;
  int count = pt->heroEnd-pt->heroBegin;
  for (int i=0;i<count;++i) {
   const ThingTemplate *thingTemplate=TheThingFactory->findTemplate(pt->heroBegin[i]);
   if (thingTemplate) revival.addInitialBuildUnit(thingTemplate,this);
  }
 }
}
