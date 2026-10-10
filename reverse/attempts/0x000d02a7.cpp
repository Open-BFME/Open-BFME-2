// ??0W3DStreakDraw@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.9 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /I.
// ?0W3DStreakDraw ctor
class Thing;
class ModuleData;

#include "ascii_string.h"
class TextureClass { public: virtual void slot00(); unsigned short m_refCount; unsigned short m_pad06; void Release_Ref(); };
template<class T> class RefCountPtr { public:
	RefCountPtr() : Ptr(0) {}
	~RefCountPtr();
	const RefCountPtr &operator=(const RefCountPtr &other);
	T *Ptr;
};
class BFME2ParticleTextureHandle { public:
	TextureClass *Ptr;
	~BFME2ParticleTextureHandle() { if (Ptr) Ptr->Release_Ref(); }
};

extern BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *, int, int);

class DrawModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DrawModule();

protected:
	const ModuleData *m_moduleData;
	void *m_drawable;
};

struct W3DStreakWeatherTexture
{
	int weather;
	AsciiString texture;
};

class W3DStreakDrawModuleData
{
public:
	unsigned char m_pad00[8];
	float m_length;
	float m_width;
	bool m_additive;
	unsigned char m_pad11[3];
	float m_color[3];
	unsigned char m_pad20[4];
	AsciiString m_textureName;
	W3DStreakWeatherTexture *m_weatherBegin;
	W3DStreakWeatherTexture *m_weatherEnd;
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Rva00138GlobalView { char head[0x138]; int m_weather; };

class ShaderClass
{
public:
	int m_bits;
	static ShaderClass _PresetAdditiveShader;
	static ShaderClass _PresetAlphaShader;
};

class Rva00126399 { public: TextureClass *Ptr; };
class Rva00167EB9 { public: const Rva00126399 &rva00167EB9(const Rva00126399 &); };
class Rva00167EC4DwordSlot { public: void set(int); };
class Rva00167EFields { public: void setBound(float); };
struct Rva00167EF8Rec { float x, y, z; };
class Rva00167EF8 { public: void rva00167EF8(const Rva00167EF8Rec &); };
class Rva00167F37FloatField { public: void set(float); };

class Rva001684D6
{
public:
	Rva001684D6();
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59(); virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63(); virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67(); virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71(); virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75(); virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79(); virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83(); virtual void s84(); virtual void s85(); virtual void s86(); virtual void s87(); virtual void s88(); virtual void s89(); virtual void s90(); virtual void s91(); virtual void s92(); virtual void s93(); virtual void s94(); virtual void s95(); virtual void s96(); virtual void s97(); virtual void s98(); virtual void s99(); virtual void s100(); virtual void s101(); virtual void s102(); virtual void s103(); virtual void s104();
	virtual void apply(int value);
	char m_storage[0x108 - 4 - 0];
};
void *operator new(unsigned int);

class BfmeStreakVtable
{
public:
	virtual void s0(); virtual void s1();
	virtual void Add_Render_Object(Rva001684D6 *object);
};

class RTS3DScene : public BfmeStreakVtable {};
class W3DDisplay { public: static RTS3DScene *m_3DScene; };

class W3DStreakDraw : public DrawModule
{
public:
	W3DStreakDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DStreakDraw();

private:
	Rva001684D6 *m_streak;
	RefCountPtr<TextureClass> m_texture;
};

W3DStreakDraw::W3DStreakDraw(Thing *thing, const ModuleData *moduleData)
	: DrawModule(thing, moduleData), m_texture()
{
	m_streak = 0;
	const W3DStreakDrawModuleData *data = (const W3DStreakDrawModuleData *)m_moduleData;
	const W3DStreakWeatherTexture *found = 0;
	if (data->m_weatherEnd - data->m_weatherBegin != 0) {
		_ReadWriteBarrier();
		int weather = ((Rva00138GlobalView *)TheWritableGlobalData)->m_weather;
		for (const W3DStreakWeatherTexture *entry = data->m_weatherBegin; entry != data->m_weatherEnd; ++entry) {
			if (entry->weather == weather) {
				found = entry;
				break;
			}
		}
	}
	if (found)
		m_texture = (const RefCountPtr<TextureClass> &)BFME2LoadParticleTexture(found->texture.str(), 0, 0);
	else
		m_texture = (const RefCountPtr<TextureClass> &)BFME2LoadParticleTexture(data->m_textureName.str(), 0, 0);

	m_streak = new Rva001684D6();
	if (m_streak) {
		((Rva00167EB9 *)m_streak)->rva00167EB9((const Rva00126399 &)m_texture);
		((Rva00167EC4DwordSlot *)m_streak)->set(data->m_additive ? ShaderClass::_PresetAdditiveShader.m_bits : ShaderClass::_PresetAlphaShader.m_bits);
		((Rva00167EFields *)m_streak)->setBound(data->m_width);
		Rva00167EF8Rec color;
		color.x = data->m_color[0];
		color.y = data->m_color[1];
		color.z = data->m_color[2];
		((Rva00167EF8 *)m_streak)->rva00167EF8(color);
		((Rva00167F37FloatField *)m_streak)->set(data->m_length);
		W3DDisplay::m_3DScene->Add_Render_Object(m_streak);
		m_streak->apply(1);
	}
}
