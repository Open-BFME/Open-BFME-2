// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib 
// W3DTreeBuffer::updateTexture, retail 0x000EB40F (684 bytes), twin of the shrub
// body at 0x000E7B3F (same providers). Here the atlas key is the type's own
// nameC (+0x50) instead of its data's. Layout:
// texture handles +0x38/+0x3C, atlas lists +0x40/+0x68, 64 types of 0x5C at
// +0x44558 (count +0x45C58). The list providers are BFME2's own: clear
// 0x00170EBC, add 0x00171067, lookup 0x00171583, result 0x00171625.
#include "ascii_string.h"

struct Vec2 { float x, y; };

class CountedAsset { public: void Release_Ref(); };
class AssetReference
{
public:
	~AssetReference() { if (m_object) m_object->Release_Ref(); }
	CountedAsset *m_object;
};

class TextureClass { public: void Release_Ref(); };
class BFME2ParticleTextureHandle
{
public:
	~BFME2ParticleTextureHandle() { if (Ptr) Ptr->Release_Ref(); }
	TextureClass *Ptr;
};
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char *, int, int);

template <class T> class RefCountPtr;
template <> class RefCountPtr<TextureClass>
{
public:
	RefCountPtr const &operator=(RefCountPtr const &other);
	TextureClass *Ptr;
};
class TextureBaseClass
{
public:
	int rva0013275A() const;
	int rva00132784() const;
};

class Rva00170EBC { public: void rva00170EBC(bool); };
class Rva00171583 { public: bool rva00171583(const unsigned int &key, Vec2 *outSize, Vec2 *outPos); };
class Rva00171024
{
public:
	void rva00171067(const BFME2ParticleTextureHandle &handle);
	AssetReference rva00171625();
};

class TextureReport
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual TextureReport *setText(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void show(int mode);
};
class TextureDebug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void beginReport();
	virtual void slot64(); virtual void slot68();
	virtual TextureReport *getReport(int, int, int);
};
extern TextureDebug *theDebug;
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

#define TREE_TEXTURE_REPORT(message) do { \
	if (bfmeRva000387C0()) { \
		_bfme_debugRecordCallsite(1); \
		theDebug->beginReport(); \
		theDebug->getReport(0, 0, 0)->setText(message)->show(2); \
	} \
} while (0)

struct Rva000EB40FType
{
	char prefix[0x24];
	Vec2 coord24, coord2c, coord34, coord3c;
	bool doShadow;
	AsciiString textureName;
	char modelName[4];
	AsciiString nameC;
	char suffix[8];
};

static inline const unsigned int &handleKey(const BFME2ParticleTextureHandle &handle)
{
	return *(const unsigned int *)&handle;
}
static inline const RefCountPtr<TextureClass> &assetPtr(const AssetReference &asset)
{
	return *(const RefCountPtr<TextureClass> *)&asset;
}

class W3DTreeBuffer
{
protected:
	void updateTexture();
public:
	char prefix[0x38];
	RefCountPtr<TextureClass> texture38, texture3c;
	char list40[0x28], list68[0x28];
	char gap90[0x44558 - 0x90];
	Rva000EB40FType types[64];
	int numTypes;
};

void W3DTreeBuffer::updateTexture()
{
	((Rva00170EBC *)list40)->rva00170EBC(false);
	((Rva00170EBC *)list68)->rva00170EBC(true);
	int i;
	for (i = 0; i < numTypes; ++i) {
		((Rva00171024 *)list40)->rva00171067(BFME2LoadParticleTexture(types[i].nameC.str(), 0, 0));
		if (types[i].doShadow)
			((Rva00171024 *)list68)->rva00171067(BFME2LoadParticleTexture(types[i].textureName.str(), 0, 0));
	}
	for (i = 0; i < numTypes; ++i) {
		((Rva00171583 *)list40)->rva00171583(handleKey(BFME2LoadParticleTexture(types[i].nameC.str(), 0, 0)),
			&types[i].coord24, &types[i].coord34);
		if (types[i].doShadow)
			((Rva00171583 *)list68)->rva00171583(handleKey(BFME2LoadParticleTexture(types[i].textureName.str(), 0, 0)),
				&types[i].coord2c, &types[i].coord3c);
	}
	texture38 = assetPtr(((Rva00171024 *)list40)->rva00171625());
	texture3c = assetPtr(((Rva00171024 *)list68)->rva00171625());
	if ((unsigned)((TextureBaseClass *)&texture38)->rva0013275A() > 1024 ||
		(unsigned)((TextureBaseClass *)&texture38)->rva00132784() > 1024)
		TREE_TEXTURE_REPORT("Combined tree texture is bigger than 1024x1024. This will cause errors and significant slowdown on most graphics cards and has to be fixed!");
	if ((unsigned)((TextureBaseClass *)&texture3c)->rva0013275A() > 1024 ||
		(unsigned)((TextureBaseClass *)&texture3c)->rva00132784() > 1024)
		TREE_TEXTURE_REPORT("Combined tree shadow texture is bigger than 1024x1024. This will cause errors and significant slowdown on most graphics cards and has to be fixed!");
}
