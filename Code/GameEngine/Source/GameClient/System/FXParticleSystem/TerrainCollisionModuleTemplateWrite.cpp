// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva0056499B@TerrainCollisionModuleTemplate@FXParticleSystem@@QAEXPAVFile@@I@Z @0x0056499B 285B chain lane writeINI.
// Evidence: vslot 3 of TerrainCollisionModuleTemplate; calls rowed WriteHeader 0x00564284 then ostringstream then HeightOffset 0x001F8B5F EventFX 0x001F82EE Orient/PerParticle/Kill 0x001F8384 then str/Write/free then footer 0x003AFC6B; members +0x8 +0x9 +0x10 AsciiString +0x14 S001F87D5 +0x20.
// Pattern from GpuDrawModuleTemplate::rva00563D3F 0x00563D3F.
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

// Target identity: exported LifeEvent ModuleTemplate vtable RVA 0x81C198
// points to retail 0x56435C in slot 3. BFME 1 ba7ddda7e8's
// fx_particle_system_bulk.cpp LifeEventModuleTemplate::writeINI supplies the
// purpose and field order; the BFME 2 accesses independently prove the offsets.
// The first eight bytes hold the two category-interface vptrs. The info
// subobject starts at +0xC; its event name and random variable are at +0x10/+0x14.
class LifeEventModuleTemplate {
public:
	virtual ~LifeEventModuleTemplate();
	virtual void moduleSlot1();
	virtual void moduleSlot2();
	virtual void writeINI(File &file, unsigned int flags) const;
private:
	char m_pad4[4];
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

class TerrainCollisionModuleTemplate {
public:
	void rva0056499B(File *file, unsigned int flags);
private:
	char m_pad0[8];
	bool m_perParticle;
	bool m_killAfterEvent;
	char m_padA[6];
	AsciiString m_eventFX;
	S001F87D5 m_heightOffset;
	bool m_orientFXToTerrain;
};

void TerrainCollisionModuleTemplate::rva0056499B(File *file, unsigned int flags)
{
	Rva00564284WriteHeader(this, file, &flags);
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
	Rva001F8B5FWrite(oss, flags, "HeightOffset", m_heightOffset);
	Rva001F82EEWrite(oss, flags, "EventFX", m_eventFX);
	Rva001F8384Write(oss, flags, "OrientFXToTerrain", &m_orientFXToTerrain);
	Rva001F8384Write(oss, flags, "PerParticle", &m_perParticle);
	Rva001F8384Write(oss, flags, "KillAfterEvent", &m_killAfterEvent);
	Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
	Rva003AFC6BWrite(file, &flags);
}

} // namespace FXParticleSystem
