// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?Rva0055E891WriteVelocityHeader@@YAXPBXPAVFile@@PAI@Z @0x0055E891 216B. Velocity-template INI header writer.
// Evidence: BFME1 donor Rva005F8FC0WriteVelocityHeader.cpp category 4; retail push 4 to rowed GetKey; rowed Pad then 3x rowed _M_put_nowiden then rowed _M_put_char then rowed str then rowed Rva001F458BWrite then *flags+=2; callers are writeINI bodies.
// Honest Rva name; /O1 for and/or/push idioms; /EHsc for ostringstream+string unwind; bfmealloc for _free dealloc.
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

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6951Pad(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os, unsigned int n);

namespace FXParticleSystem {
enum ModuleCategory {
	MODULE_CATEGORY_VELOCITY = 4
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

void Rva0055E891WriteVelocityHeader(const void *self, File *file, unsigned int *flags)
{
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > stream(0x10);
	const char *name = ((const ModuleClassView *)((const char *)self + 4))->getClass()->name;
	const char *key = FXParticleSystem::GetKey(FXParticleSystem::MODULE_CATEGORY_VELOCITY);
	_STL::basic_ostream<char, _STL::char_traits<char> > &r = Rva001F6951Pad(stream, *flags);
	r._M_put_nowiden(key);
	r._M_put_nowiden(" = ");
	r._M_put_nowiden(name);
	r._M_put_char('\n');
	Rva001F458BWrite(*file, reinterpret_cast<const Rva001F458BText &>(stream.str()));
	*flags += 2;
}
