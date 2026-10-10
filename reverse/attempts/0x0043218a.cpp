// ?translateGameMessage@PlaceEventTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z
// partial score=0.9761537616920237 date=2026-10-10
// ?translateGameMessage@PlaceEventTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z
// partial score=0.9682092474785946 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /I. /ICode/GameEngine/Include /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /DWIN32 /MD /ICode/Libraries/Include /ICode/GameEngine/Include /ICode/GameEngine/Source/Common /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <list>
#include <math.h>
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Common/BfmeAudioEventPrefix136.h"
extern GameLogic *TheGameLogic;
struct Rva001EDD80Pair {int x,y;};
class Rva001EDD80 {public:bool rva001EDD80(const Rva001EDD80Pair*,const Rva001EDD80Pair*);};
class Mouse {public:char pad[0x12F0];unsigned int doubleClickTime;};extern Mouse *TheMouse;
class Drawable;
class DrawableList:public _STL::list<Drawable*>{public:__forceinline DrawableList(){} ~DrawableList()throw();};
class PickAndPlayInfo {public:PickAndPlayInfo();bool air;Drawable*target;void*weapon;int power;unsigned int unknown10;Coord3D position;unsigned int unknown20;};
class Player {public:char pad[0x54];int index;};
class Object {public:Player*getControllingPlayer()const;Drawable*getDrawable()const;char pad[0x38];Coord3D position;char pad44[0x74-0x44];ObjectID id;};
class ThingTemplate {public:char pad[0x11F];unsigned char kinds;char pad120[0x5D8-0x120];unsigned short templateID;};
union GameMessageArgumentType {int integer;Rva001EDD80Pair pixel;};
class GameMessage {public:enum Type{CONSTRUCT=0x41A,PORT=0x463,CANNOT=0x7EB};const GameMessageArgumentType*getArgument(int)const;void appendIntegerArgument(int);void appendLocationArgument(const Coord3D&);void appendRealArgument(float);void appendObjectIDArgument(ObjectID);Type getType()const{return type;}char pad[0x10];Type type;};
void pickAndPlayUnitVoiceResponse(const DrawableList*,GameMessage::Type,PickAndPlayInfo*);
bool Rva0030596CIntersects(void*,Coord3D,float);
typedef bool (__cdecl *PlacementIntersects)(void*,BfmeEventPositionView,float);
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
class InGameUI {public:
V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14)
virtual void message(AsciiString,...); //3C cdecl
V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24)
virtual void displayCantBuildMessage(int); //64
V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43) V(44) V(45) V(46)
virtual void clearMode(bool); //BC
virtual struct PlacementOptions *getOptions(); //C0
V(49) V(50) V(51) V(52) V(53) V(54)
virtual void placeBuildAvailable(const ThingTemplate*,const Object*); //DC
virtual const ThingTemplate*getPendingPlaceType(); //E0
virtual ObjectID getPendingPlaceSourceObjectID(); //E4
virtual void setPlacementStart(const Rva001EDD80Pair*); //E8
virtual void setPlacementEnd(const Rva001EDD80Pair*); //EC
virtual bool isPlacementAnchored(); //F0
virtual void getPlacementPoints(Rva001EDD80Pair*,Rva001EDD80Pair*); //F4
virtual float getPlacementAngle(); //F8
virtual bool canPlacePort(); //FC
virtual void clearPlacementPort(bool); //100
virtual void resetPlacementPort(); //104
V(66) V(67) V(68) V(69) V(70) V(71) V(72)
virtual DrawableList *getAllSelectedDrawables(); //124
V(74) V(75) V(76) V(77) V(78) V(79) V(80)
virtual void setRadiusCursorNone(); //144
};
extern InGameUI *TheInGameUI;
struct PlacementOptions {char pad[0x1C];int value;};
class View {public:V10(0) V10(1) V10(2) V10(3) V10(4) V10(5) V10(6) V10(7) V10(8) virtual void screenToTerrain(const Rva001EDD80Pair*,Coord3D*,bool);};extern View*TheTacticalView;
class BuildAssistant {public:V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
virtual int isLocationLegalToBuild(const Coord3D*,const ThingTemplate*,float,int,Object*,Object*); //40
V(17) V(18) V(19) V(20) V(21) V(22)
virtual bool isBuildPort(const ThingTemplate*,Object*); //5C
virtual int canMakeUnit(Object*,const ThingTemplate*,int); //60
void getPortTransform(const Coord3D*,const ThingTemplate*,float,float*,Coord3D*);
};extern BuildAssistant*TheBuildAssistant;
class GhostObjectManager {public:char pad[4];int playerIndex;};extern GhostObjectManager*TheGhostObjectManager;
class MessageStream {public:V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) virtual GameMessage*appendMessage(GameMessage::Type);};extern MessageStream*TheMessageStream;
struct MiscAudio {char pad[0xE8];OpaqueRefElement4 noCanDo;};
class AudioManager {public:V10(0) V10(1) V(20) V(21) V(22) V(23) V(24) virtual void addAudioEvent(const BfmeAudioEventPrefix136*);V(26) V(27) V(28) V(29) V10(3) V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) virtual MiscAudio*getMiscAudio();};extern AudioManager*TheAudio;
#undef V10
#undef V
enum GameMessageDisposition {KEEP_MESSAGE=0,DESTROY_MESSAGE=1};
class PlaceEventTranslator {public:virtual GameMessageDisposition translateGameMessage(const GameMessage*);Rva001EDD80Pair downPos;unsigned int downFrame,upFrame;bool down,drag;};
GameMessageDisposition PlaceEventTranslator::translateGameMessage(const GameMessage *msg){
 GameMessageDisposition disp=KEEP_MESSAGE;
 switch(msg->getType()){
 case 14: downPos=msg->getArgument(0)->pixel;downFrame=msg->getArgument(2)->integer;down=true;drag=false;break;
 case 16: if(down){upFrame=msg->getArgument(2)->integer;down=false;}break;
 case 4:{
  const ThingTemplate *build=TheInGameUI->getPendingPlaceType();
  if(build&&!TheInGameUI->isPlacementAnchored()){
   Rva001EDD80Pair mouse=msg->getArgument(0)->pixel;Coord3D world;TheTacticalView->screenToTerrain(&mouse,&world,false);
   Object *builder=TheGameLogic->findObjectByID(TheInGameUI->getPendingPlaceSourceObjectID());
   if(!builder){TheInGameUI->placeBuildAvailable(0,0);break;}
   TheInGameUI->setPlacementStart(&mouse);disp=DESTROY_MESSAGE;
  }break;
 }
 case 3:{
  Rva001EDD80Pair mouse=msg->getArgument(0)->pixel;
  if(down&&((Rva001EDD80*)TheMouse)->rva001EDD80(&downPos,&mouse))drag=true;
  if(TheInGameUI->isPlacementAnchored()){
   Rva001EDD80Pair start;TheInGameUI->getPlacementPoints(&start,0);int x=mouse.x-start.x,y=mouse.y-start.y;
   float dragDistance=(float)sqrt((double)(x*x+y*y));if(dragDistance>=5.0f){TheInGameUI->setPlacementEnd(&mouse);disp=DESTROY_MESSAGE;}
  }break;
 }
 case 27:case 28:
  if(TheInGameUI->getPendingPlaceType()){
   if(drag&&upFrame-downFrame>=TheMouse->doubleClickTime)break;
   TheInGameUI->clearMode(false);TheInGameUI->placeBuildAvailable(0,0);disp=DESTROY_MESSAGE;
  }break;
 case 23:case 24:{
  const ThingTemplate *build=TheInGameUI->getPendingPlaceType();TheInGameUI->setRadiusCursorNone();
  if(build&&TheInGameUI->isPlacementAnchored()){
   float angle=TheInGameUI->getPlacementAngle();Coord3D world;Rva001EDD80Pair start,end;
   TheInGameUI->getPlacementPoints(&start,&end);TheTacticalView->screenToTerrain(&start,&world,false);
   Object *builder=TheGameLogic->findObjectByID(TheInGameUI->getPendingPlaceSourceObjectID());
   bool port=TheBuildAssistant->isBuildPort(build,builder);
   int canMake=TheBuildAssistant->canMakeUnit(builder,build,-1);
   if(canMake!=0&&canMake!=1){
    if(canMake==2){TheInGameUI->message("GUI:NotEnoughMoneyToBuild");break;}
    else if(canMake==4){TheInGameUI->message("GUI:ProductionQueueFull");break;}
    else if(canMake==5){TheInGameUI->message("GUI:ParkingPlacesFull");break;}
    else if(canMake==6){TheInGameUI->message("GUI:UnitMaxedOut");break;}
    TheInGameUI->placeBuildAvailable(0,0);break;
   }
   int legal;
   if(port)legal=0;else legal=TheBuildAssistant->isLocationLegalToBuild(&world,build,angle,0x49F,builder,0);
   if(builder){int index=TheGhostObjectManager->playerIndex;if(index==(TheGameLogic?builder->getControllingPlayer():builder->getControllingPlayer())->index&&((PlacementIntersects)Rva0030596CIntersects)((void*)build,*(const BfmeEventPositionView*)&world,angle))legal=8;}
   bool skip=false;
   if(port&&!TheInGameUI->canPlacePort()){TheInGameUI->setPlacementStart(0);skip=true;}
   if(legal==0){
    if(skip){disp=DESTROY_MESSAGE;break;}
    if(build->kinds&0x10){float newAngle;Coord3D newWorld;TheBuildAssistant->getPortTransform(&world,build,angle,&newAngle,&newWorld);world=newWorld;angle=newAngle;}
    if(TheBuildAssistant->isBuildPort(build,builder)){
     if(TheInGameUI->canPlacePort()){
     GameMessage *place=TheMessageStream->appendMessage(GameMessage::PORT);place->appendIntegerArgument(build->templateID);
     place->appendLocationArgument(builder->position);place->appendLocationArgument(world);
     TheInGameUI->clearPlacementPort(false);TheInGameUI->resetPlacementPort();
     int value=0xFFFFFE;PlacementOptions *options=TheInGameUI->getOptions();if(options)value=options->value;place->appendIntegerArgument(value);place->appendObjectIDArgument(builder->id);
     }
    }else{
     GameMessage *place=TheMessageStream->appendMessage(GameMessage::CONSTRUCT);place->appendIntegerArgument(build->templateID);place->appendLocationArgument(world);place->appendRealArgument(angle);
     GameMessage::Type type=place->getType();pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(),type,0);
     TheInGameUI->clearPlacementPort(false);TheInGameUI->resetPlacementPort();
    }
    TheInGameUI->clearMode(false);TheInGameUI->placeBuildAvailable(0,0);
   }else{
    if(!skip){
     TheInGameUI->displayCantBuildMessage(legal);DrawableList list;list.push_back(builder->getDrawable());PickAndPlayInfo info;info.position=world;
     pickAndPlayUnitVoiceResponse(&list,GameMessage::CANNOT,&info);
     static BfmeAudioEventPrefix136 noCanDoSound(TheAudio->getMiscAudio()->noCanDo,0);TheAudio->addAudioEvent(&noCanDoSound);TheInGameUI->setPlacementStart(0);
    }
   }
   disp=DESTROY_MESSAGE;
  }break;
 }
 }
 return disp;
}
