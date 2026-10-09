// ?doParticles@ButterflyDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z
// partial score=0.669017 date=2026-10-09
// Native560B11..561375 Butterfly renderer complete2148B; two wing quads per particle.
// Purpose from WB1424D50 and exact Streak sibling. Five64B matrix default lifetimes
// precede the loop in retail; conditional rotation owns a sixth.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include <math.h>
class RenderInfoClass;
class RefCountClass;
class Vector3 {public:float X,Y,Z;Vector3(){}__forceinline Vector3(float x,float y,float z){X=x;Y=y;Z=z;}};
class Vector4 {public:float X,Y,Z,W;__forceinline void Set(float x,float y,float z,float w){X=x;Y=y;Z=z;W=w;}};
class Matrix4 {public:Vector4 Row[4];__forceinline void identity(){Row[0].Set(1,0,0,0);Row[1].Set(0,1,0,0);Row[2].Set(0,0,1,0);Row[3].Set(0,0,0,1);}__forceinline void transposeFrom(const Matrix4&m){Row[0].Set(m.Row[0].X,m.Row[1].X,m.Row[2].X,m.Row[3].X);Row[1].Set(m.Row[0].Y,m.Row[1].Y,m.Row[2].Y,m.Row[3].Y);Row[2].Set(m.Row[0].Z,m.Row[1].Z,m.Row[2].Z,m.Row[3].Z);Row[3].Set(m.Row[0].W,m.Row[1].W,m.Row[2].W,m.Row[3].W);}};
class Rva0007671F:public Matrix4 {public:Rva0007671F();};
struct D3DXMATRIX {float m[4][4];};
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationZ(D3DXMATRIX*,float);
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationX(D3DXMATRIX*,float);
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationY(D3DXMATRIX*,float);
extern "C" D3DXMATRIX*__stdcall D3DXMatrixRotationAxis(D3DXMATRIX*,const Vector3*,float);
template<class T>class ShareBufferClass {public:T*Get_Array(){return Array;}private:char pad[12];T*Array;};
extern ShareBufferClass<Vector3>*g_00E065C8;
extern ShareBufferClass<Vector4>*g_00E065CC;
class ShaderClass {public:unsigned ShaderBits;static ShaderClass _PresetAdditive2DShader,_PresetAlpha2DShader,_PresetAdditiveSpriteShader,_PresetAlphaSpriteShader,_PresetATestSpriteShader,_PresetMultiplicativeSpriteShader;void Enable_Fog(const char*);};
extern ShaderClass g_00DB6250;
class TextureClass {public:void Release_Ref();};
class BFME2ParticleTextureHandle {public:~BFME2ParticleTextureHandle(){if(Ptr)Ptr->Release_Ref();}TextureClass*Ptr;};
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char*,int,int);
template<class T>class RefCountPtr {public:const RefCountPtr&operator=(const RefCountPtr&);T*Ptr;};
class Rva0090F8C0Holder {public:void set(int,RefCountClass*,RefCountClass*,RefCountClass*,RefCountClass*);};
class Rva00177860 {public:void rva00177F82(RenderInfoClass&);void*refs[4];int count;RefCountPtr<TextureClass> texture;unsigned shader;float tail[4];};
extern Rva00177860*g_00E06254;
class DX8Wrapper {public:static unsigned render_state_changed;static Matrix4 render_state_view;static bool FogEnable;};
namespace FXParticleSystem {class ButterflyDrawModule;}
class WW3D {friend class FXParticleSystem::ButterflyDrawModule;static bool IsCurrentlyRenderingShadowMap;};
class Rva001F4E2D {public:bool rva001F4E2D();};
class Rva001F4D2D {public:float rva001F4D2D();};
class Rva001F4DC4 {public:float rva001F4DC4();};
class Rva001F4DE6 {public:int rva001F4DE6();};
struct RGBColor {float red,green,blue;};
class Rva001F4E1BSlot {public:const RGBColor*get()const;};
class Rva001F4DF9 {public:float rva001F4DF9();};
struct ButterflyParticle {char prefix[16];Vector3 axis;Vector3 position;char gap[0x3c];ButterflyParticle*next;};
class ButterflyParticleStorage {public:virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual ButterflyParticle*getFirstParticle();};
class Rva0004CABDSevenEight {public:int get()const;};
class ParticleSystem {public:char p0[8];int shader;char pC[4];AsciiString texture;char p14[0x90];ButterflyParticleStorage*storage;};
ParticleSystem*Make001FCBD7();
struct ButterflyBox {Vector3 center,extent;};
__forceinline float quadFabs(float x){unsigned n=*(unsigned*)&x;n&=0x7fffffff;return *(float*)&n;}
namespace FXParticleSystem {
class ButterflyDrawModule {public:virtual int doParticles(RenderInfoClass&,void*,int*);private:ParticleSystem*system;__forceinline ParticleSystem*getSystem(){return system?system:Make001FCBD7();}};
int ButterflyDrawModule::doParticles(RenderInfoClass&rinfo,void*bounds,int*particleCount){
 if(WW3D::IsCurrentlyRenderingShadowMap)return 0;
 int count=0;Vector3*positions=g_00E065C8->Get_Array();Vector4*colors=g_00E065CC->Get_Array();
 const ButterflyBox*box=(const ButterflyBox*)bounds;
 float cx=box->center.X,cy=box->center.Y,cz=box->center.Z;
 float ex=box->extent.X,ey=box->extent.Y,ez=box->extent.Z;
 Rva0007671F view;Rva0007671F matrixA,matrixB,matrixC,matrixD;
 if(DX8Wrapper::render_state_changed&0x80000)view.identity();else view.transposeFrom(DX8Wrapper::render_state_view);
 if(!((unsigned char)((Rva0004CABDSevenEight*)getSystem())->get())){
 ButterflyParticle*p=getSystem()->storage->getFirstParticle();
 for(;p;p=p->next){
  if(((Rva001F4E2D*)p)->rva001F4E2D())continue;
  const Vector3*pos=&p->position;float size=((Rva001F4D2D*)p)->rva001F4D2D();float angle=((Rva001F4DC4*)p)->rva001F4DC4();
  if(quadFabs(pos->X-cx)>ex+size)continue;
  if(quadFabs(pos->Y-cy)>ey+size)continue;
  if(quadFabs(pos->Z-cz)>ez+size)continue;
  float wingHeight=(float)cos(angle)*size*2.0f;
  float low=0.0f-size;
  if(wingHeight<low)wingHeight=low;
  float wingWidth=(float)sin(angle)*size*2.0f;
  float negWing=0.0f-wingWidth;
  Vector4 vertices[8];
  vertices[0].Set(0,size,0,1);vertices[1].Set(wingWidth,size,wingHeight,1);
  vertices[2].Set(0,low,0,1);vertices[3].Set(wingWidth,low,wingHeight,1);
  vertices[4].Set(0,size,0,1);vertices[5].Set(negWing,size,wingHeight,1);
  vertices[6].Set(0,low,0,1);vertices[7].Set(negWing,low,wingHeight,1);
  if(fabs(p->axis.X)>0.0001f){
   Rva0007671F rotation;
   float facing=(float)(atan2(0.0f-p->axis.Y,p->axis.X)-1.5707963267948966);
   D3DXMatrixRotationZ((D3DXMATRIX*)&rotation,facing);
   for(int i=0;i<8;++i){Vector4&v=vertices[i];
    float w=rotation.Row[3].X*v.X+rotation.Row[3].Y*v.Y+rotation.Row[3].Z*v.Z+rotation.Row[3].W*v.W;
    float z=rotation.Row[2].X*v.X+rotation.Row[2].Y*v.Y+rotation.Row[2].Z*v.Z+rotation.Row[2].W*v.W;
    float y=rotation.Row[1].X*v.X+rotation.Row[1].Y*v.Y+rotation.Row[1].Z*v.Z+rotation.Row[1].W*v.W;
    float x=rotation.Row[0].X*v.X+rotation.Row[0].Y*v.Y+rotation.Row[0].Z*v.Z+rotation.Row[0].W*v.W;
    v.Set(x,y,z,w);
   }
  }
  Vector3 translation(pos->X,pos->Y,pos->Z);int start=count*4;
  for(int j=0;j<8;++j){Vector4&v=vertices[j];v.X+=translation.X;v.Y+=translation.Y;v.Z+=translation.Z;
   float z=view.Row[3].X*v.X+view.Row[3].Y*v.Y+view.Row[3].Z*v.Z+view.Row[3].W*v.W;float zz=view.Row[2].X*v.X+view.Row[2].Z*v.Z+view.Row[2].Y*v.Y+view.Row[2].W*v.W;float y=view.Row[1].Z*v.Z+view.Row[1].X*v.X+view.Row[1].Y*v.Y+view.Row[1].W*v.W;float x=view.Row[0].Z*v.Z+view.Row[0].X*v.X+view.Row[0].W*v.W+view.Row[0].Y*v.Y;positions[start+j].X=x;positions[start+j].Y=y;positions[start+j].Z=zz;
  }
  const RGBColor*color=((Rva001F4E1BSlot*)p)->get();float alpha=((Rva001F4DF9*)p)->rva001F4DF9();
  if(color){for(int k=0;k<8;++k){*(RGBColor*)&colors[start+k]=*color;colors[start+k].W=alpha;}}else{for(int k=0;k<8;++k)colors[start+k].Set(0,0,0,alpha);}
  count+=2;if(count>=512)break;
 }
 }
 if(count>0){BFME2ParticleTextureHandle texture=BFME2LoadParticleTexture(getSystem()->texture.str(),0,0);
  if(g_00E06254){g_00E06254->texture=*(RefCountPtr<TextureClass>*)&texture;
   ShaderClass shader=ShaderClass::_PresetAdditiveSpriteShader;
   switch(getSystem()->shader){case 2:shader=g_00DB6250;break;case 3:shader=ShaderClass::_PresetAlphaSpriteShader;break;case 4:shader=ShaderClass::_PresetATestSpriteShader;break;case 5:shader=ShaderClass::_PresetMultiplicativeSpriteShader;break;case 6:shader=ShaderClass::_PresetAdditive2DShader;break;case 7:shader=ShaderClass::_PresetAlpha2DShader;break;}
   if(DX8Wrapper::FogEnable)shader.Enable_Fog("HardwareFog");g_00E06254->shader=shader.ShaderBits;
   ((Rva0090F8C0Holder*)g_00E06254)->set(count,(RefCountClass*)g_00E065C8,(RefCountClass*)g_00E065CC,0,0);g_00E06254->rva00177F82(rinfo);
  }
 }
 return count;
}
}
