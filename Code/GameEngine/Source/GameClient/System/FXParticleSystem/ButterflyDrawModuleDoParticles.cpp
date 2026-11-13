// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep -ICode/Libraries/Source/WWVegas/WW3D2
// ?doParticles@ButterflyDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z
// retail 0x00560B11..0x00561375 (2148 bytes, RET 0xC): two wing quads per particle.
//
// Identity (target): slot 4 of the module vtable at 0x00C1C404, directly
// followed by the "ButterflyDrawModule" name string; WorldBuilder twin
// 0x01424D50 (FXParticleSystem::ButterflyDrawModule::doParticles, asserts in
// fxpsbutterflydrawmodule.cpp). Same signature and texture/shader tail as the
// matched StreakDrawModule::doParticles 0x0055FD6B. Five 64-byte matrix
// lifetimes precede the loop; the conditional rotation owns a sixth.
// WWMath, Vector4 and Matrix4 inlines follow the ZH donor headers
// (reference/open-bfme-1, GeneralsMD WWMath); DX8Wrapper::Get_Transform follows
// reference/shims/bfme2_get_transform/dx8wrapper.h. Handoff:
// reverse/attempt_support/0x00560b11-20261019.md.
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ascii_string.h"
#include <math.h>
float Rva001333F0Atan2(float y, float x);
#include "../../../../../Libraries/Source/WWVegas/WWMath/WWMathClass.h"
// ----------------------------------------------------------------------------
// Cos
// ----------------------------------------------------------------------------
__forceinline float WWMath::Cos(float val)
{
	float retval;
	__asm {
		fld [val]
		fcos
		fstp [retval]
	}
	return retval;
}
// ----------------------------------------------------------------------------
// Sin
// ----------------------------------------------------------------------------
__forceinline float WWMath::Sin(float val)
{
	float retval;
	__asm {
		fld [val]
		fsin
		fstp [retval]
	}
	return retval;
}

namespace FXParticleSystem {class ButterflyDrawModule;}
class RenderInfoClass;
class RefCountClass;
#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"
#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"
#include "../../../../../Libraries/Source/WWVegas/WWMath/Matrix4Data.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/RenderStateStruct.h"
/*
** Multiply a Matrix4x4 by a Vector4
*/
__forceinline Vector4 operator * (const Matrix4 & a, const Vector4 & v) {
	return Vector4(
		a[0][0] * v[0] + a[0][1] * v[1] + a[0][2] * v[2] + a[0][3] * v[3],
		a[1][0] * v[0] + a[1][1] * v[1] + a[1][2] * v[2] + a[1][3] * v[3],
		a[2][0] * v[0] + a[2][1] * v[1] + a[2][2] * v[2] + a[2][3] * v[3],
		a[3][0] * v[0] + a[3][1] * v[1] + a[3][2] * v[2] + a[3][3] * v[3]
	);
}

#include "../../../../Include/GameClient/Rva0007671F.h"
struct D3DXMATRIX {float m[4][4];};
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationZ(D3DXMATRIX*,float);
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationX(D3DXMATRIX*,float);
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationY(D3DXMATRIX*,float);
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationAxis(D3DXMATRIX*,const Vector3*,float);
template<class T>class ShareBufferClass {public:T*Get_Array(){return Array;}private:char pad[12];T*Array;};
extern ShareBufferClass<Vector3>*g_00E065C8;
extern ShareBufferClass<Vector4>*g_00E065CC;
#include "../../../../../Libraries/Source/WWVegas/WW3D2/ShaderClass.h"
// Use the existing four-byte particle shader storage owner.
extern unsigned int BfmeParticleType2ShaderBits;
// The existing world cache owns the complete matrix at RVA 009EE7C4.
class TextureClass {public:void Release_Ref();};
class BFME2ParticleTextureHandle {public:~BFME2ParticleTextureHandle(){if(Ptr)Ptr->Release_Ref();}TextureClass*Ptr;};
#include "../../../../../GameEngineDevice/Include/W3DDevice/GameClient/TextureAsset.h"
template<class T>class RefCountPtr {public:const RefCountPtr&operator=(const RefCountPtr&);T*Ptr;};
#include "../../../../../Libraries/Source/WWVegas/WW3D2/Rva0090F8C0Holder.h"
class Rva00177860 {public:void Render(RenderInfoClass&);void*refs[4];int count;RefCountPtr<TextureClass> texture;unsigned shader;float tail[4];};
extern Rva00177860*g_00E06254;
class DX8Wrapper {
protected:
	static RenderStateStruct render_state;
private:
friend class FXParticleSystem::ButterflyDrawModule;protected:static unsigned render_state_changed;static Matrix4 DeviceProjectionMatrix;static bool FogEnable;public:static __forceinline void Get_Transform(int t,Matrix4&m){switch((int)t){case 0x100:if(render_state_changed&0x40000)m.Make_Identity();else m=DX8Wrapper::render_state.world.Transpose();break;case 2:if(render_state_changed&0x80000)m.Make_Identity();else m=DX8Wrapper::render_state.view.Transpose();break;case 3:m=DeviceProjectionMatrix.Transpose();break;default:m.Make_Identity();break;}}};
#include "../../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"
#include "../../../../Include/GameClient/Rva001F4E2D.h"
#include "../../../../Include/GameClient/Rva001F4D2D.h"
#include "../../../../Include/GameClient/Rva001F4DC4.h"
#include "../../../../../Libraries/Include/Lib/RGBColor.h"
#include "../../../../Include/GameClient/Rva001F4E1BSlot.h"
#include "../../../../Include/GameClient/Rva001F4DF9.h"
struct ButterflyParticle {char prefix[16];Vector3 axis;Vector3 position;char gap[0x3c];ButterflyParticle*next;};
class ButterflyParticleStorage {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual ButterflyParticle*getFirstParticle();};
#include "../../../../Include/GameClient/Rva0004CABDSevenEight.h"
#include "../../../../Include/GameClient/ParticleSystemClass.h"
struct ButterflyBox {Vector3 center,extent;};
__forceinline float quadFabs(float x){unsigned n=*(unsigned*)&x;n&=0x7fffffff;return *(float*)&n;}
namespace FXParticleSystem {
class ButterflyDrawModule {public:virtual int doParticles(RenderInfoClass&,void*,int*);private: ::ParticleSystem*system;__forceinline ::ParticleSystem*getSystem(){return system?system:Make001FCBD7();}};
int ButterflyDrawModule::doParticles(RenderInfoClass&rinfo,void*bounds,int*particleCount){
 if(WW3D::IsCurrentlyRenderingShadowMap)return 0;
 int count=0;Vector3*positions=g_00E065C8->Get_Array();Vector4*colors=g_00E065CC->Get_Array();
 Vector4 transformed;
 const ButterflyBox*box=(const ButterflyBox*)bounds;
 float cx=box->center.X,cy=box->center.Y,cz=box->center.Z;
 float ex=box->extent.X,ey=box->extent.Y,ez=box->extent.Z;
 Rva0007671F view;Rva0007671F matrixB,matrixC,matrixD,matrixA;  // slot order follows the names (hash), not declaration order
 DX8Wrapper::Get_Transform(2,view);
 if(!((unsigned char)((Rva0004CABDSevenEight*)getSystem())->get())){
 ButterflyParticle*butterflyParticle=((ButterflyParticleStorage*)getSystem()->m_A4)->getFirstParticle();
 for(;butterflyParticle;butterflyParticle=butterflyParticle->next){
  if(((Rva001F4E2D*)butterflyParticle)->rva001F4E2D())continue;
  const Vector3*pos=&butterflyParticle->position;float size=((Rva001F4D2D*)butterflyParticle)->rva001F4D2D();float angle=((Rva001F4DC4*)butterflyParticle)->rva001F4DC4();
  if(quadFabs(pos->X-cx)>ex+size)continue;
  if(quadFabs(pos->Y-cy)>ey+size)continue;
  if(quadFabs(pos->Z-cz)>ez+size)continue;
  float wingHeight=WWMath::Cos(angle)*size*2.0f;
  float low=0.0f-size;
  if(wingHeight<low)wingHeight=low;
  float wingWidth=WWMath::Sin(angle)*size*2.0f;
  float negWing=0.0f-wingWidth;
  Vector4 vertices[8];
  vertices[0]=Vector4(0,size,0,1);vertices[1]=Vector4(wingWidth,size,wingHeight,1);
  vertices[2]=Vector4(0,low,0,1);vertices[3]=Vector4(wingWidth,low,wingHeight,1);
  vertices[4]=Vector4(0,size,0,1);vertices[5]=Vector4(negWing,size,wingHeight,1);
  vertices[6]=Vector4(0,low,0,1);vertices[7]=Vector4(negWing,low,wingHeight,1);
  if(fabs(butterflyParticle->axis.X)>0.0001f){
   Rva0007671F rotation;
   float facing=(float)(Rva001333F0Atan2(0.0f-butterflyParticle->axis.Y,butterflyParticle->axis.X)-1.5707963267948966);
   D3DXMatrixRotationZ((D3DXMATRIX*)&rotation,facing);
   for(int i=0;i<8;++i){transformed=rotation*vertices[i];vertices[i]=transformed;}
  }
  Vector4 translation(pos->X,pos->Y,pos->Z,0.0f);int start=count*4;
  for(int j=0;j<8;++j){vertices[j]+=translation;transformed=view*vertices[j];
   positions[start+j].X=transformed.X;positions[start+j].Y=transformed.Y;positions[start+j].Z=transformed.Z;
  }
  const RGBColor*color=((Rva001F4E1BSlot*)butterflyParticle)->get();float alpha=((Rva001F4DF9*)butterflyParticle)->rva001F4DF9();
  if(color){for(int k=0;k<8;++k){colors[start+k].X=color->red;colors[start+k].Y=color->green;colors[start+k].Z=color->blue;colors[start+k].W=alpha;}}else{for(int k=0;k<8;++k)colors[start+k].Set(0,0,0,alpha);}
  count+=2;if(count>=512)break;
 }
 }
 if(count>0){BFME2ParticleTextureHandle texture=TextureAsset::Get(getSystem()->m_particleTypeName.str(),0,0);
  if(g_00E06254){RefCountPtr<TextureClass>&dst=g_00E06254->texture;dst=*(RefCountPtr<TextureClass>*)&texture;
   ShaderClass shader=ShaderClass::_PresetAdditiveSpriteShader;
   switch((int)getSystem()->m_shaderType){case 2:shader=*reinterpret_cast<const ShaderClass *>(&BfmeParticleType2ShaderBits);break;case 3:shader=ShaderClass::_PresetAlphaSpriteShader;break;case 4:shader=ShaderClass::_PresetATestSpriteShader;break;case 5:shader=ShaderClass::_PresetMultiplicativeSpriteShader;break;case 6:shader=ShaderClass::_PresetAdditive2DShader;break;case 7:shader=ShaderClass::_PresetAlpha2DShader;break;}
   if(DX8Wrapper::FogEnable)shader.Enable_Fog("HardwareFog");g_00E06254->shader=shader.ShaderBits;
   ((Rva0090F8C0Holder*)g_00E06254)->set(count,(RefCountClass*)g_00E065C8,(RefCountClass*)g_00E065CC,0,0);g_00E06254->Render(rinfo);
  }
 }
 return count;
}
}

// Retail and donor evidence: reverse/attempt_support/0x00560b11-20261019.md.
