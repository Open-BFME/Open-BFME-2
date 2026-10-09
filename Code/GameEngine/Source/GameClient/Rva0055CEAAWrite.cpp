// cl: /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva0055CEAA@LineEmissionVolumeModuleTemplate@FXParticleSystem@@UAEXPAVFile@@I@Z at 0x0055CEAA size 263
// Evidence: chain via 0x003AFC6B; vslot 3 of LineEmissionVolumeModuleTemplate; WriteHeader 0x0055CB5D then bool IsHollow 0x001F89C3 then IsZero-gated StartPoint/EndPoint Vec writes 0x001F89E2 then str Write 0x001F458B then 0x003AFC6B; bool at +0xC Vecs at +0x10/+0x1C.
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
struct Vec001F8810 {
	float x;
	float y;
	float z;
};
struct RGBColor {
	float red;
	float green;
	float blue;
};
int Rva0055CCEFIsZero(const RGBColor &color);
void Rva001F89E2Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const Vec001F8810 &value);

namespace FXParticleSystem {

class LineEmissionVolumeModuleTemplate {
public:
	virtual void rva0055CEAA(File *file, unsigned int flags);
private:
	char m_pad04[12 - 4];
	bool m_isHollow;
	char m_pad2[3];
	Vec001F8810 m_startPoint;
	Vec001F8810 m_endPoint;
};

void LineEmissionVolumeModuleTemplate::rva0055CEAA(File *file, unsigned int flags)
{
	Rva0055CB5DWriteHeader(this, file, &flags);
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
	Rva001F89C3Write(oss, flags, "IsHollow", &m_isHollow);
	if (!(unsigned char)Rva0055CCEFIsZero(reinterpret_cast<const RGBColor &>(m_startPoint)))
		Rva001F89E2Write(oss, flags, "StartPoint", m_startPoint);
	if (!(unsigned char)Rva0055CCEFIsZero(reinterpret_cast<const RGBColor &>(m_endPoint)))
		Rva001F89E2Write(oss, flags, "EndPoint", m_endPoint);
	Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
	Rva003AFC6BWrite(file, &flags);
}

} // namespace FXParticleSystem
