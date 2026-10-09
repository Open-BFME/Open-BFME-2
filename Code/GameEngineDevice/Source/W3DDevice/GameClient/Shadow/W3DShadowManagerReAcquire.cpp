// cl: /I. /O1 /MD /EHsc /DNDEBUG /G7 /arch:SSE /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// BF1 clean W3DShadow.cpp 874e38488c semantic lead; target layout/scale
// and four allocations come from native9A710..9A8D3 and WB777D40.
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "reference/shims/bfme_colmathaabox/wwmath.h"
#include "reference/shims/bfme_colmathaabox/vector3.h"
// Native ctor callback47A6A9 is empty; native iterator initializes one12B
// coordinate at receiver+C. Element original type unknown; this address view
// inherits canonical Coord3D storage and emits the proven3B ICF callback.
struct Rva0009A710LightPosition : Coord3D { __declspec(noinline) Rva0009A710LightPosition(); };
Rva0009A710LightPosition::Rva0009A710LightPosition() {}
class Rva000F1A32 {public:Rva000F1A32();private:char body[12];};
class Rva005D2575 {
public:Rva005D2575();private:char body[0x1c];
};
class Rva0010C785 {public:Rva0010C785();private:char body[0x274];};
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

// Target evidence: retail 0x0009A383 checks four global pointers in order and
// calls each manager only when its pointer is non-null. The 91-byte body is
// byte-verified.
// Donor evidence: Zero Hour W3DShadow.cpp gives the same aggregate purpose
// and names its first two checks as volumetric and projected shadow managers.
// Inference: the target function keeps that owner and appends two checks. The
// latter helpers retain address-derived names because their owners are unknown.

typedef bool Bool;

class W3DVolumetricShadowManager
{
public:
	Bool ReAcquireResources();
};

class W3DProjectedShadowManager
{
public:
	Bool ReAcquireResources();
};

class Rva00108660ResourceManager
{
public:
	Bool ReAcquireResources();
};

class Rva0007DA23ResourceManager
{
public:
	Bool ReAcquireResources();
};

extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;
// TheW3DVolumetricShadowManager: matched references place it at VA 0xdebcd8 (zero-filled .bss).
W3DVolumetricShadowManager * TheW3DVolumetricShadowManager;
extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;
// TheW3DProjectedShadowManager: matched references place it at VA 0xdec2cc (zero-filled .bss).
W3DProjectedShadowManager * TheW3DProjectedShadowManager;
extern Rva00108660ResourceManager *Rva00DEC2D8Manager;
extern Rva0007DA23ResourceManager *Rva00DE1FF8Manager;
// Rva00DE1FF8Manager: matched references place it at VA 0xde1ff8 (zero-filled .bss).
Rva0007DA23ResourceManager * Rva00DE1FF8Manager;

class W3DShadowManager {
public:W3DShadowManager(); Bool ReAcquireResources();
private:
 bool m_isShadowScene;char padding[3];unsigned m_shadowColor;
 int m_stencilShadowMask;Rva0009A710LightPosition m_lightPos[1];
};

Bool W3DShadowManager::ReAcquireResources()
{
	Bool result = true;
	if (TheW3DVolumetricShadowManager && !TheW3DVolumetricShadowManager->ReAcquireResources())
		result = false;
	if (TheW3DProjectedShadowManager && !TheW3DProjectedShadowManager->ReAcquireResources())
		result = false;
	if (Rva00DEC2D8Manager && !Rva00DEC2D8Manager->ReAcquireResources())
		result = false;
	if (Rva00DE1FF8Manager && !Rva00DE1FF8Manager->ReAcquireResources())
		result = false;
	return result;
}

// ?Rva00DEC2D8Manager@@3PAVRva00108660ResourceManager@@A: matched references place it at VA 0xdec2d8; also referenced as ?R2Ptr01306DF0@@3PAVR2GlobalReceiver@@A.
Rva00108660ResourceManager * Rva00DEC2D8Manager = 0;

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
 Rva0010C785 *projected=new Rva0010C785;
 Rva00DEC2D8Manager=(Rva00108660ResourceManager*)projected;
 g_00DEC2D4=(AudioManager0029E159*)projected;
 Rva00DE1FF8Manager=(Rva0007DA23ResourceManager*)new Rva0007C50B;
 ((W3DGameClientShadowShim*)this)->setLightPosition(0,m_lightPos[0].x,m_lightPos[0].y,m_lightPos[0].z);
}
