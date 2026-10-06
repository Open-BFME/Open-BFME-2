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
	void Add_Ref(void);
	void Release_Ref(void);
};

inline void TextureBaseClass::Add_Ref(void)
{
	++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
}

class TextureClass : public TextureBaseClass
{
};

class MaterialInfoClass
{
public:
	int m_refs;
	int m_08;
	VertexMaterialClass **VmatVector;
	int m_10;
	int m_14;
	int VmatCount;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int TextureCount;
};

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
