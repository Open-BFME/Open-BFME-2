// ??0BfmeMapPictureTexture@@QAE@PAX0@Z
// partial score=0.78 date=2026-10-07
// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0BfmeMapPictureTexture@@QAE@PBD@Z,
// retail 0x002DB93E, 85 bytes. Dedicated TU.
//
// The map-picture image keeps its texture behind a retaining holder: the
// constructor allocates a filename-built texture and adopts it. The retail
// body follows that shape directly, including the failing-new skip around
// the texture build (0x2DB882 pin) and the retaining adopt (0xEF87B pin).
//
// The 0x000EF8A1 constructor is a second shape in the same holder. Target facts:
// it allocates 0x3C bytes, forwards its two stack arguments with 0x800 and 3
// to the rowed initializer at 0x000EF272, then calls Set_Texture at 0x000EF87B.
// Donor-carried declaration: BfmeOwnerZQ::bfmeInitZQ comes from the existing
// BFME1 conversion in BfmeConv1803.cpp. Structural inference: the allocation
// has a BfmeOwnerZQ base view and an unknown 0x3C-byte derived layout; the two
// arguments stay opaque void pointers because target bytes only forward them.

typedef int Int;

#define NULL 0

typedef unsigned int size_t;
void *__cdecl operator new(size_t bytes);

class BfmeThingJC
{
public:
	BfmeThingJC(void *a);
	char m_pad[0x3C];
};

class BfmeOwnerZQ
{
public:
	__forceinline BfmeOwnerZQ(void *first, void *second)
	{
		bfmeInitZQ((void *)0x800, first, second, (void *)3);
	}

	BfmeOwnerZQ *bfmeInitZQ(void *first, void *second, void *third, void *fourth);
	void bfmeBaseInitZQ(void *first, void *second, void *third, void *fourth, int fifth, int sixth);

	void *m_bfmeVfZQ;
	char m_pad[0x38];
};

class TextureClass
{
public:
	TextureClass(const char *filename);
	void Add_Ref() { ++m_numRefs; }
	void Release_Ref();

public:
	Int m_unk00;
	unsigned short m_numRefs;
	unsigned short m_flags;
	char m_padTail[0x3C - 8];
};

template <typename T>
class RefCountPtr
{
public:
	RefCountPtr() : m_ptr(0) {}
	RefCountPtr &operator=(T *ptr);
	~RefCountPtr();

public:
	T *m_ptr;
};

class BfmeMapPictureTexture
{
public:
	BfmeMapPictureTexture(const char *filename);
	BfmeMapPictureTexture(void *first, void *second);
	void Set_Texture(TextureClass *texture);

public:
	RefCountPtr<TextureClass> m_texture;
};

// ?Set_Texture@BfmeMapPictureTexture@@QAEXPAVTextureClass@@@Z
void BfmeMapPictureTexture::Set_Texture(TextureClass *texture)
{
	if (texture != NULL)
	{
		texture->Add_Ref();
		if (m_texture.m_ptr != NULL)
			m_texture.m_ptr->Release_Ref();
		m_texture.m_ptr = texture;
		texture->m_flags |= 0x100;
	}
}

// ??0BfmeMapPictureTexture@@QAE@PBD@Z
BfmeMapPictureTexture::BfmeMapPictureTexture(const char *filename)
{
	Set_Texture((TextureClass *)new BfmeThingJC((void *)filename));
}

// ??0BfmeMapPictureTexture@@QAE@PAX0@Z
// Address-derived overload identity at 0x000EF8A1. The target constructor
// clears the one-pointer holder then adopts the helper result through the
// rowed Set_Texture method; caller argument meanings are unknown.
BfmeMapPictureTexture::BfmeMapPictureTexture(void *first, void *second)
{
	Set_Texture((TextureClass *)new BfmeOwnerZQ(first, second));
}
