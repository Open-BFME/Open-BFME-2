// ??0W3DShadowManager@@QAE@XZ
// partial score=0.99 date=2026-10-09
// cl: /O1 /MD /EHsc /DNDEBUG /G7 /arch:SSE /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// BF1 clean W3DShadow.cpp 874e38488c semantic lead; target layout/scale
// and four allocations come from native9A710..9A8D3 and WB777D40.
struct Coord3D {Coord3D();float x,y,z;};
#include "../reference/shims/bfme_colmathaabox/wwmath.h"
#include "../reference/shims/bfme_colmathaabox/vector3.h"
class Rva000F1A32 {public:Rva000F1A32();private:char body[12];};
class Rva005D2575 {
public:Rva005D2575();private:char body[0x1c];
};
class Rva00108DBC {public:Rva00108DBC();private:char body[0x274];};
class Rva0007C50B {public:Rva0007C50B();private:char body[0x2c];};
class W3DVolumetricShadowManager;
class W3DProjectedShadowManager;
class Rva00108660ResourceManager;
class Rva0007DA23ResourceManager;
class AudioManager0029E159;
extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;
extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;
extern Rva00108660ResourceManager *Rva00DEC2D8Manager;
extern AudioManager0029E159 *g_00DEC2D4;
extern Rva0007DA23ResourceManager *Rva00DE1FF8Manager;
struct ShadowTerrainLight {float x,y,z;};
class GlobalData {public:char prefix[0x920];ShadowTerrainLight light[1];};
extern GlobalData *TheWritableGlobalData;
class W3DGameClientShadowShim {
public:void setLightPosition(int,float,float,float);
};
class W3DShadowManager {
public:W3DShadowManager();
private:
 bool m_isShadowScene;char padding[3];unsigned m_shadowColor;
 int m_stencilShadowMask;Coord3D m_lightPos[1];
};
W3DShadowManager::W3DShadowManager() {
 m_shadowColor=0x7fa0a0a0;
 m_isShadowScene=false;
 m_stencilShadowMask=0;
 Vector3 lightRay(-TheWritableGlobalData->light[0].x,
 -TheWritableGlobalData->light[0].y,-TheWritableGlobalData->light[0].z);
 lightRay.Normalize();
 Vector3 scaled=lightRay*10000000.0f;
 Coord3D *out=&m_lightPos[0];out->x=scaled.X;out->y=scaled.Y;out->z=scaled.Z;
 // Existing ledger provider names are retained; the physical targets,
 // not the historical class spellings, identify each submanager here.
 TheW3DVolumetricShadowManager=(W3DVolumetricShadowManager*)new Rva000F1A32;
 TheW3DProjectedShadowManager=(W3DProjectedShadowManager*)new Rva005D2575;
 Rva00108DBC *projected=new Rva00108DBC;
 Rva00DEC2D8Manager=(Rva00108660ResourceManager*)projected;
 g_00DEC2D4=(AudioManager0029E159*)projected;
 Rva00DE1FF8Manager=(Rva0007DA23ResourceManager*)new Rva0007C50B;
 ((W3DGameClientShadowShim*)this)->setLightPosition(0,m_lightPos[0].x,m_lightPos[0].y,m_lightPos[0].z);
}
