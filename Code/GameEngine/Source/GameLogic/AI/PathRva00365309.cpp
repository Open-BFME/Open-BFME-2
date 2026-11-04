// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// Path::rva00365309 (native 0x00365309..0x00365B8A, RET 28): bends the path at
// an optimized node into a circular arc. WB 0x00F1FC60 confirms the curve
// construction (offset/radial/remainder Vector3 rotations, the sweep and the
// segment loop); ZH Vector3 math and Path/PathNode ownership are semantic guides.
// Native accesses supply portal +0x20, optimized link +0x8, the option flags
// 0/1/4/8 and every call address. No original method name is asserted.
// Shapes the retail bytes need: WWMath's Rotate_Z(sinf(angle), cosf(angle))
// through math.h's inline float wrappers (explicit sin/cos locals schedule the
// cos fstp early at all four sites); start/dest/delta/center/end as member-wise
// Coord3D copies with the delta block-scoped; the 0x363B4B angle helper visible
// as an inline noinline copy; PathNode with class-scoped pooled new/delete.
// provides portal20, optimized-link8, options0/1/4/8, and all call addresses.
#define COORD3D_VIEW_INLINE
#define COORD3D_VIEW_INLINE_ONLY
#define COORD3D_VIEW_DTOR
#include "Lib/Coord3DCtorView.h"
#include <math.h>
#include <new>
enum PathfindLayerEnum {LAYER_GROUND=1};
struct Rva0028AC4EEntry;
class Object {public:const Rva0028AC4EEntry *rva0028AC4E()const;};
class Rva001E3F27FloatChaseField {public:float get()const;};
class Rva00065964ObjectPool {public:void *rva002635C2()throw();};
extern Rva00065964ObjectPool g_pathNodePool;
void FreePooledNode(void *);
class PathNode {public:
 static void *operator new(size_t){return g_pathNodePool.rva002635C2();}
 static void operator delete(void *p){FreePooledNode(p);}
 PathNode(const Coord3D *,PathfindLayerEnum)throw();
 PathfindLayerEnum getLayer()const{return layer;}
 PathNode *next,*previous,*nextOptimized;Coord3D pos;PathfindLayerEnum layer;bool canOptimize;char pad1D[3];int portalID;
};
class WWMath {public:static float __fastcall Inv_Sqrt(float);};
class Vector3 {public:
 float X,Y,Z;
 __forceinline Vector3(){} __forceinline Vector3(const Vector3 &v){X=v.X;Y=v.Y;Z=v.Z;} __forceinline Vector3(float x,float y,float z):X(x),Y(y),Z(z){} 
 __forceinline float Length2()const{return X*X+Y*Y+Z*Z;}
 __forceinline void Normalize(){float len2=Length2();if(len2!=0.0f){float oolen=WWMath::Inv_Sqrt(len2);X*=oolen;Y*=oolen;Z*=oolen;}}
 __forceinline void Scale(float s){X*=s;Y*=s;Z*=s;}
 __forceinline void Rotate_Z(float s_angle,float c_angle){float tmp_x=X;float tmp_y=Y;X=c_angle*tmp_x-s_angle*tmp_y;Y=s_angle*tmp_x+c_angle*tmp_y;}
 __forceinline void Rotate_Z(float angle){Rotate_Z(sinf(angle),cosf(angle));}
 static __forceinline float Cross_Product_Z(const Vector3 &lhs,const Vector3 &rhs){return lhs.X*rhs.Y-lhs.Y*rhs.X;}
};
struct Rva00363B4BVector {float x,y,z;};
float ACos(float);
inline __declspec(noinline) float rva00363B4BAngle(const Rva00363B4BVector *lhs, const Rva00363B4BVector *rhs)
{
    float dot = lhs->z * rhs->z + lhs->y * rhs->y + lhs->x * rhs->x;
    if (dot > 1.0f) dot = 1.0f;
    if (dot < -1.0f) dot = -1.0f;
    if (dot >= 0.99f) return 0.0f;
    return ACos(dot);
}
static __forceinline float angleBetween(const Vector3 &lhs,const Vector3 &rhs){return rva00363B4BAngle((const Rva00363B4BVector *)&lhs,(const Rva00363B4BVector *)&rhs);}
struct DirectionOptions {bool flag0,flag1;float value4;bool flag8;};
#include "../../../Include/GameLogic/AIPathfind.h"
#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;
#include "../../../Include/GameLogic/PathfindPath.h"
bool Path::rva00365309(Object *obj,PathNode *node,const Coord3D *input,DirectionOptions *options,int surfaces,float maxAngle,bool blocked)
{
 PathNode *next=node->nextOptimized;
 if(node->portalID!=0x7fffffff || !next){if(!options->flag0)rva003649B1(node);return true;}
 float radius=options->value4;
 Coord3D start=node->pos;
 Coord3D dest=next->pos;
 {
  Coord3D delta=dest;
  delta.sub(&start);
  float halfLength=delta.length()*0.5f;
  if(halfLength<radius)radius=halfLength;
 }
 Vector3 direction(input->x,input->y,input->z);
 direction.Normalize();
 Vector3 towards(dest.x-start.x,dest.y-start.y,dest.z-start.z);
 towards.Normalize();
 float sign=Vector3::Cross_Product_Z(direction,towards)>0.0f?1:-1;
 bool positive=true;
 float bend=angleBetween(direction,towards);
 if(bend<0.19634955f || bend>maxAngle){if(!options->flag0)rva003649B1(node);return true;}
 float rotation=1.5707963705062866f;
 if(options->flag1){
  if(bend<1.5707963705062866){options->flag1=false;if(options->flag0)return false;}
  else sign=-sign;
 }
 if(sign<0.0f){positive=false;bend=-bend;rotation=-rotation;}
 Vector3 offset=direction;
 offset.Rotate_Z(rotation);
 offset.Scale(radius);
 if(!options->flag0)rva003649B1(node);
 Coord3D center=node->pos;
 center.x+=offset.X;center.y+=offset.Y;
 Vector3 toDest(dest.x,dest.y,dest.z);
 toDest.X-=center.x;toDest.Y-=center.y;
 Vector3 radial=toDest;
 radial.Rotate_Z(-rotation);
 radial.Normalize();
 radial.Scale(radius);
 Coord3D end=center;
 end.x+=radial.X;end.y+=radial.Y;
 offset.Scale(-1.0f);
 Vector3 firstRadial=offset;firstRadial.Z=0.0f;firstRadial.Normalize();
 Vector3 secondRadial=radial;secondRadial.Z=0.0f;secondRadial.Normalize();
 float sweep=angleBetween(firstRadial,secondRadial);
 float radialSign=Vector3::Cross_Product_Z(secondRadial,firstRadial)>0.0f?1:-1;
 if(radialSign==sign)sweep=6.2831855f-sweep;
 Vector3 remainder(dest.x,dest.y,0.0f);
 remainder.X-=end.x;remainder.Y-=end.y;
 remainder.Normalize();
 remainder.Rotate_Z(-rotation);
 float extra=angleBetween(remainder,secondRadial);
 sweep+=extra;
 if(options->flag1)sweep=6.2831855f-sweep;
 if(sweep>4.712389f){sweep-=6.2831855f;if(sweep<0.0f)sweep=0.0f;}
 int segments=rva003641AE(sweep,radius);
 if(segments<2)return true;
 if(!positive)sweep=-sweep;
 float step=sweep/(float)segments;
 for(int i=1;i<=segments;i++){
  Vector3 point=offset;
  point.Rotate_Z((float)i*step);
  Coord3D position=center;
  position.x+=point.X;position.y+=point.Y;position.z=start.z;
  if(options->flag0){
   if(!TheAI->pathfinder()->IsValidMovementPositionForObject(&position,node->getLayer(),surfaces,obj))return false;
   if(i==segments && !(unsigned char)TheAI->pathfinder()->IsLinePassable(obj,(void *)surfaces,node->getLayer(),&position,&dest,*(void *const *)&blocked,0,0))return false;
  } else {
   appendNode(&position,node->getLayer(),0x7fffffff);
   node->pos=position;
  }
 }
 if(!options->flag0 && !options->flag8){
  PathNode *saved=new PathNode(&node->pos,LAYER_GROUND);
  dest.add(&node->pos);
  dest.scale(0.5f);
  node->pos=dest;
  const Rva0028AC4EEntry *entry=obj->rva0028AC4E();if(entry)radius=((const Rva001E3F27FloatChaseField *)entry)->get();
  rva00364AA2(saved,node,next,radius);delete saved;
 }
 return true;
}
