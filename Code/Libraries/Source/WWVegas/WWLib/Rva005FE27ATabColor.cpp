// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva005FE27A@Rva005FE750@@QAEXHHHABVUnicodeString@@@Z @0x005FE27A 249B: Rva005FE750 tab color update.
// Kept apart from Rva005FE750.cpp, whose declared-only vector specialization (for
// linking) cannot express the STLport subscript this body's codegen needs. The
// subscript is spelled as STLport's *(begin() + n) through a helper of its own,
// so this unit odr-uses no vector member (other units emit those under other
// flags, which tools/link_check.py refuses as a second copy).
// Evidence: prev 0x005FE589 and next 0x005FE835 same vector family same flags; callees rowed vector 0x005FE4A3 Rva 0x005242D7 Rva 0x0052413E releaseBuffer 0x00036410; vtable 0x0087A3F4.

#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"

struct BfmeContainerRecord005FDEC7
{
	unsigned int word0;
	unsigned int word1;
	UnicodeString text;
};

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};

class Rva005242D7
{
public:
	~Rva005242D7();
private:
	char m_pad[12];
};

class Image;

class Rva00524306
{
public:
	void rva00524306(const StringBase<char> &val);
	void rva00524725(const AsciiString &key, const Image *image);
};

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
int __cdecl Rva00525235Fire(void *a1, void *a2, const char *a3, const char *a4, int *a5, int *a6);
struct Rva005FDF1COuter;
void __cdecl Rva005FDF1CSet(int level, Rva005FDF1COuter *outer, const UnicodeString &text);

__forceinline const char *GetStr005FE27A(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : "";
}

class Rva005FE750
{
public:
	virtual ~Rva005FE750();
	void rva005FE27A(int idx, int w0, int w1, const UnicodeString &text);
private:
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0C;
	Rva005242D7 m_18;
	int m_24;
	_STL::vector<BfmeContainerRecord005FDEC7, _STL::allocator<BfmeContainerRecord005FDEC7> > m_28;
};


__forceinline BfmeContainerRecord005FDEC7 *Start005FE27A(
	const _STL::vector<BfmeContainerRecord005FDEC7, _STL::allocator<BfmeContainerRecord005FDEC7> > &v)
{
	return *(BfmeContainerRecord005FDEC7 *const *)&v;
}

void Rva005FE750::rva005FE27A(int idx, int w0, int w1, const UnicodeString &text)
{
	BfmeContainerRecord005FDEC7 &rec = *(Start005FE27A(m_28) + idx);
	if (w0 != rec.word0)
	{
		AsciiString key;
		const char *mid = GetStr005FE27A(m_08);
		key.format("_level%u.%s_Image%d", m_04, mid, idx);
		if (w0)
			((Rva00524306 *)&m_18)->rva00524725(key, (const Image *)w0);
		else
			((Rva00524306 *)&m_18)->rva00524306(*(const StringBase<char> *)&key);
		rec.word0 = (unsigned int)w0;
	}
	if (w1 != rec.word1)
	{
		int savedW1 = w1;
		const char *mid2 = GetStr005FE27A(m_08);
		Rva00525235Fire(TheRva00222A8BTarget, (void *)m_04, mid2, "SetTabColor", &idx, &w1);
		rec.word1 = (unsigned int)savedW1;
	}
	if (text.compare(rec.text) != 0)
	{
		if (idx == m_24)
			Rva005FDF1CSet(m_04, (Rva005FDF1COuter *)&m_08, text);
		rec.text.set(text);
	}
}
