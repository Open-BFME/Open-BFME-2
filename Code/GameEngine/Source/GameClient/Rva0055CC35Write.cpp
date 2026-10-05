// cl: /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva0055CC35@PointEmissionVolumeModuleTemplate@FXParticleSystem@@QAEXPAVFile@@I@Z at 0x0055CC35 size 186
// Evidence: chain via just-landed 0x003AFC6B; vslot 3 of PointEmissionVolumeModuleTemplate; calls rowed WriteHeader 0x0055CB5D then rowed bool-line 0x001F89C3 IsHollow then rowed str then rowed Write 0x001F458B then rowed 0x003AFC6B; member bool at +0xC.
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

void Rva0055CB5DWriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);
void Rva001F89C3Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	const char *key,
	const bool *value);

namespace FXParticleSystem {

class PointEmissionVolumeModuleTemplate {
public:
	void rva0055CC35(File *file, unsigned int flags);
private:
	char m_pad[12];
	bool m_isHollow;
};

void PointEmissionVolumeModuleTemplate::rva0055CC35(File *file, unsigned int flags)
{
	Rva0055CB5DWriteHeader(this, file, &flags);
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
	Rva001F89C3Write(oss, flags, "IsHollow", &m_isHollow);
	Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
	Rva003AFC6BWrite(file, &flags);
}

} // namespace FXParticleSystem
