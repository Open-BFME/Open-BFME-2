// ??0W3DShadowManager@@QAE@XZ
// partial score=0.98 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /O1 /Oy- /G7 /arch:SSE /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
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
 unsigned char opaque[0x274];
public:
 Rva00108660ResourceManager();
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

struct ShadowLightPoint {
 float x,y,z;
 ShadowLightPoint() {}
};
class W3DShadowManager
{
public:
 W3DShadowManager();
 Bool ReAcquireResources();
 bool scene; char pad01[3]; unsigned color; unsigned stencil;
 ShadowLightPoint light[1];
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

#include "wwmath.h"
#include "vector3.h"
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct ShadowGlobalLightView { char pad[0x920]; float x,y,z; };
class Rva000F1A32 { char opaque[0xC]; public: Rva000F1A32(); };
class ShadowProjectedConstructorView {
 int field0,field4,field8,fieldC,field10,field14,field18;
public: __declspec(noinline) ShadowProjectedConstructorView();
};
ShadowProjectedConstructorView::ShadowProjectedConstructorView()
{
 field0=0;field4=0;field8=0;fieldC=0;field10=0;field14=0;field18=0;
}
class Rva0007C50B { char opaque[0x2C]; public: Rva0007C50B(); };
extern class ProjectedShadowManager *TheProjectedShadowManager;
class W3DGameClientShadowShim { public: void setLightPosition(int,float,float,float); };
W3DShadowManager::W3DShadowManager()
{
 color=0x7FA0A0A0;
 scene=false;
 stencil=0;
 ShadowGlobalLightView *g=(ShadowGlobalLightView*)TheWritableGlobalData;
 Vector3 ray(0.0f-g->x,0.0f-g->y,0.0f-g->z);
 ray.Normalize();
 Vector3 scaled=ray*10000000.0f;
 ShadowLightPoint *out=light;
 out->x=scaled.X;out->y=scaled.Y;out->z=scaled.Z;
 TheW3DVolumetricShadowManager=(W3DVolumetricShadowManager*)new Rva000F1A32;
 TheW3DProjectedShadowManager=(W3DProjectedShadowManager*)new ShadowProjectedConstructorView;
 Rva00108660ResourceManager *v2=new Rva00108660ResourceManager;
 Rva00DEC2D8Manager=v2;
 TheProjectedShadowManager=(ProjectedShadowManager*)v2;
 Rva00DE1FF8Manager=(Rva0007DA23ResourceManager*)new Rva0007C50B;
 ((W3DGameClientShadowShim*)this)->setLightPosition(0,light[0].x,light[0].y,light[0].z);
}
