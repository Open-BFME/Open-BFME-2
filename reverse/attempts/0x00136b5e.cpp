// ?rva00136B5E@@YAXPBD0@Z
// partial score=0.6 date=2026-10-08
// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /arch:SSE
// ?rva00136B5E@@YAXPBD0@Z @0x00136B5E 137B.
// Cdecl pair setter: when both arguments are non-null, resolves the asset
// prototype (matched Rva009EBCE0_GetPrototype), holds the texture in the first
// argument slot via the matched TextureRef ctor, stores the texture's +8 word
// (or -1) through the unrowed thiscall 0x00136A21 on the global holder, and sets
// the string with the matched StringBase::set. Both locals release their
// texture on scope exit. Evidence: target only; names are address-derived.

struct BfmeResetAnyRef;

class TextureBaseClass
{
public:
	void Release_Ref();

	char m_pad00[8];
	int m_id08;
};

class Rva009EBCE0AssetReference
{
public:
	~Rva009EBCE0AssetReference()
	{
		if (m_tex)
			m_tex->Release_Ref();
	}

	TextureBaseClass *m_tex;
};

Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char *name);

class Rva00131DCBTextureRef
{
public:
	Rva00131DCBTextureRef(const BfmeResetAnyRef &ref);
	~Rva00131DCBTextureRef()
	{
		if (m_tex)
			m_tex->Release_Ref();
	}

	TextureBaseClass *m_tex;
};

template <typename T>
class StringBase
{
public:
	void set(const char *s);
};

class Rva00136A21Holder
{
public:
	StringBase<char> *rva00136A21(int *id);
};

extern Rva00136A21Holder g_00DF29B4;

void rva00136B5E(const char *name, const char *value)
{
	if (name && value)
	{
		Rva009EBCE0AssetReference proto = Rva009EBCE0_GetPrototype(name);
		Rva00131DCBTextureRef tex((const BfmeResetAnyRef &)proto);
		int id = tex.m_tex ? tex.m_tex->m_id08 : -1;
		g_00DF29B4.rva00136A21(&id)->set(value);
	}
}
