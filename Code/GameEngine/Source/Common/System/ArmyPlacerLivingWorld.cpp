// Native37FD2B..37FE3D RET16; WB F632F0 ArmyPlacer::PlaceLivingWorldArmy.
// Existing 4B Rva0037F57E ctor/dtor receiver carrier retained; naming/layout
// reconciliation is separate. The list policy matches the verified native
// DB8FEC pooled header used by ArmySummary Load. Target calls prove every ABI.
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
#include "Coord3D.h"
#include "ascii_string.h"
class Object;
template<class T>class Rva001EB984PoolAllocator {};
namespace _STL{template<class T>class allocator;template<class T,class A>class list;}
typedef _STL::list<Object*,Rva001EB984PoolAllocator<Object*> > LoadedObjectList;
struct Rva0037FE3DNode{Rva0037FE3DNode*next;};
struct Rva0037FE3DList{Rva0037FE3DNode*head;};
class Player;
class Rva0037FE3D{public:void rva0037FAC6(const Rva0037FE3DList&,const Coord3D*,const Coord3D*,Player*,bool);};
class Rva002E2903Player{public:char bytes00[0x14];int playerID;};
class ArmySummary{public:bool getSpawnPositions(int,Coord3D*,Coord3D*,bool);};
struct Rva002B488EResult{char bytes00[0x78];ArmySummary*summary;};
class Rva0037F57E{public:Rva0037F57E();virtual~Rva0037F57E();void rva0037FD2B(LoadedObjectList*,Rva002E2903Player*,Rva002B488EResult*,bool);};
class Player;
class PlayerList{public:Player*Rva002A7A6F(int);};extern PlayerList*ThePlayerList;
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class Rva002B2B66{public:int rva002B2B66();};
class View;
// Pointer-only native virtual prefix; no complete View layout is asserted.
class Rva0037FDE9CameraSlots{public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
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
 virtual void slot48();
 virtual void slot49();
 virtual void atC8(const Coord3D*,int,float,float);
};extern View*TheTacticalView;
enum RadarEventType{RADAR_EVENT_INVALID=11};
class Radar{public:void createEvent(const Coord3D*,RadarEventType,float);};extern Radar*TheRadar;
class InGameUI;
// Native slot48 is a cdecl member: explicit this plus value-string are popped.
class Rva0037FE31MessageSlots{public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void __cdecl at48(AsciiString);
};extern InGameUI*TheInGameUI;
void Rva0037F57E::rva0037FD2B(LoadedObjectList*list,Rva002E2903Player*lwPlayer,Rva002B488EResult*army,bool reinforcement){
 const Rva0037FE3DList&view=*(const Rva0037FE3DList*)list;
 if(view.head->next==view.head)return;
 Player*player=ThePlayerList->Rva002A7A6F(lwPlayer->playerID);
 if(!player)return;
 Coord3D spawn={0.f,0.f,0.f},gather={1.f,0.f,0.f};
 army->summary->getSpawnPositions(lwPlayer->playerID,&spawn,&gather,reinforcement);
 ((Rva0037FE3D*)this)->rva0037FAC6(view,&spawn,&gather,player,reinforcement);
 int playerID=lwPlayer->playerID;
 if(((Rva002B2B66*)TheLivingWorldLogic)->rva002B2B66()!=playerID)return;
 if(!reinforcement)((Rva0037FDE9CameraSlots*)TheTacticalView)->atC8(&gather,0,0.f,0.f);
 else{
  if(TheRadar)TheRadar->createEvent(&gather,(RadarEventType)0,4.f);
  if(TheInGameUI)((Rva0037FE31MessageSlots*)TheInGameUI)->at48(AsciiString("LW:ReinforcementsArrived"));
 }
}
