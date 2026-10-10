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

struct BfmePod4 { int a[1]; };

template <class T> class SimpleVecClass
{
public:
	virtual ~SimpleVecClass();
	T *Vector;
	int VectorMax;
};

template <class T> class SimpleDynVecClass : public SimpleVecClass<T>
{
public:
	int ActiveCount;
	friend class W3DFontLibrary;
protected:
	bool Shrink();
};

class FontLibrary
{
public:
	virtual ~FontLibrary();
};

extern unsigned int g_Va00DE2084;

class W3DFontLibrary : public FontLibrary
{
public:
	virtual ~W3DFontLibrary();
};

W3DFontLibrary::~W3DFontLibrary()
{
	SimpleDynVecClass<BfmePod4> *fonts = (SimpleDynVecClass<BfmePod4> *)&g_Va00DE2084;
	for (int i = 0; i < fonts->ActiveCount; ++i)
	{
		RefCountedFont *font = (RefCountedFont *)fonts->Vector[i].a[0];
		if (--font->NumRefs == 0)
			font->Delete_This();
	}
	fonts->ActiveCount = 0;
	fonts->Shrink();
}
