// ?rva0029D9F9@InGameUI@@QAE?AVCoord2D@@XZ
// partial score=0.7306874546218809 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /ICode/Libraries/Include
// Native29DB61..29DCA9328B posts a formation-facing command and voice response.
// ZH placement/voice routines guide the composition; BFME command464 and
// fields5AC/5B0/990/9B0 plus virtual slots7C/C0/C4/124 are native facts.
// Native29D9F9..29DB61 RET4 writes two floats through the hidden-result
// argument. The existing caller29DB61 and pin prove its InGameUI receiver;
// Coord2D by-value return is the established ABI view, not a lexical identity.
// ZH InGameUI has no formation-direction counterpart; a clean BFME1
// same-name donor is not established. Native/WB guide this BFME-specific helper.
// WB MathCoord2D supplies the arithmetic guide; offsets and traversal are native.
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
class Object {public:char p[0x38];Coord3D position;};
class Drawable {public:char p[0xfc];Object*object;};
struct FormationDrawNode {FormationDrawNode*next,*prev;Drawable*value;};
class DrawableList {public:FormationDrawNode*head;};
class PickAndPlayInfo {public:PickAndPlayInfo();bool air;void *target;void *weapon;int special;unsigned unknown10;Coord3D position;int unknown20;};
class GameMessage {public:enum Type{MSG_FORMATION=0x464};void appendLocationArgument(const Coord3D &);void appendRealArgument(float);void appendIntegerArgument(int);void appendBooleanArgument(bool);};
void pickAndPlayUnitVoiceResponse(const DrawableList *,GameMessage::Type,PickAndPlayInfo *);
class MessageStream {public:
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
virtual GameMessage *createMessage(int);};
extern MessageStream *TheMessageStream;
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
virtual unsigned getFrame();};
extern GameClient *TheGameClient;
class Rva0022AD10Subsystem {public:char pad2c[0x2c];float threshold;char pad30[4];bool active;};
extern Rva0022AD10Subsystem *TheFormationAssistant;
extern int g_009BA4E8;
class CommandButton {public:char pad14[0x14];int command;};
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
virtual void slot54();
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
Coord2D rva0029D9F9();bool rva0029DB61();
char pad4[0x5ac-4];int expires;bool active;char pad5b1[0x98d-0x5b1];bool cached;char pad98e[2];Coord3D position;Coord3D end;Coord2D direction;int formation;
};
extern InGameUI *TheInGameUI;
#include <math.h>
Coord2D InGameUI::rva0029D9F9() {
 Coord2D d;float threshold=TheFormationAssistant->threshold;
 d.x=end.x-position.x;d.y=end.y-position.y;
 if(threshold*threshold>d.x*d.x+d.y*d.y){
  if(cached)return direction;
  d.x=0.0f;d.y=0.0f;
  const DrawableList*list=getAllSelectedDrawables();
  for(FormationDrawNode*n=list->head->next;n!=list->head;n=n->next){
   Object*obj=n->value->object;if(obj){d.x+=position.x-obj->position.x;d.y+=position.y-obj->position.y;}
  }
  float inv=1.0f/(float)sqrt(d.x*d.x+d.y*d.y);
  float scale=TheFormationAssistant->threshold*0.5f;
  d.x*=inv;d.y*=inv;d.x*=scale;d.y*=scale;
 }else cached=true;
 direction=d;return d;
}
