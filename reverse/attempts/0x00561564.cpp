// ?doParticles@LightningDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z
// partial score=0.7872030653 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?doParticles@LightningDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z
// partial score=0.7711756993006993 date=2026-10-10
// cl: /ICode/Libraries/Include/Lib /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ob2
#include "Coord3D.h"

#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class RenderInfoClass;

class Vector3
{
public:
	Vector3();
 Real X, Y, Z;
};

class Vector4
{
public:
	Real X, Y, Z, W;
};

struct RGBColor
{
	Real red, green, blue;
};

template <class T> class ShareBufferClass
{
public:
	T *Get_Array(void) { return Array; }
private:
	char m_pad00[0xc];
	T *Array; // +0x0C
};
extern ShareBufferClass<Vector3> *g_00E065C8;
extern ShareBufferClass<Vector4> *g_00E065CC;
extern ShareBufferClass<float> *g_00E065D0;
extern ShareBufferClass<unsigned char> *g_00E065D4;

class ShaderClass
{
public:
	ShaderClass(const ShaderClass &s) { ShaderBits = s.ShaderBits; }
	ShaderClass &operator=(const ShaderClass &s) { ShaderBits = s.ShaderBits; return *this; }
	void Enable_Fog(const char *source);

	static ShaderClass _PresetAdditive2DShader;
	static ShaderClass _PresetAlpha2DShader;
	static ShaderClass _PresetAdditiveSpriteShader;
	static ShaderClass _PresetAlphaSpriteShader;
	static ShaderClass _PresetATestSpriteShader;
	static ShaderClass _PresetMultiplicativeSpriteShader;
private:
	unsigned int ShaderBits;
};
extern ShaderClass g_00DB6250;

class TextureClass
{
public:
	void Release_Ref();
};

class BFME2ParticleTextureHandle
{
public:
	~BFME2ParticleTextureHandle()
	{
		if (Ptr)
			Ptr->Release_Ref();
	}
	TextureClass *Ptr;
};
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *name, int a, int b);

class StreakLineClass
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void Render(RenderInfoClass &rinfo); // slot 12 (+0x30)
	void Reset_Line(void);
	void Set_Texture(TextureClass *texture);
	void Set_Shader(ShaderClass shader);
 void Set_Texture_Tile_Factor(float);
	void Set_LocsWidthsColors(unsigned int num_points, Vector3 *locs, float *widths,
		Vector4 *colors, unsigned int *personalities);
};
extern StreakLineClass *g_00E0626C;

class DX8Wrapper
{
public:
	static bool Get_Fog_Enable(void) { return FogEnable; }
protected:
	static bool FogEnable;
};

namespace FXParticleSystem { class LightningDrawModule; }

class WW3D
{
	friend class FXParticleSystem::LightningDrawModule;
	static bool IsCurrentlyRenderingShadowMap;
};

class Rva001F4E2D { public: bool rva001F4E2D(); };
class Rva001F4D2D { public: float rva001F4D2D(); };
class Rva001F4E1BSlot { public: const RGBColor *get() const; };
class Rva001F4DF9 { public: float rva001F4DF9(); };
class Rva001F4DC4 { public: float rva001F4DC4(); };

struct StreakParticle
{
	char m_pad00[0x1c];
	Vector3 m_pos; // +0x1C
	char m_pad28[0x2c];
 unsigned seed;unsigned frame;
 char m_pad5c[8];
	StreakParticle *m_next; // +0x64
	char m_pad68[0x20];
	UnsignedInt m_id; // +0x88
};

class StreakParticleStorage
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual StreakParticle *getFirstParticle(); // slot 8 (+0x20)
};

class Rva0004CABDSevenEight
{
public:
	int get() const;
};

class ParticleSystem
{
public:
	char m_pad00[8];
	Int m_shaderType; // +0x08
	char m_pad0C[4];
	AsciiString m_textureName; // +0x10
	char m_pad14[0x90];
	StreakParticleStorage *m_storage; // +0xA4
};
extern ParticleSystem *Make001FCBD7(void);

struct StreakBox
{
	Vector3 m_center;
	Vector3 m_extent;
};

static inline float StreakFabs(float val)
{
	int value = *(int *)&val;
	value &= 0x7fffffff;
	return *(float *)&value;
}


class GameClientRandomVariable { public:float getValue()const; };
class WWMath { public:static float Random_Float(); };
class DefaultModuleHeadBase {public:virtual ~DefaultModuleHeadBase();protected: ::ParticleSystem* m_system;unsigned int storage[3];};
namespace FXParticleSystem {class Rva003AA228Slice {public:virtual void unusedVirtual();};class Rva003AA228:public DefaultModuleHeadBase,public Rva003AA228Slice {public:Rva003AA228(void*,void*);};}
class ParticleModule005F2CA0:public FXParticleSystem::Rva003AA228 {public:ParticleModule005F2CA0(void*,void*);virtual void moduleSlot();virtual void slot2();virtual void slot3();};
struct Rva00561C34RandomVariable {unsigned distribution;float minimum,maximum;};
namespace FXParticleSystem {
class LightningDrawModuleInfoBase {public:virtual ~LightningDrawModuleInfoBase();};
class LightningDrawModuleInfo:public LightningDrawModuleInfoBase {public:LightningDrawModuleInfo();virtual ~LightningDrawModuleInfo();virtual const char* GetSnapshotName();virtual void LoadPostProcess();virtual void DoXfer(class Xfer&);Rva00561C34RandomVariable a,b,c;float value;unsigned char flag;};
class ParticleSystem;template<class T>class TrackingPtr{};
class LightningDrawModuleTemplate {public:char pad[12];Rva00561C34RandomVariable a,b,c;float value;unsigned char flag;};
class LightningDrawModule:public ParticleModule005F2CA0,public LightningDrawModuleInfo {public:LightningDrawModule(TrackingPtr<ParticleSystem>&,const LightningDrawModuleTemplate*);virtual ~LightningDrawModule();virtual int doParticles(RenderInfoClass&,void*,int*);private: ::ParticleSystem* getSystem()const{return m_system?m_system:Make001FCBD7();}Vector3 pointsA[3][30];Vector3 pointsB[3][30];int count;struct Vec{float x,y,z;void Set(float a,float b,float c){x=a;y=b;z=c;}void normalize(){((Coord3D*)this)->normalize();}} axisA,axisB,axisC;int tail;};
LightningDrawModule::LightningDrawModule(TrackingPtr<ParticleSystem>& system,const LightningDrawModuleTemplate* source):ParticleModule005F2CA0(&system,(void*)source),LightningDrawModuleInfo(){
 a=source->a;b=source->b;c=source->c;value=source->value;flag=source->flag;
 count=1;axisA.Set(1,0,0);axisB.Set(0,1,0);axisC.Set(0,1,0);tail=0;
}
}

Vector3::Vector3() {}

int FXParticleSystem::LightningDrawModule::doParticles(RenderInfoClass& rinfo,void* bounds,int* particleCount) {
 if(WW3D::IsCurrentlyRenderingShadowMap)return 0;
 int n=0;
 Vector3* locs=g_00E065C8->Get_Array();
 float* widths=g_00E065D0->Get_Array();
 Vector4* colors=g_00E065CC->Get_Array();
 unsigned char* angles=g_00E065D4->Get_Array();
 bool refresh=false;unsigned savedSeed=1;unsigned ids[512];
 StreakParticle* p=0;
 if(!(unsigned char)((Rva0004CABDSevenEight*)getSystem())->get())p=getSystem()->m_storage->getFirstParticle();
 if(p){
  if(tail!=p->frame){tail=p->frame;refresh=true;savedSeed=p->seed;if(value>WWMath::Random_Float())count=2;else count=1;}
 for(;p;p=p->m_next) {
  float size=((Rva001F4D2D*)p)->rva001F4D2D();
  if(refresh)p->seed=savedSeed;
  ids[n]=p->m_id;
  locs[n].X=p->m_pos.X;locs[n].Y=p->m_pos.Y;locs[n].Z=p->m_pos.Z;
  widths[n]=size;
  const RGBColor* color=((Rva001F4E1BSlot*)p)->get();
  if(color){colors[n].X=color->red;colors[n].Y=color->green;colors[n].Z=color->blue;}
  else{colors[n].X=0;colors[n].Y=0;colors[n].Z=0;}
  colors[n].W=((Rva001F4DF9*)p)->rva001F4DF9();
  angles[n]=(unsigned char)(((Rva001F4DC4*)p)->rva001F4DC4()*255.0f/6.2831855f);
  n++;if(n==512)break;
 }
 }
 if(g_00E0626C && n>=2){
  BFME2ParticleTextureHandle texture=BFME2LoadParticleTexture(getSystem()->m_textureName.str(),0,0);
  if(refresh){
   axisA.Set(locs[n-1].X-locs[0].X,locs[n-1].Y-locs[0].Y,locs[n-1].Z-locs[0].Z);axisA.normalize();
   axisC.Set(0,0,1);
   axisB.x=axisC.y*axisA.z-axisA.y*axisC.z;
   axisB.y=axisA.x*axisC.z-axisC.x*axisA.z;
_ReadWriteBarrier();
   axisB.z=axisC.x*axisA.y-axisC.y*axisA.x;
   axisC.x=axisB.z*axisA.y-axisA.z*axisB.y;
   axisC.y=axisA.z*axisB.x-axisB.z*axisA.x;
   axisC.z=axisA.x*axisB.y-axisB.x*axisA.y;
   for(int j=0;j<count;j++)for(int i=0;i<n;i++){
    if(i!=0 && i!=n-1){
     float v0=((GameClientRandomVariable*)&a)->getValue();
     float v1=((GameClientRandomVariable*)&b)->getValue();
     float v2=((GameClientRandomVariable*)&c)->getValue();
     pointsB[j][i].X=v2*axisA.x+v0*axisB.x+v1*axisC.x;
     pointsB[j][i].Y=v2*axisA.y+v0*axisB.y+v1*axisC.y;
     pointsB[j][i].Z=v2*axisA.z+v0*axisB.z+v1*axisC.z;
     pointsA[j][i].X=locs[i].X+pointsB[j][i].X;
     pointsA[j][i].Y=locs[i].Y+pointsB[j][i].Y;
     pointsA[j][i].Z=locs[i].Z+pointsB[j][i].Z;
    }else{
     pointsB[j][i].X=pointsA[j][i].X=locs[i].X;
     pointsB[j][i].Y=pointsA[j][i].Y=locs[i].Y;
     pointsB[j][i].Z=pointsA[j][i].Z=locs[i].Z;
    }
   }
  }else{
   for(int j=0;j<count;j++)for(int i=0;i<n;i++){
    if(i!=0 && i!=n-1){
     pointsA[j][i].X=pointsB[j][i].X+locs[i].X;
     pointsA[j][i].Y=pointsB[j][i].Y+locs[i].Y;
     pointsA[j][i].Z=pointsB[j][i].Z+locs[i].Z;
    }else{
     pointsA[j][i].X=pointsB[j][i].X;
     pointsA[j][i].Y=pointsB[j][i].Y;
     pointsA[j][i].Z=pointsB[j][i].Z;
    }
   }
  }
  g_00E0626C->Set_Texture((TextureClass*)&texture);g_00E0626C->Reset_Line();
  ShaderClass shader=ShaderClass::_PresetAdditiveSpriteShader;
  switch(getSystem()->m_shaderType){
   case 2:shader=g_00DB6250;break;case 3:shader=ShaderClass::_PresetAlphaSpriteShader;break;
   case 4:shader=ShaderClass::_PresetATestSpriteShader;break;case 5:shader=ShaderClass::_PresetMultiplicativeSpriteShader;break;
   case 6:shader=ShaderClass::_PresetAdditive2DShader;break;case 7:shader=ShaderClass::_PresetAlpha2DShader;break;
  }
  if(DX8Wrapper::Get_Fog_Enable())shader.Enable_Fog("HardwareFog");g_00E0626C->Set_Shader(shader);
  for(int j=0;j<count;j++){
   g_00E0626C->Set_LocsWidthsColors(n,(Vector3*)&pointsA[j][0],g_00E065D0->Get_Array(),g_00E065CC->Get_Array(),ids);
   if(!flag)g_00E0626C->Set_Texture_Tile_Factor(1.0f/(n-1));else g_00E0626C->Set_Texture_Tile_Factor(1.0f);
   g_00E0626C->Render(rinfo);
  }
 }
 return n;
}
