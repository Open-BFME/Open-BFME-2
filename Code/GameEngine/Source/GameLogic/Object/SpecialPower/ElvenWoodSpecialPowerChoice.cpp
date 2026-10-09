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
class ModuleData {public:unsigned char prefix[0x7c];_STL::vector<ElvenWoodChoice> choices;};
class BehaviorModule {public:virtual void behaviorModuleAnchor();protected:const ModuleData*m_data;Object*m_object;};
class SpecialPowerModuleInterface {public:virtual void specialPowerModuleInterfaceAnchor();};
class ModuleInterface {public:virtual void moduleInterfaceAnchor();};
class SpecialPowerModule:public BehaviorModule,public SpecialPowerModuleInterface,public ModuleInterface {public:SpecialPowerModule(Thing*,const ModuleData*);protected:virtual~SpecialPowerModule();};
class ElvenWoodSpecialPower:public SpecialPowerModule {public:Object*addObject(const Coord3D*,const AsciiString*);void rva004C3C36(const Coord3D*);};
extern int GetGameLogicRandomValue(int,int,char*,int);
void ElvenWoodSpecialPower::rva004C3C36(const Coord3D *position)
{
 AsciiString chosen;
 const ModuleData *settings=m_data;
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
