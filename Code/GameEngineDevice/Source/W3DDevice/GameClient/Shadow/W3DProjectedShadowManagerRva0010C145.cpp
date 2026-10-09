// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva0010C145@W3DProjectedShadowManager@@QAEPAVW3DProjectedShadow@@PAVRenderObjClass@@PAUShadowTypeInfo@Shadow@@_N2@Z
// retail 0x0010C145..0x0010C2D5 (400 bytes, ret 0x10).
// Decal-style sibling of the rowed W3DProjectedShadowManager::addShadow
// (0x0010C578, W3DProjectedShadow.cpp) in the same manager vtable (slot 5 at
// 0x007CF9D0; addShadow's texture lookup 0x0010BC90 and 13-word factory
// 0x0010BB11 are the only calls). Rejects a missing render object or shadow
// info; takes the info's size (+0x0C/+0x10; a zero side falls back to twice
// the render object's bounding-box extent from vtable +0x110 as in
// addShadow) and height (+0x20), then creates the shadow from the texture
// named by the info (+0x00) with its type (+0x08), byte +0x26 and offsets
// (+0x14/+0x18) passed unchanged. The first flag files it in the manager list
// at +0x0C with factory flags (1 0 0); else the second flag files it at +0x1C
// with a second texture named by the info's +0x04 string and flags (0 tex 1);
// otherwise it goes to the list at +0x08 with (0 0 0). No WorldBuilder twin;
// Zero Hour's addDecal(RenderObjClass* ShadowTypeInfo*) is the nearest lead.
// Flag meanings and the method name are not recovered.

typedef float Real;
typedef bool Bool;

class RenderObjClass;
class W3DProjectedShadow;
class W3DShadowTexture;

class Shadow
{
public:
	struct ShadowTypeInfo;
};

struct ShadowNameBuffer
{
	int refs;
	unsigned short length;
	unsigned short capacity;
	char text[1];
};

struct ShadowDecalInfoView
{
	const char *name() const { return m_name ? m_name->text : ""; }
	const char *secondName() const { return m_secondName ? m_secondName->text : ""; }

	ShadowNameBuffer *m_name; // +0x00
	ShadowNameBuffer *m_secondName; // +0x04
	int m_type; // +0x08
	Real m_sizeX; // +0x0C
	Real m_sizeY; // +0x10
	Real m_offsetX; // +0x14
	Real m_offsetY; // +0x18
	Real m_unused1C;
	Real m_height; // +0x20
	unsigned char m_force; // +0x24
	unsigned char m_pad25;
	unsigned char m_byte26; // +0x26
};

struct ShadowBounds
{
	Real center[3];
	Real extent[3];
};

class ShadowBoundsCall
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
	virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void getBounds(ShadowBounds &bounds); // +0x110
};

class Rva0010BC90ShadowManager
{
public:
	W3DShadowTexture *getTexture(const char *name);
};

class Rva0010BB11ShadowFactory
{
public:
	W3DProjectedShadow *create(W3DShadowTexture *texture, RenderObjClass *object, int type,
		unsigned char flag, float sizeX, float sizeY, float height, float offsetX, float offsetY,
		void *list, unsigned char a, int b, unsigned char c);
};

class W3DProjectedShadowManager
{
public:
	W3DProjectedShadow *rva0010C145(RenderObjClass *object, Shadow::ShadowTypeInfo *raw, Bool first, Bool second);

private:
	void *m_vtable00;
	int m_04;
	char m_list08[4];
	char m_list0C[0x10];
	char m_list1C[4];
};

W3DProjectedShadow *W3DProjectedShadowManager::rva0010C145(RenderObjClass *object, Shadow::ShadowTypeInfo *raw, Bool first, Bool second)
{
	ShadowDecalInfoView *info = (ShadowDecalInfoView *)raw;
	if (object == 0 || info == 0)
		return 0;
	Real height = info->m_height;
	Real sizeX = info->m_sizeX;
	Real sizeY = info->m_sizeY;
	if (sizeX == 0.0f || sizeY == 0.0f)
	{
		ShadowBounds bounds;
		((ShadowBoundsCall *)object)->getBounds(bounds);
		if (sizeX == 0.0f)
			sizeX = bounds.extent[0] * 2.0f;
		if (sizeY == 0.0f)
			sizeY = bounds.extent[1] * 2.0f;
	}
	Rva0010BC90ShadowManager *textures = (Rva0010BC90ShadowManager *)this;
	Rva0010BB11ShadowFactory *factory = (Rva0010BB11ShadowFactory *)this;
	if (first)
		return factory->create(textures->getTexture(info->name()), object, info->m_type, info->m_byte26,
			sizeX, sizeY, height, info->m_offsetX, info->m_offsetY, m_list0C, 1, 0, 0);
	else if (second)
		return factory->create(textures->getTexture(info->name()), object, info->m_type, info->m_byte26,
			sizeX, sizeY, height, info->m_offsetX, info->m_offsetY, m_list1C, 0,
			(int)textures->getTexture(info->secondName()), 1);
	else
		return factory->create(textures->getTexture(info->name()), object, info->m_type, info->m_byte26,
			sizeX, sizeY, height, info->m_offsetX, info->m_offsetY, m_list08, 0, 0, 0);
}
