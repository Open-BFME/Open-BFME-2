// cl: -DNDEBUG -DWIN32 -D_WINDOWS /O1 /G7 /arch:SSE -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/projectedshadow -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow /ICode/Libraries/Include
#include "always.h"

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
class CameraClass {protected:void Update_Frustum() const;public:__forceinline const FrustumClass &Get_Frustum() const {const CameraClass *volatile p=this;Update_Frustum();return *(const FrustumClass *)((const char *)p+0x100);} };
class RenderInfoClass { public: CameraClass &Camera; };
class RenderObjClass {
public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual void slot80();
 virtual void slot81();
 virtual void slot82();
 virtual void slot83();
 virtual void slot84();
 virtual void slot85();
 virtual void slot86();
 virtual void slot87();
 virtual void slot88();
 virtual void slot89();
 virtual void slot90();
 virtual void slot91();
 virtual void slot92();
 virtual void slot93();
 virtual void slot94();
 virtual void slot95();
 virtual int Is_Really_Visible() const;
 Vector3 Get_Position() const;
};
struct ShadowTextureView10DF33 { char pad00[0x64]; AABoxClass box64; SphereClass sphere7c; };
struct ShadowRenderEntry10DF33 { char pad00[4]; bool enabled04; bool invisible05; char pad06[0x2e]; unsigned type34; char pad38[0x30]; ShadowTextureView10DF33 *texture68; int pad6c; RenderObjClass *object70; char pad74[0xa0]; ShadowRenderEntry10DF33 *next114; };
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
class DX8MeshRendererClass { public: void *vptr; CameraClass *camera04; void Flush(); };
extern DX8MeshRendererClass *TheDX8MeshRenderer;
// Retail defines this global in BaseHeightMap.cpp as BaseHeightMapRenderObjClass *.
// The bounds call is reached through the TU-local dispatch view above.
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
class WW3D {friend class W3DProjectedShadowManager;static bool IsCurrentlyRenderingShadowMap;public:static void Flush(RenderInfoClass &);};
static int drawStartX, drawStartY, drawEdgeX, drawEdgeY;
inline void *operator new(size_t,void *p) throw(){return p;}
inline void operator delete(void *,void *) throw(){}
struct Region3D {__declspec(nothrow) Region3D(const Region3D&);Coord3D lo,hi;};
static __forceinline void copyBox(AABoxClass *dst,const AABoxClass &src){new(dst)Region3D(*(const Region3D *)&src);}
enum ShadowType {SHADOW_NONE=0};
class W3DProjectedShadowManager { public:
 void *vptr;
 ShadowRenderEntry10DF33 *m_shadowList,*m_decalList,*m_simpleDecalList;
 void *m_10;
 ShadowPair10DF33 *m_14;
 void *m_18,*m_1c;
 char pad20[0x254-0x20];int count254;int unused258;int nShadowDecalVertsInBuf;int unused260;int nShadowDecalIndicesInBuf;int tail268[3];
 void flushDecals(ShadowType,class W3DShadowTexture *,W3DShadowTexture *,int);
 void rva0010C841(ShadowRenderEntry10DF33 *,int,int);
 void rva0010A736(ShadowPair10DF33 *);
 int rva0010DA71(RenderInfoClass&);
 int rva0010DF33(RenderInfoClass&);
};
int W3DProjectedShadowManager::rva0010DF33(RenderInfoClass &rinfo)
{
 ShadowRenderEntry10DF33 *shadow;
 static AABoxClass aaBox;
 static SphereClass sphere;
 int projectionCount=0;
 if(!WW3D::IsCurrentlyRenderingShadowMap && (m_shadowList || m_decalList || m_simpleDecalList || m_1c) && TheTerrainRenderObject) {
 {
 TerrainRect10DF33 rect;
 reinterpret_cast<ShadowTerrainDispatch10DF33 *>(TheTerrainRenderObject)->bounds238(&rect);
 drawStartX=rect.x0-4; drawStartY=rect.y0-4;
 drawEdgeX=rect.x1+4; drawEdgeY=rect.y1+4;
 }
 nShadowDecalVertsInBuf=0x8000; nShadowDecalIndicesInBuf=0x10000;
 if (m_simpleDecalList) {
 ShadowTextureView10DF33 *lastTexture=0;
 unsigned lastType=0;
 for(shadow=m_simpleDecalList; shadow; shadow=shadow->next114) {
  if(shadow->enabled04 && !shadow->invisible05) {
   if(!lastTexture) lastTexture=shadow->texture68;
   if(!lastType) lastType=shadow->type34;
   if(shadow->texture68!=lastTexture || shadow->type34!=lastType) {
    flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,0,0);
    lastTexture=shadow->texture68; lastType=shadow->type34;
   }
   if(!shadow->object70 || shadow->object70->Is_Really_Visible()) {
    rva0010C841(shadow,1,0); ++projectionCount;
   }
  }
 }
 flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,0,0);
 }
 if(m_shadowList) {
 TheDX8MeshRenderer->camera04=&rinfo.Camera;
 ShadowTextureView10DF33 *lastTexture=0;
 unsigned lastType=0;
 for(shadow=m_shadowList;shadow;shadow=shadow->next114) {
  if(shadow->enabled04 && !shadow->invisible05) {
   if(shadow->type34 & 0x2c61) {
    if(!lastTexture) lastTexture=shadow->texture68;
    if(!lastType) lastType=shadow->type34;
    if(shadow->texture68!=lastTexture || shadow->type34!=lastType) {
     flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,0,0);
     lastTexture=shadow->texture68; lastType=shadow->type34;
    }
    if(!shadow->object70 || shadow->object70->Is_Really_Visible() || (shadow->type34 & 0xc00)) {
     rva0010C841(shadow,1,0); ++projectionCount;
    }
    continue;
   }
   sphere=shadow->texture68->sphere7c;
   sphere.Center+=shadow->object70->Get_Position();
   CollisionMath::OverlapType result=CollisionMath::Overlap_Test(rinfo.Camera.Get_Frustum(),sphere);
   if(result==CollisionMath::OVERLAPPED) {
    copyBox(&aaBox,shadow->texture68->box64);
    aaBox.Translate(shadow->object70->Get_Position());
    if(CollisionMath::Overlap_Test(rinfo.Camera.Get_Frustum(),aaBox)==CollisionMath::OUTSIDE) continue;
   } else if(result==CollisionMath::OUTSIDE) continue;
   if(result==CollisionMath::INSIDE) {
    copyBox(&aaBox,shadow->texture68->box64);
    aaBox.Translate(shadow->object70->Get_Position());
   }
  }
 }
 flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,0,0);
 WW3D::Flush(rinfo);
 }
 if (m_decalList) {
 ShadowTextureView10DF33 *lastTexture=0;
 unsigned lastType=0;
 for(shadow=m_decalList; shadow; shadow=shadow->next114) {
  if(shadow->enabled04 && !shadow->invisible05) {
   if(!lastTexture) lastTexture=shadow->texture68;
   if(!lastType) lastType=shadow->type34;
   if(shadow->texture68!=lastTexture || shadow->type34!=lastType) {
    flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,0,0);
    lastTexture=shadow->texture68; lastType=shadow->type34;
   }
   if(!shadow->object70 || shadow->object70->Is_Really_Visible()) {
    rva0010C841(shadow,1,0); ++projectionCount;
   }
  }
 }
 flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,0,0);
 }
 if(m_14) {
 ShadowTextureView10DF33 *lastTexture=0,*lastTexture2=0;
 unsigned lastType=0;
 for(ShadowPair10DF33 *pair=m_14;pair;pair=pair->next64) {
  if(pair->enabled04 && !pair->invisible05) {
   if(!lastTexture) lastTexture=pair->shadow58 ? pair->shadow58->texture68 : 0;
   if(!lastTexture2) lastTexture2=pair->shadow5c ? pair->shadow5c->texture68 : 0;
   if(!lastType) lastType=pair->type34;
   ShadowTextureView10DF33 *texture=pair->shadow58 ? pair->shadow58->texture68 : 0;
   ShadowTextureView10DF33 *texture2=pair->shadow5c ? pair->shadow5c->texture68 : 0;
   unsigned type=m_14->type34;
   if(texture!=lastTexture || texture2!=lastTexture2 || type!=lastType) {
    flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,(W3DShadowTexture *)lastTexture2,0);
    lastTexture=texture; lastTexture2=texture2; lastType=type;
   }
   if(!pair->object60 || pair->object60->Is_Really_Visible()) {
    rva0010A736(pair); ++projectionCount;
   }
  }
 }
 flushDecals((ShadowType)lastType,(W3DShadowTexture *)lastTexture,(W3DShadowTexture *)lastTexture2,0);
 }
 return projectionCount+rva0010DA71(rinfo);
}return 0;
}
