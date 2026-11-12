// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
// ?Rva000C4BAEParse@@YAXPAVINI@@PAX1PBX@Z @0x000C4BAE 197B
// Retail INI parse reached via table slot 0x7CB4DC beside TimeOfDayTexture.
// Builds stack BfmeNarrowRecord00079C23 via rowed ctor 0x797C4; text0 via rowed
// string assign 0x1B790 with empty literal fallback; word0 via rowed scanIndexList
// 0x2BD39 with TimeOfDayNames; word1 via rowed scanInt 0x2ECCF; text1 via the same
// string assign; push_back via rowed 0xC46FC into instance+0x70; destroys via
// pinned dtor 0x79554. Evidence: all callees rowed or pinned; REF TimeOfDayTexture;
// record ints at +0x24 +0x28 match Bfme 0x2C layout.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <string>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::~basic_string(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(char const *); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::assign(char const *, char const *); }
namespace _STL { template <> char * __char_traits_base<char, int>::copy(char *, char const *, unsigned int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

#include "../../../Include/Common/INI/INI.h"

#include "../../../Include/Common/BfmeNarrowRecord00079C23.h"

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
