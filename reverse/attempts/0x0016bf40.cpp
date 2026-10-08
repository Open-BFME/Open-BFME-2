// ?get_deformed_vertices@MeshModelClass@@QAEXPAVVector3@@0PBVHTreeClass@@@Z
// partial score=0.447 date=2026-10-09
// cl: /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ZH meshgeometry.cpp get_deformed_vertices guides the run-based transforms.
// Target extends it with two bind-position streams, planar bone/percent-weight
// arrays, a precomputed run list and compact quaternion transforms.
// Existing MeshClass Get_Deformed_Vertices call sites identify the overloads;
// target fields, run step and planar array indexing are independently measured.
#include "matrix3d.h"
#include "quat.h"

void Rva00129510Inc();
struct BfmeSkinTransform {Quaternion Rotation;Vector3 Translation;};
struct BfmeSkinPivot {char name[16];BfmeSkinPivot *parent;BfmeSkinTransform Base,Current;int index;bool visible;char tail[7];};
typedef char BfmeSkinPivotStride[sizeof(BfmeSkinPivot)==0x58?1:-1];
class HTreeClass {public:char fields00[0x14];BfmeSkinPivot *pivots;};
template<class T> struct BfmeSkinBuffer {char fields00[0xc];T *data;};
template<bool translate> static __forceinline void skinRotate(const BfmeSkinTransform &t,const Vector3 &v,Vector3 &out) {
 const Quaternion &q=t.Rotation;
 float x=(v.Z*q.Y-v.Y*q.Z)+v.X*q.W;
 float y=q.W*v.Y-(q.X*v.Z-v.X*q.Z);
 float z=(v.Y*q.X-v.X*q.Y)+v.Z*q.W;
 float w=-(q.X*v.X+q.Y*v.Y+q.Z*v.Z);
 if(translate) {
  out.X=(q.Y*z-y*q.Z)+(x*q.W-w*q.X)+t.Translation.X;
  out.Y=(y*q.W-w*q.Y)-(q.X*z-x*q.Z)+t.Translation.Y;
  out.Z=(y*q.X-x*q.Y)+(z*q.W-w*q.Z)+t.Translation.Z;
 } else {
  out.X=(q.Y*z-y*q.Z)+(x*q.W-w*q.X);
  out.Y=(y*q.W-w*q.Y)-(q.X*z-x*q.Z);
  out.Z=(y*q.X-x*q.Y)+(z*q.W-w*q.Z);
 }
}
static __forceinline void skinMatrix(const BfmeSkinTransform &t,Matrix3D &m) {
 const Quaternion &q=t.Rotation;
 float xx=q.X*q.X*2.0f,xy=q.X*q.Y*2.0f,xz=q.Z*q.X*2.0f;
 float wx=q.W*q.X*2.0f,yy=q.Y*q.Y*2.0f,yz=q.Z*q.Y*2.0f;
 float wy=q.W*q.Y*2.0f,zz=q.Z*q.Z*2.0f,wz=q.W*q.Z*2.0f;
 m[0][0]=1.0f-yy-zz;m[0][1]=xy-wz;m[0][2]=xz+wy;
 m[1][0]=xy+wz;m[1][1]=1.0f-zz-xx;m[1][2]=yz-wx;
 m[2][0]=xz-wy;m[2][1]=yz+wx;m[2][2]=1.0f-yy-xx;
 m[0][3]=t.Translation.X;m[1][3]=t.Translation.Y;m[2][3]=t.Translation.Z;
}
static __forceinline void skinScale(Matrix3D &m,float s) {
 m[0]*=s;m[1]*=s;m[2]*=s;
}
static __forceinline void skinBlend(const Matrix3D &a,const Vector3 &v,const Matrix3D &b,const Vector3 &w,Vector3 &out) {
 out.X=v.X*a[0][0]+v.Y*a[0][1]+w.X*b[0][0]+w.Y*b[0][1]+w.Z*b[0][2]+v.Z*a[0][2]+b[0][3]+a[0][3];
 out.Y=v.Y*a[1][1]+w.Y*b[1][1]+w.Z*b[1][2]+v.X*a[1][0]+w.X*b[1][0]+v.Z*a[1][2]+b[1][3]+a[1][3];
 out.Z=w.Y*b[2][1]+v.Y*a[2][1]+w.Z*b[2][2]+v.X*a[2][0]+w.X*b[2][0]+v.Z*a[2][2]+b[2][3]+a[2][3];
}
static __forceinline void skinBlendNormals(const Matrix3D &a,const Vector3 &v,const Matrix3D &b,const Vector3 &w,Vector3 &out) {
 out.X=v.Y*a[0][1]+w.Y*b[0][1]+w.Z*b[0][2]+v.X*a[0][0]+v.Z*a[0][2]+w.X*b[0][0];
 out.Y=v.Y*a[1][1]+w.Y*b[1][1]+w.Z*b[1][2]+w.X*b[1][0]+v.X*a[1][0]+v.Z*a[1][2];
 out.Z=v.Y*a[2][1]+w.Y*b[2][1]+w.Z*b[2][2]+w.X*b[2][0]+v.Z*a[2][2]+v.X*a[2][0];
}
class MeshModelClass {
public:
 void get_deformed_vertices(Vector3 *,const HTreeClass *);
 void get_deformed_vertices(Vector3 *,Vector3 *,const HTreeClass *);
private:
 char fields00[0x28];int vertexCount;int fields2C;
 BfmeSkinBuffer<Vector3> *vertices[2],*normals[2];
 char fields40[0x10];BfmeSkinBuffer<unsigned short> *bones,*runs;
};
// ?get_deformed_vertices@MeshModelClass@@QAEXPAVVector3@@0PBVHTreeClass@@@Z present-unmatched
void MeshModelClass::get_deformed_vertices(Vector3 *dst,Vector3 *dstNorm,const HTreeClass *tree) {
 if(!runs)return;
 if(!bones)return;
 if(!tree)return;
 int streams=1;
 if(vertices[1])streams=2;
 Vector3 *source[2],*normal[2];
 for(int k=0;k<streams;++k) {
  source[k]=vertices[k]?vertices[k]->data:0;
  normal[k]=normals[k]?normals[k]->data:0;
 }
 unsigned short *bone=bones->data;
 unsigned short *run=runs->data;
 Rva00129510Inc();
 int total=vertexCount;
 int remaining=total;
 while(remaining>0) {
  unsigned int count=run[1];run+=2;
  remaining-=count;
  unsigned int first=bone[0],second=bone[total];
  if(streams==2 && second) {
   float firstWeight=bone[total*2]*0.01f;
   float secondWeight=bone[total*3]*0.01f;
   Matrix3D a,b;
   skinMatrix(tree->pivots[first].Current,a);
   skinMatrix(tree->pivots[second].Current,b);
   skinScale(a,firstWeight);skinScale(b,secondWeight);
   Vector3 *v=source[0],*w=source[1],*out=dst;
   int n=count;
   if(n)do {skinBlend(a,*v++,b,*w++,*out++);}while(--n);
   v=normal[0];w=normal[1];out=dstNorm;n=count;
   if(n)do {skinBlendNormals(a,*v++,b,*w++,*out++);}while(--n);
  } else {
   const BfmeSkinTransform &t=tree->pivots[first].Current;
   Vector3 *v=source[0],*out=dst;
   int n=count;
   if(n)do {skinRotate<true>(t,*v++,*out++);}while(--n);
   v=normal[0];out=dstNorm;n=count;
   if(n)do {skinRotate<false>(t,*v++,*out++);}while(--n);
  }
  bone+=count;
  for(int k=0;k<streams;++k) {source[k]+=count;normal[k]+=count;}
  dst+=count;dstNorm+=count;
 }
}
