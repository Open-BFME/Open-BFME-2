// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil
// ?rva0007F0FB@Rva0007F0FBOwner@@QAEXPAVCameraClass@@_N@Z, retail 0x0007F0FB, 1921 bytes: the water
// reflection camera setup beside the matched WaterRenderObjClass reflection pass 0x0007F87C.
// `old` is built as WWMath's Matrix4x4(const Matrix3D &) does: Init copies Row[0..2] from the
// Matrix3D rows through Vector4::operator= and sets Row[3] = Vector4(0,0,0,1). The row-wise copies
// leave two coalesced address copies on c2 3077's globreg free list, so the split ranges around the
// override call renumber old's pieces and the reloads come out xmm6,xmm5,xmm4,xmm3 as in retail
// (RewriteSplitGlobregs inserts reloads by new candidate number; GrgNewGlobreg reuses _FreeGlobs LIFO).
// The transposed camera matrix uses the 16-float constructor and the clip plane a named Vector4.
// BFME1 donor 0bef414b52a39a3ab1ec98dca60d8a214de4260e; native BFME2 7EF35..7F0F9.
// Native camera preparation uses CameraClass* and bool, with the counted camera pointer at owner+0xFC.
// The donor provenance note above describes the preceding loadSetting body; reflection is only a donor algorithm lead.
// Native-derived reconstruction; remaining code generation and declaration-binding evidence is in reverse/attempt_support/0007f0fb-20261019.md.
// The transposed camera matrix is filled through the 16-float Matrix4x4 constructor, as ZH's FullMatrix; round 3 evidence is in reverse/attempt_support/0007f0fb-20261020.md.
#include <float.h>
// Use the retail-owned outline helpers while retaining the native inline arithmetic.
class Vector4;
__declspec(dllimport) __forceinline Vector4 operator * (const Vector4 &a, float k);
#include "../../../../../../reference/shims/bfme_vp_math/vector4.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

class Matrix3D;
class Matrix4 {
public:
 float m[4][4];
 Matrix4(){}
 __declspec(dllimport) __forceinline Matrix4(const Matrix3D &s);
 __forceinline void Init(const Matrix3D &s);
 __forceinline Vector4 &operator[](int i) { return *(Vector4*)m[i]; }
 __forceinline const Vector4 &operator[](int i) const { return *(const Vector4*)m[i]; }
 __forceinline Matrix4(float m11,float m12,float m13,float m14,float m21,float m22,float m23,float m24,
  float m31,float m32,float m33,float m34,float m41,float m42,float m43,float m44)
 {
  m[0][0]=m11; m[0][1]=m12; m[0][2]=m13; m[0][3]=m14;
  m[1][0]=m21; m[1][1]=m22; m[1][2]=m23; m[1][3]=m24;
  m[2][0]=m31; m[2][1]=m32; m[2][2]=m33; m[2][3]=m34;
  m[3][0]=m41; m[3][1]=m42; m[3][2]=m43; m[3][3]=m44;
 }
};
#include "../../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
// WWMath matrix3d.h's inline Set(x, y, z, pos), which the canonical header leaves to units.
static __forceinline void matrixSet(Matrix3D &mtx, const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis, const Vector3 &pos)
{
 mtx.Row[0][0]=xAxis.X; mtx.Row[0][1]=yAxis.X; mtx.Row[0][2]=zAxis.X; mtx.Row[0][3]=pos.X;
 mtx.Row[1][0]=xAxis.Y; mtx.Row[1][1]=yAxis.Y; mtx.Row[1][2]=zAxis.Y; mtx.Row[1][3]=pos.Y;
 mtx.Row[2][0]=xAxis.Z; mtx.Row[2][1]=yAxis.Z; mtx.Row[2][2]=zAxis.Z; mtx.Row[2][3]=pos.Z;
}
__declspec(dllimport) __forceinline Matrix4::Matrix4(const Matrix3D &s) {
 Init(s);
}
__forceinline void Matrix4::Init(const Matrix3D &matrix3D) {
 (*this)[0]=matrix3D[0]; (*this)[1]=matrix3D[1]; (*this)[2]=matrix3D[2]; (*this)[3]=Vector4(0.0f,0.0f,0.0f,1.0f);
}
class CameraClass {
public:
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
 virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
 virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
 virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
 virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
 virtual void Validate_Transform() const;
 virtual void Set_Transform(const Matrix3D &);
 char gap[0x14];
 Matrix3D transform;
 CameraClass &operator=(const CameraClass &);
 void Set_Viewport(const Vector2 &,const Vector2 &);
 void Apply();
 void Set_Reflected_Projection_Matrix(const Matrix4 &);
 const Matrix3D &Get_Transform() const { Validate_Transform();return transform; }
};
#include "../../../../../GameEngine/Include/Common/Overridable.h"
// recursively ask if there is a next override, and if not, return this.
static __forceinline Overridable *finalSetting(Overridable *setting) {
 if(!setting)return 0;
 if(setting->friend_getNextOverride())return setting->friend_getNextOverride()->friend_getFinalOverride();
 return setting;
}
class WaterTransparencySetting;
template<class T> class OVERRIDE {public:T *ptr;};
extern OVERRIDE<WaterTransparencySetting> TheWaterTransparency;
class StringClass {
 char *buffer;
public:
 StringClass(int,bool);
 ~StringClass(){Free_String();}
private:
 void Free_String();
};
struct IDirect3DDevice8;
struct RenderStateStruct { char gap[0x22c]; Matrix4 view; };
class DX8Wrapper {
public:
 static void Apply_Render_State_Changes();
 static void Get_DX8_Render_State_Value_Name(StringClass &,unsigned long,unsigned);
 static Matrix4 Projection() { return DeviceProjectionMatrix; }
protected:
 static RenderStateStruct render_state;
 static unsigned render_state_changed;
 static unsigned RenderStates[256];
 static IDirect3DDevice8 *D3DDevice;
 static unsigned render_state_changes;
 static Matrix4 DeviceProjectionMatrix;
 friend class Rva0007F0FBOwner;
};
#include "../../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"
extern unsigned number_of_DX8_calls;
extern bool bfmeCameraProjectionOverride;
// The reflection's clip-space locals are D3DX matrices (indexed .m[i][j], passed only to D3DX), not WW3D Matrix4s.
struct D3DXMATRIX { float m[4][4]; D3DXMATRIX() {} };
extern "C" D3DXMATRIX *__stdcall D3DXMatrixInverse(D3DXMATRIX *,float *,const D3DXMATRIX *);
extern "C" D3DXMATRIX *__stdcall D3DXMatrixTranspose(D3DXMATRIX *,const D3DXMATRIX *);
extern "C" Vector4 *__stdcall rva0062AF4AD3DXVec4Transform(Vector4 *,const Vector4 *,const D3DXMATRIX *);
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert(); // The rowed release reports whether this was the last unlock.
struct DeviceLock {
 DeviceLock(){BFME_DX8_Thread_Lock();}
 ~DeviceLock(){BFME_DX8_Thread_Assert();}
};
class Rva0007F0FBOwner {
 char gap[0xfc];
 CameraClass *camera;
public:
 void rva0007F0FB(CameraClass *,bool);
};

void Rva0007F0FBOwner::rva0007F0FB(CameraClass *source,bool clearOverride)
{
 DeviceLock guard;
  D3DXMATRIX inverse,projection;
 Vector4 transformedClipPlane;
 if (!_finite(source->Get_Transform().Row[0][0]))return;
 *camera=*source;
 Matrix4 old(source->Get_Transform());
 Vector3 waterNormal(0,0,1);
 Vector4 WaterPlane(waterNormal.X,waterNormal.Y,waterNormal.Z,*(float*)((char*)finalSetting((Overridable*)TheWaterTransparency.ptr)+0x4c));
 Vector3 reflectedRight,rUp,rN,rPos;

 Matrix4 full(old.m[0][0],old.m[1][0],old.m[2][0],old.m[3][0],
  old.m[0][1],old.m[1][1],old.m[2][1],old.m[3][1],
  old.m[0][2],old.m[1][2],old.m[2][2],old.m[3][2],
  old.m[0][3],old.m[1][3],old.m[2][3],old.m[3][3]);
 float axis_distance=Vector3::Dot_Product((Vector3&)full.m[0],waterNormal);
 reflectedRight=(Vector3&)full.m[0]-(2.0f*axis_distance*waterNormal);
 axis_distance=Vector3::Dot_Product((Vector3&)full.m[1],waterNormal);
 rUp=(Vector3&)full.m[1]-(2.0f*axis_distance*waterNormal);
 axis_distance=Vector3::Dot_Product((Vector3&)full.m[2],waterNormal);
 rN=(Vector3&)full.m[2]-(2.0f*axis_distance*waterNormal);
 axis_distance=Vector3::Dot_Product((Vector3&)full.m[3],waterNormal);
 axis_distance-=WaterPlane.W;
 rPos=(Vector3&)full.m[3]-(2.0f*axis_distance*waterNormal);
 Matrix3D reflected;
 matrixSet(reflected,reflectedRight,-rUp,rN,rPos);
 camera->Set_Transform(reflected);
 {Vector2 minimum,maximum;
 maximum.X=maximum.Y=1.0f;
 minimum.X=minimum.Y=0.0f;
 camera->Set_Viewport(minimum,maximum);}
 camera->Apply();
 DX8Wrapper::Apply_Render_State_Changes();
 if(DX8Wrapper::render_state_changed&0x80000) {
  inverse.m[0][0]=1.0f; inverse.m[0][1]=0.0f; inverse.m[0][2]=0.0f; inverse.m[0][3]=0.0f;
  inverse.m[1][0]=0.0f; inverse.m[1][1]=1.0f; inverse.m[1][2]=0.0f; inverse.m[1][3]=0.0f;
  inverse.m[2][0]=0.0f; inverse.m[2][1]=0.0f; inverse.m[2][2]=1.0f; inverse.m[2][3]=0.0f;
  inverse.m[3][0]=0.0f; inverse.m[3][1]=0.0f; inverse.m[3][2]=0.0f; inverse.m[3][3]=1.0f;
 } else {
  inverse.m[0][0]=DX8Wrapper::render_state.view.m[0][0]; inverse.m[0][1]=DX8Wrapper::render_state.view.m[1][0]; inverse.m[0][2]=DX8Wrapper::render_state.view.m[2][0]; inverse.m[0][3]=DX8Wrapper::render_state.view.m[3][0];
  inverse.m[1][0]=DX8Wrapper::render_state.view.m[0][1]; inverse.m[1][1]=DX8Wrapper::render_state.view.m[1][1]; inverse.m[1][2]=DX8Wrapper::render_state.view.m[2][1]; inverse.m[1][3]=DX8Wrapper::render_state.view.m[3][1];
  inverse.m[2][0]=DX8Wrapper::render_state.view.m[0][2]; inverse.m[2][1]=DX8Wrapper::render_state.view.m[1][2]; inverse.m[2][2]=DX8Wrapper::render_state.view.m[2][2]; inverse.m[2][3]=DX8Wrapper::render_state.view.m[3][2];
  inverse.m[3][0]=DX8Wrapper::render_state.view.m[0][3]; inverse.m[3][1]=DX8Wrapper::render_state.view.m[1][3]; inverse.m[3][2]=DX8Wrapper::render_state.view.m[2][3]; inverse.m[3][3]=DX8Wrapper::render_state.view.m[3][3];
 }
 D3DXMatrixInverse(&inverse,0,&inverse);
 Vector4 plane(WaterPlane.X,WaterPlane.Y,WaterPlane.Z,-WaterPlane.W);
 rva0062AF4AD3DXVec4Transform(&transformedClipPlane,&plane,&inverse);
 projection.m[0][0]=DX8Wrapper::DeviceProjectionMatrix.m[0][0]; projection.m[0][1]=DX8Wrapper::DeviceProjectionMatrix.m[1][0]; projection.m[0][2]=DX8Wrapper::DeviceProjectionMatrix.m[2][0]; projection.m[0][3]=DX8Wrapper::DeviceProjectionMatrix.m[3][0];
 projection.m[1][0]=DX8Wrapper::DeviceProjectionMatrix.m[0][1]; projection.m[1][1]=DX8Wrapper::DeviceProjectionMatrix.m[1][1]; projection.m[1][2]=DX8Wrapper::DeviceProjectionMatrix.m[2][1]; projection.m[1][3]=DX8Wrapper::DeviceProjectionMatrix.m[3][1];
 projection.m[2][0]=DX8Wrapper::DeviceProjectionMatrix.m[0][2]; projection.m[2][1]=DX8Wrapper::DeviceProjectionMatrix.m[1][2]; projection.m[2][2]=DX8Wrapper::DeviceProjectionMatrix.m[2][2]; projection.m[2][3]=DX8Wrapper::DeviceProjectionMatrix.m[3][2];
 projection.m[3][0]=DX8Wrapper::DeviceProjectionMatrix.m[0][3]; projection.m[3][1]=DX8Wrapper::DeviceProjectionMatrix.m[1][3]; projection.m[3][2]=DX8Wrapper::DeviceProjectionMatrix.m[2][3]; projection.m[3][3]=DX8Wrapper::DeviceProjectionMatrix.m[3][3];
 D3DXMatrixTranspose(&projection,&projection);
 Vector4 projectionCorner;
 projectionCorner.X=((transformedClipPlane.X>0.0f ? 1.0f : (transformedClipPlane.X<0.0f ? -1.0f : 0.0f))-projection.m[2][0])/projection.m[0][0];
 projectionCorner.Y=((transformedClipPlane.Y>0.0f ? 1.0f : (transformedClipPlane.Y<0.0f ? -1.0f : 0.0f))-projection.m[2][1])/projection.m[1][1];
 projectionCorner.Z=1.0f;
 projectionCorner.W=(1.0f-projection.m[2][2])/projection.m[3][2];
 Vector4 scaledClipPlane=transformedClipPlane*(1.0f/(transformedClipPlane.X*projectionCorner.X+transformedClipPlane.Y*projectionCorner.Y+transformedClipPlane.Z*projectionCorner.Z+transformedClipPlane.W*projectionCorner.W));
 projection.m[0][2]=scaledClipPlane.X;
 projection.m[1][2]=scaledClipPlane.Y;
 projection.m[2][2]=scaledClipPlane.Z;
 projection.m[3][2]=scaledClipPlane.W;
 camera->Set_Reflected_Projection_Matrix(*((Matrix4*)&projection));
 if(DX8Wrapper::RenderStates[152]!=0) {
  if(WW3D::SnapshotActivated) {
   StringClass value(0,true);
   DX8Wrapper::Get_DX8_Render_State_Value_Name(value,152,0);
  }
  DX8Wrapper::RenderStates[152]=0;
  typedef long (__stdcall *SetRenderState)(IDirect3DDevice8*,unsigned long,unsigned long);
  ((SetRenderState*)*(void**)DX8Wrapper::D3DDevice)[0xe4/4](DX8Wrapper::D3DDevice,152,0);
  ++number_of_DX8_calls;
  ++DX8Wrapper::render_state_changes;
 }
 bfmeCameraProjectionOverride=true;
 camera->Apply();
 if(clearOverride)bfmeCameraProjectionOverride=false;
}
