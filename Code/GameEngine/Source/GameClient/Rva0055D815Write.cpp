// cl: /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva0055D815@CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@QAEXPAVFile@@I@Z at 0x0055D815 size 339
// Evidence: chain via 0x003A5D34; vslot 3 CylinderEmissionVolumeModuleTemplate; WriteHeader 0x0055CB5D then IsHollow 0x001F89C3 then IsZero-gated Radius RadiusRate Length floats 0x003A5D34 then IsZero-gated Offset Vec 0x001F89E2 then str Write 0x001F458B then 0x003AFC6B; bool at +0xC floats at +0x10/+0x14/+0x18 Vec at +0x1C.
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
void Rva003A5D34Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	float const &value);
int t4IsZero005F4180(const float *v);
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

class CylinderEmissionVolumeModuleTemplate {
public:
	void rva0055D815(File *file, unsigned int flags);
private:
	char m_pad[12];
	bool m_isHollow;
	char m_pad2[3];
	float m_radius;
	float m_radiusRate;
	float m_length;
	Vec001F8810 m_offset;
};

void CylinderEmissionVolumeModuleTemplate::rva0055D815(File *file, unsigned int flags)
{
	Rva0055CB5DWriteHeader(this, file, &flags);
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
	Rva001F89C3Write(oss, flags, "IsHollow", &m_isHollow);
	if (!(unsigned char)t4IsZero005F4180(&m_radius))
		Rva003A5D34Write(oss, flags, "Radius", m_radius);
	if (!(unsigned char)t4IsZero005F4180(&m_radiusRate))
		Rva003A5D34Write(oss, flags, "RadiusRate", m_radiusRate);
	if (!(unsigned char)t4IsZero005F4180(&m_length))
		Rva003A5D34Write(oss, flags, "Length", m_length);
	if (!(unsigned char)Rva0055CCEFIsZero(reinterpret_cast<const RGBColor &>(m_offset)))
		Rva001F89E2Write(oss, flags, "Offset", m_offset);
	Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
	Rva003AFC6BWrite(file, &flags);
}

} // namespace FXParticleSystem
