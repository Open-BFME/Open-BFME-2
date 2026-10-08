// cl: /O1 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
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

extern const char *RenderObjectShaderNames[];

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
		Rva001F82ABWrite(oss, flags, "Shader1", &RenderObjectShaderNames[m_groups[0].m_shader]);
	if (!m_groups[1].m_renderGroup.isEmpty())
		Rva001F82EEWrite(oss, flags, "RenderGroup2", m_groups[1].m_renderGroup);
	Rva00563636Write(oss, flags, "NumObjects2", m_groups[1].m_numObjects);
	if (!(unsigned char)t4IsZero005F4180(&m_groups[1].m_percent))
		Rva003A5D34Write(oss, flags, "Percent2", m_groups[1].m_percent);
	if (m_groups[1].m_shader != 8)
		Rva001F82ABWrite(oss, flags, "Shader2", &RenderObjectShaderNames[m_groups[1].m_shader]);
	if (!m_groups[2].m_renderGroup.isEmpty())
		Rva001F82EEWrite(oss, flags, "RenderGroup3", m_groups[2].m_renderGroup);
	Rva00563636Write(oss, flags, "NumObjects3", m_groups[2].m_numObjects);
	if (!(unsigned char)t4IsZero005F4180(&m_groups[2].m_percent))
		Rva003A5D34Write(oss, flags, "Percent3", m_groups[2].m_percent);
	if (m_groups[2].m_shader != 8)
		Rva001F82ABWrite(oss, flags, "Shader3", &RenderObjectShaderNames[m_groups[2].m_shader]);
	Rva001F89C3Write(oss, flags, "SinkOnTerrainCollision", &m_sinkOnTerrainCollision);
	if (!(unsigned char)t4IsZero005F4180(&m_sinkRate))
		Rva003A5D34Write(oss, flags, "SinkRate", m_sinkRate);
	Rva001F458BWrite(file, (const Rva001F458BText &)oss.str());
	Rva003AFC6BWrite(&file, &flags);
}

} // namespace FXParticleSystem
