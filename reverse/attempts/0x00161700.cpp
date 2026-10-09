// ?Simple_Evaluate_Pivot@HTreeClass@@QBE_NPAVHAnimClass@@HMABVMatrix3D@@PAV3@@Z
// partial score=0.741118739 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /G7 /arch:SSE /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// BFME1/ZH HTreeClass::Simple_Evaluate_Pivot semantic guide at9cbfb551fe20.
// Native161700..162022 is2338B RET20; target uses compact quaternion/position
// composition instead of matrix per pivot. Existing pivot ctor/assignment prove
// stride58, parent10, relative rotation14/translation24, index4C; tree fields10/14/18.
#include "quat.h"
#include "matrix3d.h"
struct S2CompactTransform {
 Quaternion Q; Vector3 Position;
 S2CompactTransform(){}
 explicit S2CompactTransform(bool init):Q(init),Position(0.0f,0.0f,0.0f){}
};
struct S2PivotView {
 char Name[16]; S2PivotView *Parent;
 S2CompactTransform Base,Current;
 int Index; bool visible; float factor;
};
class HAnimClass;
class S2CompactAnimView {
public:
 virtual void vt0();virtual void vt4();virtual void vt8();virtual void vtC();virtual void vt10();
 virtual void vt14();virtual void vt18();virtual void vt1C();virtual void vt20();virtual void vt24();
 virtual void rva_vt28(S2CompactTransform&,int,float)const;
};
class HTreeClass {
public:
 bool Simple_Evaluate_Pivot(HAnimClass*,int,float,const Matrix3D&,Matrix3D*)const;
 char Name[16]; int NumPivots; S2PivotView *Pivot; float ScaleFactor;
};
static __forceinline void rotate(const Quaternion &q,const Vector3&v,Vector3*out){
 float x=(q.Y*v.Z-q.Z*v.Y)+q.W*v.X;
 float y=-(q.X*v.Z-q.Z*v.X)+q.W*v.Y;
 float z=-(q.Y*v.X-q.X*v.Y)+q.W*v.Z;
 float w=q.X*v.X+q.Y*v.Y+q.Z*v.Z;
 out->X=(w*q.X+q.W*x)-(y*q.Z-q.Y*z);
 out->Y=(w*q.Y+q.W*y)-(z*q.X-q.Z*x);
 out->Z=(w*q.Z+q.W*z)-(x*q.Y-q.X*y);
}
static __forceinline void compose(const S2CompactTransform&a,const S2CompactTransform&b,S2CompactTransform&result){
 rotate(a.Q,b.Position,&result.Position);result.Position+=a.Position;
 result.Q=a.Q*b.Q;
}

static __forceinline Matrix3D &S2PivotMatrix(const S2CompactTransform &q,Matrix3D &m) {
 const float xx=q.Q.X*q.Q.X*2.0f,xy=q.Q.X*q.Q.Y*2.0f,xz=q.Q.Z*q.Q.X*2.0f,wx=q.Q.W*q.Q.X*2.0f;
 const float yy=q.Q.Y*q.Q.Y*2.0f,yz=q.Q.Z*q.Q.Y*2.0f,wy=q.Q.W*q.Q.Y*2.0f;
 const float zz=q.Q.Z*q.Q.Z*2.0f,wz=q.Q.W*q.Q.Z*2.0f;
 m[0][0]=1.0f-yy-zz;m[0][1]=xy-wz;m[0][2]=xz+wy;
 m[1][0]=xy+wz;m[1][1]=1.0f-zz-xx;m[1][2]=yz-wx;
 m[2][0]=xz-wy;m[2][1]=yz+wx;m[2][2]=1.0f-yy-xx;
 m[0][3]=q.Position.X;m[1][3]=q.Position.Y;m[2][3]=q.Position.Z;
 return m;
}
bool HTreeClass::Simple_Evaluate_Pivot(HAnimClass *motion,int pivot_index,float frame,const Matrix3D &obj_tm,Matrix3D *end_tm)const {
 if(!end_tm)return false;
 end_tm->Make_Identity();
 if(!motion || pivot_index<0 || pivot_index>=NumPivots)return false;
 S2CompactTransform total(true);
 for(S2PivotView *p=&Pivot[pivot_index];p && p->Parent;p=p->Parent){
  S2CompactTransform anim;
  ((S2CompactAnimView*)motion)->rva_vt28(anim,p->Index,frame);
  anim.Position*=ScaleFactor;
  S2CompactTransform current;compose(p->Base,anim,current);
  compose(current,total,total);
 }
 S2PivotMatrix(total,*end_tm);
 end_tm->preMul(obj_tm);
 return true;
}
