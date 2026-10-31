// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??1W3DFontLibrary@@UAE@XZ, retail 0x0009023C..0x000902A6 (106 bytes, EH);
// pinned until now as the opaque ??1Rva0009023C@@UAE@XZ. The W3D font library's
// destructor (vtable 0x00BC4818, beside releaseFontData 0x00090000 and
// loadFontData 0x000902A6 of W3DFontLibraryLoadFontData.cpp): it releases the
// reference every font recorded in the library's static font list holds
// (0x00DE2084, a dynamic vector of reference-counted fonts), empties and
// shrinks the list, and runs FontLibrary's destructor. WW3D has no source
// donor for this body; the shape is read from the retail loop.
class RefCountedFont
{
public:
	virtual void Delete_This();
	int NumRefs;
};

struct BfmePod4
{
public:
	int a[1]; // +0x00
};

#include "../../../../../Libraries/Source/WWVegas/WWLib/simplevec.h"
// The real header keeps Shrink protected; expose it for the destructor body.
class BfmePod4FontListAccess : public SimpleDynVecClass<BfmePod4>
{
public:
	using SimpleDynVecClass<BfmePod4>::Shrink;
	using SimpleDynVecClass<BfmePod4>::ActiveCount;
	using SimpleVecClass<BfmePod4>::Vector;
};

class FontLibrary
{
public:
	virtual ~FontLibrary();
};

// The cache worker owns this sixteen-byte object at VA 0x00DE2084.
class FontCharsClass;
extern SimpleDynVecClass<FontCharsClass *> BfmeFontCharsCache;

class W3DFontLibrary : public FontLibrary
{
public:
	virtual ~W3DFontLibrary();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline W3DFontLibrary::~W3DFontLibrary()
{
	BfmePod4FontListAccess *fonts = (BfmePod4FontListAccess *)&BfmeFontCharsCache;
	for (int i = 0; i < fonts->ActiveCount; ++i)
	{
		RefCountedFont *font = (RefCountedFont *)fonts->Vector[i].a[0];
		if (--font->NumRefs == 0)
			font->Delete_This();
	}
	fonts->ActiveCount = 0;
	fonts->Shrink();
}

// ?bfmeAnchorW3DFontLibraryDtor absent-from-retail
void bfmeAnchorW3DFontLibraryDtor(W3DFontLibrary *w3DFontLibrary)
{
	w3DFontLibrary->W3DFontLibrary::~W3DFontLibrary();
}
