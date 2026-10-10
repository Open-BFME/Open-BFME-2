// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva0010C2D5@W3DProjectedShadowManager@@QAEPAVW3DProjectedShadow@@HPAVRenderObjClass@@PAUShadowTypeInfo@Shadow@@1@Z
// retail 0x0010C2D5..0x0010C578 (675 bytes, ret 0x10, EH frame).
// Two-texture decal sibling of the rowed 0x0010C145 in the same manager: takes
// an id word, the render object and TWO shadow infos (each: texture name +0x00,
// size +0x0C/+0x10, offsets +0x14/+0x18). Zero sizes of any info fall back to
// twice the render object's bounding extent (vtable +0x110), as Zero Hour's
// addDecal(RenderObjClass*, ShadowTypeInfo*) does for one info. Both names are
// looked up with the manager texture getter 0x0010BC90 (the second lookup
// failing drops the first reference). The shadow comes from the manager's free
// list (+0x18, next link +0x64, recycled through the rowed reset 0x0010953E) or
// is newly allocated (0x68 bytes, base ctor 0x00109D8C, final vtable 0x007CF9F4,
// init 0x0010BDF8). The two texture slots (+0x58/+0x5C) get the textures at +0x68
// and the sizes at +0x58/+0x5C, the rowed updateOffsets 0x00108996 gets each
// info's offsets, and the shadow is filed in the manager's decal list (+0x14)
// in front of the first entry using the same pair of textures (else at the head),
// as Zero Hour's addDecal keeps same-texture decals adjacent.
// Basis: Zero Hour addDecal list insertion (donor); layout, flags, vtable and
// call order are read from retail 0x0010C2D5 and its rowed siblings. The method
// name and the id word's meaning are not recovered.

class RenderObjClass;

void *operator new(unsigned int size);
inline void *operator new(unsigned int, void *where) { return where; }

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

	ShadowNameBuffer *m_name; // +0x00
	ShadowNameBuffer *m_secondName; // +0x04
	int m_type; // +0x08
	float m_sizeX; // +0x0C
	float m_sizeY; // +0x10
	float m_offsetX; // +0x14
	float m_offsetY; // +0x18
};

struct ShadowBounds
{
	float center[3];
	float extent[3];
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

class W3DShadowTexture
{
public:
	virtual void release(); // slot 0, run when the count at +4 reaches zero
	int m_refs; // +0x04
};

struct ShadowTextureSlot
{
	char m_pad00[0x58];
	float m_sizeX; // +0x58
	float m_sizeY; // +0x5C
	char m_pad60[8];
	W3DShadowTexture *m_texture; // +0x68
};

class Rva007B1380
{
public:
	Rva007B1380();
	virtual void slot0();

private:
	char m_pad04[0x30];
};

class W3DProjectedShadow : public Rva007B1380
{
public:
	virtual void slot0();
	bool rva0010BDF8();

	int m_34;
	char m_pad38[0x20];
	ShadowTextureSlot *m_58;
	ShadowTextureSlot *m_5c;
	RenderObjClass *m_60;
	W3DProjectedShadow *m_next; // +0x64
};

class Rva0010959E
{
public:
	void rva0010953E();
};

class Rva007AED00Table
{
public:
	void updateOffsets(int index, float first, float second);
};

class Rva0010BC90ShadowManager
{
public:
	W3DShadowTexture *getTexture(const char *name);
};

class W3DProjectedShadowManager
{
public:
	W3DProjectedShadow *rva0010C2D5(int id, RenderObjClass *object, Shadow::ShadowTypeInfo *first,
		Shadow::ShadowTypeInfo *second);

private:
	void *m_vtable00;
	int m_04;
	char m_pad08[0xC];
	W3DProjectedShadow *m_decalList; // +0x14
	W3DProjectedShadow *m_freeList; // +0x18
};

static void releaseTexture(W3DShadowTexture *texture)
{
	if (--texture->m_refs == 0)
		texture->release();
}

W3DProjectedShadow *W3DProjectedShadowManager::rva0010C2D5(int id, RenderObjClass *object,
	Shadow::ShadowTypeInfo *first, Shadow::ShadowTypeInfo *second)
{
	ShadowDecalInfoView *a = (ShadowDecalInfoView *)first;
	ShadowDecalInfoView *b = (ShadowDecalInfoView *)second;
	if (a == 0 || b == 0)
		return 0;
	float aX = a->m_sizeX;
	float aY = a->m_sizeY;
	float bX = b->m_sizeX;
	float bY = b->m_sizeY;
	if (object)
	{
		if (aX == 0.0f || aY == 0.0f || bX == 0.0f || bY == 0.0f)
		{
			ShadowBounds bounds;
			((ShadowBoundsCall *)object)->getBounds(bounds);
			if (aX == 0.0f)
				aX = bounds.extent[0] * 2.0f;
			if (aY == 0.0f)
				aY = bounds.extent[1] * 2.0f;
			if (bX == 0.0f)
				bX = bounds.extent[0] * 2.0f;
			if (bY == 0.0f)
				bY = bounds.extent[1] * 2.0f;
		}
	}
	Rva0010BC90ShadowManager *textures = (Rva0010BC90ShadowManager *)this;
	W3DShadowTexture *textureA = textures->getTexture(a->name());
	if (textureA == 0)
		return 0;
	W3DShadowTexture *textureB = textures->getTexture(b->name());
	if (textureB == 0)
	{
		releaseTexture(textureA);
		return 0;
	}
	W3DProjectedShadow *shadow = m_freeList;
	if (shadow)
	{
		m_freeList = shadow->m_next;
		((Rva0010959E *)shadow)->rva0010953E();
	}
	else
	{
		void *memory = operator new(0x68);
		shadow = memory ? new (memory) W3DProjectedShadow : 0;
		if (shadow == 0 || !shadow->rva0010BDF8())
		{
			releaseTexture(textureA);
			releaseTexture(textureB);
			return 0;
		}
	}
	shadow->m_34 = id;
	shadow->m_60 = object;
	if (shadow->m_58)
		shadow->m_58->m_texture = textureA;
	if (shadow->m_5c)
		shadow->m_5c->m_texture = textureB;
	ShadowTextureSlot *slot = shadow->m_58;
	slot->m_sizeX = aX;
	slot->m_sizeY = aY;
	slot = shadow->m_5c;
	slot->m_sizeX = bX;
	slot->m_sizeY = bY;
	((Rva007AED00Table *)shadow)->updateOffsets(0, a->m_offsetX, a->m_offsetY);
	((Rva007AED00Table *)shadow)->updateOffsets(1, b->m_offsetX, b->m_offsetY);
	W3DProjectedShadow *head = m_decalList;
	W3DProjectedShadow *previous = 0;
	W3DProjectedShadow *node;
	for (node = m_decalList; node; previous = node, node = node->m_next)
	{
		W3DShadowTexture *nodeA = node->m_58 ? node->m_58->m_texture : 0;
		if (nodeA == textureA)
		{
			W3DShadowTexture *nodeB = node->m_5c ? node->m_5c->m_texture : 0;
			if (nodeB == textureB)
			{
				shadow->m_next = node;
				if (previous)
					previous->m_next = shadow;
				else
					m_decalList = shadow;
				break;
			}
		}
	}
	if (node == 0)
	{
		shadow->m_next = head;
		m_decalList = shadow;
	}
	return shadow;
}
