// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/shims/stringinline /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
// W3DTreeBuffer::updateTexture, retail 0x000EB40F (684 bytes), twin of the shrub
// body at 0x000E7B3F (same providers). Here the atlas key is the type's own
// nameC (+0x50) instead of its data's. Layout:
// texture handles +0x38/+0x3C, atlas lists +0x40/+0x68, 64 types of 0x5C at
// +0x44558 (count +0x45C58). The list providers are BFME2's own: clear
// 0x00170EBC, add 0x00171067, lookup 0x00171583, result 0x00171625.
#include "W3DTreeRecord.h"
#include "W3DTreeTypeRecord.h"
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
class TextureAsset
{
public:
	static BFME2ParticleTextureHandle Get(const char *, int, int);
};

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
	AssetReference rva00171625();
};
// 0x00171067 is rowed as TexturePacker::rva00171067 (Rva00171067FindOrCreate.cpp).
class TexturePacker
{
public:
	void rva00171067(const BFME2ParticleTextureHandle &handle);
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
// Bind the singleton's Debug owner; TextureDebug is only the local call view.
class Debug;
extern Debug *theDebug;
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

#define TREE_TEXTURE_REPORT(message) do { \
	if (bfmeRva000387C0()) { \
		_bfme_debugRecordCallsite(1); \
		((TextureDebug *)theDebug)->beginReport(); \
		((TextureDebug *)theDebug)->getReport(0, 0, 0)->setText(message)->show(2); \
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


class Rva000E6AC0Base
{
public:
	Rva000E6AC0Base() {}
	virtual ~Rva000E6AC0Base() {}
};

class Rva000E6AC0 : public Rva000E6AC0Base
{
public:
	Rva000E6AC0();
	void rva000E65B1();
	virtual ~Rva000E6AC0();
private:
	unsigned char m_storage[0x38 - 4]; // +0x04
protected:
	RefCountPtr<TextureClass> texture38, texture3c; // +0x38
	char list40[0x28], list68[0x28]; // +0x40
private:
	unsigned char m_pad90[0x5BC - 0x90];
protected:
	float m_sinkScale; // +0x5BC
};

class Rva0052413E
{
public:
	Rva0052413E() throw();
	~Rva0052413E();
private:
	unsigned char m_storage[12];
};

struct TTree;

class W3DTreeBuffer : public Rva000E6AC0
{
	friend class Rva000EC9C6;
protected:
	void updateTexture();
	void updateTopplingTree(TTree *tree);
public:
	W3DTreeBuffer();
public:
	void rva000EA24D();
private:
	Rva000EDA94Record m_records[1200];
private:
	int m_count;
private:
	unsigned char m_44544;
private:
	unsigned char m_44545; // +0x44545
private:
	unsigned char m_44546;
private:
	unsigned char m_44547;
private:
	Rva0052413E m_objects;
private:
	unsigned char m_44554;
private:
	unsigned char m_44555;
private:
	unsigned char m_44556;
private:
	unsigned char m_44557;
private:
	Rva000EC67F m_types[64]; // +0x44558
private:
	int m_typeCount;
private:
	int m_45c5c; // +0x45C5C
private:
	int m_45c60;
private:
	unsigned char m_45c64;
public:
	bool rva000EA48D(void *key, const Coord3D *direction, float height);
	bool rva000EA644(void *key);
	void rva000EA2C0(void *key);
	bool rva000EA6A7(void *key);
	void rva000EB2EF(int index);
	void rva000EB0E6(int index);
	bool rva000ECF2A(unsigned key, int mode);
	void startMorph(int index, int mode);
	int addTreeType(const AsciiString &modelName, const AsciiString &nameC, const void *data, int shadowKind,
		const AsciiString &textureName, const AsciiString &templateName);
	int rva000ECDF5(const AsciiString &templateName, int shadowKind, const AsciiString &textureName);
};

void W3DTreeBuffer::updateTexture()
{
	((Rva00170EBC *)list40)->rva00170EBC(false);
	((Rva00170EBC *)list68)->rva00170EBC(true);
	int i;
	for (i = 0; i < m_typeCount; ++i) {
		((TexturePacker *)list40)->rva00171067(TextureAsset::Get(m_types[i].m_string50.str(), 0, 0));
		if (m_types[i].m_flags44[0])
			((TexturePacker *)list68)->rva00171067(TextureAsset::Get(m_types[i].m_string48.str(), 0, 0));
	}
	for (i = 0; i < m_typeCount; ++i) {
		((Rva00171583 *)list40)->rva00171583(handleKey(TextureAsset::Get(m_types[i].m_string50.str(), 0, 0)),
			reinterpret_cast<Vec2 *>(&m_types[i].m_coords24[0]), reinterpret_cast<Vec2 *>(&m_types[i].m_coords34[0]));
		if (m_types[i].m_flags44[0])
			((Rva00171583 *)list68)->rva00171583(handleKey(TextureAsset::Get(m_types[i].m_string48.str(), 0, 0)),
				reinterpret_cast<Vec2 *>(&m_types[i].m_coords24[1]), reinterpret_cast<Vec2 *>(&m_types[i].m_coords34[1]));
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
