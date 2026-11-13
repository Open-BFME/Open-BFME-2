// cl: /I. /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Native 0049083C..004909D7 RET0; existing ArrowStorm slot17 caller 490A74
// proves bool/no-argument ABI. Original member name remains unasserted.
// WB 11DD780/ArrowStormUpdate.cpp 217..218 supplies the same control flow;
// no clean BFME1/ZH ArrowStorm body is available at donor575ba2b04.
// Native module4/owner8, target44, list88, ID8C, counters90/94 and data
// C8/DC match the existing target constructor, field parser and xfer.
// Reads of node+8 and findObjectByID prove a four-byte list element;
// reconcile the existing address-derived STL provider to that width.
// Calls bind only existing owned providers. The explicit pop_front
// specialization declaration uses the already-owned 22-byte implementation.

#include <list>
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../Include/Common/Rva004907AAElement.h"
template<> void _STL::list<Rva004907AAElement,_STL::allocator<Rva004907AAElement> >::pop_front();
class Object {public:char pad[0x438];unsigned char status;};
struct ArrowStormUpdateModuleData {char pad[0xC8];AsciiString weapon;float radius;int shotsPerTarget,shotsPerBurst,maxShots;bool emptyGround;};
class WeaponTemplate;
#include "../../../../Include/GameLogic/WeaponStore.h"
extern WeaponStore *TheWeaponStore;
extern GameLogic *TheGameLogic;
#include "../../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
float GetGameLogicRandomValueReal(float,float,char*,int);
class ArrowStormUpdate {
private:
 bool rva0049083C();
 char p00[4];
 const ArrowStormUpdateModuleData *data;
 Object *object;
 char p0c[0x44-0x0c];
 Coord3D target;
 char p50[0x88-0x50];
 _STL::list<Rva004907AAElement,_STL::allocator<Rva004907AAElement> > targets;
 ObjectID current;
 int shotsAtCurrent,shotsTotal;
 bool finished;
};
bool ArrowStormUpdate::rva0049083C()
{
 Object *owner=object;
 const ArrowStormUpdateModuleData *arrowStormUpdateModuleData=data;
 if(shotsAtCurrent>=arrowStormUpdateModuleData->shotsPerTarget){current=INVALID_OBJECT_ID;shotsAtCurrent=0;}
 Object *victim=0;
 if(current)victim=TheGameLogic->findObjectByID(current);
 while(!victim && !targets.empty()){
  current=(ObjectID)targets.front().id;
  shotsAtCurrent=0;
  targets.pop_front();
  victim=TheGameLogic->findObjectByID(current);
  if(victim && (victim->status&1))victim=0;
 }
 const WeaponTemplate *weapon=TheWeaponStore->findWeaponTemplate(arrowStormUpdateModuleData->weapon);
 if(!victim){
  if(arrowStormUpdateModuleData->emptyGround){
  Coord3D position;
  position.x=GetGameLogicRandomValueReal(target.x-arrowStormUpdateModuleData->radius,target.x+arrowStormUpdateModuleData->radius,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\ArrowStormUpdate.cpp",217);
  position.y=GetGameLogicRandomValueReal(target.y-arrowStormUpdateModuleData->radius,target.y+arrowStormUpdateModuleData->radius,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\ArrowStormUpdate.cpp",218);
  position.z=TheTerrainLogic->getGroundHeight(position.x,position.y);
  TheWeaponStore->createAndFireTempWeapon(weapon,owner,&position);
 }else return true;
 }else{
  TheWeaponStore->rva002CE964(weapon,owner,victim);
  ++shotsAtCurrent;
 }
 ++shotsTotal; if(shotsTotal>=arrowStormUpdateModuleData->maxShots)return true;return false;
}
