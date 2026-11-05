// cl: /O1 /G7 /arch:SSE /MD /EHsc /ICode/Libraries/Include
// Native29DB61..29DCA9328B posts a formation-facing command and voice response.
// ZH placement/voice routines guide the composition; BFME command464 and
// fields5AC/5B0/990/9B0 plus virtual slots7C/C0/C4/124 are native facts.
// Direction helper29D9F9 writes two floats to the caller slot and returns its
// address withRET4; the by-value Coord2D ABI is an inference, not a recovered
// original name. A short local scope gives native stack-slot reuse for angle.
// Native29D9F9..29DB61 (360B) is that helper: the drag vector end-start (+0x99C,
// +0x990); below the formation assistant's threshold (+0x2C) the cached direction
// (+0x9A8, valid +0x98D) or the summed start-minus-object offsets of the selected
// drawables (slot 0x124), normalized and scaled to half the threshold. The
// WorldBuilder twin 0x00DC3470 expands MathCoord2D.h's GetLengthSqrd, Set, Add,
// Normalize/GetLength and Scale inlines; spelling them as members of a TU-local
// Coord2D view (sqr(y)+x*x, <math.h> sqrt) gives retail's XMM roles, which free
// helper functions did not. Coord2DCtorView.h's user copy constructor gives the
// cached-direction fld/fstp + mov return copy.
#include "Lib/Coord2DCtorView.h"
#include "Lib/Coord3D.h"
#include <math.h>
class Object {public:const Coord3D *getPosition() const {return &m_position;} private:char m_pad[0x38];Coord3D m_position;};
#include "../../Include/GameClient/Drawable.h"
struct DrawableListNode {DrawableListNode *m_next;DrawableListNode *m_prev;Drawable *m_drawable;};
class DrawableList {public:DrawableListNode *m_head;};
static __forceinline float sqr(float v){return v*v;}
struct C2 : Coord2D
{
public:
	__forceinline float GetLengthSqrd() const {return sqr(y)+x*x;}
	__forceinline float GetLength() const {return sqrt(sqr(y)+x*x);}
	__forceinline void Normalize() {float len=GetLength();float inv=1.0f/len;x*=inv;y*=inv;}
	__forceinline C2 &operator*=(float s) {x*=s;y*=s;return *this;}
	__forceinline void Scale(float s) {x*=s;y*=s;}
	__forceinline void Add(const Coord2D &other) {x+=other.x;y+=other.y;}
	__forceinline void Set(float ax,float ay) {x=ax;y=ay;}
};
#define C2R(v) static_cast<C2&>(v)
class PickAndPlayInfo {public:PickAndPlayInfo();bool air;void *target;void *weapon;int special;unsigned unknown10;Coord3D position;int unknown20;};
#include "../../Include/Common/MessageStream.h"
bool pickAndPlayUnitVoiceResponse(const DrawableList *,GameMessage::Type,PickAndPlayInfo *);
extern MessageStream *TheMessageStream;
#include "../../Include/GameClient/GameClientClass.h"
extern GameClient *TheGameClient;
class Rva0022AD10Subsystem {public:char pad2c[0x2c];float threshold;char pad30[4];bool active;};
extern Rva0022AD10Subsystem *TheFormationAssistant;
extern int BfmeClientFramesPerSecond;
#include "../../Include/GameClient/CommandButton.h"
class InGameUI {public:
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
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual const CommandButton *getPending();
virtual void resetPlacement(bool);
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual bool rva0029DB61();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual const DrawableList *getAllSelectedDrawables();
Coord2D rva0029D9F9();
char pad4[0x5ac-4];int expires;bool active;char pad5b1[0x98d-0x5b1];bool directionValid;char pad98e[2];Coord3D position;Coord3D end;Coord2D direction;int formation;
};
extern InGameUI *TheInGameUI;
__declspec(noinline) inline Coord2D InGameUI::rva0029D9F9() {
 Coord2D dir(end.x-position.x,end.y-position.y);
 if(C2R(dir).GetLengthSqrd()<TheFormationAssistant->threshold*TheFormationAssistant->threshold) {
  if(directionValid)return direction;
  C2R(dir).Set(0.0f,0.0f);
  const DrawableList *list=getAllSelectedDrawables();
  for(DrawableListNode *node=list->m_head->m_next;node!=list->m_head;node=node->m_next) {
   Object *obj=node->m_drawable->getObject();
   if(obj) {
    const Coord3D *pos=obj->getPosition();
    Coord2D delta(position.x-pos->x,position.y-pos->y);
    C2R(dir).Add(delta);
   }
  }
  C2R(dir).Normalize();
  C2R(dir).Scale(TheFormationAssistant->threshold/2.0f);
 } else {
  directionValid=true;
 }
 direction=dir;
 return dir;
}
bool InGameUI::rva0029DB61() {
 bool result=false;
 expires=TheGameClient->getFrame()+1.5*BfmeClientFramesPerSecond;
 if(!expires)expires=1;
 if(active) {
  float angle;{Coord2D direction=rva0029D9F9();angle=direction.toAngle();}
  bool armed=false;
  const CommandButton *button=TheInGameUI->getPending();
  if(button && button->m_command==10)armed=true;
  GameMessage *msg=TheMessageStream->appendMessage(GameMessage::MSG_DO_MOVETO_FORMATION);
  Coord3D p;p.x=position.x;p.y=position.y;p.z=position.z;
  msg->appendLocationArgument(p);msg->appendRealArgument(angle);msg->appendIntegerArgument(formation);msg->appendBooleanArgument(armed);
  PickAndPlayInfo info;info.position=position;
  pickAndPlayUnitVoiceResponse(getAllSelectedDrawables(),GameMessage::MSG_DO_MOVETO_FORMATION,&info);
  result=true;TheFormationAssistant->active=true;
 }
 resetPlacement(false);return result;
}
