// ?findFontCharsHandle@@YAPAVFontCharsClass@@PBDM_NH@Z
// partial score=0.9 date=2026-09-24
// cl: /O1 /G7 /EHsc /DNDEBUG

// Font-cache find-or-create worker, retail 0x0009017D (191 bytes).
// BFME2's outlined equivalent of the ZH WW3DAssetManager::Get_FontChars flow
// (assetmgr.cpp: loop the cache for an Is_Font match and Add_Ref it home,
// else new a FontCharsClass, Initialize it, Add_Ref and append it to the
// list): the point size is a float, a fourth detail argument rides every
// worker call, the cache is a raw array plus count behind the list object,
// and the whole body runs under the EH prologue. All callees are settled
// rows or pins (Is_Font, operator new, the FontChars ctor, Initialize, the
// SimpleDynVec Add fold); the list object, array and count ride masking.

class W3DMPO
{
public:
	virtual ~W3DMPO();
};

class RefCountClass
{
public:
	void Add_Ref() { ++m_refs; }
	void Release_Ref();

private:
	int m_refs;                   // +0x04 behind the W3DMPO vtable
};

class FontCharsClass : public W3DMPO, public RefCountClass
{
public:
	FontCharsClass();
	bool Is_Font(const char *font_name, float point_size, bool is_bold, int extra);
	void Initialize_GDI_Font(const char *font_name, float point_size, bool is_bold, int extra);

private:
	char m_body[0x464 - 8];
};

template <class Type>
class SimpleDynVecClass
{
public:
	virtual ~SimpleDynVecClass();
	bool Add(const Type &object, int new_size_hint);
	bool Grow(int new_size_hint);

	Type *Vector;
	int VectorMax;
	int ActiveCount;
};

extern SimpleDynVecClass<FontCharsClass *> g_fontCharsCache;
extern FontCharsClass **g_fontCharsArray;
extern int g_fontCharsCount;

// ?findFontCharsHandle@@YAPAVFontCharsClass@@PBDMMH@Z @0x0009017D
FontCharsClass *findFontCharsHandle(const char *name, float point_size, bool is_bold, int extra)
{
	for (int i = 0; i < g_fontCharsCount; i++) {
		FontCharsClass *entry = g_fontCharsArray[i];
		if (entry->Is_Font(name, point_size, is_bold, extra)) {
			entry->Add_Ref();
			return entry;
		}
	}

	FontCharsClass *font = new FontCharsClass;
	FontCharsClass *created = font;
	created->Initialize_GDI_Font(name, point_size, is_bold, extra);
	created->Add_Ref();
	g_fontCharsCache.Add(font, 0);
	return created;
}
