// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /MD

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "Common/BfmeAudioEventPrefix136.h"
// PC worker2DA1CC-2DA318: native object/drawable constructors2DA461/2DA4DB
// pass the hidden three-float return buffer and bool reference here. Tags1/2
// dispatch to GameClient slot0x40 and rowed GameLogic::findObjectByID.
// PC accesses independently establish position+0x3C and validity+0x48 on the
// event, Object position+0x38, and the address-named views in cases3..5.
// BFME1 AudioEventRTSResolveOwnerPosition.cpp at6583b3c1ff21db4a561285717028fdafc780b7db
// supplies the semantic owner-position lead; its layout and case mapping differ.
// The case3..5 receiver identities remain unasserted. Existing global providers
// bind the observed DF EF10/18 storage without adding new singleton spellings.

struct Coord3D {float x,y,z;};
class Drawable {public: const Coord3D *getPosition() const;};
class Object {public: char pad[0x38]; BfmeEventPositionView position;};
// Zero Hour's GameCommon.h spells the id an enum; retail's 0x00049DC5 row takes it.
enum ObjectID { INVALID_ID = 0, FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff };
class GameLogic {public: Object *findObjectByID(ObjectID);};
class GameClient {public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual Drawable *findDrawableByID(int);
};
class Rva003FA835 {public: BfmeEventPositionView rva003FA835();};
class Rva002BFDAE {public: void *rva002BFDAE(void *);};
struct Rva002B488EResult {char pad[0x44];float x,y;};
struct Rva002B2579Position {char pad[0x18];BfmeEventPositionView position;};
struct Rva002B2579Result {char pad[0x2c];Rva002B2579Position *data; Rva002B2579Position *get() const {return data;}};
class Rva002BA8F1Logic {public: Rva002B488EResult *rva002B488E(int);Rva002B2579Result *rva002B2579(int);};
extern GameLogic *TheGameLogic;
extern GameClient *TheGameClient;
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;

BfmeEventPositionView BfmeAudioEventPrefix136::rva002DA1CC(bool &valid) {
 switch(m_int38) {
 case 1: {
  Drawable *draw=TheGameClient->findDrawableByID(m_int34);
  if(draw) {m_b48=1;m_position=*(const BfmeEventPositionView*)draw->getPosition();}
  break;
 }
 case 2: {
  Object *obj=TheGameLogic->findObjectByID((ObjectID)m_int34);
  if(obj) {m_b48=1;m_position=obj->position;}
  break;
 }
 case 3:
  if(g_00DFEF18) {
   Rva003FA835 *window=(Rva003FA835*)((Rva002BFDAE *)g_00DFEF18)->rva002BFDAE((void*)m_int34);
   if(window) {m_b48=1;m_position=window->rva003FA835();}
  }
  break;
 case 4:
  if((*(Rva002BA8F1Logic **)&TheLivingWorldLogic)) {
   Rva002B488EResult *item=(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B488E(m_int34);
   if(item) {m_b48=1; BfmeEventPositionView pos; pos.x=item->x;pos.y=item->y;pos.z=0; m_position=pos;}
  }
  break;
 case 5:
  if((*(Rva002BA8F1Logic **)&TheLivingWorldLogic)) {
   Rva002B2579Result *item=(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B2579(m_int34);
   if(item) {Rva002B2579Position *pos=item->get(); if(pos) {m_b48=1;m_position=pos->position;}}
  }
  break;
 }
 if(m_b48) {valid=true;return m_position;}
 valid=false;
 return BfmeEventPositionView(0,0,0);
}
