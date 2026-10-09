// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// W3DShrubBuffer::updateTexture, retail 0x000E7B3F (692B). WorldBuilder's
// debug build names it (W3DShrubBuffer.cpp, asserts at lines 176/181); BFME 1's
// matched W3DShrubBufferRva0071DAF0.cpp is the donor for the two-pass
// texture-page build. BFME 2 packs through two TexturePackers (+0x40 shrubs,
// +0x68 shadows): clear both, add every tree type's texture (and its shadow
// texture when the type casts one) as loaded by TextureAsset::Get (rowed
// 0x00132D89), then read back each texture's page coordinates, store the two
// result textures (+0x38 / +0x3C) and report a page larger than 1024 on either
// side. Tree type stride 0x5C from +0x4FB90, count at +0x51270.
#include "ascii_string.h"

typedef int Int;
typedef bool Bool;
typedef float Real;

struct Vec2
{
	Real x, y;
};

class ProxyClass
{
public:
	class ProxyData
	{
	public:
		void Release();
	};
};

// One-pointer texture handles returned by value and released on scope exit.
class BFME2ParticleTextureHandle
{
public:
	~BFME2ParticleTextureHandle() { if (m_data) m_data->Release(); }
	ProxyClass::ProxyData *m_data;
};
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *name, Int a, Int b);

class HierarchyPrototype : public ProxyClass::ProxyData
{
};

template <class T> class RefCountPtr
{
public:
	~RefCountPtr() { if (m_data) m_data->Release(); }
	const RefCountPtr &operator=(const RefCountPtr &other);
	T *m_data;
};

class AssetReference : public RefCountPtr<HierarchyPrototype>
{
};

class Rva00132D0FHolder : public RefCountPtr<HierarchyPrototype>
{
public:
	using RefCountPtr<HierarchyPrototype>::operator=;
	Int rva0013275A();
	Int rva00132784();
};

class TexturePacker
{
public:
	void rva00170EBC(Bool shadow);
	void rva00171067(const BFME2ParticleTextureHandle &texture);
	Bool rva00171583(const BFME2ParticleTextureHandle &texture, Vec2 *topLeft, Vec2 *bottomRight);
	AssetReference rva00171625();
private:
	unsigned char m_bytes[0x28];
};

class BfmeAwakenLog
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void slot4C(int report);
};
class Debug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second, int third);
};
extern Debug *theDebug;
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int kind);

#define DEBUG_CRASH_REPORT(MESSAGE) \
	do { \
		if (_bfme_debugReportingEnabled()) { \
			_bfme_debugRecordCallsite(1); \
			theDebug->slot60(); \
			theDebug->slot6C(0, 0, 0)->slot38(MESSAGE)->slot4C(2); \
		} \
	} while (0)

struct ShrubTypeData
{
	unsigned char m_pad00[0x0C];
	AsciiString m_textureName;		// +0x0C
};

struct ShrubType
{
	const ShrubTypeData *m_data;		// +0x00
	Vec2 m_topLeft;				// +0x04
	Vec2 m_shadowTopLeft;			// +0x0C
	Vec2 m_bottomRight;			// +0x14
	Vec2 m_shadowBottomRight;		// +0x1C
	Bool m_doShadow;			// +0x24
	AsciiString m_shadowTextureName;	// +0x28
	unsigned char m_pad2c[0x5C - 0x2C];
};

class W3DShrubBuffer
{
protected:
	void updateTexture();
private:
	unsigned char m_pad00[0x38];
	Rva00132D0FHolder m_texture;		// +0x38
	Rva00132D0FHolder m_shadowTexture;	// +0x3C
	TexturePacker m_packer;			// +0x40
	TexturePacker m_shadowPacker;		// +0x68
	unsigned char m_pad90[0x4FB90 - 0x90];
	ShrubType m_types[63];			// +0x4FB90
	unsigned char m_pad51290[0x51270 - (0x4FB90 + 63 * 0x5C)];
	Int m_numTypes;				// +0x51270
};

void W3DShrubBuffer::updateTexture()
{
	m_packer.rva00170EBC(false);
	m_shadowPacker.rva00170EBC(true);
	Int i;
	for (i = 0; i < m_numTypes; i++)
	{
		m_packer.rva00171067(BFME2LoadParticleTexture(m_types[i].m_data->m_textureName.str(), 0, 0));
		if (m_types[i].m_doShadow)
			m_shadowPacker.rva00171067(BFME2LoadParticleTexture(m_types[i].m_shadowTextureName.str(), 0, 0));
	}
	for (i = 0; i < m_numTypes; i++)
	{
		m_packer.rva00171583(BFME2LoadParticleTexture(m_types[i].m_data->m_textureName.str(), 0, 0),
			&m_types[i].m_topLeft, &m_types[i].m_bottomRight);
		if (m_types[i].m_doShadow)
			m_shadowPacker.rva00171583(BFME2LoadParticleTexture(m_types[i].m_shadowTextureName.str(), 0, 0),
				&m_types[i].m_shadowTopLeft, &m_types[i].m_shadowBottomRight);
	}
	m_texture = m_packer.rva00171625();
	m_shadowTexture = m_shadowPacker.rva00171625();
	if (m_texture.rva0013275A() > 1024U || m_texture.rva00132784() > 1024U)
		DEBUG_CRASH_REPORT("Combined shrub texture is bigger than 1024x1024. This will cause errors and significant slowdown on most graphics cards and has to be fixed!");
	if (m_shadowTexture.rva0013275A() > 1024U || m_shadowTexture.rva00132784() > 1024U)
		DEBUG_CRASH_REPORT("Combined shrub shadow texture is bigger than 1024x1024. This will cause errors and significant slowdown on most graphics cards and has to be fixed!");
}
