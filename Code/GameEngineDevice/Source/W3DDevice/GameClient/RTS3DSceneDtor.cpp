// cl: /O1 /DNDEBUG /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Target362B6F7BD..6F927; ctor6F470 independently establishes Scene108,
// Subsystem12 at108, ref-list114, lights130/150 and environments164/38C/5B4.
// ZH W3DScene.cpp RTS3DScene destructor supplies the release and buffer order.
// Preserve the established address-derived owner used by deleting-dtor callers.
#include <new>
class RenderObjClass;
#include "../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"
class LightClass:public RefCountClass{};
#include "../../../../Libraries/Source/WWVegas/WW3D2/MaterialPassClass.h"
class W3DShroudMaterialPassClass:public RefCountClass{};
class SimpleSceneClass{public:virtual~SimpleSceneClass();char pad[0x104];};
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"
class BfmeRefSceneList{public:virtual~BfmeRefSceneList();char head[20];};
class LightEnvironmentClass{public:~LightEnvironmentClass();char data[0x228];};
struct SceneVector3{float X,Y,Z;};
class Rva006F7BD:public SimpleSceneClass,public SubsystemInterface{public:virtual~Rva006F7BD();private:
BfmeRefSceneList list114;bool drawTerrainOnly;LightClass*globalLight[4];LightClass*scratchLight;SceneVector3 ambient144;LightClass*infantryLight[4];int numLights;LightEnvironmentClass env164,env38C,env5B4;bool flag7DC;
W3DShroudMaterialPassClass*shroudPass;MaterialPassClass*heatPass,*heatOnlyPass;int mode,translucentCount;RenderObjClass**translucentBuffer;int occludedCount;RenderObjClass**potentialOccluders,**potentialOccludees,**nonOccluders;int counts[4];};
#define RELEASE(p) if(p){p->Release_Ref();p=0;}
Rva006F7BD::~Rva006F7BD(){
for(int i=0;i<4;++i){RELEASE(globalLight[i]);RELEASE(infantryLight[i]);}
RELEASE(scratchLight);RELEASE(shroudPass);RELEASE(heatPass);RELEASE(heatOnlyPass);
if(translucentBuffer)delete[]translucentBuffer;
if(nonOccluders)delete[]nonOccluders;
if(potentialOccludees)delete[]potentialOccludees;
if(potentialOccluders)delete[]potentialOccluders;
}
