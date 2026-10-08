// cl: /O1 /arch:SSE /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// LargeGroupAudioAudioMap bodies (retail 0x003EE0CF..0x003EE6F6).
//
// Identity: WorldBuilder names the unit LargeGroupAudioAudioMap.cpp (the
// "two Sound blocks within the same LargeGroupAudioMap" string of 0x003EE576)
// and the shorts at +0xE0/+0xE2 m_startThreshold/m_stopThreshold
// (wb_members asserts in LargeGroupAudioAudioMap::update). The constructor
// 0x003EE0CF is the one LargeGroupAudio::parseLargeGroupAudioMapDefinition
// calls with the block name; the destructor 0x003EE1BE is slot 0's callee
// (vtable 0x00C3613C, deleting dtor 0x003EE3E2). The +0x1C vector holds
// LargeGroupAudioSoundKeyPair objects (WorldBuilder names their ctor
// 0x00569FB3 and dtor 0x0056A061). parseSoundBlock 0x003EE576 is WorldBuilder's
// name for its twin 0x1035FB0 (same callees, same "two Sound blocks" throw).
// 0x003EE23C is the per-map xfer LargeGroupAudio::xfer runs inside each
// "AudioMap" block (WB twin 0x1035D30, unnamed): it writes the pair count and
// each pair's name and id ahead of a "SoundKeyPair" block, and on load reports
// false when the count differs or a saved pair is missing.
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

class INI;
struct FieldParse;

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
	char m_pad00[8];
	int m_loadType;	// +0x08
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
	char *mFailureMessage;
	int mErrorCode;
};

int Rva0056A983Get();	// LargeGroupAudioSoundKeyPair field-parse table

// Retail keeps the minimum/current version bytes in xfer's dead argument slot.
struct VersionPair
{
	unsigned char minimum, current;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual void slot04();
	virtual int BeginBlock(const char *);
	virtual void EndBlock();
	virtual void SkipBlock(const char *);
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual Xfer &xferAsciiString(AsciiString *);
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual Xfer &xferInt(int *);
};

// The sound key pair's name getter 0x00568BE2 keeps its ledger spelling.
class BitRange
{
public:
	AsciiString rva00568BE2();
};

// The pair's id sum 0x00568991 keeps its ledger owner.
class Rva005688D2
{
public:
	int rva00568991();
};

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
	void rva00569BBC(Xfer *xfer, VersionPair *version);	// 0x00569BBC
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
	bool rva003EE23C(Xfer *xfer, VersionPair *version);
	void rva003EE3FE(const LargeGroupAudioAudioMap &other);
	static void parseSoundBlock(INI *ini, void *instance, void *store, const void *userData);
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

bool LargeGroupAudioAudioMap::rva003EE23C(Xfer *xfer, VersionPair *version)
{
	bool complete = true;
	int count = m_soundKeyPairs.size();
	xfer->xferInt(&count);

	if (xfer->IsLoading())
	{
		if (count != m_soundKeyPairs.size())
			complete = false;

		for (int i = 0; i < count; ++i)
		{
			AsciiString name;
			xfer->xferAsciiString(&name);
			int id;
			xfer->xferInt(&id);

			_STL::vector<LargeGroupAudioSoundKeyPair *>::iterator it;
			for (it = m_soundKeyPairs.begin(); it != m_soundKeyPairs.end(); ++it)
			{
				if (((BitRange *)*it)->rva00568BE2() == name)
					break;
			}

			if (it != m_soundKeyPairs.end() && id == ((Rva005688D2 *)*it)->rva00568991())
			{
				xfer->BeginBlock("SoundKeyPair");
				(*it)->rva00569BBC(xfer, version);
				xfer->EndBlock();
			}
			else
			{
				xfer->SkipBlock("SoundKeyPair");
				complete = false;
			}
		}
	}
	else
	{
		for (_STL::vector<LargeGroupAudioSoundKeyPair *>::iterator it = m_soundKeyPairs.begin(); it != m_soundKeyPairs.end(); ++it)
		{
			LargeGroupAudioSoundKeyPair *pair = *it;
			AsciiString name = ((BitRange *)pair)->rva00568BE2();
			xfer->xferAsciiString(&name);
			int id = ((Rva005688D2 *)pair)->rva00568991();
			xfer->xferInt(&id);
			xfer->BeginBlock("SoundKeyPair");
			pair->rva00569BBC(xfer, version);
			xfer->EndBlock();
		}
	}

	return complete;
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

void LargeGroupAudioAudioMap::parseSoundBlock(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	LargeGroupAudioAudioMap *self = (LargeGroupAudioAudioMap *)instance;
	_STL::vector<LargeGroupAudioSoundKeyPair *> &vec = self->m_soundKeyPairs;

	const char *name = ini->getNextTokenOrNull(NULL);
	LargeGroupAudioSoundKeyPair *pair = new LargeGroupAudioSoundKeyPair(self, name);
	vec.push_back(pair);
	ini->initFromINI(pair, (const FieldParse *)Rva0056A983Get());

	for (_STL::vector<LargeGroupAudioSoundKeyPair *>::iterator it = vec.begin(), end = vec.end(); it != end; ++it)
	{
		if (pair != *it && ((BitRange *)pair)->rva00568BE2() == ((BitRange *)*it)->rva00568BE2())
		{
			if (ini->m_loadType != 2 && ini->m_loadType != 5)
				throw INIException(3, "LargeGroupAudio: You cannot use the same name(%s) for two Sound blocks within the same LargeGroupAudioMap(%s)",
					((BitRange *)pair)->rva00568BE2().str(), self->m_name.str());
			delete *it;
			vec.erase(it);
			return;
		}
	}
}
