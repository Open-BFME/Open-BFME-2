// ?rva00365309@Path@@QAE_NPAVObject@@PAVPathNode@@PBUCoord3D@@PAUDirectionOptions@@HMH@Z
// partial score=0.6670113041490117 date=2026-10-09
// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /Oy-
// Native365309..365B8A RET28; WB F1FC60 confirms curve construction.
// ZH Vector3 math and Path/PathNode ownership are semantic guides. Native
// provides portal20, optimized-link8, options0/1/4/8, and all call addresses.
#include "Lib/Coord3D.h"
#include <math.h>
#include <new>
enum PathfindLayerEnum {LAYER_GROUND=1};
struct Rva0028AC4EEntry;
class Object {public:const Rva0028AC4EEntry *rva0028AC4E()const;};
class Rva001E3F27FloatChaseField {public:float get()const;};
class PathNode {public:
 PathNode(const Coord3D *,PathfindLayerEnum)throw();
 PathNode *next,*previous,*nextOptimized;Coord3D pos;PathfindLayerEnum layer;bool canOptimize;char pad1D[3];int portalID;
};
class WWMath {public:static float __fastcall Inv_Sqrt(float);};
class Vector3 {public:
 float X,Y,Z;
 __forceinline Vector3(){} __forceinline Vector3(const Vector3 &v){X=v.X;Y=v.Y;Z=v.Z;} __forceinline Vector3(float x,float y,float z):X(x),Y(y),Z(z){} __forceinline ~Vector3(){}
 __forceinline float Length2()const{return X*X+Y*Y+Z*Z;}
 __forceinline void Normalize(){float len2=Length2();if(len2!=0.0f){float inv=WWMath::Inv_Sqrt(len2);X*=inv;Y*=inv;Z*=inv;}}
 __forceinline void Scale(float s){X*=s;Y*=s;Z*=s;}
 __forceinline void Rotate_Z(float angle){float sine=(float)sin(angle),cosine=(float)cos(angle);float x=cosine*X-sine*Y;Y=cosine*Y+sine*X;X=x;}
};
struct Rva00363B4BVector {float x,y,z;};
float rva00363B4BAngle(const Rva00363B4BVector *,const Rva00363B4BVector *);
static __forceinline float angleBetween(const Vector3 &a,const Vector3 &b){return rva00363B4BAngle((const Rva00363B4BVector *)&a,(const Rva00363B4BVector *)&b);}
struct DirectionOptions {bool flag0,flag1;float value4;bool flag8;};
class Pathfinder {public:
 bool IsValidMovementPositionForObject(const Coord3D *,int,int,const Object *);
 int IsLinePassable(void *,void *,PathfindLayerEnum,const Coord3D *,const Coord3D *,void *,int,int);
};
class AI {public:char pad00[0x10];Pathfinder *finder;Pathfinder *pathfinder()const{return finder;}};
extern AI *TheAI;
class Rva00065964ObjectPool {public:void *rva002635C2()throw();};
extern Rva00065964ObjectPool g_pathNodePool;
void FreePooledNode(void *);
class Path {public:
 bool rva00365309(Object *,PathNode *,const Coord3D *,DirectionOptions *,int,float,int);
 void rva003649B1(const PathNode *);
 void rva002655E3(const Coord3D *,PathfindLayerEnum,int);
 void rva00364AA2(PathNode *,PathNode *,PathNode *,float);
 int rva003641AE(float,float);
};
bool Path::rva00365309(Object *obj,PathNode *node,const Coord3D *input,DirectionOptions *options,int surfaces,float maxAngle,int blocked)
{
 PathNode *next=node->nextOptimized;
 if(node->portalID!=0x7fffffff || !next){if(!options->flag0)rva003649B1(node);return true;}
 float radius=options->value4;
 Coord3D dest;dest.x=next->pos.x;dest.y=next->pos.y;dest.z=next->pos.z;
 Coord3D start;start.x=node->pos.x;start.y=node->pos.y;start.z=node->pos.z;
 Coord3D delta;delta.x=dest.x-start.x;delta.y=dest.y-start.y;delta.z=dest.z-start.z;
 float half=delta.length()*0.5f;if(half<radius)radius=half;
 Vector3 direction(input->x,input->y,input->z);direction.Normalize();
 Vector3 towards(dest.x-start.x,dest.y-start.y,dest.z-start.z);towards.Normalize();
 float sign=direction.X*towards.Y-direction.Y*towards.X>0.0f?1:-1;
 bool positive=true;
 float bend=angleBetween(direction,towards);
 if(bend<0.19634955f || bend>maxAngle){if(!options->flag0)rva003649B1(node);return true;}
 maxAngle=1.5707963705062866f;
 if(options->flag1){if(bend>=1.5707963705062866)sign=-sign;else{options->flag1=false;if(options->flag0)return false;}}
 if(sign<0.0f){positive=false;bend=-bend;maxAngle=-maxAngle;}
 Vector3 offset=direction;offset.Rotate_Z(maxAngle);offset.Scale(radius);
 if(!options->flag0)rva003649B1(node);
 float centerX=node->pos.x+offset.X,centerY=node->pos.y+offset.Y;
 Vector3 radial(dest.x-centerX,dest.y-centerY,dest.z);radial.Rotate_Z(-maxAngle);radial.Normalize();radial.Scale(radius);
 float endX=centerX+radial.X,endY=centerY+radial.Y;
 offset.Scale(-1.0f);
 Vector3 firstRadial(offset.X,offset.Y,0.0f);firstRadial.Normalize();
 Vector3 secondRadial(radial.X,radial.Y,0.0f);secondRadial.Normalize();
 float sweep=angleBetween(firstRadial,secondRadial);
 float radialSign=secondRadial.X*firstRadial.Y-secondRadial.Y*firstRadial.X>0.0f?1:-1;
 if(radialSign==sign)sweep=6.2831855f-sweep;
 Vector3 remainder(dest.x-endX,dest.y-endY,0.0f);remainder.Normalize();remainder.Rotate_Z(-maxAngle);
 float extra=angleBetween(remainder,secondRadial);sweep+=extra;
 if(options->flag1)sweep=6.2831855f-sweep;
 if(sweep>4.712389f){sweep-=6.2831855f;if(sweep<0.0f)sweep=0.0f;}
 int segments=rva003641AE(sweep,radius);
 if(segments>1){
  if(!positive)sweep=-sweep;
  float step=sweep/(float)segments;
  for(int i=1;i<=segments;i++){
   Vector3 point=offset;point.Rotate_Z((float)i*step);
   Coord3D position;position.x=centerX+point.X;position.y=centerY+point.Y;position.z=start.z;
   if(!options->flag0){rva002655E3(&position,node->layer,0x7fffffff);node->pos=position;}
   else {
    if(!TheAI->pathfinder()->IsValidMovementPositionForObject(&position,node->layer,surfaces,obj))return false;
    if(i==segments && !(unsigned char)TheAI->pathfinder()->IsLinePassable(obj,(void *)surfaces,node->layer,&position,&dest,(void *)blocked,0,0))return false;
   }
  }
  if(!options->flag0 && !options->flag8){
   void *memory=g_pathNodePool.rva002635C2();PathNode *saved=memory?new(memory)PathNode(&node->pos,LAYER_GROUND):0;
   dest.x=(dest.x+node->pos.x)*0.5f;dest.y=(dest.y+node->pos.y)*0.5f;dest.z=(dest.z+node->pos.z)*0.5f;node->pos=dest;
   const Rva0028AC4EEntry *entry=obj->rva0028AC4E();if(entry)radius=((const Rva001E3F27FloatChaseField *)entry)->get();
   rva00364AA2(saved,node,next,radius);if(saved)FreePooledNode(saved);
  }
 }
 return true;
}
