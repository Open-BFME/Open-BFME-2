// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?Rva0055F290WriteHeader@@YAXPBXPAVFile@@PAI@Z, retail 0x0055F290, 216 bytes.
// Module header INI writer for category 3, same 216B shape as 0x0055E891 (cat 4)
// and 0x0055CB5D (cat 5): rowed oss ctor, virtual getClass name+4, rowed GetKey
// cat 3, rowed Pad, 3x rowed _M_put_nowiden, rowed _M_put_char, rowed str,
// rowed Rva001F458BWrite, free, indent+=2, rowed oss/ios_base dtors.
// Callers: writeINI body at 0x0055F368.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <sstream>
// basic_ostringstream<char>'s constructor is the rowed body 0x001FA85C
// (stlport_narrow_ostringstream_ctor.cpp). Declared here so this unit calls it
// instead of emitting its own constructor chain, whose _STLP_NO_EXCEPTIONS
// basic_streambuf<char> constructor is not retail's.
namespace _STL { template <> basic_ostringstream<char, char_traits<char>, allocator<char> >::basic_ostringstream(int); }
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_ostream<char, char_traits<char> >::basic_ostream(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> basic_ostream<char, char_traits<char> >::~basic_ostream(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> void basic_stringbuf<char, char_traits<char>, allocator<char> >::_M_append_buffer() const; }
namespace _STL { template <> void basic_ostream<char, char_traits<char> >::_M_put_char(char); }
namespace _STL { template <> void basic_ostream<char, char_traits<char> >::_M_put_nowiden(char const *); }
namespace _STL { template <> bool basic_ios<char, char_traits<char> >::_S_eof(int); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::append(unsigned int, char); }
namespace _STL { template <> void basic_ios<char, char_traits<char> >::clear(int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> locale basic_ios<char, char_traits<char> >::imbue(locale const &); }
namespace _STL { template <> void basic_ios<char, char_traits<char> >::init(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::push_back(char); }
namespace _STL { template <> basic_streambuf<char, char_traits<char> > * basic_ios<char, char_traits<char> >::rdbuf(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_ostringstream<char, char_traits<char>, allocator<char> >::str() const; }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_stringbuf<char, char_traits<char>, allocator<char> >::str() const; }
namespace _STL { template <> char basic_ios<char, char_traits<char> >::widen(char) const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$append@PBD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAEAAV01@PBD0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> template <> basic_string<char,char_traits<char>,allocator<char> > & basic_string<char,char_traits<char>,allocator<char> >::append<char const *>(char const *,char const *,forward_iterator_tag const &); }
// Suppress this TU's non-retail copy of ??1?$basic_ostringstream@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@UAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_ostringstream<char,char_traits<char>,allocator<char> >::~basic_ostringstream(); }
// Suppress this TU's non-retail copy of ?xsputn@?$basic_stringbuf@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@MAEHPBDH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> int basic_stringbuf<char,char_traits<char>,allocator<char> >::xsputn(char const *,int); }
// Suppress this TU's non-retail copy of ??$uninitialized_copy@PADPAD@_STL@@YAPADPAD00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * uninitialized_copy<char *,char *>(char *,char *,char *); }
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}

#include "../../Include/Common/File.h"
struct Rva001F458BText {
	const char *m_start;
	const char *m_finish;
};
File &Rva001F458BWrite(File &file, const Rva001F458BText &text);

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6951Pad(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os, unsigned int n);

namespace FXParticleSystem {
enum ModuleCategory {
	MODULE_CATEGORY_FIRST = 0
};
const char *GetKey(ModuleCategory category);
}

struct ModuleClassEntry {
	const char *key;
	const char *name;
};
class ModuleClassView {
public:
	virtual ModuleClassEntry *getClass() const;
};

void Rva0055F290WriteHeader(const void *self, File *file, unsigned int *flags)
{
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > stream(0x10);
	const char *name = ((const ModuleClassView *)((const char *)self + 4))->getClass()->name;
	const char *key = FXParticleSystem::GetKey((FXParticleSystem::ModuleCategory)3);
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(stream, *flags);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	r._M_put_nowiden(name);
	r._M_put_char('\n');
	Rva001F458BWrite(*file, reinterpret_cast<const Rva001F458BText &>(stream.str()));
	*flags += 2;
}
