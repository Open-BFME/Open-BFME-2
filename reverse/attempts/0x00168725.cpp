// ?Cast_Ray@Rva001684D6@@UAE_NAAVRayCollisionTestClass@@@Z
// partial score=0.9756 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2renderobj /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Reference semantic guide: BFME1 streak.cpp Cast_Ray (575ba2b04).
// Target segments use point storage C4 and renderer width EC; collision
// dispatch is virtual slot120 and the complete native boundary is474 bytes.
#include "rendobj.h"
#include <math.h>
class RayCollisionTestClass {public:CastResultStruct*Result;int CollisionType;RenderObjClass*CollidedRenderObj;LineSegClass Ray;};
struct PointStorage {void*vt;Vector3*Vector;int Capacity,Count;};
class Rva001684D6:public RenderObjClass {public:virtual bool Cast_Ray(RayCollisionTestClass&);private:PointStorage points;char widths[16];char textureShader[8];float Width;char rendererRest[24];};
static __forceinline void transformArray(const Matrix3D&A,const Vector3*in,Vector3*out,int count){while(count--){out->X=+(+(A[0][0]*in->X))+A[0][2]*in->Z;out->X+=A[0][1]*in->Y;out->X+=A[0][3];out->Y=A[1][0]*in->X+A[1][1]*in->Y;out->Y+=A[1][2]*in->Z;out->Y+=A[1][3];out->Z=A[2][0]*in->X+A[2][2]*in->Z;out->Z+=A[2][1]*in->Y;out->Z+=A[2][3];++in;++out;}}
bool Rva001684D6::Cast_Ray(RayCollisionTestClass&raytest){
if((Get_Collision_Type()&raytest.CollisionType)==0)return false;
bool retval=false;float fraction=1.0F;
for(unsigned index=1;index<(unsigned)points.Count;++index){Vector3 curr[2];Transform.mulVector3Array(&points.Vector[index-1],curr,2);LineSegClass line_seg(curr[0],curr[1]);Vector3 p0,p1;
if(raytest.Ray.Find_Intersection(line_seg,&p0,&fraction,&p1,0)){
float dist=(p0-p1).Length();
if(dist<=Width&&fraction>=0&&fraction<raytest.Result->Fraction){retval=true;break;}}}
if(retval){raytest.Result->Fraction=fraction;raytest.Result->SurfaceType=13;raytest.CollidedRenderObj=this;}return retval;}
