// cl: /O1 /DNDEBUG /MD /GX
//
// ??0W3DProjectileStreamDraw@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x000D1370,
// 145 bytes. Draw-side ctor completing the W3DProjectileStreamDraw file-unit
// (ModuleData parse/ctor/factory, instance factory 0x650B0, pool key and name
// getter all rowed; this ctor is the factory's sole raw caller, news 0x64).
//
// Shape: EH ctor over the rowed Rva000B19A1 intermediate base (DrawableModule
// 0x306B19 family: m_drawable at +4, proven by that TU), vtable 0x00BCE010,
// texture member at +0x0C loaded by filename through the pinned
// BFME2LoadParticleTexture 0x132D89 into a full-expression temp (hidden out
// reuses the dead ModuleData arg slot at [ebp+0xC]) copied via the rowed
// RefCountPtr<TextureClass> op= 0x424D0 with the temp's inline release
// (rowed Release_Ref 0x61ED10) after, then 0x14 dwords at +0x10 plus the
// +0x60 word zeroed. The filename reads Drawable+8 as a length-prefixed
// string (chars at +8; null means the pooled empty); identity of that slot
// stays open. Row supersedes the ctor pin.

class Thing;
class ModuleData;

class Drawable
{
public:
	void *m_vtable; // +0
	int m_unk04; // +4
	const char *m_prefixedName08; // +8 (length-prefixed string; chars at +8)
};

class Rva000B19A1
{
public:
	Rva000B19A1(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva000B19A1();

protected:
	Drawable *m_drawable; // +4
	int m_pad08; // +8
};

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
	int m_pad[2];
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : m_ptr(0) {}
	const RefCountPtr &operator=(const RefCountPtr &other);
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }

public:
	T *m_ptr;
};

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

BFME2ParticleTextureHandle __cdecl BFME2LoadParticleTexture(const char *filename, int a, int b);

class W3DProjectileStreamDraw : public Rva000B19A1
{
public:
	W3DProjectileStreamDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DProjectileStreamDraw();

private:
	RefCountPtr<TextureClass> m_texture; // +0x0C
	int m_zeros10[0x14]; // +0x10
	int m_zero60; // +0x60
};

// ??0W3DProjectileStreamDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0x000D1370
W3DProjectileStreamDraw::W3DProjectileStreamDraw(Thing *thing, const ModuleData *moduleData)
	: Rva000B19A1(thing, moduleData)
	, m_texture()
{
	const char *rawName = m_drawable->m_prefixedName08;
	const char *texName = rawName != 0 ? rawName + 8 : "";
	m_texture = BFME2LoadParticleTexture(texName, 0, 0);
	for (int i = 0; i < 0x14; ++i)
		m_zeros10[i] = 0;
	m_zero60 = 0;
}
