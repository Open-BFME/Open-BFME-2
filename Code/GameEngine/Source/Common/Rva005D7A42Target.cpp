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
class Rva002A8F24 {public:void *rva002A8F24(Player*);};
extern Rva002A8F24 *g_00DFEEF8;
extern GameLogic *TheGameLogic;
class Rva005C4AD1LeaField {public:void *get()const;};
struct Rva005D7A42Store {char pad[8];Rva005C4AD1LeaField*owner;};
struct Rva005D7A42IDs {ObjectID*begin;ObjectID*end;ObjectID*limit;};
class Rva005EE816 {public:bool rva005EE8DD(const Coord3D*,Object*);};
class Rva005D7A42 {public:bool rva005D7A42(Object*source);};
// ?rva005D7A42@Rva005D7A42@@QAE_NPAVObject@@@Z
bool Rva005D7A42::rva005D7A42(Object*source){
 Rva005D7A42Store*store=(Rva005D7A42Store*)g_00DFEEF8->rva002A8F24(source->getControllingPlayer());
 Rva005D7A42IDs*ids=(Rva005D7A42IDs*)store->owner->get();
 for(ObjectID*p=ids->begin;p!=ids->end;++p){
  Object*object=TheGameLogic->findObjectByID(*p);
  if(object->body->value14()<0.5f)return ((Rva005EE816*)this)->rva005EE8DD((const Coord3D*)((char*)object+0x38),source);
 }
 return false;
}
