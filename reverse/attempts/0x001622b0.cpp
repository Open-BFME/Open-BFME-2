// ?Capture_Update@HTreeClass@@QAEHH@Z
// partial score=0.88 date=2026-09-24
// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc
struct Vector3 { float X,Y,Z; __forceinline Vector3() {} __forceinline Vector3(float x,float y,float z):X(x),Y(y),Z(z){}
 __forceinline Vector3(const Vector3 &v) { X=v.X; Y=v.Y; Z=v.Z; }
 __forceinline Vector3 &operator=(const Vector3 &v) { X=v.X; Y=v.Y; Z=v.Z; return *this; }
 __forceinline Vector3 &operator+=(const Vector3 &b) { X+=b.X; Y+=b.Y; Z+=b.Z; return *this; } };
__forceinline Vector3 operator+(const Vector3 &a,const Vector3 &b) { return Vector3(a.X+b.X,a.Y+b.Y,a.Z+b.Z); }
struct Quaternion { float X,Y,Z,W;
 __forceinline Quaternion &operator=(const Quaternion &s) { X=s.X; Y=s.Y; Z=s.Z; W=s.W; return *this; }
 __forceinline Vector3 Rotate_Vector(const Vector3 &v) const {
  float x=(v.Z*Y-Z*v.Y)+(v.X*W); float y=v.Y*W-(v.Z*X-Z*v.X); float z=(v.Y*X-Y*v.X)+(v.Z*W); float w=-(((v.X*X)+(v.Z*Z))+(v.Y*Y));
  return Vector3((z*Y-Z*y)+(x*W-X*w), (y*W-Y*w)-(z*X-Z*x), (y*X-Y*x)+(z*W-Z*w)); }
 __forceinline void Rotate_Vector(const Vector3 &v, Vector3 *result) const {
  float x=(v.Z*Y-Z*v.Y)+(v.X*W); float y=v.Y*W-(v.Z*X-Z*v.X); float z=(v.Y*X-Y*v.X)+(v.Z*W); float w=-(((v.X*X)+(v.Z*Z))+(v.Y*Y));
  result->X=(z*Y-Z*y)+(x*W-X*w); result->Y=(y*W-Y*w)-(z*X-Z*x); result->Z=(y*X-Y*x)+(z*W-Z*w); }
 __forceinline void postMul(const Quaternion &b) { Quaternion a=*this;
  X=(b.X*a.W)+((a.X*b.W)+(b.Z*a.Y-a.Z*b.Y)); Y=((a.Y*b.W)+(b.Y*a.W))-(b.Z*a.X-a.Z*b.X); Z=((a.Z*b.W)+(b.Y*a.X-a.Y*b.X))+(b.Z*a.W); W=b.W*a.W-(((b.X*a.X)+(b.Z*a.Z))+(b.Y*a.Y)); }
 __forceinline void postMulW(const Quaternion &b) { Quaternion a=*this;
  X=((b.X*a.W)+(a.X*b.W))+(b.Z*a.Y-a.Z*b.Y); Y=((a.Y*b.W)+(b.Y*a.W))-(b.Z*a.X-a.Z*b.X); Z=((b.Z*a.W)+(a.Z*b.W))+(b.Y*a.X-a.Y*b.X); W=b.W*a.W-(((b.X*a.X)+(b.Y*a.Y))+(b.Z*a.Z)); }
};
#define ROTADD_W(T,R,V) T += R.Rotate_Vector(V)
#define ROTADD_L(T,R,V) { Vector3 _t; R.Rotate_Vector(V,&_t); T.X = T.X+_t.X; T.Y = T.Y+_t.Y; T.Z = T.Z+_t.Z; }
#define ROTADD(T,R,V) ROTADD_L(T,R,V)
struct QuatTransform { Quaternion Rotation; Vector3 Translation; __forceinline QuatTransform() {} };
struct CapturedBone { int Index; Quaternion Rotation; Vector3 Translation; bool WorldSpaceTranslation; };
struct PivotClass { char Name[16]; PivotClass *Parent; QuatTransform BaseTransform; QuatTransform Transform; int Index; bool IsVisible; float Fade; };
class HTreeClass { char TreeFields[16]; int NumPivots; PivotClass *Pivot; float ScaleFactor; CapturedBone *Begin,*End,*Capacity; public: int Capture_Update(int pivot_index); };
int HTreeClass::Capture_Update(int pivot_index) {
 CapturedBone *bone=Begin;
 while (bone!=End) { if (bone->Index>=pivot_index) break; ++bone; }
 if (bone==End || bone->Index!=pivot_index) return -1;
 if (bone->WorldSpaceTranslation) {
  Quaternion rot=bone->Rotation;
  QuatTransform &t=Pivot[pivot_index].Transform;
  ROTADD_W(t.Translation,t.Rotation,Vector3(0.0f,0.0f,0.0f));
  t.Rotation.postMul(rot);
  t.Translation+=bone->Translation;
 } else {
  QuatTransform &t=Pivot[pivot_index].Transform;
  ROTADD_L(t.Translation,t.Rotation,bone->Translation);
  t.Rotation.postMul(bone->Rotation);
 }
 ++bone;
 return bone==End ? -1 : bone->Index;
}
