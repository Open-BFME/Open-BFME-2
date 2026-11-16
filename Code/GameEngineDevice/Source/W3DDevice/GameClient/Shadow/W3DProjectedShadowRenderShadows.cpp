// cl: -DNDEBUG -DWIN32 -D_WINDOWS /O1 /G7 /arch:SSE -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/projectedshadow -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow /ICode/Libraries/Include
// platformsdk
// stlport
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#include "always.h"
typedef DWORD D3DRENDERSTATETYPE;

// Native10DF33..10E482 is the full1359-byte four-list shadow render walk.
// Primary semantic guide: ZH W3DProjectedShadow.cpp renderShadows; clean BFME1
// donor575ba2b04 W3DProjectedShadowRenderShadows.cpp supplies the richer lists.
// Native facts: manager lists4/8/C/14/1C, counters25C/264, next114, flags4/5,
// texture68/object70, paired58/5C/60/64, mask2C61 and camera frustum100.
// The original target method name is unproven; keep an address-derived name.
// A volatile local camera pointer preserves the witnessed18 stack home across
// Update_Frustum and keeps EBX zero through the loops. This is a codegen lever,
// not a claim that the original source marked the pointer volatile.
// Region3D's owned43-byte constructor copies the same six float words as the
// box record. Placement construction binds that actual owner with no alias.
// Its body has no calls and cannot throw. Native calls WW3D::Flush(rinfo), not
// the donor's direct mesh-renderer Flush. Callee neutral views remain uncertain.
#include "vector3.h"
#include "Lib/Coord3D.h"
#include "aabox.h"
#include "sphere.h"
class FrustumClass;
#include "frustum.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"
__forceinline const FrustumClass &CameraClass::Get_Frustum() const
{
 Update_Frustum();
 return *(const FrustumClass *)field100;
}
// Preserve the render caller's volatile camera home without changing the shared getter.
static __forceinline const FrustumClass &shadowFrustum(const CameraClass &camera)
{
 const CameraClass *volatile p=&camera;
 camera.Get_Frustum();
 return *(const FrustumClass *)p->field100;
}
#define __PLACEMENT_VEC_NEW_INLINE  // always.h defines array placement-new itself
#include "../../../../../Libraries/Source/WWVegas/WW3D2/RenderInfoClass.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;
typedef int Color;
long fast_float2long_round(float);
float fast_float_trunc(float);
#define REAL_TO_INT(x) ((Int)(fast_float2long_round(fast_float_trunc(x))))
#include "lightenvironment.h"
class SpecialRenderInfoClass;
#include "../../../../../../reference/shims/bfme2_projectedshadow/GameClient/Shadow.h"
#include "../../../../../../reference/shims/bfme2_projectedshadow/W3DDevice/GameClient/W3DProjectedShadow.h"
// Target uses a plain 16B sphere storage view; avoid instantiating the
// donor public constructor COMDAT, which the code-identity gate rejects.
struct ShadowSphereView10DF33 {Vector3 Center;float Radius;ShadowSphereView10DF33(){} };
struct ShadowTextureView10DF33 { char pad00[0x64]; AABoxClass box64; ShadowSphereView10DF33 sphere7c; };
struct Coord3D;
class BridgeView10C841;
struct ShadowRenderEntry10DF33
{
public:
	char m_pad00[0x4];
	bool enabled04; // +0x04
	bool invisible05; // +0x05
	char m_pad06[0x2];
	Coord3D m_position; // +0x08
	Coord3D m_normal; // +0x14
	Real m_angle; // +0x20
	char m_pad24[0x4];
	UnsignedInt m_diffuse; // +0x28
	char m_pad2C[0x4];
	Bool m_isRotating; // +0x30
	char m_pad31[0x3];
	ShadowType m_type; // +0x34
	char m_pad38[0x20];
	Real m_decalSizeX; // +0x58
	Real m_decalSizeY; // +0x5C
	Real m_maxHeight; // +0x60
	Bool m_useTerrainHeight; // +0x64
	char m_pad65[0x3];
	W3DShadowTexture *m_shadowTexture[2]; // +0x68
	RenderObjClass *m_robj; // +0x70
	char m_pad74[0x4];
	Real m_decalOffsetU; // +0x78
	Real m_decalOffsetV; // +0x7C
	char m_pad80[0x8];
	Coord3D m_lastScanPosition; // +0x88
	Int m_casterDrawableID[16]; // +0x94
	BridgeView10C841 *m_casterBridge[16]; // +0xD4
	ShadowRenderEntry10DF33 *next114; // +0x114
};
struct ShadowPair10DF33 { char pad00[4]; bool enabled04; bool invisible05; char pad06[0x2e]; unsigned type34; char pad38[0x20]; ShadowRenderEntry10DF33 *shadow58,*shadow5c; RenderObjClass *object60; ShadowPair10DF33 *next64; };
struct TerrainRect10DF33 { int x0,y0,x1,y1; };
struct ShadowTerrainDispatch10DF33 {
 virtual void slot000();
 virtual void slot001();
 virtual void slot002();
 virtual void slot003();
 virtual void slot004();
 virtual void slot005();
 virtual void slot006();
 virtual void slot007();
 virtual void slot008();
 virtual void slot009();
 virtual void slot010();
 virtual void slot011();
 virtual void slot012();
 virtual void slot013();
 virtual void slot014();
 virtual void slot015();
 virtual void slot016();
 virtual void slot017();
 virtual void slot018();
 virtual void slot019();
 virtual void slot020();
 virtual void slot021();
 virtual void slot022();
 virtual void slot023();
 virtual void slot024();
 virtual void slot025();
 virtual void slot026();
 virtual void slot027();
 virtual void slot028();
 virtual void slot029();
 virtual void slot030();
 virtual void slot031();
 virtual void slot032();
 virtual void slot033();
 virtual void slot034();
 virtual void slot035();
 virtual void slot036();
 virtual void slot037();
 virtual void slot038();
 virtual void slot039();
 virtual void slot040();
 virtual void slot041();
 virtual void slot042();
 virtual void slot043();
 virtual void slot044();
 virtual void slot045();
 virtual void slot046();
 virtual void slot047();
 virtual void slot048();
 virtual void slot049();
 virtual void slot050();
 virtual void slot051();
 virtual void slot052();
 virtual void slot053();
 virtual void slot054();
 virtual void slot055();
 virtual void slot056();
 virtual void slot057();
 virtual void slot058();
 virtual void slot059();
 virtual void slot060();
 virtual void slot061();
 virtual void slot062();
 virtual void slot063();
 virtual void slot064();
 virtual void slot065();
 virtual void slot066();
 virtual void slot067();
 virtual void slot068();
 virtual void slot069();
 virtual void slot070();
 virtual void slot071();
 virtual void slot072();
 virtual void slot073();
 virtual void slot074();
 virtual void slot075();
 virtual void slot076();
 virtual void slot077();
 virtual void slot078();
 virtual void slot079();
 virtual void slot080();
 virtual void slot081();
 virtual void slot082();
 virtual void slot083();
 virtual void slot084();
 virtual void slot085();
 virtual void slot086();
 virtual void slot087();
 virtual void slot088();
 virtual void slot089();
 virtual void slot090();
 virtual void slot091();
 virtual void slot092();
 virtual void slot093();
 virtual void slot094();
 virtual void slot095();
 virtual void slot096();
 virtual void slot097();
 virtual void slot098();
 virtual void slot099();
 virtual void slot100();
 virtual void slot101();
 virtual void slot102();
 virtual void slot103();
 virtual void slot104();
 virtual void slot105();
 virtual void slot106();
 virtual void slot107();
 virtual void slot108();
 virtual void slot109();
 virtual void slot110();
 virtual void slot111();
 virtual void slot112();
 virtual void slot113();
 virtual void slot114();
 virtual void slot115();
 virtual void slot116();
 virtual void slot117();
 virtual void slot118();
 virtual void slot119();
 virtual void slot120();
 virtual void slot121();
 virtual void slot122();
 virtual void slot123();
 virtual void slot124();
 virtual void slot125();
 virtual void slot126();
 virtual void slot127();
 virtual void slot128();
 virtual void slot129();
 virtual void slot130();
 virtual void slot131();
 virtual void slot132();
 virtual void slot133();
 virtual void slot134();
 virtual void slot135();
 virtual void slot136();
 virtual void slot137();
 virtual void slot138();
 virtual void slot139();
 virtual void bounds238(TerrainRect10DF33 *);
};
#include "../../../../../Libraries/Source/WWVegas/WW3D2/DX8MeshRendererClass.h"
// The canonical class is opaque; native renderShadows writes its camera at +4.
struct ShadowMeshRendererView { void *vptr; CameraClass *camera04; };
extern DX8MeshRendererClass *TheDX8MeshRenderer;
// Retail defines this global in BaseHeightMap.cpp as BaseHeightMapRenderObjClass *.
// The bounds call is reached through the TU-local dispatch view above.
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
#include "../../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"
inline bool WW3D::Is_Snapshot_Activated() { return SnapshotActivated; }
// WW3D::Flush(RenderInfoClass &) 0x001173F0, under the ledger row's spelling.
void __cdecl rva001173f0(unsigned int renderArgument);
class W3DDualProjectedShadow;
static int drawStartX, drawStartY, drawEdgeX, drawEdgeY;
#include "../../../../../Libraries/Include/Lib/Region3D.h"
static __forceinline void copyBox(AABoxClass *dst,const AABoxClass &src){new(dst)Region3D(*(const Region3D *)&src);}

int W3DProjectedShadowManager::rva0010DF33(RenderInfoClass &rinfo)
{
 ShadowRenderEntry10DF33 *shadow;
 static AABoxClass aaBox;
 static ShadowSphereView10DF33 sphere;
 int projectionCount=0;
 if(!WW3D::IsCurrentlyRenderingShadowMap && (reinterpret_cast<ShadowRenderEntry10DF33 *>(m_shadowList) || reinterpret_cast<ShadowRenderEntry10DF33 *>(m_decalList) || reinterpret_cast<ShadowRenderEntry10DF33 *>(m_simpleDecalList) || reinterpret_cast<ShadowRenderEntry10DF33 *>(m_list1C)) && TheTerrainRenderObject) {
 {
 TerrainRect10DF33 rect;
 reinterpret_cast<ShadowTerrainDispatch10DF33 *>(TheTerrainRenderObject)->bounds238(&rect);
 drawStartX=rect.x0-4; drawStartY=rect.y0-4;
 drawEdgeX=rect.x1+4; drawEdgeY=rect.y1+4;
 }
 m_nShadowDecalVertsInBuf=0x8000; m_nShadowDecalIndicesInBuf=0x10000;
 if (reinterpret_cast<ShadowRenderEntry10DF33 *>(m_simpleDecalList)) {
 W3DShadowTexture *lastTexture=0;
 unsigned lastType=0;
 for(shadow=reinterpret_cast<ShadowRenderEntry10DF33 *>(m_simpleDecalList); shadow; shadow=shadow->next114) {
  if(shadow->enabled04 && !shadow->invisible05) {
   if(!lastTexture) lastTexture=shadow->m_shadowTexture[0];
   if(!lastType) lastType=shadow->m_type;
   if(shadow->m_shadowTexture[0]!=lastTexture || shadow->m_type!=lastType) {
    flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,0,0);
    lastTexture=shadow->m_shadowTexture[0]; lastType=shadow->m_type;
   }
   if(!shadow->m_robj || shadow->m_robj->Is_Really_Visible()) {
    rva0010C841(shadow,1,0); ++projectionCount;
   }
  }
 }
 flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,0,0);
 }
 if(reinterpret_cast<ShadowRenderEntry10DF33 *>(m_shadowList)) {
 ((ShadowMeshRendererView *)TheDX8MeshRenderer)->camera04=&rinfo.Camera;
 W3DShadowTexture *lastTexture=0;
 unsigned lastType=0;
 for(shadow=reinterpret_cast<ShadowRenderEntry10DF33 *>(m_shadowList);shadow;shadow=shadow->next114) {
  if(shadow->enabled04 && !shadow->invisible05) {
   if(shadow->m_type & 0x2c61) {
    if(!lastTexture) lastTexture=shadow->m_shadowTexture[0];
    if(!lastType) lastType=shadow->m_type;
    if(shadow->m_shadowTexture[0]!=lastTexture || shadow->m_type!=lastType) {
     flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,0,0);
     lastTexture=shadow->m_shadowTexture[0]; lastType=shadow->m_type;
    }
    if(!shadow->m_robj || shadow->m_robj->Is_Really_Visible() || (shadow->m_type & 0xc00)) {
     rva0010C841(shadow,1,0); ++projectionCount;
    }
    continue;
   }
   sphere=reinterpret_cast<ShadowTextureView10DF33 *>(shadow->m_shadowTexture[0])->sphere7c;
   sphere.Center+=shadow->m_robj->Get_Position();
   CollisionMath::OverlapType result=CollisionMath::Overlap_Test(shadowFrustum(rinfo.Camera),*(const SphereClass *)&sphere);
   if(result==CollisionMath::OVERLAPPED) {
    copyBox(&aaBox,reinterpret_cast<ShadowTextureView10DF33 *>(shadow->m_shadowTexture[0])->box64);
    aaBox.Translate(shadow->m_robj->Get_Position());
    if(CollisionMath::Overlap_Test(shadowFrustum(rinfo.Camera),aaBox)==CollisionMath::OUTSIDE) continue;
   } else if(result==CollisionMath::OUTSIDE) continue;
   if(result==CollisionMath::INSIDE) {
    copyBox(&aaBox,reinterpret_cast<ShadowTextureView10DF33 *>(shadow->m_shadowTexture[0])->box64);
    aaBox.Translate(shadow->m_robj->Get_Position());
   }
  }
 }
 flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,0,0);
 rva001173f0((unsigned int)&rinfo);
 }
 if (reinterpret_cast<ShadowRenderEntry10DF33 *>(m_decalList)) {
 W3DShadowTexture *lastTexture=0;
 unsigned lastType=0;
 for(shadow=reinterpret_cast<ShadowRenderEntry10DF33 *>(m_decalList); shadow; shadow=shadow->next114) {
  if(shadow->enabled04 && !shadow->invisible05) {
   if(!lastTexture) lastTexture=shadow->m_shadowTexture[0];
   if(!lastType) lastType=shadow->m_type;
   if(shadow->m_shadowTexture[0]!=lastTexture || shadow->m_type!=lastType) {
    flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,0,0);
    lastTexture=shadow->m_shadowTexture[0]; lastType=shadow->m_type;
   }
   if(!shadow->m_robj || shadow->m_robj->Is_Really_Visible()) {
    rva0010C841(shadow,1,0); ++projectionCount;
   }
  }
 }
 flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,0,0);
 }
 if(reinterpret_cast<ShadowPair10DF33 *>(m_dualDecalList)) {
 W3DShadowTexture *lastTexture=0,*lastTexture2=0;
 unsigned lastType=0;
 for(ShadowPair10DF33 *pair=reinterpret_cast<ShadowPair10DF33 *>(m_dualDecalList);pair;pair=pair->next64) {
  if(pair->enabled04 && !pair->invisible05) {
   if(!lastTexture) lastTexture=pair->shadow58 ? pair->shadow58->m_shadowTexture[0] : 0;
   if(!lastTexture2) lastTexture2=pair->shadow5c ? pair->shadow5c->m_shadowTexture[0] : 0;
   if(!lastType) lastType=pair->type34;
   W3DShadowTexture *texture=pair->shadow58 ? pair->shadow58->m_shadowTexture[0] : 0;
   W3DShadowTexture *texture2=pair->shadow5c ? pair->shadow5c->m_shadowTexture[0] : 0;
   unsigned type=reinterpret_cast<ShadowPair10DF33 *>(m_dualDecalList)->type34;
   if(texture!=lastTexture || texture2!=lastTexture2 || type!=lastType) {
    flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,(W3DShadowTexture *)lastTexture2,0);
    lastTexture=texture; lastTexture2=texture2; lastType=type;
   }
   if(!pair->object60 || pair->object60->Is_Really_Visible()) {
    queueDualDecal((W3DDualProjectedShadow *)pair); ++projectionCount;
   }
  }
 }
 flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,(W3DShadowTexture *)lastTexture2,0);
 }
 return projectionCount+rva0010DA71(rinfo);
}return 0;
}

struct IDirect3DDevice8
{
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53b(); virtual void slot54(); virtual void slot55();
	virtual void slot56();
	virtual HRESULT __stdcall SetRenderState(D3DRENDERSTATETYPE state, DWORD value) = 0;	// +0xE4
};

#include "../../../../../Libraries/Source/WWVegas/WWLib/StringClassData.h"
inline StringClass::~StringClass() { Free_String(); }

extern unsigned number_of_DX8_calls;
#include "../../../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"
__forceinline void DX8Wrapper::Set_DX8_Render_State(D3DRENDERSTATETYPE state,unsigned value) {
 if(RenderStates[state]==value)return;
 if(WW3D::Is_Snapshot_Activated()){StringClass name(0,true);Get_DX8_Render_State_Value_Name(name,state,value);}
 RenderStates[state]=value;D3DDevice->SetRenderState(state,value);++number_of_DX8_calls;++render_state_changes;
}
class GlobalData;extern GlobalData *TheWritableGlobalData;
struct ShadowGlobalView10DF33 {char pad9a7[0x9a7];bool flag9a7;};
// Native10DA71..10DF33 is the complete1218B stencil/decal list pass.
// Existing verified flushDecals and ZH stencil render-state code guide the
// composition; native states52/57/58/59/54/53, dual textures68/6C, head1C,
// flag9A7, pass count and final stencil-only Clear are independent facts.
// Assign passes in both branches (do not preinitialize): this retains native
// setup order. The unused RenderInfo argument is retained from its caller.
int W3DProjectedShadowManager::rva0010DA71(RenderInfoClass &rinfo) {
 static AABoxClass aaBox;static ShadowSphereView10DF33 sphere;
 int count=0;
 if(reinterpret_cast<ShadowRenderEntry10DF33 *>(m_list1C) && TheTerrainRenderObject) {
  {TerrainRect10DF33 rect;reinterpret_cast<ShadowTerrainDispatch10DF33 *>(TheTerrainRenderObject)->bounds238(&rect);
   drawStartX=rect.x0-4;drawStartY=rect.y0-4;drawEdgeX=rect.x1+4;drawEdgeY=rect.y1+4;}
  if(reinterpret_cast<ShadowRenderEntry10DF33 *>(m_list1C)) {
   int passes;
   if(DX8Wrapper::Has_Stencil())passes=((ShadowGlobalView10DF33 *)TheWritableGlobalData)->flag9a7?1:2;
   else passes=1;
   if(DX8Wrapper::Has_Stencil()) {
    DX8Wrapper::Set_DX8_Render_State(52,1);DX8Wrapper::Set_DX8_Render_State(57,255);
    DX8Wrapper::Set_DX8_Render_State(58,~0U);DX8Wrapper::Set_DX8_Render_State(59,~0U);
    DX8Wrapper::Set_DX8_Render_State(54,1);DX8Wrapper::Set_DX8_Render_State(53,1);
   }
   for(int pass=0;pass<passes;++pass) {
    W3DShadowTexture *lastTexture=0,*lastTexture2=0;unsigned lastType=0;
    for(ShadowRenderEntry10DF33 *shadow=reinterpret_cast<ShadowRenderEntry10DF33 *>(m_list1C);shadow;shadow=shadow->next114) {
     if(shadow->enabled04&&!shadow->invisible05) {
      if(!lastTexture)lastTexture=reinterpret_cast<ShadowRenderEntry10DF33 *>(m_list1C)->m_shadowTexture[0];
      if(!lastTexture2)lastTexture2=reinterpret_cast<ShadowRenderEntry10DF33 *>(m_list1C)->m_shadowTexture[1];
      if(!lastType)lastType=reinterpret_cast<ShadowRenderEntry10DF33 *>(m_list1C)->m_type;
      W3DShadowTexture *texture=shadow->m_shadowTexture[0],*texture2=shadow->m_shadowTexture[1];
      unsigned type=reinterpret_cast<ShadowRenderEntry10DF33 *>(m_list1C)->m_type;
      if(texture!=lastTexture||texture2!=lastTexture2||type!=lastType) {
       flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,(W3DShadowTexture *)lastTexture2,pass);
       lastTexture=texture;lastTexture2=texture2;lastType=type;
      }
      if(!shadow->m_robj||shadow->m_robj->Is_Really_Visible()) {
       rva0010C841(shadow,passes,pass);if(pass==0)++count;
      }
     }
    }
    flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,(W3DShadowTexture *)lastTexture2,pass);
   }
   if(DX8Wrapper::Has_Stencil())DX8Wrapper::Set_DX8_Render_State(52,0);
  }
  if(DX8Wrapper::Has_Stencil()) {Vector3 zero;zero.Set(0,0,0);DX8Wrapper::Clear(false,false,true,zero,0,1,0);}
  return count;
 }
 return 0;
}
