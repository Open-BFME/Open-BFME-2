// ?doParticles@LightningDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z,
// retail 0x00561564..0x00561C33, 1744 bytes, RET 12, with its EH handler 0x00799BC1.
// The constructor 0x00561C34 lives in LightningDrawModuleConstructor.cpp with the
// same class view.
//
// Both cross products use one helper with the Zero Hour Coord3D::crossProduct body,
// parenthesised per component (WB 0x1429DF0 calls Coord3D::crossProduct(&C,&A,&B) then
// (&A,&B,&C); retail inlines both). The first call reaches axisC/axisA through a named
// copy of this. Mechanism (c2 13.10.3077, traced): FactCanonSort keys an IND leaf by
// the low byte of its base's hash, so each cross pick is decided by the CSE hash-var
// number X mod 4 of the address bases (a+4, a+8, b+4, b+8) and the named-local number
// F mod 8 of the inline params a/b. The parentheses add one round node per component
// (a cross body makes 33 hash vars, so cross 2 starts at cross 1 + 1 mod 4); the
// self-based arguments add the two hash vars that put cross 1 at X == 3 mod 4 while
// &axisB (the noise-loop base) keeps X == 0 mod 4. Named locals set F (cross 1 b == 6,
// cross 2 b == 1 mod 8). Evidence: reverse/attempt_support/fp-paren-nodes-20261020.md,
// reverse/attempt_support/doparticles561564_20261019/README.md.
// WB 1429DF0: the endpoint branch stores offset before out (WB 142a59d); the noise X
// sum accumulates v2*A.x, v0*B.x, v1*C.x in retail order (one expression reassociates).
// Primary clean donor: BFME1 LightningDrawModuleCtor005F4E90.cpp at 575ba2b04.
// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ob2
#include "Coord3D.h"
#include "ascii_string.h"
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class RenderInfoClass;

class Vector3
{
public:
	Vector3() {}
 Real X, Y, Z;
};

#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

#include "RGBColor.h"

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
	__declspec(dllimport) __forceinline ShaderClass(const ShaderClass &s) { ShaderBits = s.ShaderBits; }
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
extern unsigned int BfmeParticleType2ShaderBits;

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
class TextureAsset {public: static BFME2ParticleTextureHandle Get(const char *name, int a, int b);};

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

struct Rva00561C34Point:Coord3D { Rva00561C34Point(); };
class DefaultModuleHeadBase {public:virtual ~DefaultModuleHeadBase();protected: ::ParticleSystem *m_system;unsigned int storage[3];};
namespace FXParticleSystem {class Rva003AA228Slice {public:virtual void unusedVirtual();};class Rva003AA228:public DefaultModuleHeadBase,public Rva003AA228Slice {public:Rva003AA228(void*,void*);};}
class ParticleModule005F2CA0:public FXParticleSystem::Rva003AA228 {public:ParticleModule005F2CA0(void*,void*);virtual void moduleSlot();virtual void slot2();virtual void slot3();};
struct Rva00561C34RandomVariable {unsigned distribution;float minimum,maximum;};
class RenderInfoClass;
namespace FXParticleSystem {
class LightningDrawModuleInfoBase {public:virtual ~LightningDrawModuleInfoBase();};
class LightningDrawModuleInfo:public LightningDrawModuleInfoBase {public:LightningDrawModuleInfo();virtual ~LightningDrawModuleInfo();virtual const char* GetSnapshotName();virtual void LoadPostProcess();virtual void DoXfer(class Xfer&);Rva00561C34RandomVariable a,b,c;float value;unsigned char flag;};
class ParticleSystem;template<class T>class TrackingPtr{};
class LightningDrawModuleTemplate {public:char pad[12];Rva00561C34RandomVariable a,b,c;float value;unsigned char flag;};
class LightningDrawModule:public ParticleModule005F2CA0,public LightningDrawModuleInfo {public:LightningDrawModule(TrackingPtr<ParticleSystem>&,const LightningDrawModuleTemplate*);virtual ~LightningDrawModule();virtual int doParticles(::RenderInfoClass&,void*,int*); ::ParticleSystem* getSystem()const{return m_system?m_system:Make001FCBD7();}Rva00561C34Point pointsA[3][30];Rva00561C34Point pointsB[3][30];int count;struct Vec{float x,y,z;void Set(float a,float b,float c){x=a;y=b;z=c;}void normalize(){((Coord3D*)this)->normalize();}} axisA,axisB,axisC;int tail;};
}


static inline void Rva00561564AddP(const Vector3 *position,const Coord3D *b,Coord3D *resultPosition){
 resultPosition->x=position->X+b->x;
 resultPosition->y=position->Y+b->y;
 resultPosition->z=position->Z+b->z;
}
static inline void Rva00561564CrossProduct(const FXParticleSystem::LightningDrawModule::Vec *firstVector,const FXParticleSystem::LightningDrawModule::Vec *secondVector,FXParticleSystem::LightningDrawModule::Vec *crossResult){
 crossResult->x=(firstVector->y*secondVector->z-firstVector->z*secondVector->y);
 crossResult->y=(firstVector->z*secondVector->x-firstVector->x*secondVector->z);
 crossResult->z=(firstVector->x*secondVector->y-firstVector->y*secondVector->x);
}
int FXParticleSystem::LightningDrawModule::doParticles(RenderInfoClass& rinfo,void* bounds,int* particleCount) {
 if(WW3D::IsCurrentlyRenderingShadowMap)return 0;
 int numParticles=0;
 Vector3* locs=g_00E065C8->Get_Array();
 float* widths=g_00E065D0->Get_Array();
 Vector4* colors=g_00E065CC->Get_Array();
 unsigned char* angles=g_00E065D4->Get_Array();
 bool refresh=false;unsigned savedSeed=1;unsigned ids[512];
 StreakParticle* streakParticle=0;
 if(!(unsigned char)((Rva0004CABDSevenEight*)getSystem())->get())streakParticle=getSystem()->m_storage->getFirstParticle();
 if(streakParticle){
  if(tail!=streakParticle->frame){tail=streakParticle->frame;refresh=true;savedSeed=streakParticle->seed;if(value>WWMath::Random_Float())count=2;else count=1;}
 for(;streakParticle;streakParticle=streakParticle->m_next) {
  float size=((Rva001F4D2D*)streakParticle)->rva001F4D2D();
  if(refresh)streakParticle->seed=savedSeed;
  ids[numParticles]=streakParticle->m_id;
  locs[numParticles].X=streakParticle->m_pos.X;locs[numParticles].Y=streakParticle->m_pos.Y;locs[numParticles].Z=streakParticle->m_pos.Z;
  widths[numParticles]=size;
  const RGBColor* color=((Rva001F4E1BSlot*)streakParticle)->get();
  if(color){colors[numParticles].X=color->red;colors[numParticles].Y=color->green;colors[numParticles].Z=color->blue;}
  else{colors[numParticles].X=0;colors[numParticles].Y=0;colors[numParticles].Z=0;}
  colors[numParticles].W=((Rva001F4DF9*)streakParticle)->rva001F4DF9();
  angles[numParticles]=(unsigned char)(((Rva001F4DC4*)streakParticle)->rva001F4DC4()*255.0f/6.2831855f);
  numParticles++;if(numParticles==512)break;
 }
 }
 if(g_00E0626C && numParticles>=2){
  BFME2ParticleTextureHandle texture=TextureAsset::Get(getSystem()->m_textureName.str(),0,0);
  if(refresh){
   axisA.Set(locs[numParticles-1].X-locs[0].X,locs[numParticles-1].Y-locs[0].Y,locs[numParticles-1].Z-locs[0].Z);axisA.normalize();
   axisC.x=0;axisC.y=0;axisC.z=1;
   LightningDrawModule *self=this;
   Rva00561564CrossProduct(&self->axisC,&self->axisA,&axisB);
   Rva00561564CrossProduct(&axisA,&axisB,&axisC);
   for(int j=0;j<count;j++){ Rva00561C34Point *out=pointsA[j]; Rva00561C34Point *generatedOffsets=pointsB[j];Rva00561C34Point *offset=generatedOffsets; for(int i=0;i<numParticles;i++){
    if(i!=0 && i!=numParticles-1){
     float lateralNoise=((GameClientRandomVariable*)&a)->getValue();
     float normalNoise=((GameClientRandomVariable*)&b)->getValue();
     float longitudinalNoise=((GameClientRandomVariable*)&c)->getValue();
     float sumX=longitudinalNoise*axisA.x;
     sumX=sumX+lateralNoise*axisB.x;
     sumX=sumX+normalNoise*axisC.x;
     offset[i].x=sumX;
     offset[i].y=longitudinalNoise*axisA.y+lateralNoise*axisB.y+normalNoise*axisC.y;
     offset[i].z=longitudinalNoise*axisA.z+lateralNoise*axisB.z+normalNoise*axisC.z;
     Rva00561C34Point *displacedPoint=&out[i];Rva00561C34Point *pointOffset=&offset[i];Vector3 *particlePosition=&locs[i];Rva00561564AddP(particlePosition,pointOffset,displacedPoint);
    }else{
     out[i].x=offset[i].x=locs[i].X;
     out[i].y=offset[i].y=locs[i].Y;
     out[i].z=offset[i].z=locs[i].Z;
    }
   }
  }}else{
   for(int j=0;j<count;j++){ Rva00561C34Point *out=pointsA[j]; Rva00561C34Point *cachedOffsets=pointsB[j];Rva00561C34Point *offset=cachedOffsets; for(int i=0;i<numParticles;i++){
    if(i!=0 && i!=numParticles-1){
     Rva00561C34Point *pointOffset=&offset[i];Vector3 *particlePosition=&locs[i];
     out[i].x=pointOffset->x+particlePosition->X;
     out[i].y=pointOffset->y+particlePosition->Y;
     out[i].z=pointOffset->z+particlePosition->Z;
    }else{
     out[i].x=offset[i].x;
     out[i].y=offset[i].y;
     out[i].z=offset[i].z;
    }
   }
  }
  }
  g_00E0626C->Set_Texture((TextureClass*)&texture);g_00E0626C->Reset_Line();
  ShaderClass shader=ShaderClass::_PresetAdditiveSpriteShader;
  switch(getSystem()->m_shaderType){
   case 2:shader=*reinterpret_cast<const ShaderClass *>(&BfmeParticleType2ShaderBits);break;case 3:shader=ShaderClass::_PresetAlphaSpriteShader;break;
   case 4:shader=ShaderClass::_PresetATestSpriteShader;break;case 5:shader=ShaderClass::_PresetMultiplicativeSpriteShader;break;
   case 6:shader=ShaderClass::_PresetAdditive2DShader;break;case 7:shader=ShaderClass::_PresetAlpha2DShader;break;
  }
  if(DX8Wrapper::Get_Fog_Enable())shader.Enable_Fog("HardwareFog");g_00E0626C->Set_Shader(shader);
  for(int j=0;j<count;j++){
   g_00E0626C->Set_LocsWidthsColors(numParticles,(Vector3*)&pointsA[j][0],g_00E065D0->Get_Array(),g_00E065CC->Get_Array(),ids);
   if(!flag)g_00E0626C->Set_Texture_Tile_Factor(1.0f/(numParticles-1));else g_00E0626C->Set_Texture_Tile_Factor(1.0f);
   g_00E0626C->Render(rinfo);
  }
 }
 return numParticles;
}
