// cl: /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// One-stream MeshModelClass::get_deformed_vertices, the sibling of the two-stream overload in Rva0016BF40DeformedVertices.cpp.
// Identity: the pin read from MeshClass::Get_Deformed_Vertices(Vector3*) (0x00149A10), ZH meshgeometry.cpp's call shape.
// Shape follows WorldBuilder's debug MeshGeometryClass::get_deformed_vertices (0xA0E990): buffers read through Get_Array(),
// pivots through Get_Transform(), the blend (WB 0xA0ECA0) and the single-bone loop (WB BoneTransform::TransformPositionArray,
// 0xA0EE10) as members with their loops inside, in WB's operand order. Matrices use the HTreePivotTransform::Get_Matrix3D
// spelling (0x0014D28E), scaled row by row as in BFME1 0x00925860; SkinMatrix3D stands in for BFME 2's Matrix3D blend member.
// The component references in TransformPositionArray are a reconstruction of the retail operand order, not an original-source claim.
#include "vector3.h"
#include "vector4.h"
#include "matrix3d.h"
#include "quat.h"
void Rva00129510Inc();
class SkinMatrix3D : public Matrix3D {
public:
 using Matrix3D::Row;
 __forceinline void Blend(const Vector3 *in0,const SkinMatrix3D &transform1,const Vector3 *in1,Vector3 *out,int count) const {
  while(count--) {
   out->X=Row[0].X*in0->X+Row[0].Y*in0->Y+Row[0].Z*in0->Z+Row[0].W+transform1.Row[0].X*in1->X+transform1.Row[0].Y*in1->Y+transform1.Row[0].Z*in1->Z+transform1.Row[0].W;
   out->Y=Row[1].X*in0->X+Row[1].Y*in0->Y+Row[1].Z*in0->Z+Row[1].W+transform1.Row[1].X*in1->X+transform1.Row[1].Y*in1->Y+transform1.Row[1].Z*in1->Z+transform1.Row[1].W;
   out->Z=Row[2].X*in0->X+Row[2].Y*in0->Y+Row[2].Z*in0->Z+Row[2].W+transform1.Row[2].X*in1->X+transform1.Row[2].Y*in1->Y+transform1.Row[2].Z*in1->Z+transform1.Row[2].W;
   in0++;in1++;out++;
  }
 }
};
class BoneTransform {
public:
 __forceinline void Get_Matrix3D(SkinMatrix3D &matrix) const {
  float xx=Rotation.X*Rotation.X*2.0f;
  float xy=Rotation.X*Rotation.Y*2.0f;
  float xz=Rotation.X*Rotation.Z*2.0f;
  float xw=Rotation.X*Rotation.W*2.0f;
  float yy=Rotation.Y*Rotation.Y*2.0f;
  float yz=Rotation.Y*Rotation.Z*2.0f;
  float yw=Rotation.Y*Rotation.W*2.0f;
  float zz=Rotation.Z*Rotation.Z*2.0f;
  float zw=Rotation.Z*Rotation.W*2.0f;
  matrix.Row[0].X=(1.0f-yy-zz);matrix.Row[0].Y=xy-zw;matrix.Row[0].Z=xz+yw;
  matrix.Row[1].X=xy+zw;matrix.Row[1].Y=(1.0f-zz-xx);matrix.Row[1].Z=yz-xw;
  matrix.Row[2].X=xz-yw;matrix.Row[2].Y=yz+xw;matrix.Row[2].Z=(1.0f-yy-xx);
  matrix.Row[0].W=Translation.X;matrix.Row[1].W=Translation.Y;matrix.Row[2].W=Translation.Z;
 }
 __forceinline void TransformPositionArray(const Vector3 *v,Vector3 *out,int count) const {
  while(count--) {
   const float &rotationW=Rotation.W;
   const float &translationX=Translation.X;
   const float &translationY=Translation.Y;
   float cx=Rotation.Y*v->Z-v->Y*Rotation.Z;
   float x=(Rotation.W*v->X+cx);
   const float &rotationZ=Rotation.Z;
   float y=Rotation.W*v->Y-(Rotation.X*v->Z-v->X*Rotation.Z);
   float z=Rotation.W*v->Z+(Rotation.X*v->Y-v->X*Rotation.Y);
   float w=-((Rotation.X*v->X)+Rotation.Y*v->Y+(Rotation.Z*v->Z));
   out->X=(x*rotationW-w*Rotation.X+(z*Rotation.Y-y*rotationZ)+translationX);
   out->Y=(y*rotationW-w*Rotation.Y-(z*Rotation.X-x*rotationZ)+translationY);
   out->Z=z*rotationW-w*rotationZ+(y*Rotation.X-x*Rotation.Y)+Translation.Z;
   v++;out++;
  }
 }
 Quaternion Rotation;
 Vector3 Translation;
};
struct PivotClass {char Name[16];PivotClass *Parent;BoneTransform BaseTransform;BoneTransform Transform;int Index;bool IsVisible;char tail[7];};
class HTreeClass {
public:
 const BoneTransform &Get_Transform(int pivot) const {return Pivot[pivot].Transform;}
private:
 char Name[16];int NumPivots;PivotClass *Pivot;
};
template<class T> class ShareBufferClass {public:T *Get_Array() {return Array;} private:char fields00[0xc];T *Array;};
// The canonical geometry stores the two position buffers at +0x30/+0x34
// and the normal buffers at +0x38/+0x3C; index those adjacent pointer pairs
// in the existing stream loop. slot54 is the measured bone/run buffer.
#include "MeshModelClass.h"
// Destination pointers MUST point to arrays large enough to hold all vertices
void MeshModelClass::get_deformed_vertices(Vector3 *dst_vert,const HTreeClass *htree) {
 if(slot54==0||VertexBoneLink==0||htree==0)return;
 int streams=1;
 if(slot34)streams=2;
 int i;
 Vector3 *src[2];
 for(i=0;i<streams;++i) {if((&Vertex)[i])src[i]=(&Vertex)[i]->Get_Array();else src[i]=0;}
 unsigned short *runs=slot54->Get_Array();
 unsigned short *bonelinks=VertexBoneLink->Get_Array();
 Rva00129510Inc();
 int vi=Get_Vertex_Count();
 int remaining=vi;
 while(remaining>0) {
  unsigned short *run=runs;
  int cnt=run[1];runs+=2;
  remaining-=cnt;
  int bone0=bonelinks[0];
  int bone1=bonelinks[vi];
  if(streams==2 && bone1) {
   float weight0=bonelinks[vi*2]/100.0f;
   float weight1=(bonelinks[vi*3]/100.0f);
   SkinMatrix3D transform0;
   htree->Get_Transform(bone0).Get_Matrix3D(transform0);
   SkinMatrix3D transform1;
   htree->Get_Transform(bone1).Get_Matrix3D(transform1);
   for(int j=0;j<3;j++) {transform0[j]*=weight0;transform1[j]*=weight1;}
   transform0.Blend(src[0],transform1,src[1],dst_vert,cnt);
  } else {
   const BoneTransform &tm=htree->Get_Transform(bone0);
   tm.TransformPositionArray(src[0],dst_vert,cnt);
  }
  bonelinks+=cnt;
  for(int k=0;k<streams;++k)src[k]+=cnt;
  dst_vert+=cnt;
 }
}
