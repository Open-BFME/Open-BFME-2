// ??0BfmeMapPictureTexture@@QAE@PAX00@Z
// partial score=0.95 date=2026-10-04
// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0BfmeMapPictureTexture@@QAE@PBD@Z,
// retail 0x002DB93E, 85 bytes. Dedicated TU.
//
// The map-picture image keeps its texture behind a retaining holder: the
// constructor allocates a filename-built texture and adopts it. The retail
// body follows that shape directly, including the failing-new skip around
// the texture build (0x2DB882 pin) and the retaining adopt (0xEF87B pin).

typedef int Int;

#define NULL 0

typedef unsigned int size_t;
void *__cdecl operator new(size_t bytes);

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
	BfmeMapPictureTexture(void *a, void *b, void *c);
	void Set_Texture(TextureClass *texture);

public:
	RefCountPtr<TextureClass> m_texture;
};
class BfmeOwnerZQ
{
public:
	__forceinline BfmeOwnerZQ(void *a, void *b, void *c, void *d)
	{
		bfmeInitZQ(a, b, c, d);
	}
	BfmeOwnerZQ *bfmeInitZQ(void *a, void *b, void *c, void *d);
private:
	char m_pad00[0x3c];	// sizeof 0x3c for new
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
	Set_Texture(new TextureClass(filename));
}

// ??0BfmeMapPictureTexture@@QAE@PAX00@Z @0x000EF902 (95B).
// Three-arg ctor via 0x3c-sized BfmeOwnerZQ init and retaining adopt.
// Evidence: same TU class/flags, callees rowed bfmeInitZQ 0xEF272 and
// Set_Texture 0xEF87B, callers 0xAE9E8/0xAEB6E, ret 0xc.
// ??0BfmeMapPictureTexture@@QAE@PAX00@Z present-unmatched
BfmeMapPictureTexture::BfmeMapPictureTexture(void *a, void *b, void *c)
{
	Set_Texture((TextureClass *)new BfmeOwnerZQ(b, a, c, (void *)3));
}
