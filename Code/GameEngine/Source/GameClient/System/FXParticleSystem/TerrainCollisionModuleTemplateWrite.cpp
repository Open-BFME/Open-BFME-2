// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// ?rva0056499B@TerrainCollisionModuleTemplate@FXParticleSystem@@UAEXPAVFile@@I@Z @0x0056499B 285B chain lane writeINI.
// Evidence: vslot 3 of TerrainCollisionModuleTemplate; calls rowed WriteHeader 0x00564284 then ostringstream then HeightOffset 0x001F8B5F EventFX 0x001F82EE Orient/PerParticle/Kill 0x001F8384 then str/Write/free then footer 0x003AFC6B; members +0x8 +0x9 +0x10 AsciiString +0x14 S001F87D5 +0x20.
// Pattern from GpuDrawModuleTemplate::rva00563D3F 0x00563D3F.
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
// basic_ostringstream<char>'s constructor is the rowed body 0x001FA85C
// (stlport_narrow_ostringstream_ctor.cpp). Declared here so this unit calls it
// instead of emitting its own constructor chain, whose _STLP_NO_EXCEPTIONS
// basic_streambuf<char> constructor is not retail's.
namespace _STL { template <> basic_ostringstream<char, char_traits<char>, allocator<char> >::basic_ostringstream(int); }
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_ostream<char, char_traits<char> >::basic_ostream(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> basic_ostream<char, char_traits<char> >::~basic_ostream(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> void basic_stringbuf<char, char_traits<char>, allocator<char> >::_M_append_buffer() const; }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::append(unsigned int, char); }
namespace _STL { template <> void basic_ios<char, char_traits<char> >::clear(int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> locale basic_ios<char, char_traits<char> >::imbue(locale const &); }
namespace _STL { template <> void basic_ios<char, char_traits<char> >::init(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::push_back(char); }
namespace _STL { template <> basic_streambuf<char, char_traits<char> > * basic_ios<char, char_traits<char> >::rdbuf(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_ostringstream<char, char_traits<char>, allocator<char> >::str() const; }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_stringbuf<char, char_traits<char>, allocator<char> >::str() const; }
namespace _STL { template <> char basic_ios<char, char_traits<char> >::widen(char) const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$append@PBD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAEAAV01@PBD0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> template <> basic_string<char,char_traits<char>,allocator<char> > & basic_string<char,char_traits<char>,allocator<char> >::append<char const *>(char const *,char const *,forward_iterator_tag const &); }
// Suppress this TU's non-retail copy of ??1?$basic_ostringstream@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@UAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_ostringstream<char,char_traits<char>,allocator<char> >::~basic_ostringstream(); }
// Suppress this TU's non-retail copy of ?xsputn@?$basic_stringbuf@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@MAEHPBDH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> int basic_stringbuf<char,char_traits<char>,allocator<char> >::xsputn(char const *,int); }
// Suppress this TU's non-retail copy of ??$uninitialized_copy@PADPAD@_STL@@YAPADPAD00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * uninitialized_copy<char *,char *>(char *,char *,char *); }
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}

#include "../../../../Include/Common/File.h"
#include "../../../../Include/GameClient/Rva001F458BText.h"
File &Rva001F458BWrite(File &file, const Rva001F458BText &text);
#include <stdlib.h>

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
	virtual void rva0056499B(File *file, unsigned int flags);
private:
	char m_pad04[8 - 4];
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
