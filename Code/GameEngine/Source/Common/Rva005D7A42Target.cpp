// cl: /O1 /G7 /arch:SSE /MD /ICode/GameEngine/Source/Common
// Target whole113 RET4, native5D7A42..5D7AB3. Incoming Object identity
// is independently established by getControllingPlayer28AFA9 and owned
// lookup49DC5; body-pointer254 and coordinate-address38 are retail facts.
// The owned AoE provider uses the struct Coord3D pointer spelling; its
// current declaration is retained without introducing a second symbol pin.
// The floating result at body vslot14 and the original owner/method names
// remain opaque. This receiver view is never constructed and claims no extent.
#include "GameLogicObjectLookupView.h"
class Player;struct Coord3D;
class Rva005D7A42Body {public:virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual float value14();};
class Object {public:Player *getControllingPlayer()const;char pad[0x254];Rva005D7A42Body*body;};
#include "../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;
extern GameLogic *TheGameLogic;
#include "../../Include/Common/Rva005C4AD1LeaField.h"
struct Rva005D7A42Store {char pad[8];Rva005C4AD1LeaField*owner;};
struct Rva005D7A42IDs {ObjectID*begin;ObjectID*end;ObjectID*limit;};
#include "../../Include/Common/Rva005EE816.h"
class Rva005D7A42 {public:bool rva005D7A42(Object*source);};
// ?rva005D7A42@Rva005D7A42@@QAE_NPAVObject@@@Z
bool Rva005D7A42::rva005D7A42(Object*source){
 Rva005D7A42Store*store=(Rva005D7A42Store*)TheSkirmishAIManager->rva002A8F24(source->getControllingPlayer());
 Rva005D7A42IDs*ids=(Rva005D7A42IDs*)store->owner->get();
 for(ObjectID*objectID=ids->begin;objectID!=ids->end;++objectID){
  Object*object=TheGameLogic->findObjectByID(*objectID);
  if(object->body->value14()<0.5f)return ((Rva005EE816*)this)->rva005EE8DD((const Coord3D*)((char*)object+0x38),source);
 }
 return false;
}
