// cl: /O1 /arch:SSE /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ??0StealthUpdateModuleData@@QAE@XZ, retail 0x0037588B, 334 bytes.
//
// StealthUpdate ModuleData (table 0xC18210: StealthDelay plus
// MoveThresholdSpeed plus StealthForbiddenConditions per ZH
// StealthUpdate.cpp; factory 0x24EC60 news 0xC8 sole caller; proc 0x373F2C
// rowed; pool key plus name rows in the same cluster). V1 probe of the
// maximal natural member model: empty UpdateModuleData base (Topple
// pattern) plus explicit vtable plus bitset<128> pair (rowed 0x24CA24
// reset, ModelCondition idiom) plus Real/int/bool scalars plus three
// vector<AsciiString> members (AsciiString-Vector_base alias plus erase
// pin, SpawnBehavior idiom) plus two 8-byte minus-one-zero pairs through
// the shared 0x4CEE6E fold (Bloodthirsty InitiateVoiceEntry precedent)
// plus CRT memset pair plus trailing clear of the first vector. All
// member constructions ride the init-list in declaration order; the body
// holds only the two memsets and the clear.
#include <bitset>
#include <string.h>
#include <vector>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class Bits10
{
public:
	Bits10() { ((_STL::bitset<128> *)m_words)->reset(); }

private:
	unsigned long m_words[4];
};

class Bits64
{
public:
	Bits64() { ((_STL::bitset<128> *)m_words)->reset(); }

private:
	unsigned long m_words[4];
};
class Rva004CEE6EMemberTracked
{
public:
	Rva004CEE6EMemberTracked();
	~Rva004CEE6EMemberTracked();

private:
	int m_minusOne;
	int m_zero;
};

class Rva004CEE6EMember
{
public:
	Rva004CEE6EMember();
	~Rva004CEE6EMember();

private:
	int m_minusOne;
	int m_zero;
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();
};

class StealthUpdateModuleData : public UpdateModuleData
{
public:
	StealthUpdateModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	int m_flags08; // +8, or-minus-one
	int m_zero0C; // +0xC
	Bits10 m_statusBits10; // +0x10
	float m_speed20; // +0x20
	float m_half24; // +0x24
	float m_one28; // +0x28
	int m_count2C; // +0x2C
	unsigned char m_byte30; // +0x30
	float m_zero34; // +0x34
	unsigned char m_byte38; // +0x38
	int m_zero3C; // +0x3C
	int m_zero40; // +0x40
	int m_zero44; // +0x44
	int m_zero48; // +0x48
	int m_zero4C; // +0x4C
	int m_zero50; // +0x50
	unsigned char m_one54; // +0x54
	unsigned char m_one55; // +0x55
	unsigned char m_zero56; // +0x56
	unsigned int m_zero58; // +0x58
	unsigned int m_zero5C; // +0x5C
	float m_zero60; // +0x60
	Bits64 m_statusBits64; // +0x64
	_STL::vector<AsciiString> m_strings74; // +0x74
	Rva004CEE6EMemberTracked m_pair80; // +0x80
	Rva004CEE6EMember m_pair88; // +0x88
	int m_ten90; // +0x90
	int m_ten94; // +0x94
	int m_zero98; // +0x98
	int m_zero9C; // +0x9C
	int m_zeroA0; // +0xA0
	int m_minusOneA4; // +0xA4, or-minus-one
	int m_minusOneA8; // +0xA8, or-minus-one
	int m_minusOneAC; // +0xAC, or-minus-one
	_STL::vector<AsciiString> m_stringsB0; // +0xB0
	_STL::vector<AsciiString> m_stringsBC; // +0xBC
};

// ??0StealthUpdateModuleData@@QAE@XZ @0x37588B
Rva004CEE6EMemberTracked::~Rva004CEE6EMemberTracked()
{
	m_minusOne = 0;
}

StealthUpdateModuleData::StealthUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C184D8))
	, m_flags08(-1)
	, m_zero0C(0)
	, m_speed20(0.0f)
	, m_half24(0.5f)
	, m_one28(1.0f)
	, m_count2C(30)
	, m_byte30(0)
	, m_zero34(0.0f)
	, m_byte38(0)
	, m_zero3C(0)
	, m_zero40(0)
	, m_zero44(0)
	, m_zero48(0)
	, m_zero4C(0)
	, m_zero50(0)
	, m_one54(1)
	, m_one55(1)
	, m_zero56(0)
	, m_zero58(0)
	, m_zero5C(0)
	, m_zero60(0.0f)
	, m_ten90(10)
	, m_ten94(10)
	, m_zero98(0)
	, m_zero9C(0)
	, m_zeroA0(0)
	, m_minusOneA4(-1)
	, m_minusOneA8(-1)
	, m_minusOneAC(-1)
{
	memset(&m_statusBits10, 0, 0x10);
	memset(&m_statusBits64, 0, 0x10);
	m_strings74.clear();
}
