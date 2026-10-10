// ?rva0050B98F@Made002CCC2D@@QAEXPBUFadeInputPrefix@@H@Z
// partial score=0.8766027866500022 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /Oy- /MD /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
#include <math.h>
#include <string.h>
#include "ascii_string.h"
#include "Coord3D.h"
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Team;class ThingTemplate;
struct CreateMask {unsigned words[4];};
class ThingFactory {public:const ThingTemplate *findTemplate(const AsciiString&);Object *newObject(const ThingTemplate*,Team*,const CreateMask*,bool);};
extern ThingFactory *TheThingFactory;
class Thing {public:void setPosition(const Coord3D*);void setOrientation(float);};
enum DamageType { DAMAGE_UNKNOWN=8 };enum DeathType { DEATH_UNKNOWN=22 };
class Object {public:int rva0028B511()const;void kill(DamageType,DeathType);};
struct FadeObjectPrefix {char unknown00[4];const ThingTemplate *objectTemplate;char unknown08[0x38-8];Coord3D position;float angle;char unknown48[0x304-0x48];Team *team;};
class Pathfinder {public:void AddObjectToPathfindMap(Object*);};
class AI;extern AI *TheAI;
struct FadeAIView {char unknown[0x10];Pathfinder *pathfinder;};
class TerrainLogic;extern TerrainLogic *TheTerrainLogic;
class FadeTerrainPrefix {public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual float height(float,float,int,void*,bool);};
struct FadeInputPrefix {char unknown[8];ObjectID id;};
class Made002CCC2D {public:void rva0050B98F(const FadeInputPrefix*,int);private:char unknown[0x12C];AsciiString name;float offsetX,offsetY,offsetZ;};
void Made002CCC2D::rva0050B98F(const FadeInputPrefix *input,int unused) {
 Object *source=TheGameLogic->findObjectByID(input->id);
 const ThingTemplate *type=TheThingFactory->findTemplate(name);
 if(type) {
  CreateMask mask;memset(&mask,0,sizeof(mask));
  Object *made=TheThingFactory->newObject(type,(((FadeObjectPrefix*)source)->team?((FadeObjectPrefix*)source)->team:((FadeObjectPrefix*)source)->team),&mask,false);
  Coord3D position;
  position.x=((FadeObjectPrefix*)source)->position.x;
  position.y=((FadeObjectPrefix*)source)->position.y;
  position.z=((FadeObjectPrefix*)source)->position.z;
  Coord3D offset;offset.x=offsetX;offset.y=offsetY;
  float angle=((FadeObjectPrefix*)source)->angle;
  struct TrigPair {float c,s;} trig;
  trig.s=(float)sin((double)angle);
  trig.c=(float)cos((double)angle);
  float x=offset.x,y=offset.y;
  float dx=x*trig.c-y*trig.s;
  float dy=x*trig.s+y*trig.c;
  offset.x=dx;offset.y=dy;
  position.x+=offset.x;position.y+=offset.y;
  position.z=((FadeTerrainPrefix*)TheTerrainLogic)->height(position.x,position.y,source->rva0028B511(),0,true);
  ((Thing*)made)->setPosition(&position);
  ((Thing*)made)->setOrientation(angle);
  source->kill(DAMAGE_UNKNOWN,DEATH_UNKNOWN);
  if(*(const unsigned char*)((const char*)((FadeObjectPrefix*)made)->objectTemplate+0x11D)&0x10)
   ((FadeAIView*)TheAI)->pathfinder->AddObjectToPathfindMap(made);
 }
}
