// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Remap_Texture@MaterialRemapperClass@@QAE?AVBfmeHandleCX@@ABV2@@Z
// retail 0x0016EC00, 196 bytes. Dedicated TU.
//
// Verbatim BFME1 MaterialRemapTexture.cpp port (their 194B) with one BFME2
// adaptation: the null arm returns an empty handle (retail zero-stores the
// hidden result) instead of copying the null source. Upstream matinfo.cpp
// supplies the cache lookup and mapping loop shape; the LastSrcTex/LastDestTex
// updates go through the inline copy-assignment (Add_Ref-new, Release-old,
// store) and every return copies through the inline copy-constructor
// (store plus conditional Add_Ref). Release_Ref resolves to the matched
// 0x61ED10 row; no pins needed.

class VertexMaterialClass;

class TextureBaseClass
{
public:
	__declspec(dllimport) __forceinline void Add_Ref(void);
	void Release_Ref(void);
};

__declspec(dllimport) __forceinline void TextureBaseClass::Add_Ref(void)
{
	++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
}

class TextureClass : public TextureBaseClass
{
};

#include "MaterialInfoClass.h"

struct VmatRemapStruct
{
	VertexMaterialClass *Src;
	VertexMaterialClass *Dest;
};

// Same spelling as the BFME1 donor so the existing BfmeHandleCX pins resolve.
class BfmeHandleCX
{
public:
	TextureClass *p;

	BfmeHandleCX(void) : p(0)
	{
	}

	BfmeHandleCX(const BfmeHandleCX &other) : p(other.p)
	{
		if (p)
			p->Add_Ref();
	}

	~BfmeHandleCX(void)
	{
		if (p)
			p->Release_Ref();
	}

	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.p)
			other.p->Add_Ref();
		if (p)
			p->Release_Ref();
		p = other.p;
		return *this;
	}
};

struct TextureRemapStruct
{
	BfmeHandleCX Src;
	BfmeHandleCX Dest;
};

class MaterialRemapperClass
{
public:
	BfmeHandleCX Remap_Texture(const BfmeHandleCX &src);

	MaterialInfoClass *SrcMatInfo;
	MaterialInfoClass *DestMatInfo;
	int TextureCount;
	TextureRemapStruct *TextureRemaps;
	int VertexMaterialCount;
	VmatRemapStruct *VertexMaterialRemaps;
	void *LastSrcVmat;
	void *LastDestVmat;
	BfmeHandleCX LastSrcTex;
	BfmeHandleCX LastDestTex;
};


BfmeHandleCX MaterialRemapperClass::Remap_Texture(const BfmeHandleCX &src)
{
	if (!src.p) return BfmeHandleCX();
	if (src.p == LastSrcTex.p) return LastDestTex;
	for (int i = 0; i < TextureCount; ++i) {
		if (TextureRemaps[i].Src.p == src.p) {
			LastSrcTex = src;
			LastDestTex = TextureRemaps[i].Dest;
			return TextureRemaps[i].Dest;
		}
	}
	return BfmeHandleCX();
}

// Retail 001494F0..00149506 is an independently padded 22-byte body:
// thiscall, one borrowed four-byte source, returns the destination address.
// It copies a pointer, then retains its nonnull pointee by incrementing the
// WORD at +4. No direct code or data reference survives in retail, so neither
// TextureClass nor the donor's BfmeHandleCX name is established here. The
// address-derived class describes only this one-pointer copying operation.
// Lead: clean BFME1 MaterialRemapTexture.cpp at cf0a80c22858 compiled using
// this unit's flags. Its same-shaped BfmeHandleCX copy cannot use that name:
// the existing BFME2 pin owns the distinct 21-byte body at 000424BB.
class Rva001494F0RetainedPointer
{
public:
    void *m_object;
    Rva001494F0RetainedPointer(const Rva001494F0RetainedPointer &other);
};

Rva001494F0RetainedPointer::Rva001494F0RetainedPointer(
    const Rva001494F0RetainedPointer &other) : m_object(other.m_object)
{
    if (m_object)
        ++*reinterpret_cast<unsigned short *>(static_cast<char *>(m_object) + 4);
}
