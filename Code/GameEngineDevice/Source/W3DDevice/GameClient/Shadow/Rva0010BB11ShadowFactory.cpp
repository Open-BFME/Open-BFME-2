// cl: /O1 /G7 /arch:SSE /GX- /MD
//
// ?create@Rva0010BB11ShadowFactory@@QAEPAVW3DProjectedShadow@@PAVW3DShadowTexture@@PAVRenderObjClass@@HEMMMMMPAXEHE@Z,
// retail 0x0010BB11..0x0010BC90 (383B), thiscall ret 0x34.
//
// BFME 2's pooled projected-decal factory: it takes a decal from the
// manager's free list (+0x10, linked through +0x114) and resets it, or
// allocates a fresh 0x118-byte one; sets the stencil/timed flags, owner,
// both textures, type and sizes (with offsets stored as offset/size); and
// splices it into the caller's list right after the first decal using the
// same texture pair, so draws batch by texture. Decal types 1, 0x20, 0x40,
// 0x400, 0x800, 0x1000 and 0x2000 are counted at +0x250.
//
// Evidence (target): WorldBuilder twin 0x8D5330 has the same statements;
// callers such as 0x0010C065 and 0x0010C6B9 push the thirteen arguments.
// Callees are the rowed decal constructor 0x0010BA2C, its reset 0x0010BA61
// and setReferenced 0x00108538. Class and field names are the ledger's
// address-derived owners; the manager's original method name is unknown.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned char UnsignedByte;

class W3DShadowTexture;
class RenderObjClass;
class Rva007AE5E0Referenced;

struct Rva00108895Triplet
{
    float first, second, third;
    void set(float value) { first = value; second = value; third = value; }
};

class Rva000F0F2B
{
public:
    Rva000F0F2B();
    virtual ~Rva000F0F2B();
protected:
    char m_body[0x68 - 4];
};

// The rowed 0x118-byte decal constructor 0x0010BA2C.
class Rva0010BA2COwner : public Rva000F0F2B
{
public:
    Rva0010BA2COwner() throw();
    void rva00108895();
private:
    unsigned int retained68[2];
    void *retained70;
    unsigned char flag74;
    char unknown75[3];
    float value78;
    float value7C;
    unsigned int word80;
    unsigned char flag84;
    unsigned char flag85;
    char unknown86[2];
    Rva00108895Triplet sentinel88;
    unsigned int array94[16];
    unsigned int arrayD4[16];
    Rva0010BA2COwner *next114;
};

// The rowed reset of a recycled decal, 0x0010BA61.
class Rva0010BA61
{
public:
	void rva0010BA61();
};

// The rowed owner binding 0x00108538.
class Rva007AE5E0Owner
{
public:
	void setReferenced(Rva007AE5E0Referenced *owner);
};

class W3DProjectedShadow;
// The decal's fields at retail offsets; W3DProjectedShadow's own header spells a different layout.
class Rva0010BB11DecalView
{
public:
	char m_pad00[0x34];
	Int m_type;				// +0x34
	char m_pad38[0x58 - 0x38];
	Real m_sizeX;				// +0x58
	Real m_sizeY;				// +0x5C
	Real m_value60;				// +0x60
	char m_pad64[0x68 - 0x64];
	W3DShadowTexture *m_texture[2];		// +0x68
	char m_pad70[0x74 - 0x70];
	UnsignedByte m_flag74;			// +0x74
	char m_pad75[0x78 - 0x75];
	Real m_offsetU;				// +0x78
	Real m_offsetV;				// +0x7C
	Int m_value80;				// +0x80
	Bool m_flag84;				// +0x84
	Bool m_flag85;				// +0x85
	char m_pad86[0x114 - 0x86];
	Rva0010BB11DecalView *m_next;		// +0x114
};

class Rva0010BB11ShadowFactory
{
public:
	W3DProjectedShadow *create(W3DShadowTexture*,RenderObjClass*,int,unsigned char,float,float,float,float,float,void*,unsigned char,int,unsigned char);
	char m_pad00[0x10];
private:
	W3DProjectedShadow *m_freeList; // +0x10
	char m_pad14[0x23C];
	int m_counted; // +0x250
};

// Its callers keep the out-of-line call retail makes.
__declspec(noinline) W3DProjectedShadow *Rva0010BB11ShadowFactory::create(W3DShadowTexture *texture, RenderObjClass *robj, Int type,
	UnsignedByte flag, Real sizeX, Real sizeY, Real value, Real offsetU, Real offsetV,
	void *list, UnsignedByte flag84, Int secondTexture, UnsignedByte flag85)
{
	if (!texture)
		return 0;
	if (flag85 && !secondTexture)
		return 0;

	Rva0010BB11DecalView *shadow;
	if (m_freeList)
	{
		shadow = (Rva0010BB11DecalView *)m_freeList;
		m_freeList = (W3DProjectedShadow *)shadow->m_next;
		reinterpret_cast<Rva0010BA61 *>(shadow)->rva0010BA61();
	}
	else
	{
		Rva0010BA2COwner *owner = new Rva0010BA2COwner;
		shadow = reinterpret_cast<Rva0010BB11DecalView *>(owner);	// allocated through a local, as retail merges the new result once
	}

	if (!shadow)
		return 0;

	if (flag84)
		shadow->m_flag84 = true;
	else if (flag85)
		shadow->m_flag85 = true;

	Int shadowType = type;
	reinterpret_cast<Rva007AE5E0Owner *>(shadow)->setReferenced(reinterpret_cast<Rva007AE5E0Referenced *>(robj));
	// Texture stages are written through a running index (WorldBuilder computes
	// both offsets from it), which also fixes retail's store order.
	Int stage = 0;
	shadow->m_texture[stage] = texture;
	stage = 1;
	shadow->m_texture[stage] = reinterpret_cast<W3DShadowTexture *>(secondTexture);
	shadow->m_type = shadowType;
	shadow->m_flag74 = flag;
	shadow->m_value80 = 0;
	shadow->m_sizeX = sizeX;
	shadow->m_sizeY = sizeY;
	shadow->m_value60 = value;
	if (sizeX == 0.0f)
		shadow->m_offsetU = 0.0f;
	else
		shadow->m_offsetU = offsetU / sizeX;
	if (sizeY == 0.0f)
		shadow->m_offsetV = 0.0f;
	else
		shadow->m_offsetV = offsetV / sizeY;

	// Keep decals sharing a texture pair together so they draw in one batch.
	Rva0010BB11DecalView **head = reinterpret_cast<Rva0010BB11DecalView **>(list);
	Rva0010BB11DecalView *prev = 0;
	Rva0010BB11DecalView *cur;
	for (cur = *head; cur; prev = cur, cur = cur->m_next)
	{
		if (cur->m_texture[0] == texture && cur->m_texture[1] == reinterpret_cast<W3DShadowTexture *>(secondTexture))
		{
			shadow->m_next = cur;
			if (prev)
				prev->m_next = shadow;
			else
				*head = shadow;
			break;
		}
	}
	if (!cur)
	{
		shadow->m_next = *head;
		*head = shadow;
	}

	switch (shadow->m_type)
	{
	case 1:
	case 0x20:
	case 0x40:
	case 0x400:
	case 0x800:
	case 0x1000:
	case 0x2000:
		m_counted++;
		break;
	}
	return (W3DProjectedShadow *)shadow;
}
