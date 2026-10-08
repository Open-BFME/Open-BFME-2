// cl: /O1 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// The wind (category 7) particle module template's INI writer; see the
// comment on the body. Same writer-helper views as
// TerrainCollisionModuleTemplateWrite.cpp, built /O1 /arch:SSE as retail is.
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

void Rva003A5DA0WriteWindHeader(const void *self, File *file, unsigned int *flags);
void Rva001F82ABWrite(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	char const **value);
void Rva003A5D34Write(
	_STL::basic_ostream<char, _STL::char_traits<char> > &os,
	unsigned int pad,
	char const *key,
	float const &value);

namespace FXParticleSystem {

// ?writeINI@?$DefaultModuleTemplate@$06@FXParticleSystem@@UBEXAAVFile@@I@Z
// @0x003A5E78 675B: the category-7 (wind) module template's writeINI, slot 3
// of vtables 0x0081BFA4/0x0081BFB8 (the second the concrete template's).
// BFME 1 donor: game/GameEngine/Source/GameClient/System/FXParticleSystem/
// WindModuleTemplateWriteINI.cpp (same field offsets, keys and defaults);
// BFME 2 reaches the rowed wind header 0x003A5DA0, enum and float line
// writers 0x001F82AB/0x003A5D34 and footer 0x003AFC6B by name.
extern const char *const WindMotionNames[];

template <int Category> class DefaultModuleTemplate;

template <> class DefaultModuleTemplate<7> {
public:
	virtual void writeINI(File &file, unsigned int flags) const;

private:
	void *m_moduleClassView;
	void *m_moduleInfoView;
	unsigned int m_windMotion;			// 0x0C
	float m_windStrength;				// 0x10
	float m_windFullStrengthDist;		// 0x14
	float m_windZeroStrengthDist;		// 0x18
	float m_pad1c[2];
	float m_windAngleChangeMin;			// 0x24
	float m_windAngleChangeMax;			// 0x28
	float m_pad2c;
	float m_windMotionStartAngleMin;	// 0x30
	float m_windMotionStartAngleMax;	// 0x34
	float m_pad38;
	float m_windMotionEndAngleMin;		// 0x3C
	float m_windMotionEndAngleMax;		// 0x40
	float m_pad44;
	float m_turbulenceAmplitude;		// 0x48
	float m_turbulenceFrequency;		// 0x4C
};

void DefaultModuleTemplate<7>::writeINI(File &file, unsigned int flags) const
{
	Rva003A5DA0WriteWindHeader(this, &file, &flags);
	_STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
	if (m_windMotion != 1)
		Rva001F82ABWrite(oss, flags, "WindMotion", (char const **)(WindMotionNames + m_windMotion));
	if (m_windStrength != 2.0f)
		Rva003A5D34Write(oss, flags, "WindStrength", m_windStrength);
	if (m_windFullStrengthDist != 75.0f)
		Rva003A5D34Write(oss, flags, "WindFullStrengthDist", m_windFullStrengthDist);
	if (m_windZeroStrengthDist != 200.0f)
		Rva003A5D34Write(oss, flags, "WindZeroStrengthDist", m_windZeroStrengthDist);
	if (m_windAngleChangeMin != 0.15f)
		Rva003A5D34Write(oss, flags, "WindAngleChangeMin", m_windAngleChangeMin);
	if (m_windAngleChangeMax != 0.45f)
		Rva003A5D34Write(oss, flags, "WindAngleChangeMax", m_windAngleChangeMax);
	if (m_windMotionStartAngleMin != 0.0f)
		Rva003A5D34Write(oss, flags, "WindPingPongStartAngleMin", m_windMotionStartAngleMin);
	if (m_windMotionStartAngleMax != 0.7853982f)
		Rva003A5D34Write(oss, flags, "WindPingPongStartAngleMax", m_windMotionStartAngleMax);
	if (m_windMotionEndAngleMin != 5.4977875f)
		Rva003A5D34Write(oss, flags, "WindPingPongEndAngleMin", m_windMotionEndAngleMin);
	if (m_windMotionEndAngleMax != 6.2831855f)
		Rva003A5D34Write(oss, flags, "WindPingPongEndAngleMax", m_windMotionEndAngleMax);
	if (m_turbulenceAmplitude != 0.0f)
		Rva003A5D34Write(oss, flags, "TurbulenceAmplitude", m_turbulenceAmplitude);
	if (m_turbulenceFrequency != 0.0f)
		Rva003A5D34Write(oss, flags, "TurbulenceFrequency", m_turbulenceFrequency);
	Rva001F458BWrite(file, (const Rva001F458BText &)oss.str());
	Rva003AFC6BWrite(&file, &flags);
}

} // namespace FXParticleSystem
