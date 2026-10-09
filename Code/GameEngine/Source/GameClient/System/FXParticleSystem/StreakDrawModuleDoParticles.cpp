// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?doParticles@StreakDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z
// retail 0x0055FD6B..0x005600F8 (909 bytes EH RET 0xC).
//
// Identity (target): the body sits in slot 4 of the module vtable at
// 0x00C1C388 directly followed by the "StreakDrawModule" name string; the
// same slot of the GpuDrawModule vtable holds the rowed
// FXParticleSystem::GpuDrawModule::doParticles 0x005639A4 so the signature is
// shared (the second argument is the culling box here). The StreakLineClass
// it fills is g_00E06224 published by the rowed Rva00560135 ctor and its
// neighbours are StreakDrawModuleTemplate::parse 0x0055FD2F and
// StreakDrawModuleInfo's ctor 0x0055FD41. WorldBuilder twin 0x01421C20
// (unnamed) has the same calls and constants.
// Body: nothing while WW3D::IsCurrentlyRenderingShadowMap. Unless the
// particle system (+0x04; the rowed null system Make001FCBD7 otherwise) is of
// type 7 or 8 (rowed Rva0004CABDSevenEight::get) its storage's (+0xA4) slot 8
// list (+0x64 links) is walked: live particles (rowed CPUParticle member
// 0x001F4E2D) whose
// position (+0x1C) lies within the box grown by their size (0x001F4D2D;
// WWMath::Fabs bit mask) are appended (at most 512) to the four
// FXParticleSystem::CategoryModule<CAT_DRAW> share buffers (position colour
// from 0x001F4E1B or black alpha 0x001F4DF9 size and the angle 0x001F4DC4
// scaled by 255/2pi to a byte) plus a local id array (+0x88). With a streak
// line and at least two points the system's texture (+0x10 name; rowed
// BFME2LoadParticleTexture) and the shader picked by its +0x08 type
// (AdditiveSprite by default; HardwareFog when DX8Wrapper::FogEnable) are set
// the points are handed over the first colour is cleared and the line
// renders (slot 12). Returns the point count.
// Shape notes: the system getter is the inline ternary (retail keeps both
// arm orders it produces); the culling box is read into six scalars and the
// position is copied member by member as in the WorldBuilder twin; the
// rowed int getter 0x0004CABD is tested as a byte (every retail caller tests
// AL) and the rowed Set_Texture is handed the texture handle's address as
// retail does. Data: 0x00DB6244 0x00DB6248 0x00DB6268 0x00DB6280 are taken as
// the Additive2D Alpha2D ATestSprite and MultiplicativeSprite presets (Zero
// Hour definition order around the ledger's AdditiveSprite 0x00DB624C and
// AlphaSprite 0x00DB6254 plus their shader bits); 0x00DB6250 is a BFME-only
// preset kept address-named.

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

namespace FXParticleSystem { class StreakDrawModule; }

class WW3D
{
	friend class FXParticleSystem::StreakDrawModule;
	static bool IsCurrentlyRenderingShadowMap;
};

namespace FXParticleSystem { class CPUParticle { public: bool rva001F4E2D(); }; }
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

namespace FXParticleSystem {
class StreakDrawModule
{
public:
	virtual Int doParticles(RenderInfoClass &rinfo, void *bounds, Int *particleCount);

private:
	ParticleSystem *getSystem() const
	{
		return m_system == 0 ? Make001FCBD7() : m_system;
	}

	ParticleSystem *m_system; // +0x04
};

Int StreakDrawModule::doParticles(RenderInfoClass &rinfo, void *bounds, Int *particleCount)
{
	if (WW3D::IsCurrentlyRenderingShadowMap)
		return 0;

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
	UnsignedInt ids[512];
	StreakParticle *p = 0;

	if (!(unsigned char)((Rva0004CABDSevenEight *)getSystem())->get())
		p = getSystem()->m_storage->getFirstParticle();
	{
		for (; p != 0; p = p->m_next)
		{
			if (((CPUParticle *)p)->rva001F4E2D())
				continue;
			const Vector3 *pos = &p->m_pos;
			float size = ((Rva001F4D2D *)p)->rva001F4D2D();
			if (StreakFabs(pos->X - centerX) > extentX + size)
				continue;
			if (StreakFabs(pos->Y - centerY) > extentY + size)
				continue;
			if (StreakFabs(pos->Z - centerZ) > extentZ + size)
				continue;
			ids[count] = p->m_id;
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

	if (g_00E06224 != 0 && count >= 2)
	{
		BFME2ParticleTextureHandle texture = BFME2LoadParticleTexture(getSystem()->m_textureName.str(), 0, 0);
		g_00E06224->Reset_Line();
		g_00E06224->Set_Texture((TextureClass *)&texture);
		ShaderClass shader = ShaderClass::_PresetAdditiveSpriteShader;
		switch (getSystem()->m_shaderType)
		{
		case 2: shader = g_00DB6250; break;
		case 3: shader = ShaderClass::_PresetAlphaSpriteShader; break;
		case 4: shader = ShaderClass::_PresetATestSpriteShader; break;
		case 5: shader = ShaderClass::_PresetMultiplicativeSpriteShader; break;
		case 6: shader = ShaderClass::_PresetAdditive2DShader; break;
		case 7: shader = ShaderClass::_PresetAlpha2DShader; break;
		}
		if (DX8Wrapper::Get_Fog_Enable())
			shader.Enable_Fog("HardwareFog");
		g_00E06224->Set_Shader(shader);
		g_00E06224->Set_LocsWidthsColors(count, g_00E065C8->Get_Array(), g_00E065D0->Get_Array(),
			g_00E065CC->Get_Array(), ids);
		colors[0].X = 0.0f;
		colors[0].Y = 0.0f;
		colors[0].Z = 0.0f;
		colors[0].W = 0.0f;
		g_00E06224->Render(rinfo);
	}
	return count;
}
}
