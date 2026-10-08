// ?addObject@ElvenWoodSpecialPower@@QAEPAVObject@@PBUCoord3D@@PBVAsciiString@@@Z
// partial score=0.9 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc

#include "../Code/Libraries/Include/Lib/Coord3D.h"
#include "ascii_string.h"
#include <string.h>
class Team;
class Thing { public: void setPosition(const Coord3D*); };
class Object : public Thing {public: unsigned char prefix[0x304]; Team *team; void setTeam(Team*);};
struct CreateMask { unsigned words[4]; };
class ThingTemplate {public: unsigned char prefix[0x108]; unsigned char kinds[28]; unsigned char gap[0x4e0-0x124]; float scale;};
class Rva002D06CA {public: void *rva002D06CA(const AsciiString*);};
extern Rva002D06CA *TheThingFactory;
class ThingFactory {public: Object *newObject(const ThingTemplate*,Team*,const CreateMask*,bool);};
class Matrix3D {public:
 float row[3][4];
 explicit Matrix3D(bool init) { if(init) { row[0][0]=1;row[0][1]=0;row[0][2]=0;row[0][3]=0;row[1][0]=0;row[1][1]=1;row[1][2]=0;row[1][3]=0;row[2][0]=0;row[2][1]=0;row[2][2]=1;row[2][3]=0;} }
};
class TerrainLogic {public:
 void rva00283642(const ThingTemplate*,const Coord3D*,const Matrix3D*,float);
 void rva00280176(const ThingTemplate*,const Coord3D*,const Matrix3D*,float);
 void rva0027D3D9(const ThingTemplate*,const Coord3D*,const Matrix3D*,float);
};
extern TerrainLogic *TheTerrainLogic;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const ModuleData *m_data;
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleInterface
{
public:
	virtual void specialPowerModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModule : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public ModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );

protected:
	virtual ~SpecialPowerModule();
};

class ElvenWoodSpecialPower : public SpecialPowerModule
{
public:
	ElvenWoodSpecialPower( Thing *thing, const ModuleData *moduleData );
	Object *addObject(const Coord3D*,const AsciiString*);

protected:
	virtual ~ElvenWoodSpecialPower();
};

ElvenWoodSpecialPower::ElvenWoodSpecialPower( Thing *thing, const ModuleData *moduleData )
	: SpecialPowerModule( thing, moduleData )
{
}

// ??1ElvenWoodSpecialPower@@MAE@XZ present-unmatched
ElvenWoodSpecialPower::~ElvenWoodSpecialPower()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?specialPowerModuleInterfaceAnchor@SpecialPowerModuleInterface@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

Object *ElvenWoodSpecialPower::addObject(const Coord3D *position,const AsciiString *name)
{
 const ThingTemplate *templ=static_cast<const ThingTemplate*>(TheThingFactory->rva002D06CA(name));
 if (templ) {
  if ((templ->kinds[12]&0x10)||(templ->kinds[11]&0xc0)) {
   Matrix3D matrix(true);
   float scale=templ->scale;
   unsigned kind=*reinterpret_cast<const unsigned*>(templ->kinds+8);
   if(kind&0x40000000) TheTerrainLogic->rva00283642(templ,position,&matrix,scale);
   else if(kind&0x80000000) TheTerrainLogic->rva00280176(templ,position,&matrix,scale);
   else TheTerrainLogic->rva0027D3D9(templ,position,&matrix,scale);
  } else {
   CreateMask mask;
   memset(&mask,0,sizeof(mask));
   Object *object=reinterpret_cast<ThingFactory*>(TheThingFactory)->newObject(templ,0,&mask,false);
   if(object) { object->setTeam(m_object->team);object->setPosition(position);return object; }
  }
 }
 return 0;
}
