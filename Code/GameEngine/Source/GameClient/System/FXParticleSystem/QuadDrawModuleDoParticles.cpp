// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code /ICode/Libraries/Include/Lib /Ireference/shims /Ireference/shims/bfme_vp_math /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?doParticles@QuadDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z
// retail 0x005601D9..0x00560A1B (2114 bytes EH thiscall RET 0xC).
//
// Identity (target): slot 4 of the QuadDrawModule vtable (shared signature
// with the matched StreakDrawModule::doParticles 0x0055FD6B); WorldBuilder
// twin 0x01422720 has the same calls, constants and the 512-particle cap.
// Body: nothing while WW3D::IsCurrentlyRenderingShadowMap. The view matrix
// comes from DX8Wrapper::Get_Transform(D3DTS_VIEW) (BFME 2 shape, WB
// 0x009C1560 / matched copy 0x000768FE: dead WORLD/PROJECTION arms folded by
// the constant). Live particles (0x001F4E2D) within the culling box grown by
// their size (0x001F4D2D) get a +-size quad in the XZ plane, rotated about
// the particle's axis kind (0x001F4DE6: Z/X/Y by D3DX or an arbitrary axis
// with Y negated), translated to the position, transformed by the view and
// appended (at most 512) to the position/colour share buffers g_00E065C8 /
// g_00E065CC (colour 0x001F4E1B or black, alpha 0x001F4DF9). With any
// particle the system texture (rowed TextureAsset::Get) and the shader
// picked by its type (AdditiveSprite default; type 2 is
// BfmeParticleType2ShaderBits from StreakDrawModuleDoParticles; HardwareFog
// with DX8Wrapper::FogEnable) go to the quad renderer g_00E0623C, which
// receives the buffers and renders (0x00177F82). Returns the count.
// Shape notes (target): WB's debug body initialises the four corners by
// direct member stores (no inline Set parameter temps, unlike the
// black-colour arm) and adds the translation through Vector4::operator+=;
// both keep retail's float operand order under the plain ZH Matrix4x4 *
// Vector4. Matrix types: pristine ZH WWMath at donor
// a18d9ed50607e9175de4d6568798d7d73119de09 (donor fact); the
// RenderStateStruct view matrix at +0x22C (0x009EE804) is target evidence.
#include "ascii_string.h"
class RenderInfoClass;
class RefCountClass;
// Keep the native inline Vector4 constructor while using its existing external owner.
#include <vector4.h>
#include "vector3.h"
#include "../../../../../Libraries/Source/WWVegas/WWMath/Matrix4Data.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/RenderStateStruct.h"
// Zero Hour matrix4.h's Matrix4x4 * Vector4, which the canonical Matrix4 does not declare.
__forceinline Vector4 operator * (const Matrix4 & a, const Vector4 & v) {
	return Vector4(
		a[0][0] * v[0] + a[0][1] * v[1] + a[0][2] * v[2] + a[0][3] * v[3],
		a[1][0] * v[0] + a[1][1] * v[1] + a[1][2] * v[2] + a[1][3] * v[3],
		a[2][0] * v[0] + a[2][1] * v[1] + a[2][2] * v[2] + a[2][3] * v[3],
		a[3][0] * v[0] + a[3][1] * v[1] + a[3][2] * v[2] + a[3][3] * v[3]
	);
}
class Rva0007671F:public Matrix4 {public:Rva0007671F();};
struct D3DXMATRIX {float m[4][4];};
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationZ(D3DXMATRIX*,float);
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationX(D3DXMATRIX*,float);
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationY(D3DXMATRIX*,float);
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationAxis(D3DXMATRIX*,const Vector3*,float);
template<class T>class ShareBufferClass {public:T*Get_Array(){return Array;}private:char pad[12];T*Array;};
extern ShareBufferClass<Vector3>*g_00E065C8;
extern ShareBufferClass<Vector4>*g_00E065CC;
#include "../../../../../Libraries/Source/WWVegas/WW3D2/ShaderClass.h"
extern unsigned int BfmeParticleType2ShaderBits;
class TextureClass {public:void Release_Ref();};
class BFME2ParticleTextureHandle {public:~BFME2ParticleTextureHandle(){if(Ptr)Ptr->Release_Ref();}TextureClass*Ptr;};
#include "../../../../../GameEngineDevice/Include/W3DDevice/GameClient/TextureAsset.h"
template<class T>class RefCountPtr {public:const RefCountPtr&operator=(const RefCountPtr&);T*Ptr;};
class Rva0090F8C0Holder {public:void set(int,RefCountClass*,RefCountClass*,RefCountClass*,RefCountClass*);};
class Rva00177860 {public:void Render(RenderInfoClass&);void*refs[4];int count;RefCountPtr<TextureClass> texture;unsigned shader;float tail[4];};
extern Rva00177860*g_00E0623C;
enum D3DTRANSFORMSTATETYPE {D3DTS_VIEW=2,D3DTS_PROJECTION=3,D3DTS_WORLD=256,D3DTS_FORCE_DWORD=0x7fffffff};
class DX8Wrapper {public:enum {WORLD_IDENTITY=1<<18,VIEW_IDENTITY=1<<19};static bool Get_Fog_Enable(){return FogEnable;}
 // BFME 2 DX8Wrapper::Get_Transform (WB 0x009C1560)
 static __forceinline void Get_Transform(D3DTRANSFORMSTATETYPE transform, Matrix4x4& matrix4x4)
{
	switch ((int)transform) {
	case D3DTS_WORLD:
		if (render_state_changed&WORLD_IDENTITY) matrix4x4.Make_Identity();
		else matrix4x4=render_state.world.Transpose();
		break;
	case D3DTS_VIEW:
		if (render_state_changed&VIEW_IDENTITY) matrix4x4.Make_Identity();
		else matrix4x4=render_state.view.Transpose();
		break;
	case D3DTS_PROJECTION:
		matrix4x4=DeviceProjectionMatrix.Transpose();
		break;
	default:
		matrix4x4.Make_Identity();
		break;
	}
}
protected:static bool FogEnable;static unsigned render_state_changed;static RenderStateStruct render_state;static Matrix4 DeviceProjectionMatrix;};
namespace FXParticleSystem {class QuadDrawModule;}
#include "../../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"
class Rva001F4E2D {public:bool rva001F4E2D();};
class Rva001F4D2D {public:float rva001F4D2D();};
#include "../../../../Include/GameClient/Rva001F4DC4.h"
class Rva001F4DE6 {public:int rva001F4DE6();};
#include "RGBColor.h"
#include "../../../../Include/GameClient/Rva001F4E1BSlot.h"
class Rva001F4DF9 {public:float rva001F4DF9();};
struct QuadParticle {char prefix[16];Vector3 axis;Vector3 position;char gap[0x3c];QuadParticle*next;};
class QuadParticleStorage {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual QuadParticle*getFirstParticle();};
#include "../../../../Include/GameClient/Rva0004CABDSevenEight.h"
#include "../../../../Include/GameClient/ParticleSystemClass.h"
struct QuadBox {Vector3 center,extent;};
__forceinline float quadFabs(float x){unsigned n=*(unsigned*)&x;n&=0x7fffffff;return *(float*)&n;}
namespace FXParticleSystem {
class QuadDrawModule {public:virtual int doParticles(RenderInfoClass&,void*,int*);private: ::ParticleSystem*system;__forceinline ::ParticleSystem*getSystem(){return system?system:Make001FCBD7();}};
int QuadDrawModule::doParticles(RenderInfoClass&rinfo,void*bounds,int*particleCount){
 if(WW3D::IsCurrentlyRenderingShadowMap)return 0;
 int count=0;Vector3*positions=g_00E065C8->Get_Array();Vector4*colors=g_00E065CC->Get_Array();
 const QuadBox*box=(const QuadBox*)bounds;
 float cx=box->center.X,cy=box->center.Y,cz=box->center.Z;
 float ex=box->extent.X,ey=box->extent.Y,ez=box->extent.Z;
 Rva0007671F view;Rva0007671F rotation;
 DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
 QuadParticle*quadParticle=0;if(!((unsigned char)((Rva0004CABDSevenEight*)getSystem())->get()))
 quadParticle=((QuadParticleStorage*)getSystem()->m_A4)->getFirstParticle();{
 for(;quadParticle;quadParticle=quadParticle->next){
  if(((Rva001F4E2D*)quadParticle)->rva001F4E2D())continue;
  const Vector3*pos=&quadParticle->position;float size=((Rva001F4D2D*)quadParticle)->rva001F4D2D();float angle=((Rva001F4DC4*)quadParticle)->rva001F4DC4();
  if(quadFabs(pos->X-cx)>ex+size)continue;
  if(quadFabs(pos->Y-cy)>ey+size)continue;
  if(quadFabs(pos->Z-cz)>ez+size)continue;
  Vector4 vertices[4];vertices[0].X=-size;vertices[0].Y=0;vertices[0].Z=size;vertices[0].W=1;vertices[1].X=size;vertices[1].Y=0;vertices[1].Z=size;vertices[1].W=1;vertices[2].X=-size;vertices[2].Y=0;vertices[2].Z=-size;vertices[2].W=1;vertices[3].X=size;vertices[3].Y=0;vertices[3].Z=-size;vertices[3].W=1;
  int axis=((Rva001F4DE6*)quadParticle)->rva001F4DE6();
  if(axis==4)D3DXMatrixRotationZ((D3DXMATRIX*)&rotation,angle);
  else if(axis==2)D3DXMatrixRotationX((D3DXMATRIX*)&rotation,angle);
  else if(axis==3)D3DXMatrixRotationY((D3DXMATRIX*)&rotation,angle);
  else if(axis==5){Vector3 axisv(quadParticle->axis.X,-quadParticle->axis.Y,quadParticle->axis.Z);D3DXMatrixRotationAxis((D3DXMATRIX*)&rotation,&axisv,angle);}
  else rotation.Make_Identity();
  for(int i=0;i<4;++i)vertices[i]=rotation*vertices[i];
  Vector4 translation(pos->X,pos->Y,pos->Z,0);int start=count*4;
  for(int j=0;j<4;++j){vertices[j]+=translation;
   Vector4 out;out=view*vertices[j];positions[start+j].X=out[0];positions[start+j].Y=out[1];positions[start+j].Z=out[2];
  }
  const RGBColor*color=((Rva001F4E1BSlot*)quadParticle)->get();float alpha=((Rva001F4DF9*)quadParticle)->rva001F4DF9();
  if(color){for(int k=0;k<4;++k){colors[start+k].X=color->red;colors[start+k].Y=color->green;colors[start+k].Z=color->blue;colors[start+k].W=alpha;}}else{for(int k=0;k<4;++k)colors[start+k].Set(0,0,0,alpha);}
  if(++count==512)break;
 }
 }
 if(count>0){BFME2ParticleTextureHandle texture=TextureAsset::Get(getSystem()->m_particleTypeName.str(),0,0);
  if(g_00E0623C){RefCountPtr<TextureClass>&slot=g_00E0623C->texture;slot=*(RefCountPtr<TextureClass>*)&texture;
   ShaderClass shader=ShaderClass::_PresetAdditiveSpriteShader;
   switch((int)getSystem()->m_shaderType){case 2:shader=*reinterpret_cast<const ShaderClass*>(&BfmeParticleType2ShaderBits);break;case 3:shader=ShaderClass::_PresetAlphaSpriteShader;break;case 4:shader=ShaderClass::_PresetATestSpriteShader;break;case 5:shader=ShaderClass::_PresetMultiplicativeSpriteShader;break;case 6:shader=ShaderClass::_PresetAdditive2DShader;break;case 7:shader=ShaderClass::_PresetAlpha2DShader;break;}
   if(DX8Wrapper::Get_Fog_Enable())shader.Enable_Fog("HardwareFog");g_00E0623C->shader=shader.ShaderBits;
   ((Rva0090F8C0Holder*)g_00E0623C)->set(count,(RefCountClass*)g_00E065C8,(RefCountClass*)g_00E065CC,0,0);g_00E0623C->Render(rinfo);
  }
 }
 return count;
}
}
