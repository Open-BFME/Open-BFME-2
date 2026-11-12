// cl: /O1 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// ?writeINI@RenderObjectDrawModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
// @0x00563655 675B: the render-object draw module template's INI writer,
// slot 3 of vtables 0x0081C1C8 (RenderObjectDrawModuleTemplate) and
// 0x0081C270 (its ConcreteModuleTemplate). After the rowed draw header
// 0x0055C9A0 it writes MultiRenderObjects (+0x14), then for each of the three
// render groups (+0x18, stride 0x10) the group name unless empty, the object
// count (rowed 0x00563636), the percent unless zero (rowed test 0x0055D3D9)
// and the shader unless the default 8 (keyword table 0x00C1B610), then
// SinkOnTerrainCollision (+0x0C) and SinkRate (+0x10) unless zero. Built /O1
// like the wind writer; field names are the keys retail writes.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <sstream>
// basic_stringbuf<char>'s constructor is the rowed body 0x001F6813
// (stlport_narrow_ostringstream_dtor.cpp); declared so this unit does not emit
// its own constructor chain with a non-retail basic_streambuf<char> constructor.
namespace _STL { template <> basic_stringbuf<char, char_traits<char>, allocator<char> >::basic_stringbuf(int); }
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

void Rva0055C9A0WriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);
#include "../../../../Include/GameClient/Rva005635DEPayload.h"
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
void Rva001F82ABWrite(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	char const **value);
void Rva001F89C3Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	const char *key,
	const bool *value);
int t4IsZero005F4180(const float *v);

namespace FXParticleSystem {

extern const char *const ParticleShaderTypeNames[];

struct RenderObjectGroup {
	AsciiString m_renderGroup;
	Rva005635DEPayload m_numObjects;
	float m_percent;
	int m_shader;
};

class RenderObjectDrawModuleTemplate {
public:
	virtual void writeINI(File &file, unsigned int flags) const;

private:
	void *m_moduleClassView;
	void *m_moduleInfoView;
	bool m_sinkOnTerrainCollision;			// 0x0C
	float m_sinkRate;						// 0x10
	bool m_multiRenderObjects;				// 0x14
	RenderObjectGroup m_groups[3];			// 0x18
};

void RenderObjectDrawModuleTemplate::writeINI(File &file, unsigned int flags) const
{
	Rva0055C9A0WriteHeader(this, &file, &flags);
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
	Rva001F89C3Write(oss, flags, "MultiRenderObjects", &m_multiRenderObjects);
	if (!m_groups[0].m_renderGroup.isEmpty())
		Rva001F82EEWrite(oss, flags, "RenderGroup1", m_groups[0].m_renderGroup);
	Rva00563636Write(oss, flags, "NumObjects1", m_groups[0].m_numObjects);
	if (!(unsigned char)t4IsZero005F4180(&m_groups[0].m_percent))
		Rva003A5D34Write(oss, flags, "Percent1", m_groups[0].m_percent);
	if (m_groups[0].m_shader != 8)
		Rva001F82ABWrite(oss, flags, "Shader1", const_cast<const char **>(&ParticleShaderTypeNames[m_groups[0].m_shader]));
	if (!m_groups[1].m_renderGroup.isEmpty())
		Rva001F82EEWrite(oss, flags, "RenderGroup2", m_groups[1].m_renderGroup);
	Rva00563636Write(oss, flags, "NumObjects2", m_groups[1].m_numObjects);
	if (!(unsigned char)t4IsZero005F4180(&m_groups[1].m_percent))
		Rva003A5D34Write(oss, flags, "Percent2", m_groups[1].m_percent);
	if (m_groups[1].m_shader != 8)
		Rva001F82ABWrite(oss, flags, "Shader2", const_cast<const char **>(&ParticleShaderTypeNames[m_groups[1].m_shader]));
	if (!m_groups[2].m_renderGroup.isEmpty())
		Rva001F82EEWrite(oss, flags, "RenderGroup3", m_groups[2].m_renderGroup);
	Rva00563636Write(oss, flags, "NumObjects3", m_groups[2].m_numObjects);
	if (!(unsigned char)t4IsZero005F4180(&m_groups[2].m_percent))
		Rva003A5D34Write(oss, flags, "Percent3", m_groups[2].m_percent);
	if (m_groups[2].m_shader != 8)
		Rva001F82ABWrite(oss, flags, "Shader3", const_cast<const char **>(&ParticleShaderTypeNames[m_groups[2].m_shader]));
	Rva001F89C3Write(oss, flags, "SinkOnTerrainCollision", &m_sinkOnTerrainCollision);
	if (!(unsigned char)t4IsZero005F4180(&m_sinkRate))
		Rva003A5D34Write(oss, flags, "SinkRate", m_sinkRate);
	Rva001F458BWrite(file, (const Rva001F458BText &)oss.str());
	Rva003AFC6BWrite(&file, &flags);
}

} // namespace FXParticleSystem
