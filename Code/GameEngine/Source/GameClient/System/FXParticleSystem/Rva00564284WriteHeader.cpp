// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?Rva00564284WriteHeader@@YAXPBXPAVFile@@PAI@Z, retail 0x00564284, 216 bytes.
// Header writer: Pad(stream,*flags) then key + " = " + class name + newline then Write + *flags+=2.
// Evidence: push 8 to rowed GetKey@FXParticleSystem; self+4 virtual getClass()->name at [eax+4]; rowed Pad/Put/str/Rva001F458BWrite/_free; callers writeINI at 0x00564377/0x005649B6; same 216B shape as ?Rva0055E891WriteVelocityHeader@@YAXPBXPAVFile@@PAI@Z.
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
	MODULE_CATEGORY_8 = 8
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

void Rva00564284WriteHeader(const void *self, File *file, unsigned int *flags)
{
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > stream(0x10);
	const char *name = ((const ModuleClassView *)((const char *)self + 4))->getClass()->name;
	const char *key = FXParticleSystem::GetKey(FXParticleSystem::MODULE_CATEGORY_8);
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(stream, *flags);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	r._M_put_nowiden(name);
	r._M_put_char('\n');
	Rva001F458BWrite(*file, reinterpret_cast<const Rva001F458BText &>(stream.str()));
	*flags += 2;
}
