// cl: /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?Rva0055CB5DWriteHeader@@YAXPBXPAVFile@@PAI@Z @0x0055CB5D 216B: module header File INI key-string line via oss Pad str Write for category 5.
// Evidence: calls rowed oss ctor 0x001FA85C then virtual getClass name+4 then rowed GetKey 0x003AFD16 cat5 then rowed Pad 0x001F6951 then rowed _M_put_nowiden x3 then rowed _M_put_char then rowed str 0x001FA473 then rowed Write 0x001F458B then free 0x30830 then indent+=2 then rowed oss dtor and ios_base dtor; precedent Rva0055C9A0Write.cpp cat6; chain via 0x001F6951.
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

class File {
public:
	virtual ~File();
	virtual bool open(const char *n, int a = 0);
	virtual void close();
	virtual int read(void *b, int bsz);
	virtual int write(const void *b, int bsz);
};
struct Rva001F458BText {
	const char *m_start;
	const char *m_finish;
};
File &Rva001F458BWrite(File &file, const Rva001F458BText &text);
extern "C" void __cdecl free(void *p);

namespace FXParticleSystem {
enum ModuleCategory {
	MODULE_CATEGORY_FIRST
};
const char *GetKey(ModuleCategory c);
}

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6951Pad(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int n);

struct ModuleClassEntry {
	const char *key;
	const char *name;
};

class ModuleClassView {
public:
	virtual ModuleClassEntry *getClass() const;
};

void Rva0055CB5DWriteHeader(const void *self, File *file, unsigned int *flags)
{
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
	const char *value = ((ModuleClassView *)((unsigned char *)self + 4))->getClass()->name;
	const char *key = FXParticleSystem::GetKey((FXParticleSystem::ModuleCategory)5);
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(oss, (unsigned int)*flags);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	r._M_put_nowiden(value);
	r._M_put_char('\n');
	Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
	*flags += 2;
}
