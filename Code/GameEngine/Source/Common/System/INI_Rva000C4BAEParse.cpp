// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva000C4BAEParse@@YAXPAVINI@@PAX1PBX@Z @0x000C4BAE 197B
// Retail INI parse reached via table slot 0x7CB4DC beside TimeOfDayTexture.
// Builds stack BfmeNarrowRecord00079C23 via rowed ctor 0x797C4; text0 via rowed
// string assign 0x1B790 with empty literal fallback; word0 via rowed scanIndexList
// 0x2BD39 with TimeOfDayNames; word1 via rowed scanInt 0x2ECCF; text1 via the same
// string assign; push_back via rowed 0xC46FC into instance+0x70; destroys via
// pinned dtor 0x79554. Evidence: all callees rowed or pinned; REF TimeOfDayTexture;
// record ints at +0x24 +0x28 match Bfme 0x2C layout.
#include <vector>
#include <string>

typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	int scanIndexList(const char *token, ConstCharPtrArray nameList);
	int scanInt(const char *token);
};

struct BfmeNarrowRecord00079C23
{
	BfmeNarrowRecord00079C23();
	~BfmeNarrowRecord00079C23();
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > text0;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > text1;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > text2;
	unsigned int word0;
	unsigned int word1;
};

extern char *TimeOfDayNames[];

void __cdecl Rva000C4BAEParse(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
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
	record.word0 = tok1 ? (unsigned int)ini->scanIndexList(tok1, (ConstCharPtrArray)TimeOfDayNames) : 0;
	const char *tok2 = ini->getNextTokenOrNull(0);
	record.word1 = tok2 ? (unsigned int)ini->scanInt(tok2) : 0;
	const char *tok3 = ini->getNextTokenOrNull(0);
	if (tok3)
		record.text1 = tok3;
	else
		record.text1 = "";
	((_STL::vector<BfmeNarrowRecord00079C23, _STL::allocator<BfmeNarrowRecord00079C23> > *)((char *)instance + 0x70))->push_back(record);
}
