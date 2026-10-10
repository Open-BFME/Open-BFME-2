// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// FXParticleSystem::DefaultModule<6>::doParticles, native55C478..55C86D,
// full1013B RET12. WB1418FF0 independently names the method and source file
// fxpsdefaultdrawmodule.cpp; slot4 and the shared particle loop agree with
// the matched StreakDrawModule::doParticles55FD6B (the primary C++ guide).
// Native: system4/storageA4, particle position1C/next64, four share buffers,
// box center/extents, size/color/alpha/angle providers and cap512. BF2 adds
// GlobalData C60 guard, PointGroup atE06098, draw typeC, billboard flag80 and
// opaque render payload88. No more-specific payload type is asserted.
// Both output paths use the same proven point-group setup and texture holder.
// A small forceinline depth getter preserves native argument evaluation:
// payload system first, depth system second; expression ternary reverses it.
// PointGroup volume callee17F6E0 is WB-named RenderVolumeParticleA290C0;
// its third pointer argument is a target-specific ABI view, not BF1's
// two-argument signature. Receiver remains neutral in the callee declaration.
// The texture/resource/point-group providers keep their established bindings.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class RenderInfoClass;

class Vector3
{
public:
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
	void Set_LocsWidthsColors(unsigned int num_points, Vector3 *locs, float *widths,
		Vector4 *colors, unsigned int *personalities);
};
extern StreakLineClass *g_00E06224;

class DX8Wrapper
{
public:
	static bool Get_Fog_Enable(void) { return FogEnable; }
protected:
	static bool FogEnable;
};

namespace FXParticleSystem { template<int CATEGORY> class DefaultModule; }

class WW3D
{
	friend class FXParticleSystem::DefaultModule<6>;
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
	char m_pad28[0x3c];
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
	Int m_drawType; // +0x0C
	AsciiString m_textureName; // +0x10
	char m_pad14[0x80-0x14];
 bool m_billboard;
 char m_pad81[0x88-0x81];
 char m_renderPayload[0xA4-0x88];
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

class GlobalData;
extern GlobalData* TheWritableGlobalData;
class PointGroupClass {public:
 enum FlagsType { TRANSFORM=0}; enum PointModeEnum { QUADS=1 };
 void Set_Texture(TextureClass*);
 void Set_Flag(FlagsType,bool);
 void Set_Shader(ShaderClass);
 void Set_Point_Mode(PointModeEnum);
 void Set_Arrays(ShareBufferClass<Vector3>*,ShareBufferClass<Vector4>*,ShareBufferClass<unsigned int>*,ShareBufferClass<float>*,ShareBufferClass<unsigned char>*,ShareBufferClass<unsigned char>*,int,float,float,float,float);
 void Render(RenderInfoClass&,int);
};
extern PointGroupClass* g_00E06098;
class Rva00179100 {public: void SetFlag(bool);};
class Rva0017F6E0PointGroupVolume {public: void RenderVolumeParticle(RenderInfoClass&,int,void*);};
namespace FXParticleSystem {
template<int CATEGORY> class DefaultModule
{
public:
 virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual Int doParticles(RenderInfoClass &rinfo, void *bounds, Int *particleCount);

private:
	__forceinline int getDepth()const {return getSystem()->m_drawType==4?6:0;}
 ParticleSystem *getSystem() const
	{
		return m_system == 0 ? Make001FCBD7() : m_system;
	}

	ParticleSystem *m_system; // +0x04
};

template<> Int DefaultModule<6>::doParticles(RenderInfoClass &rinfo, void *bounds, Int *particleCount)
{
	if(WW3D::IsCurrentlyRenderingShadowMap)return 0;
 if(*reinterpret_cast<int*>(reinterpret_cast<char*>(TheWritableGlobalData)+0xC60)!=-1)return 0;

	Int count = 0;
	Vector3 *locs = g_00E065C8->Get_Array();
	float *widths = g_00E065D0->Get_Array();
	Vector4 *colors = g_00E065CC->Get_Array();
	unsigned char *angles = g_00E065D4->Get_Array();
	const StreakBox *box = (const StreakBox *)bounds;
	float centerX = box->m_center.X;
	float centerY = box->m_center.Y;
	float centerZ = box->m_center.Z;
	float extentX = box->m_extent.X;
	float extentY = box->m_extent.Y;
	float extentZ = box->m_extent.Z;
		StreakParticle *p = 0;

	if (!(unsigned char)((Rva0004CABDSevenEight *)getSystem())->get())
		p = getSystem()->m_storage->getFirstParticle();
	{
		for (; p != 0; p = p->m_next)
		{
			if (((Rva001F4E2D *)p)->rva001F4E2D())
				continue;
			const Vector3 *pos = &p->m_pos;
			float size = ((Rva001F4D2D *)p)->rva001F4D2D();
			if (StreakFabs(pos->X - centerX) > extentX + size)
				continue;
			if (StreakFabs(pos->Y - centerY) > extentY + size)
				continue;
			if (StreakFabs(pos->Z - centerZ) > extentZ + size)
				continue;
			locs[count].X = pos->X;
			locs[count].Y = pos->Y;
			locs[count].Z = pos->Z;
			widths[count] = size;
			const RGBColor *color = ((Rva001F4E1BSlot *)p)->get();
			if (color != 0)
			{
				colors[count].X = color->red;
				colors[count].Y = color->green;
				colors[count].Z = color->blue;
			}
			else
			{
				colors[count].X = 0.0f;
				colors[count].Y = 0.0f;
				colors[count].Z = 0.0f;
			}
			colors[count].W = ((Rva001F4DF9 *)p)->rva001F4DF9();
			angles[count] = (unsigned char)(((Rva001F4DC4 *)p)->rva001F4DC4() * 255.0f / 6.2831855f);
			count++;
			if (count == 512)
				break;
		}
	}


 if(count>0) {
  BFME2ParticleTextureHandle texture=BFME2LoadParticleTexture(getSystem()->m_textureName.str(),0,0);
  if(g_00E06098!=0) {
   g_00E06098->Set_Texture((TextureClass*)&texture);
   g_00E06098->Set_Flag(PointGroupClass::TRANSFORM,true);
   ShaderClass shader=ShaderClass::_PresetAdditiveSpriteShader;
   switch(getSystem()->m_shaderType) {
    case 2: shader=g_00DB6250;break;
    case 3: shader=ShaderClass::_PresetAlphaSpriteShader;break;
    case 4: shader=ShaderClass::_PresetATestSpriteShader;break;
    case 5: shader=ShaderClass::_PresetMultiplicativeSpriteShader;break;
    case 6: shader=ShaderClass::_PresetAdditive2DShader;break;
    case 7: shader=ShaderClass::_PresetAlpha2DShader;break;
   }
   if(DX8Wrapper::Get_Fog_Enable())shader.Enable_Fog("HardwareFog");
   g_00E06098->Set_Shader(shader);
   g_00E06098->Set_Point_Mode(PointGroupClass::QUADS);
   g_00E06098->Set_Arrays(g_00E065C8,g_00E065CC,0,g_00E065D0,g_00E065D4,0,count,0.0f,0.0f,0.0f,0.0f);
   ((Rva00179100*)g_00E06098)->SetFlag(!getSystem()->m_billboard);
   if(getSystem()->m_drawType==4)
    ((Rva0017F6E0PointGroupVolume*)g_00E06098)->RenderVolumeParticle(rinfo,getDepth(),getSystem()->m_renderPayload);
   else g_00E06098->Render(rinfo,(int)getSystem()->m_renderPayload);
  }
 }
 return count;
}
}
