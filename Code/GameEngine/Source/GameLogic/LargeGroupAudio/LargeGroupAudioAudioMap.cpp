// cl: /O1 /arch:SSE /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// LargeGroupAudioAudioMap bodies (retail 0x003EE0CF..0x003EE23B).
//
// Identity: WorldBuilder names the unit LargeGroupAudioAudioMap.cpp (the
// "two Sound blocks within the same LargeGroupAudioMap" string of 0x003EE576)
// and the shorts at +0xE0/+0xE2 m_startThreshold/m_stopThreshold
// (wb_members asserts in LargeGroupAudioAudioMap::update). The constructor
// 0x003EE0CF is the one LargeGroupAudio::parseLargeGroupAudioMapDefinition
// calls with the block name; the destructor 0x003EE1BE is slot 0's callee
// (vtable 0x00C3613C, deleting dtor 0x003EE3E2). The element class of the
// +0x1C vector keeps its address-derived name from its destructor 0x0056A061.
typedef bool Bool;
// Retail frees vector storage through the C++-linkage free (0x00030830),
// which keeps the unwind-state store before each call.
#define free bfmeUnusedCRTFree
#include <cstdlib>
#undef free
void free(void *);
#include <vector>
#include <bitset>
#include <string.h>
#include "ascii_string.h"

extern float g_secondsPerLogicFrame;

// Base shared with the LargeGroupAudio key holder (dtor 0x001E3624): vptr,
// +4 next override, +8 override flag, +0xC.
class Rva001E3624
{
public:
	Rva001E3624() : m_next04(0), m_alloc08(0), m_extra0C(-1) {}
	virtual ~Rva001E3624();
private:
	Rva001E3624 *m_next04;
	unsigned char m_alloc08;
	int m_extra0C;
};

class LargeGroupAudioAudioMap;

class LargeGroupAudioSoundKeyPair
{
public:
	LargeGroupAudioSoundKeyPair(LargeGroupAudioAudioMap *owner, const char *name);	// 0x00569FB3
	~LargeGroupAudioSoundKeyPair();	// 0x0056A061
	void rva0056A378(const LargeGroupAudioSoundKeyPair &other);	// 0x0056A378
private:
	char m_storage[0x68];
};

// Opaque 0x4C-byte zero-initialised member (ctor 0x00042526).
class Rva0042526Member
{
public:
	Rva0042526Member() { memset(this, 0, sizeof(*this)); }
	char m_storage[0x4C];
};

class LargeGroupAudioAudioMap : public Rva001E3624
{
public:
	LargeGroupAudioAudioMap(AsciiString name);
	virtual ~LargeGroupAudioAudioMap();
	void rva003EE3FE(const LargeGroupAudioAudioMap &other);
private:
	float m_10;										// +0x10
	float m_14;										// +0x14
	AsciiString m_name;								// +0x18
	_STL::vector<LargeGroupAudioSoundKeyPair *> m_soundKeyPairs;	// +0x1C
	Rva0042526Member m_28;							// +0x28
	Rva0042526Member m_74;							// +0x74
	_STL::bitset<128> m_C0;							// +0xC0
	_STL::bitset<128> m_D0;							// +0xD0
	unsigned short m_startThreshold;				// +0xE0
	unsigned short m_stopThreshold;					// +0xE2
	unsigned char m_E4;								// +0xE4
	unsigned char m_E5;								// +0xE5
	float m_E8;										// +0xE8
	float m_EC;										// +0xEC
	float m_F0;										// +0xF0
	float m_F4;										// +0xF4
};

LargeGroupAudioAudioMap::LargeGroupAudioAudioMap(AsciiString name)
	: m_name(name)
{
	m_startThreshold = -1;
	m_stopThreshold = -1;
	m_EC = -1.0f;
	m_E8 = -1.0f;
	m_F4 = -1.0f;
	m_F0 = -1.0f;
	m_10 = 10000.0f;
	m_14 = g_secondsPerLogicFrame * 20.0f;
	m_E4 = 10;
	m_E5 = 1;
}

LargeGroupAudioAudioMap::~LargeGroupAudioAudioMap()
{
	for (_STL::vector<LargeGroupAudioSoundKeyPair *>::iterator it = m_soundKeyPairs.begin(); it != m_soundKeyPairs.end(); ++it)
		delete *it;
}

void LargeGroupAudioAudioMap::rva003EE3FE(const LargeGroupAudioAudioMap &other)
{
	if (&other == this)
		return;

	for (_STL::vector<LargeGroupAudioSoundKeyPair *>::iterator it = m_soundKeyPairs.begin(); it != m_soundKeyPairs.end(); ++it)
		delete *it;
	m_soundKeyPairs.clear();

	m_EC = -1.0f;
	m_E8 = -1.0f;
	m_F4 = -1.0f;
	m_F0 = -1.0f;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_name = other.m_name;
	m_28 = other.m_28;
	m_74 = other.m_74;
	m_C0 = other.m_C0;
	m_D0 = other.m_D0;
	m_startThreshold = other.m_startThreshold;
	m_stopThreshold = other.m_stopThreshold;
	m_E4 = other.m_E4;
	m_E5 = other.m_E5;

	m_soundKeyPairs.reserve(other.m_soundKeyPairs.size());
	for (_STL::vector<LargeGroupAudioSoundKeyPair *>::const_iterator src = other.m_soundKeyPairs.begin(); src != other.m_soundKeyPairs.end(); ++src)
	{
		LargeGroupAudioSoundKeyPair *pair = new LargeGroupAudioSoundKeyPair(this, NULL);
		m_soundKeyPairs.push_back(pair);
		pair->rva0056A378(**src);
	}
}
