// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?BFME2LoadParticleTexture@@YA?AVBFME2ParticleTextureHandle@@PBDHH@Z
// Retail 0x00132D89, 237 bytes. Target disassembly shows a name lookup at
// 0x0061F230, typed-ref conversion at 0x00131DCB, and, on a miss, a 0x3C-byte
// allocation/filename ctor at 0x00132D43 followed by Add_Prototype at
// 0x0061EF90. The two option dwords are stored at object +0x30/+0x34. The
// helper class identities at 0x00131DCB and 0x00132D43 remain address-derived.

class TextureClass
{
public:
	virtual void slot00();
	unsigned short m_refCount;
	unsigned short m_pad06;
	void Release_Ref();
};

class BfmeThingSJ : public TextureClass
{
public:
	BfmeThingSJ(int val);
};

extern const void *const g_00BD2690[];

class HierarchyPrototypeRef
{
public:
	HierarchyPrototypeRef() : m_object(0) {}
	HierarchyPrototypeRef(const HierarchyPrototypeRef &that)
		: m_object(that.m_object)
	{
		if (m_object)
			++*(unsigned short *)((char *)m_object + 4);
	}
	~HierarchyPrototypeRef()
	{
		if (m_object)
			((TextureClass *)m_object)->Release_Ref();
	}

	void *m_object;
};

extern HierarchyPrototypeRef Rva0061F230_GetPrototype(const char *name);

struct BfmeResetTagged
{
	virtual int pad00();
	virtual int pad01();
	virtual int pad02();
	virtual int pad03();
	virtual int pad04();
	virtual int pad05();
	virtual int pad06();
	virtual int pad07();
	virtual int pad08();
	virtual int pad09();
	virtual int pad10();
	virtual int pad11();
	virtual int pad12();
	virtual unsigned GetClassId();
};

struct BfmeResetAnyRef
{
	BfmeResetTagged *pointer;
};

struct BfmeResetTextureRef
{
	void *pointer;
	BfmeResetTextureRef &operator=(const BfmeResetAnyRef &rhs);
};

// This opaque wrapper uses the 0x131DCB ctor-shaped helper. Its one-dword
// layout and the subsequent assignment at 0x131D99 follow the target calls.
class Rva00131DCBTextureRef : public BfmeResetTextureRef
{
public:
	Rva00131DCBTextureRef(const BfmeResetAnyRef &rhs);
	~Rva00131DCBTextureRef()
	{
		if (pointer)
			((TextureClass *)pointer)->Release_Ref();
	}
};

class Rva00132D43TextureCtor : public BfmeThingSJ
{
	unsigned char m_pad08[0x28];

public:
	int m_option0;
	int m_option1;
	int m_pad38;
	Rva00132D43TextureCtor(const char *filename);
};

class BFME2ParticleTextureHandle
{
public:
	TextureClass *Ptr;
	BFME2ParticleTextureHandle() : Ptr(0) {}
	BFME2ParticleTextureHandle(TextureClass *ptr) : Ptr(ptr)
	{
		if (Ptr)
			++Ptr->m_refCount;
	}
	~BFME2ParticleTextureHandle()
	{
		if (Ptr)
			Ptr->Release_Ref();
	}
};

extern void Add_Prototype(void *prototype);

Rva00132D43TextureCtor::Rva00132D43TextureCtor(const char *filename)
	: BfmeThingSJ((int)filename)
{
	*(const void **)this = g_00BD2690;
}

BFME2ParticleTextureHandle __cdecl BFME2LoadParticleTexture(
	const char *filename, int option0, int option1)
{
	if (!filename)
		return BFME2ParticleTextureHandle();

	Rva00131DCBTextureRef texture(
		(const BfmeResetAnyRef &)Rva0061F230_GetPrototype(filename));
	if (!texture.pointer)
	{
		Add_Prototype(new Rva00132D43TextureCtor(filename));
		static_cast<BfmeResetTextureRef &>(texture) =
			(const BfmeResetAnyRef &)Rva0061F230_GetPrototype(filename);
	}
	else
	{
		Rva00132D43TextureCtor *resource =
			(Rva00132D43TextureCtor *)texture.pointer;
		resource->m_option0 = option0;
		((Rva00132D43TextureCtor *)texture.pointer)->m_option1 = option1;
	}
	return BFME2ParticleTextureHandle((TextureClass *)texture.pointer);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeDoBNH@@YAXPAVBfmeThingBNH@@PAXHH@Z=?BFME2LoadParticleTexture@@YA?AVBFME2ParticleTextureHandle@@PBDHH@Z")
