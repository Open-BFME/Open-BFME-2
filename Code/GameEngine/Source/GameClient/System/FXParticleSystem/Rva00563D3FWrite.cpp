// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva00563D3F@GpuDrawModuleTemplate@FXParticleSystem@@UAEXPAVFile@@I@Z @0x00563D3F 288B chain lane writeINI via WriteHeader
// Evidence: vslot 3 of GpuDrawModuleTemplate 0x0081C1F8; calls rowed WriteHeader 0x0055C9A0 then ostringstream then rowed Rva00563636Write 0x00563636 FramesPerRow TotalFrames then rowed isEmpty 0x00001E2F gated DetailTexture 0x001F82EE then rowed t4IsZero 0x0055D3D9 gated SpeedMultiplier 0x003A5D34 then rowed str 0x001FA473 plus Rva001F458BWrite 0x001F458B plus free 0x00030830 plus Rva003AFC6BWrite 0x003AFC6B; members +0xC +0x10 payload +0x14 AsciiString +0x18 float.
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
#include "ascii_string.h"

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

void Rva0055C9A0WriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);
struct Rva005635DEPayload {
	long value;
};
void Rva00563636Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const Rva005635DEPayload &value);
void Rva001F82EEWrite(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const AsciiString &value);
void Rva003A5D34Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	float const &value);
int t4IsZero005F4180(const float *v);

namespace FXParticleSystem {

class GpuDrawModuleTemplate {
public:
	virtual void rva00563D3F(File *file, unsigned int flags);
private:
	char m_pad04[12 - 4];
	Rva005635DEPayload m_framesPerRow;
	Rva005635DEPayload m_totalFrames;
	AsciiString m_detailTexture;
	float m_speedMultiplier;
};

void GpuDrawModuleTemplate::rva00563D3F(File *file, unsigned int flags)
{
	Rva0055C9A0WriteHeader(this, file, &flags);
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
	Rva00563636Write(oss, flags, "FramesPerRow", m_framesPerRow);
	Rva00563636Write(oss, flags, "TotalFrames", m_totalFrames);
	if (!m_detailTexture.isEmpty())
		Rva001F82EEWrite(oss, flags, "DetailTexture", m_detailTexture);
	if (!(unsigned char)t4IsZero005F4180(&m_speedMultiplier))
		Rva003A5D34Write(oss, flags, "SpeedMultiplier", m_speedMultiplier);
	Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
	Rva003AFC6BWrite(file, &flags);
}

} // namespace FXParticleSystem
