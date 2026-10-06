// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?Rva0055FA5FWriteHeader@@YAXPBXPAVFile@@PAI@Z, retail 0x0055FA5F, 216 bytes.
// Module header INI writer for category 2, same 216B shape as 0x0055E891 (cat 4)
// 0x0055CB5D (cat 5) and 0x0055F290 (cat 3): rowed oss ctor, virtual getClass
// name+4, rowed GetKey cat 2, rowed Pad, 3x rowed _M_put_nowiden, rowed
// _M_put_char, rowed str, rowed Rva001F458BWrite, free, indent+=2.
// Callers: writeINI bodies at 0x0055FB53 and 0x005625E1.
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

void Rva0055FA5FWriteHeader(const void *self, File *file, unsigned int *flags)
{
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > stream(0x10);
	const char *name = ((const ModuleClassView *)((const char *)self + 4))->getClass()->name;
	const char *key = FXParticleSystem::GetKey((FXParticleSystem::ModuleCategory)2);
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(stream, *flags);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	r._M_put_nowiden(name);
	r._M_put_char('\n');
	Rva001F458BWrite(*file, reinterpret_cast<const Rva001F458BText &>(stream.str()));
	*flags += 2;
}
