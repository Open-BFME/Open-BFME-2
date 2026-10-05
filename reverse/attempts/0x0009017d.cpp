// ?getFontCharsHandle@@YAPAVFontCharsClass@@PBDM_NH@Z
// partial score=0.975 date=2026-10-05
// ?getFontCharsHandle@@YAPAVFontCharsClass@@PBDM_NH@Z
// partial score=0.99 date=2026-10-03
// ?getFontCharsHandle@@YAPAVFontCharsClass@@PBDM_NH@Z
// partial score=0.99 date=2026-09-30
// cl: /O1 /G7 /arch:SSE /EHsc

// getFontCharsHandle, retail 0x0009017D (191 bytes).
// BFME2 find-or-create font-cache worker: scans the global FontCharsList for
// a FontCharsClass matching (name, float pointSize, bold, extra) through
// Is_Font, Add_Refs and returns the hit; on a miss it allocates a 0x464-byte
// FontCharsClass with the rowed operator new, runs the rowed default ctor,
// initializes it, Add_Refs it and appends it with a zero size hint.
// Donor is BFME1 WW3DAssetManager::Get_FontChars (assetmgr.cpp); BFME2 repairs
// are the float point size, the fourth detail argument and the two-argument
// vector Add. Is_Font, Initialize_GDI_Font, the default ctor and operator new
// are rows; the Add call needs this TU's own FontCharsClass-star alias pin at
// 0x0009014A (same 4-byte-element body as the rowed unsigned twin).
//
// SHAPE LAW (0.99 re-bank): the Add argument must be an RVALUE, written as the
// ternary `font ? font : (FontCharsClass *)0`. Passing the local `font`
// directly makes MSVC register a second exception object for the address-taken
// local (`push ecx` twice, 194B, font spilled to eax/[ebp-0x14]). The rvalue
// temporary removes that object and pins font in esi, giving the exact 191B
// and matching 0x9017D..0x90208. The one remaining wall is scheduler-only:
// retail stores the temporary to [ebp-0x10] at 0x90209 (inside the
// Initialize_GDI_Font argument push sequence) while this build stores it at
// 0x90225 (immediately before the Add call); every other byte is identical.
// Casts (`(FontCharsClass *)font`, `font + 0`, `0 + font`), a named temp, a
// function-scope local, an explicit operator new declaration and throw()
// specs on the ctor/callee were all tried and do not move the store.

class FontCharsClass
{
public:
	FontCharsClass();
	bool Is_Font(const char *fontName, float pointSize, bool isBold, int extra);
	void Initialize_GDI_Font(const char *fontName, float pointSize, bool isBold, int extra);
	void Add_Ref() { ++m_refCount; }

private:
	void *m_vtableSlot;       // +0x00
	int m_refCount;           // +0x04
	char m_pad[0x464 - 8];
};

template <class Type>
class SimpleDynVecClass
{
public:
	virtual ~SimpleDynVecClass();
	int Count() const { return m_activeCount; }
	Type &operator[](int index) { return m_vector[index]; }
	bool Add(const Type &object, int newSizeHint);

private:
	Type *m_vector;     // +0x04
	int m_vectorMax;    // +0x08
	int m_activeCount;  // +0x0C
};

extern SimpleDynVecClass<FontCharsClass *> FontCharsList;

// ?getFontCharsHandle@@YAPAVFontCharsClass@@PBDM_NH@Z @0x0009017D
FontCharsClass *getFontCharsHandle(const char *name, float pointSize, bool isBold, int extra)
{
	for (int i = 0; i < FontCharsList.Count(); i++) {
		if (FontCharsList[i]->Is_Font(name, pointSize, isBold, extra)) {
			FontCharsList[i]->Add_Ref();
			return FontCharsList[i];
		}
	}

	FontCharsClass *font = new FontCharsClass;
	font->Initialize_GDI_Font(name, pointSize, isBold, extra);
	font->Add_Ref();
	FontCharsList.Add(font ? font : (FontCharsClass *)0, 0);
	return font;
}
