// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva00381C82AddChatText@@YAXHABVUnicodeString@@H@Z, retail 0x00381C82, 107 bytes.
// Chat helper: builds a BfmeStringRecord005DDD40 (text via StringBase set, word
// = color) inlines default ctor zeroing, pushes it into g_00E022F8[window]
// (12-byte vectors, imul 12 needs /G7) then notifies g_00E02310 list via
// forEach 0x0038188B with forwarder 0x001FF3A9. Evidence: callers at
// 0x002494C1/0x002494E5/0x0024950A in LANAPIOnGameCreate.cpp which declares
// Rva00381C82AddChatText(Int, UnicodeString, Color); vector array
// g_00E022F8[2] from stlport_vector_stringrecord_5ddd40_clear.cpp;
// forEach pattern and forwarder cast from Rva0053947DDtor.cpp/Rva005DC3C1.cpp.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "unicode_string.h"
#include <vector>

struct BfmeStringRecord005DDD40 {
	UnicodeString text;
	unsigned int word;
	BfmeStringRecord005DDD40() : word(0) {}
};

extern _STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > g_00E022F8[2];

class Rva0038188BListener
{
public:
	virtual void notify(void *, int);
};

class Rva0038188BList
{
public:
	void forEach(void (Rva0038188BListener::*notify)(void *, int), void *arg, int value);
private:
	Rva0038188BListener **m_begin;
	Rva0038188BListener **m_end;
	Rva0038188BListener **m_capacity;
	unsigned int m_index;
};

extern Rva0038188BList g_00E02310;

class Rva001FF3A9
{
public:
	virtual void rva001FF3A9();
};

void Rva00381C82AddChatText(int window, const UnicodeString &text, int color)
{
	BfmeStringRecord005DDD40 rec;
	rec.text.set(text);
	rec.word = (unsigned int)color;
	g_00E022F8[window].push_back(rec);
	g_00E02310.forEach((void (Rva0038188BListener::*)(void *, int))&Rva001FF3A9::rva001FF3A9, (void *)window, (int)&rec);
}
