// cl: /O1 /G7 /arch:SSE /MD /EHsc /ICode/Libraries/Include
// Native29DB61..29DCA9328B posts a formation-facing command and voice response.
// ZH placement/voice routines guide the composition; BFME command464 and
// fields5AC/5B0/990/9B0 plus virtual slots7C/C0/C4/124 are native facts.
// Direction helper29D9F9 writes two floats to the caller slot and returns its
// address withRET4; the by-value Coord2D ABI is an inference, not a recovered
// original name. A short local scope gives native stack-slot reuse for angle.
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
class DrawableList;
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
class Rva0022AD10Subsystem {public:char pad34[0x34];bool active;};
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
char pad4[0x5ac-4];int expires;bool active;char pad5b1[0x990-0x5b1];Coord3D position;char pad99c[0x9b0-0x99c];int formation;
};
extern InGameUI *TheInGameUI;
bool InGameUI::rva0029DB61() {
 bool result=false;
 expires=TheGameClient->getFrame()+1.5*g_009BA4E8;
 if(!expires)expires=1;
 if(active) {
  float angle;{Coord2D direction=rva0029D9F9();angle=direction.toAngle();}
  bool armed=false;
  const CommandButton *button=TheInGameUI->getPending();
  if(button && button->command==10)armed=true;
  GameMessage *msg=TheMessageStream->createMessage(0x464);
  Coord3D p;p.x=position.x;p.y=position.y;p.z=position.z;
  msg->appendLocationArgument(p);msg->appendRealArgument(angle);msg->appendIntegerArgument(formation);msg->appendBooleanArgument(armed);
  PickAndPlayInfo info;info.position=position;
  pickAndPlayUnitVoiceResponse(getAllSelectedDrawables(),GameMessage::MSG_FORMATION,&info);
  result=true;TheFormationAssistant->active=true;
 }
 resetPlacement(false);return result;
}
