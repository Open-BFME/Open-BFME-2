// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// ?doParticles@RenderObjectDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z
// Native 00562DDB..005634F7 (1820B), RET12. Vtable slot4 at RVA81C454,
// table followed by RenderObjectDrawModule, and WB1428210 establish identity.
// Types of the three parameters follow the shared category6 rendering slot.
// Matrix operations use pinned BF1 a7c38d3b WWMath; particle offsets and
// helper calls are read independently from target. StreakDrawModuleDoParticles
// is the target-verified sibling for the storage/culling/tracking-pointer ABI.
// Preserve inline row access without emitting a competing Matrix3 indexer.
#include "../../../../../../reference/shims/bfme_matrix3_owner_link/matrix3.h"
#include "matrix3d.h"
// Retain inline indexing without a competing external Matrix3 helper.
#include "../../../../../../reference/shims/bfme_matrix3_owner_link/matrix3.h"
#include "../../../../../Libraries/Include/Lib/RGBColor.h"

class RenderInfoClass;
class RenderObjClass;
class ParticleSystem;
ParticleSystem *Make001FCBD7();
#include "../../../../Include/GameClient/Rva0004CABDSevenEight.h"
class Rva001F4D4F {public:float rva001F4D4F();};
class Rva001F4D76 {public:float rva001F4D76();};
class Rva001F4D9D {public:float rva001F4D9D();};
#include "../../../../Include/GameClient/Rva001F4DC4.h"
#include "../../../../Include/Common/Rva001F4DE6.h"
#include "../../../../Include/GameClient/Rva001F4DF9.h"
#include "../../../../Include/GameClient/Rva001F4E1BSlot.h"
namespace FXParticleSystem {class CPUParticle {public:bool rva001F4E2D();};}
class Rva0007671F {public:Rva0007671F();float row[4][4];};
extern "C" Rva0007671F *__stdcall D3DXMatrixRotationX(Rva0007671F*,float);
extern "C" Rva0007671F *__stdcall D3DXMatrixRotationY(Rva0007671F*,float);
extern "C" Rva0007671F *__stdcall D3DXMatrixRotationZ(Rva0007671F*,float);
extern "C" Rva0007671F *__stdcall D3DXMatrixRotationAxis(Rva0007671F*,const Vector3*,float);
bool Rva0010EA49_SetDiffuse(RenderObjClass*,float,float,float);
bool Rva0010E676_SetEmissive(RenderObjClass*,float,float,float);
bool Rva0010E87A_SetOpacity(RenderObjClass*,float);

template<int N> class ParticleSlots : public ParticleSlots<N-1> {public:virtual void slot(char (*)[N]);};
template<> class ParticleSlots<0> {};
class ParticleTransformView:public ParticleSlots<21> {public:virtual void setTransform(const Matrix3D&);};
class ParticleSceneView:public ParticleSlots<100> {public:virtual void *scene();virtual void setScene(void*);};
struct RenderParticle;
class RenderParticleStorage:public ParticleSlots<8> {public:virtual RenderParticle *first();};
struct ParticleRenderSystemView {
 char pad0[8];int shader;char padC[0x98];RenderParticleStorage *storage;
 char padA8[0x14];Matrix3D transform;char padEC[0xB4];bool independentRotation;
};
struct RenderParticle {
 char pad0[0x10];Vector3 axis;Vector3 position;char pad28[0x14];ParticleRenderSystemView *system;
 char pad40[0x1C];int shader;char pad60[4];RenderParticle *next;
 char pad68[0x24];RenderObjClass *object;
 ParticleRenderSystemView *getSystem(){return system?system:(ParticleRenderSystemView*)Make001FCBD7();}
};
struct ParticleCullBox {Vector3 center,extent;};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class ParticleTerrainView:public ParticleSlots<6> {public:virtual float groundHeight(float,float,void*);};

static __forceinline Matrix3 RenderRotationProduct(const Matrix3 &matrix3,const Matrix3 &b) {
 return Matrix3(Vector3((matrix3[0][0]*b[0][0]+matrix3[0][1]*b[1][0]+matrix3[0][2]*b[2][0]),(matrix3[0][0]*b[0][1]+matrix3[0][1]*b[1][1]+matrix3[0][2]*b[2][1]),(matrix3[0][0]*b[0][2]+matrix3[0][1]*b[1][2]+matrix3[0][2]*b[2][2])),Vector3((matrix3[1][0]*b[0][0]+matrix3[1][1]*b[1][0]+matrix3[1][2]*b[2][0]),(matrix3[1][0]*b[0][1]+matrix3[1][1]*b[1][1]+matrix3[1][2]*b[2][1]),(matrix3[1][0]*b[0][2]+matrix3[1][1]*b[1][2]+matrix3[1][2]*b[2][2])),Vector3((matrix3[2][0]*b[0][0]+matrix3[2][1]*b[1][0]+matrix3[2][2]*b[2][0]),(matrix3[2][0]*b[0][1]+matrix3[2][1]*b[1][1]+matrix3[2][2]*b[2][1]),(matrix3[2][0]*b[0][2]+matrix3[2][1]*b[1][2]+matrix3[2][2]*b[2][2])));
}
namespace FXParticleSystem {
class RenderObjectDrawModule {
public:
 virtual int doParticles(RenderInfoClass&,void*,int*);
private:
 ParticleRenderSystemView *system;
 char pad8[0x14];bool groundClipping;float groundOffset;bool particleShader;
 ParticleRenderSystemView *getSystem(){return system?system:(ParticleRenderSystemView*)Make001FCBD7();}
};
int RenderObjectDrawModule::doParticles(RenderInfoClass&,void *bounds,int*) {
 int count=0;
 Rva0007671F rotation;
 ParticleCullBox *box=(ParticleCullBox*)bounds;
 float cx=box->center.X,cy=box->center.Y,cz=box->center.Z;
 float ex=box->extent.X,ey=box->extent.Y,ez=box->extent.Z;
 RenderParticle *renderParticle=0;
 if(!(unsigned char)((Rva0004CABDSevenEight*)getSystem())->get())
  renderParticle=getSystem()->storage->first();
 for(;renderParticle;renderParticle=renderParticle->next) {
  if(((CPUParticle*)renderParticle)->rva001F4E2D())continue;
  // The x extent goes through a second local so its value merges in a register
  // first (measured: with this copy the plain row-major rotation product below
  // compiles to retail without hand-permuted terms).
  float sxExtent=((Rva001F4D4F*)renderParticle)->rva001F4D4F();
  float sx=sxExtent;
  float sy=((Rva001F4D76*)renderParticle)->rva001F4D76();
  float sz=((Rva001F4D9D*)renderParticle)->rva001F4D9D();
  if(WWMath::Fabs(renderParticle->position.X-cx)>sx+ex)continue;
  if(WWMath::Fabs(renderParticle->position.Y-cy)>sy+ey)continue;
  bool underground=false;
  if(groundClipping) {
   if(renderParticle->position.Z-sz>cz+ez)continue;
   if(((ParticleTerrainView*)TheTerrainLogic)->groundHeight(renderParticle->position.X,renderParticle->position.Y,0)>renderParticle->position.Z)underground=true;
  } else if(WWMath::Fabs(renderParticle->position.Z-cz)>sz+ez)continue;
  const RGBColor *color=((Rva001F4E1BSlot*)renderParticle)->get();
  float alpha=((Rva001F4DF9*)renderParticle)->rva001F4DF9();
  int axis=((Rva001F4DE6*)renderParticle)->rva001F4DE6();
  float angle=((Rva001F4DC4*)renderParticle)->rva001F4DC4();
  if(axis==4)D3DXMatrixRotationZ(&rotation,angle);
  else if(axis==2)D3DXMatrixRotationX(&rotation,angle);
  else if(axis==3)D3DXMatrixRotationY(&rotation,angle);
  else if(axis==5) {Vector3 direction(renderParticle->axis.X,-renderParticle->axis.Y,renderParticle->axis.Z);D3DXMatrixRotationAxis(&rotation,&direction,angle);}
  if(renderParticle->object) {
   Matrix3D transform(renderParticle->getSystem()->transform);
   if(underground) transform[2][3]=groundOffset+transform[2][3];
   else {
    if(axis!=1) {
     Matrix3 orientation(*(Matrix3D*)&rotation);
     if(!renderParticle->getSystem()->independentRotation){Matrix3 base(transform);orientation=RenderRotationProduct(base,orientation);}
     transform.Set_Rotation(orientation);
    }
    if(sx<0.0001f)sx=0.0001f;
    if(sy<0.0001f)sy=0.0001f;
    if(sz<0.0001f)sz=0.0001f;
    if(sx!=1.0f||sy!=1.0f||sz!=1.0f)transform.Scale(sx,sy,sz);
    transform.Set_Translation(Vector3(renderParticle->position.X,renderParticle->position.Y,renderParticle->position.Z));
   }
   ((ParticleTransformView*)renderParticle->object)->setTransform(transform);
   int shader=particleShader?renderParticle->shader:getSystem()->shader;
   switch(shader) {
   case 10:Rva0010E676_SetEmissive(renderParticle->object,color->red*alpha,color->green*alpha,color->blue*alpha);break;
   case 9:Rva0010E87A_SetOpacity(renderParticle->object,alpha);break;
   case 8:Rva0010EA49_SetDiffuse(renderParticle->object,color->red*alpha,color->green*alpha,color->blue*alpha);break;
   }
   if(((ParticleSceneView*)renderParticle->object)->scene())((ParticleSceneView*)renderParticle->object)->setScene(0);
  }
  if(++count==512)break;
 }
 return count;
}
}
