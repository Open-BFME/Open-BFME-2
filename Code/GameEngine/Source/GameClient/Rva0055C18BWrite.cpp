// cl: /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?Rva0055C18BWriteHeader@@YAXPBXPAVFile@@PAI@Z @0x0055C18B 216B: module header File INI key-string line via oss Pad str Write for category 0.
// Evidence: calls rowed oss ctor 0x001FA85C then virtual getClass name+4 then rowed GetKey 0x003AFD16 cat0 then rowed Pad 0x001F6951 then rowed _M_put_nowiden x3 then rowed _M_put_char then rowed str 0x001FA473 then rowed Write 0x001F458B then free 0x30830 then indent+=2 then rowed oss dtor and ios_base dtor; precedent Rva0055C9A0Write.cpp cat6; chain via 0x001F6951.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

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

void Rva0055C18BWriteHeader(const void *self, File *file, unsigned int *flags)
{
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
	const char *value = ((ModuleClassView *)((unsigned char *)self + 4))->getClass()->name;
	const char *key = FXParticleSystem::GetKey((FXParticleSystem::ModuleCategory)0);
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(oss, (unsigned int)*flags);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	r._M_put_nowiden(value);
	r._M_put_char('\n');
	Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
	*flags += 2;
}

// Retail 0x0055B65D/216: the same module-header writer for category 1.
// Its own +4 virtual class view, +4 name access, GetKey(1), stream calls,
// temporary string cleanup and indentation increment establish the behavior.
// WorldBuilder's corresponding body independently follows that same sequence;
// the original owning module type and method name remain unresolved.
void Rva0055B65DWriteHeader(const void *self, File *file, unsigned int *flags)
{
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
	const char *value = ((ModuleClassView *)((unsigned char *)self + 4))->getClass()->name;
	const char *key = FXParticleSystem::GetKey((FXParticleSystem::ModuleCategory)1);
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(oss, (unsigned int)*flags);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	r._M_put_nowiden(value);
	r._M_put_char('\n');
	Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
	*flags += 2;
}
