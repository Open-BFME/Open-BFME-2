// cl: /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ZH meshgeometry.cpp get_deformed_vertices guides the run-based transforms.
// Target extends it with two bind-position streams, planar bone/percent-weight
// arrays, a precomputed run list and compact quaternion transforms.
// Existing MeshClass Get_Deformed_Vertices call sites identify the overloads;
// target fields, run step and planar array indexing are independently measured.
// Shape follows WorldBuilder's debug MeshGeometryClass::get_deformed_vertices (0xA0F000, meshgeometry.cpp),
// its BoneTransform members (bonetransform.h) and two thiscall Matrix3D blend members (0xA0ECA0, 0xA0F390).
#include "matrix3d.h"
#include "quat.h"

void Rva00129510Inc();
// HTree pivot transform at pivot+0x30: rotation quaternion and translation.
struct BoneTransform {
 __forceinline void Get_Matrix3D(Matrix3D &matrix) const {
  float xx=Rotation.X*Rotation.X*2.0f;
  float xy=Rotation.X*Rotation.Y*2.0f;
  float xz=Rotation.X*Rotation.Z*2.0f;
  float xw=Rotation.X*Rotation.W*2.0f;
  float yy=Rotation.Y*Rotation.Y*2.0f;
  float yz=Rotation.Y*Rotation.Z*2.0f;
  float yw=Rotation.Y*Rotation.W*2.0f;
  float zz=Rotation.Z*Rotation.Z*2.0f;
  float zw=Rotation.Z*Rotation.W*2.0f;
  matrix[0][0]=1.0f-yy-zz;matrix[0][1]=xy-zw;matrix[0][2]=xz+yw;
  matrix[1][0]=xy+zw;matrix[1][1]=1.0f-zz-xx;matrix[1][2]=yz-xw;
  matrix[2][0]=xz-yw;matrix[2][1]=yz+xw;matrix[2][2]=1.0f-yy-xx;
  matrix[0][3]=Translation.X;matrix[1][3]=Translation.Y;matrix[2][3]=Translation.Z;
 }
 __forceinline void TransformPositionArray(const Vector3 *inPosition,Vector3 *outPosition,int count) const {
  while(count--) {
   float x=Rotation.W*inPosition->X+(Rotation.Y*inPosition->Z-inPosition->Y*Rotation.Z);
   float y=Rotation.W*inPosition->Y-(Rotation.X*inPosition->Z-inPosition->X*Rotation.Z);
   float z=Rotation.W*inPosition->Z+(Rotation.X*inPosition->Y-inPosition->X*Rotation.Y);
   float w=-(Rotation.X*inPosition->X+Rotation.Y*inPosition->Y+Rotation.Z*inPosition->Z);
   outPosition->X=(x*Rotation.W-w*Rotation.X+(z*Rotation.Y-y*Rotation.Z))+Translation.X;
   outPosition->Y=(y*Rotation.W-w*Rotation.Y)-(z*Rotation.X-x*Rotation.Z)+Translation.Y;
   outPosition->Z=(z*Rotation.W-w*Rotation.Z)+(y*Rotation.X-x*Rotation.Y)+Translation.Z;
   inPosition++;
   outPosition++;
  }
 }
 __forceinline void TransformNormalArray(const Vector3 *inNormal,Vector3 *outNormal,int count) const {
  while(count--) {
   float x=Rotation.W*inNormal->X+(Rotation.Y*inNormal->Z-inNormal->Y*Rotation.Z);
   float y=Rotation.W*inNormal->Y-(Rotation.X*inNormal->Z-inNormal->X*Rotation.Z);
   float z=Rotation.W*inNormal->Z+(Rotation.X*inNormal->Y-inNormal->X*Rotation.Y);
   float w=-(Rotation.X*inNormal->X+Rotation.Y*inNormal->Y+Rotation.Z*inNormal->Z);
   outNormal->X=(x*Rotation.W-w*Rotation.X+(z*Rotation.Y-y*Rotation.Z));
   outNormal->Y=(y*Rotation.W-w*Rotation.Y)-(z*Rotation.X-x*Rotation.Z);
   outNormal->Z=(z*Rotation.W-w*Rotation.Z)+(y*Rotation.X-x*Rotation.Y);
   inNormal++;
   outNormal++;
  }
 }
 Quaternion Rotation;
 Vector3 Translation;
};
struct BfmeSkinPivot {char name[16];BfmeSkinPivot *parent;BoneTransform Base,Transform;int index;bool visible;char tail[7];};
typedef char BfmeSkinPivotStride[sizeof(BfmeSkinPivot)==0x58?1:-1];
class HTreeClass {
public:
 const BoneTransform &Get_Transform(int pivot) const {return Pivot[pivot].Transform;}
private:
 char fields00[0x14];BfmeSkinPivot *Pivot;
};
template<class T> struct BfmeSkinBuffer {T *Get_Array() {return Array;} char fields00[0xc];T *Array;};
// The two blend members BFME 2's Matrix3D carries and the shared WWMath header lacks, as a layout-identical view.
struct Matrix3DBlend : public Matrix3D {
 __forceinline void blendVector3Array(const Vector3 *in,const Matrix3D &secondTransform,const Vector3 *secondPositions,Vector3 *out,int count) const {
  while(count--) {
   out->X=(Row[0].X*in->X+Row[0].Y*in->Y+Row[0].Z*in->Z+Row[0].W+secondTransform[0].X*secondPositions->X+secondTransform[0].Y*secondPositions->Y+secondTransform[0].Z*secondPositions->Z+secondTransform[0].W);
   out->Y=Row[1].X*in->X+Row[1].Y*in->Y+Row[1].Z*in->Z+Row[1].W+secondTransform[1].X*secondPositions->X+secondTransform[1].Y*secondPositions->Y+secondTransform[1].Z*secondPositions->Z+secondTransform[1].W;
   out->Z=Row[2].X*in->X+Row[2].Y*in->Y+Row[2].Z*in->Z+Row[2].W+secondTransform[2].X*secondPositions->X+secondTransform[2].Y*secondPositions->Y+secondTransform[2].Z*secondPositions->Z+secondTransform[2].W;
   ++in;
   ++secondPositions;
   ++out;
  }
 }
 __forceinline void blendNormalArray(const Vector3 *in,const Matrix3DBlend &secondTransform,const Vector3 *secondNormals,Vector3 *out,int count) const {
  while(count--) {
   out->X=Row[0].X*in->X+Row[0].Y*in->Y+Row[0].Z*in->Z+secondTransform.Row[0].X*secondNormals->X+secondTransform.Row[0].Y*secondNormals->Y+secondTransform.Row[0].Z*secondNormals->Z;
   out->Y=(Row[1].X*in->X+((Row[1].Y*in->Y))+Row[1].Z*in->Z+(secondTransform.Row[1].X*secondNormals->X)+((secondTransform.Row[1].Y*secondNormals->Y))+(secondTransform.Row[1].Z*secondNormals->Z));
   out->Z=Row[2].X*in->X+Row[2].Y*in->Y+Row[2].Z*in->Z+secondTransform.Row[2].X*secondNormals->X+secondTransform.Row[2].Y*secondNormals->Y+secondTransform.Row[2].Z*secondNormals->Z;
   ++in;
   ++secondNormals;
   ++out;
  }
 }
};
class MeshModelClass {
public:
 void get_deformed_vertices(Vector3 *,const HTreeClass *);
 void get_deformed_vertices(Vector3 *,Vector3 *,const HTreeClass *);
 int Get_Vertex_Count() const {return VertexCount;}
private:
 char fields00[0x28];int VertexCount;int fields2C;
 BfmeSkinBuffer<Vector3> *Vertex[2],*VertexNorm[2];
 char fields40[0x10];BfmeSkinBuffer<unsigned short> *VertexBoneLink,*VertexBoneRuns;
};
// Destination pointers MUST point to arrays large enough to hold all vertices
void MeshModelClass::get_deformed_vertices(Vector3 *dst_vert,Vector3 *dst_norm,const HTreeClass *htree) {
 if(VertexBoneRuns==0||VertexBoneLink==0||htree==0)return;
 int streams=1;
 if(Vertex[1]!=0)streams=2;
 Vector3 *src_vert[2];
 Vector3 *src_norm[2];
 int i;
 for(i=0;i<streams;i++) {
  if(Vertex[i]!=0)src_vert[i]=Vertex[i]->Get_Array();else src_vert[i]=0;
  if(VertexNorm[i]!=0)src_norm[i]=VertexNorm[i]->Get_Array();else src_norm[i]=0;
 }
 unsigned short *runs=VertexBoneRuns->Get_Array();
 unsigned short *bonelink=VertexBoneLink->Get_Array();
 Rva00129510Inc();
 int vertex_count=Get_Vertex_Count();
 int vi=vertex_count;
 while(vi>0) {
  int cnt=runs[1];
  runs+=2;
  vi-=cnt;
  int bone0=bonelink[0];
  int bone1=bonelink[vertex_count];
  if(streams==2&&bone1!=0) {
   const BoneTransform *firstTransform=0,*bt1=0;
   float firstWeight=(bonelink[vertex_count*2]/100.0f);
   float secondWeight=(bonelink[vertex_count*3]/100.0f);
   firstTransform=&htree->Get_Transform(bone0);
   Matrix3D firstMatrix;
   firstTransform->Get_Matrix3D(firstMatrix);
   bt1=&htree->Get_Transform(bone1);
   Matrix3D secondMatrix;
   bt1->Get_Matrix3D(secondMatrix);
   for(int row=0;row<3;row++) {
    firstMatrix[row]*=firstWeight;
    secondMatrix[row]*=secondWeight;
   }
   ((const Matrix3DBlend &)firstMatrix).blendVector3Array(src_vert[0],secondMatrix,src_vert[1],dst_vert,cnt);
   ((const Matrix3DBlend &)firstMatrix).blendNormalArray(src_norm[0],(const Matrix3DBlend &)secondMatrix,src_norm[1],dst_norm,cnt);
  } else {
   const BoneTransform &tm=htree->Get_Transform(bone0);
   tm.TransformPositionArray(src_vert[0],dst_vert,cnt);
   tm.TransformNormalArray(src_norm[0],dst_norm,cnt);
  }
  bonelink+=cnt;
  for(i=0;i<streams;i++) {
   src_vert[i]+=cnt;
   src_norm[i]+=cnt;
  }
  dst_vert+=cnt;
  dst_norm+=cnt;
 }
}

// Corresponding matrix rows are weighted together before transforming each run.
// Positions include translation; normal vectors use only the rotation terms.
