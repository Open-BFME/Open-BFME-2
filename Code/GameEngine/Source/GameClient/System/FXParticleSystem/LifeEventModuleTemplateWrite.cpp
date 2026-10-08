// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// BFME 2 export 0x0056435C identifies LifeEventModuleTemplate::writeINI.
// Native 258B boundary and calls establish EventTime +0x14, EventFX +0x10,
// PerParticle +8 and KillAfterEvent +9. BFME 1 ba7ddda7e8f26116 bulk source
// carries the same write order and semantics; the verified BFME 2 terrain
// sibling supplies the target stream configuration and helper declarations.
// Use the existing byte-verified STLport max<unsigned> provider at 0x13740.
// A declaration avoids emitting another library copy or changing optimization
// state around a header inline.
#include <stl/_algobase.h>
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b);
}

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

void Rva00564284WriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);

struct S001F87D5 {
	char _0[4];
	float x;
	float y;
};

void Rva001F8B5FWrite(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const S001F87D5 &value);
void Rva001F82EEWrite(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	const AsciiString &value);
void Rva001F8384Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	bool const *value);

namespace FXParticleSystem {

class LifeEventModuleTemplate {
public:
	virtual void writeINI(File &file, unsigned int flags) const;
private:
	char m_pad4[4]; // Primary vptr plus opaque secondary prefix: flags at +8.
	bool m_perParticle;
	bool m_killAfterEvent;
	char m_padA[6];
	AsciiString m_eventFX;
	S001F87D5 m_eventTime;
	
};

void LifeEventModuleTemplate::writeINI(File &file, unsigned int flags) const
{
	Rva00564284WriteHeader(this, &file, &flags);
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
	Rva001F8B5FWrite(oss, flags, "EventTime", m_eventTime);
	Rva001F82EEWrite(oss, flags, "EventFX", m_eventFX);
	Rva001F8384Write(oss, flags, "PerParticle", &m_perParticle);
	Rva001F8384Write(oss, flags, "KillAfterEvent", &m_killAfterEvent);
	Rva001F458BWrite(file, (const Rva001F458BText &)oss.str());
	Rva003AFC6BWrite(&file, &flags);
}

} // namespace FXParticleSystem
