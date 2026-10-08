// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// BFME1 de2635e79 BfmeVolumetricShadowRender.cpp supplies the two-pass
// semantic lead. Native107F8B..1080B4 RET4 independently proves camera
// argument, frustum100, flag60, enabled4/5, links6C/70 and manager8/C.
// Provider declarations at106FB6 and107E76 retain their existing ledger
// identities. The target proves the common receiver address; original
// helper method names remain unknown. Unclaimed native callees are pinned
// from their complete boundaries and call ABI without asserting recovery.
#include "vector3.h"
class FrustumClass {};
class AABoxClass {public: Vector3 Center, Extent;};
class RenderObjClass {public: Vector3 Get_Position() const;};
class CameraClass : public RenderObjClass {
protected: void Update_Frustum() const;
public: const FrustumClass &Get_Frustum() const {
 Update_Frustum();return *(const FrustumClass*)((const char*)this+0x100);
}
};
class RenderInfoClass {public: CameraClass *camera;};
class BaseHeightMapRenderObjClass {public:
 bool getMaximumVisibleBox(const FrustumClass&,AABoxClass*,bool);
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct ShadowGlobalDataView {char pad[0x60];bool volumes;};
class DX8Caps {public:char pad[0x90];unsigned caps;};
class DX8Wrapper {
 static DX8Caps *CurrentCaps;
public:
 static void __cdecl Set_DX8_Render_State(unsigned long,unsigned int);
 static unsigned int Stencil_Caps(){return CurrentCaps->caps;}
};
class W3DVolumetricShadow {public: int bfmeIntersectsVisibleBounds(const AABoxClass&) const;};
class Rva00107E76Mgr {public: void rva00107D8A(); void rva00107E76();};
class W3DVolumetricShadowV2 {
public:
 void rva001074D5();
 bool rva00107046(Vector3*);
 void *vtable;bool enabled,invisible;char pad06[0x66];
 W3DVolumetricShadowV2 *next,*bufferNext;
private:
 RenderObjClass *object;
 char gap78[8];float extent,extraExtrusionPadding;
 char gap88[8];float lightOffsetX,lightOffsetY,lightOffsetZ;
};
class W3DVolumetricShadowManagerV2 {
public:
 void rva001076F6();
 void rva0010720E(int);
 void drawAndRelease(int);
 void renderShadows(RenderInfoClass&);
private:
 char pad[8];W3DVolumetricShadowV2 *shadows;void *lock;
};
void W3DVolumetricShadowManagerV2::renderShadows(RenderInfoClass &info)
{
 AABoxClass bbox;
 TheTerrainRenderObject->getMaximumVisibleBox(info.camera->Get_Frustum(),&bbox,true);
 bool setupDone=false;
 if(((ShadowGlobalDataView*)TheWritableGlobalData)->volumes){
  W3DVolumetricShadowV2 *shadow=shadows;
  W3DVolumetricShadowV2 *bufferedShadow=0;
  bool stencilDone=false;
  if(shadow){
   for(;shadow;shadow=shadow->next){
    if(shadow->enabled&&!shadow->invisible){
     if((unsigned char)((W3DVolumetricShadow*)shadow)->bfmeIntersectsVisibleBounds(bbox)){
      shadow->rva001074D5();
      if(shadow->rva00107046(&info.camera->Get_Position())){
       shadow->bufferNext=bufferedShadow;
       bufferedShadow=shadow;
      }else{
       if(!setupDone){setupDone=true;rva001076F6();}
       if(!stencilDone){stencilDone=true;rva0010720E(0);}
       ((Rva00107E76Mgr*)shadow)->rva00107D8A();
      }
     }
    }
   }
  }
  if(lock)drawAndRelease(0);
  if(bufferedShadow){
   if(!setupDone){setupDone=true;rva001076F6();}
   rva0010720E(1);
   for(shadow=bufferedShadow;shadow;shadow=shadow->bufferNext)
    ((Rva00107E76Mgr*)shadow)->rva00107E76();
   if(lock)drawAndRelease(1);
  }
 }
 if(DX8Wrapper::Stencil_Caps()&0x100)DX8Wrapper::Set_DX8_Render_State(0xB9,0);
}

// BFME1 de2635e79 W3DVolumetricShadowVisibleBoundsPredicate.cpp supplies
// the extrusion-bound predicate semantic lead. Native107046..10713A RET4
// proves the point argument and fields74/80/84/90/94 independently of the
// donor. The matched renderer above passes CameraClass::Get_Position.
// The original predicate name is unknown; retain the admitted address name.
bool W3DVolumetricShadowV2::rva00107046(Vector3 *point)
{
 Vector3 pos=object->Get_Position();
 if(pos.Z+extraExtrusionPadding<point->Z)return 0;
 return ((lightOffsetX>0.0f?lightOffsetX:0.0f)+extent+pos.X>point->X &&
         pos.X-extent+(lightOffsetX<0.0f?lightOffsetX:0.0f)<point->X &&
         (lightOffsetY>0.0f?lightOffsetY:0.0f)+extent+pos.Y>point->Y &&
         pos.Y-extent+(lightOffsetY<0.0f?lightOffsetY:0.0f)<point->Y);
}
