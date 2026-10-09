// ?addProp@W3DTerrainVisual@@UAEXPBVThingTemplate@@PBUCoord3D@@MM@Z
// partial score=1.0 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
#include <string.h>
#include "ascii_string.h"
struct Coord3D {float x,y,z; Coord3D(const Coord3D&v):x(v.x),y(v.y),z(v.z){} ~Coord3D(){} };
template<unsigned N> class BitFlags { unsigned words[(N+31)/32]; public: BitFlags(){clear();} void clear(){memset(words,0,sizeof(words));} void set(int n){words[n>>5]|=1u<<(n&31);} };
typedef BitFlags<591> ModelConditionFlags;
class W3DModelDrawModuleData { char pad[8]; public: AsciiString model; bool flag; };
class ModuleData { public:
 virtual void v00();
 virtual void v01();
 virtual void v02();
 virtual void v03();
 virtual void v04();
 virtual void v05();
 virtual void v06();
 virtual void v07();
 virtual void v08();
 virtual void v09();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual AsciiString getBestModelNameForWB(const ModelConditionFlags&) const;
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual const W3DModelDrawModuleData* getAsW3DModelDrawModuleData() const;
};
struct ModuleRecord { char pad[20]; };
class ModuleInfo { public: ModuleRecord *begin,*end,*storage; int getCount()const {return end-begin;} const ModuleData *getNthData(int)const; };
class ThingTemplate { public: char pad[0x2f0]; ModuleInfo draw; };
class GlobalData { public: char pad[0x134]; int time,weather; };
extern GlobalData*TheGlobalData;
class BaseHeightMapRenderObjClass { public: void addProp(int,Coord3D,float,float,const AsciiString&,bool); };
struct StringBufferCount {char pad[4]; unsigned short len;};
__forceinline bool nonempty(const AsciiString&s){ const StringBufferCount*p=*(const StringBufferCount*const*)&s;return p&&p->len!=0;}
class W3DTerrainVisual { public: virtual void addProp(const ThingTemplate*,const Coord3D*,float,float); private: char pad[0x10]; BaseHeightMapRenderObjClass*terrain; };
void W3DTerrainVisual::addProp(const ThingTemplate*t,const Coord3D*pos,float angle,float scale) {
 ModelConditionFlags state;state.clear();
 if(TheGlobalData->weather==1)state.set(8);
 if(TheGlobalData->time==4)state.set(7);
 AsciiString model; bool flag=true;
 const ModuleInfo&mi=t->draw;
 if(mi.getCount()>0) {
  const ModuleData*mdd=mi.getNthData(0);
  const W3DModelDrawModuleData*md;
  if(mdd) { model=mdd->getBestModelNameForWB(state);md=mdd->getAsW3DModelDrawModuleData(); } else md=0;
  if(md) {model=md->model;flag=md->flag;}
 }
 if(terrain&&nonempty(model))terrain->addProp(1,*pos,angle,scale,model,flag);
}
