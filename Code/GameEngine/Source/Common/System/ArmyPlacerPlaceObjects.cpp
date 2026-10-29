// Native 0037FAC6..0037FD2B, RET20; WB00F62D50 names ArmyPlacer::PlaceObjects.
// Retain the established receiver name until the ArmyPlacer views are merged.
// The native +258 AI view and slots168/188 supply the airborne height path;
// only accessed prefixes are modeled. Two EH states reset the local-static
// name/key guard bits; coordinates and the 32-byte command own no cleanup.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
#include "ascii_string.h"
#include "Coord3D.h"
#include "../GameLogicObjectLookupView.h"
class Player;
#include "../Thing/thing.h"
class ArmyLocomotor {public:char pad[0x48];float flightHeight;};
class ArmyLocomotorSet {public:char pad[0x1d0];ArmyLocomotor**locomotors;};
class ArmyUnitAI {public:
 virtual void slot000();
 virtual void slot001();
 virtual void slot002();
 virtual void slot003();
 virtual void slot004();
 virtual void slot005();
 virtual void slot006();
 virtual void slot007();
 virtual void slot008();
 virtual void slot009();
 virtual void slot010();
 virtual void slot011();
 virtual void slot012();
 virtual void slot013();
 virtual void slot014();
 virtual void slot015();
 virtual void slot016();
 virtual void slot017();
 virtual void slot018();
 virtual void slot019();
 virtual void slot020();
 virtual void slot021();
 virtual void slot022();
 virtual void slot023();
 virtual void slot024();
 virtual void slot025();
 virtual void slot026();
 virtual void slot027();
 virtual void slot028();
 virtual void slot029();
 virtual void slot030();
 virtual void slot031();
 virtual void slot032();
 virtual void slot033();
 virtual void slot034();
 virtual void slot035();
 virtual void slot036();
 virtual void slot037();
 virtual void slot038();
 virtual void slot039();
 virtual void slot040();
 virtual void slot041();
 virtual void slot042();
 virtual void slot043();
 virtual void slot044();
 virtual void slot045();
 virtual void slot046();
 virtual void slot047();
 virtual void slot048();
 virtual void slot049();
 virtual void slot050();
 virtual void slot051();
 virtual void slot052();
 virtual void slot053();
 virtual void slot054();
 virtual void slot055();
 virtual void slot056();
 virtual void slot057();
 virtual void slot058();
 virtual void slot059();
 virtual void slot060();
 virtual void slot061();
 virtual void slot062();
 virtual void slot063();
 virtual void slot064();
 virtual void slot065();
 virtual void slot066();
 virtual void slot067();
 virtual void slot068();
 virtual void slot069();
 virtual void slot070();
 virtual void slot071();
 virtual void slot072();
 virtual void slot073();
 virtual void slot074();
 virtual void slot075();
 virtual void slot076();
 virtual void slot077();
 virtual void slot078();
 virtual void slot079();
 virtual void slot080();
 virtual void slot081();
 virtual void slot082();
 virtual void slot083();
 virtual void slot084();
 virtual void slot085();
 virtual void slot086();
 virtual void slot087();
 virtual void slot088();
 virtual void slot089();
 virtual bool at168();
 virtual void slot091();
 virtual void slot092();
 virtual void slot093();
 virtual void slot094();
 virtual void slot095();
 virtual void slot096();
 virtual void slot097();
 virtual ArmyLocomotorSet*at188();
};
class Object {public:void teleportTo(const Coord3D*,bool);char pad[0x258];ArmyUnitAI *ai;};
extern GameLogic*TheGameLogic;
struct Rva0037FE3DNode {Rva0037FE3DNode*next,*prev;Object*object;};
struct Rva0037FE3DList {Rva0037FE3DNode*head;};
struct Rva00372571Params;
class AIGroup {public:void add(Object*);void groupMoveToPosition(Rva00372571Params*,int);void groupSetPositionInFormation(const Coord3D*,const Coord3D*,int);};
class AI {public:AIGroup*createGroup();void destroyGroup(AIGroup*);};extern AI*TheAI;
class BfmeC986 {public:void bfmeGo986C(int,int,int,int);};
enum NameKeyType{NAMEKEY_INVALID=0};
class NameKeyGenerator {public:NameKeyType nameToKey(const AsciiString&);};extern NameKeyGenerator*TheNameKeyGenerator;
struct FormationPlacement {int kind;ObjectID id;char pad[0x10];float x,y;};
class Formation {public:void rva0042245F(float);void optimizeUnits(const Coord3D*);FormationPlacement*start,*finish,*end;};
class Rva001EB130Holder;
class FormationAssistant {public:int rva00422D1C(int);Formation*rva00424E77(int,Rva001EB130Holder*,const Coord3D*);};
class Rva0022AD10Subsystem;extern Rva0022AD10Subsystem*TheFormationAssistant;
namespace _STL{template<class T>class char_traits;template<class T>class allocator;template<class T,class C,class A>class basic_string;}
class Rva00423FBDThis {public:void Delete(_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> >*);};
class Rva0036CB94 {public:Rva0036CB94(int,int,int,int,bool);int position;unsigned char waypoint;int ignore,target,facing,formation,player;bool attack;};
#include <math.h>	// its atan2f body is retail 0x000422A0
class ArmyPlacer {public:void rva0037FAC6(const Rva0037FE3DList&,const Coord3D*,const Coord3D*,Player*,bool);};
void ArmyPlacer::rva0037FAC6(const Rva0037FE3DList&objects,const Coord3D*start,const Coord3D*goal,Player*player,bool walkOn) {
 AIGroup*group=TheAI->createGroup();
 if(!group)return;
 for(Rva0037FE3DNode*it=objects.head->next;it!=objects.head;it=it->next)group->add(it->object);
 static AsciiString templateName("WalkOnTemplate");
 static NameKeyType templateKey=TheNameKeyGenerator->nameToKey(templateName);
 int formationType=((FormationAssistant*)TheFormationAssistant)->rva00422D1C(templateKey);
 if(formationType!=-1){
  float angle=atan2f(goal->y-start->y,goal->x-start->x);
  Formation*formation=((FormationAssistant*)TheFormationAssistant)->rva00424E77(formationType,(Rva001EB130Holder*)&objects,start);
  if(formation){
   formation->rva0042245F(angle);
   formation->optimizeUnits(start);
   FormationPlacement*last=formation->finish;
   for(FormationPlacement*it=formation->start;it!=last;++it){
    Object*object=TheGameLogic->findObjectByID(it->id);
    if(object){
     Coord3D position={start->x+it->x,start->y+it->y,start->z};
     ArmyUnitAI*ai=object->ai;
     if(ai && ai->at168()){
      ArmyLocomotorSet*set=ai->at188();
      ArmyLocomotor*locomotor=set?set->locomotors[0]:0;
      position.z+=locomotor?locomotor->flightHeight:200.0f;
     }
     object->teleportTo(&position,true);
     ((Thing*)object)->setOrientation(angle);
    }
   }
   ((Rva00423FBDThis*)TheFormationAssistant)->Delete((_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> >*)formation);
  }
  if(walkOn){
   Rva0036CB94 parameters((int)goal,(int)&angle,formationType,(int)player,false);
   group->groupMoveToPosition((Rva00372571Params*)&parameters,2);
  }
 }else{
  group->groupSetPositionInFormation(start,goal,2);
  ((BfmeC986*)group)->bfmeGo986C((int)goal,2,0,1);
 }
 TheAI->destroyGroup(group);
}
