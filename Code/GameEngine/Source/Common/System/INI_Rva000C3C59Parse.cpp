// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC
// stlport
// ?Rva000C3C59Parse@INI@@SAXPAV1@PAX1PBX@Z @0x000C3C59 167B.
// INI parse building a stack BfmeNarrowRecord00079C23 via rowed ctor 0x797C4,
// filling text0 and text1 via rowed string assign 0x1B790 with empty literal
// fallback, word1 via rowed scanInt 0x2ECCF, then assigning through rowed
// operator= 0x7A22A into instance+0x8C and destroying via 0x79554.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <string>
#include <cstddef>
// bfme link decl-only begin
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

#include "../../../Include/Common/BfmeNarrowRecord00079C23.h"

#include "../../../Include/Common/INI/INI.h"

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
