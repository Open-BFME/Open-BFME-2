// stlport
// cl: /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /Oa /DNDEBUG /MD /EHsc
// Native4C3C36..4C3CFF RET4 selects a weighted object entry from data7C.
// WB125E970 and BFME1 donor34f59164 Rva0025C7C0ElvenWoodChoice.cpp
// provide the semantic lead; the target proves vector7C/80, 8B entries,
// the complete random-site path and line237. Original method name unknown.
// WB125EB20 independently names the native addObject4C397F callee and
// establishes its position/name arguments and Object return; this is a
// genuine in-image first-name pin, not a claimed reconstruction of that body.
#include "Lib/Coord3D.h"
#include "ascii_string.h"
#include <vector>
class Object;class Thing;
struct ElvenWoodChoice {AsciiString name;float weight;};
#include "../../../../Include/Common/ModuleData.h"
#include "../../../../Include/GameLogic/Module/SpecialPowerModuleData.h"
class ElvenWoodSpecialPowerModuleData : public SpecialPowerModuleData {public:_STL::vector<ElvenWoodChoice> choices;};
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/SpecialPowerModule.h"
struct Coord3D;
class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void doSpecialPower(unsigned int options) = 0;
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options) = 0;
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options) = 0;
	virtual void doSpecialPowerUsingWaypoints(void *target, float angle, int commandOptions) = 0;
};
class SpecialPowerModule:public BehaviorModule,public SpecialPowerModuleInterface,public ModuleInterface {public:SpecialPowerModule(Thing*,const ModuleData*);protected:virtual~SpecialPowerModule();};
class ElvenWoodSpecialPower:public SpecialPowerModule {public:Object*addObject(const Coord3D*,const AsciiString*);void rva004C3C36(const Coord3D*);};
extern int GetGameLogicRandomValue(int,int,char*,int);
void ElvenWoodSpecialPower::rva004C3C36(const Coord3D *position)
{
 AsciiString chosen;
 const ElvenWoodSpecialPowerModuleData *settings=static_cast<const ElvenWoodSpecialPowerModuleData *>(getModuleData());
 int random=GetGameLogicRandomValue(0,99,(char*)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\SpecialPower\\ElvenWoodSpecialPower.cpp",237);
 int cumulative=0;
 for(unsigned i=0;i<settings->choices.size();++i) {
  cumulative=static_cast<int>(cumulative+settings->choices[i].weight);
  if(random<cumulative) {
   if(reinterpret_cast<const StringBase<char>*>(&settings->choices[i].name)->isEmpty()) return;
   chosen=settings->choices[i].name.str();
   break;
  }
 }
 addObject(position,&chosen);
}
