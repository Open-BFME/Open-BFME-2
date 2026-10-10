// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC
// stlport
// ?Rva000C3C59Parse@INI@@SAXPAV1@PAX1PBX@Z @0x000C3C59 167B.
// INI parse building a stack BfmeNarrowRecord00079C23 via rowed ctor 0x797C4,
// filling text0 and text1 via rowed string assign 0x1B790 with empty literal
// fallback, word1 via rowed scanInt 0x2ECCF, then assigning through rowed
// operator= 0x7A22A into instance+0x8C and destroying via 0x79554.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <string>

struct BfmeNarrowRecord00079C23
{
	BfmeNarrowRecord00079C23();
	~BfmeNarrowRecord00079C23();
	BfmeNarrowRecord00079C23 &operator=(const BfmeNarrowRecord00079C23 &o);
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > text0;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > text1;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > text2;
	unsigned int word0;
	unsigned int word1;
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	int scanInt(const char *token);
	static void Rva000C3C59Parse(INI *ini, void *instance, void *store, const void *userData);
};

void INI::Rva000C3C59Parse(INI *ini, void *instance, void *store, const void *userData)
{
	if (!instance)
		return;
	BfmeNarrowRecord00079C23 record;
	const char *tok0 = ini->getNextTokenOrNull(0);
	if (tok0)
		record.text0 = tok0;
	else
		record.text0 = "";
	const char *tok1 = ini->getNextTokenOrNull(0);
	record.word1 = tok1 ? (unsigned int)ini->scanInt(tok1) : 0;
	const char *tok2 = ini->getNextTokenOrNull(0);
	if (tok2)
		record.text1 = tok2;
	else
		record.text1 = "";
	*(BfmeNarrowRecord00079C23 *)((char *)instance + 0x8c) = record;
}
