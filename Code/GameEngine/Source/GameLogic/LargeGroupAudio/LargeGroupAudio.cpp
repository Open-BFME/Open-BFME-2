// cl: /O1 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
//
// LargeGroupAudio subsystem bodies (retail 0x0020D7AC..0x0020E1E1).
//
// Identity (target): the constructor 0x0020DD59 (pinned under its name, the
// GameLogic::init callee) installs the primary table 0x007E40A0 and the
// Snapshot table 0x007E4090; its slots fix the virtuals defined here. The
// three vectors at +0x10/+0x1C/+0x28 are the ones LargeGroupAudio::xfer and
// removeOverrides walk; the field names m_waitingForLevelLoad (+0x38) and
// m_needsToRegenerateAfterReload (+0x3A) are WorldBuilder's (wb_members).
// The +0x34 object (0x1C bytes, ctor 0x0020D7BC, vtable 0x007E3FF4) keeps the
// ledger's address-derived name Rva0020D98D (its copy ctor's address).
// LargeGroupAudioAudioMap is WorldBuilder's element class name; tying it to
// these vectors is a structural inference from xfer's "AudioMap" blocks.
typedef bool Bool;
// Retail frees vector storage through the C++-linkage free (0x00030830),
// which keeps the unwind-state store before each call.
#define free bfmeUnusedCRTFree
#include <cstdlib>
#undef free
void free(void *);
#include <vector>
#include "ascii_string.h"
#include "subsystem_interface.h"
#include "Common/Snapshot.h"

class LargeGroupAudioAudioMap;

// Out-of-line ctor of the 12-byte key container (folded with
// ObjectCreationList's; the ledger's spelling of 0x001F81BF).
class ObjectCreationList
{
public:
	ObjectCreationList();
	char m_storage[12];
};

// Base of the +0x34 holder (dtor 0x001E3624): vptr, +4 next, +8 flag, +0xC.
class Rva001E3624
{
public:
	Rva001E3624() : m_next04(0), m_alloc08(0), m_extra0C(-1) {}
	virtual ~Rva001E3624();
	void setNextOverride(Rva001E3624 *next) { m_next04 = next; }
	void markAsOverride() { m_alloc08 = 1; }
private:
	Rva001E3624 *m_next04;
	unsigned char m_alloc08;
	int m_extra0C;
};

struct FieldParse;
class Overridable;

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
	char m_pad00[8];
	int m_loadType;	// +0x08
};

int Rva003EE6F7Get();	// LargeGroupAudioAudioMap field-parse table

// Overridable-style map of sounds keyed by unit type, 0xF8 bytes.
class LargeGroupAudioAudioMap : public Rva001E3624
{
public:
	LargeGroupAudioAudioMap(AsciiString name);	// 0x003EE0CF
	void rva003EE3FE(const LargeGroupAudioAudioMap &other);	// 0x003EE3FE
	const AsciiString &getName() const { return m_name; }
private:
	char m_pad10[8];
	AsciiString m_name;	// +0x18
	char m_pad1C[0xF8 - 0x1C];
};

// Address-named workers on the audio maps and on LargeGroupAudio.
class Rva003EDC16 { public: void rva003EDC16(); };
class Rva003EDDD4 { public: void rva003EDDD4(int changed); };
class Rva003EDDF5 { public: void rva003EDDF5(int arg); };
class Rva0020DXXX { public: void rva0020D834(); };
class Rva001B4E82 { public: void rva001B4E82(void *subsystem); };

// The +0x34 holder (vtable 0x007E3FF4): the base plus a 12-byte key
// container at +0x10.
class Rva0020D98D : public Rva001E3624
{
public:
	Rva0020D98D();	// 0x0020D7BC
private:
	ObjectCreationList m_10;
};

class LargeGroupAudio : public SubsystemInterface, public Snapshot
{
public:
	LargeGroupAudio();
	virtual ~LargeGroupAudio();

	virtual void init();
	virtual bool vslot05();
	virtual void reset();
	virtual void update();

	Overridable *removeOverrides();

	static void parseLargeGroupAudioMapDefinition(INI *ini);

protected:
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);

private:
	_STL::vector<LargeGroupAudioAudioMap *> m_audioMaps;				// +0x10
	_STL::vector<LargeGroupAudioAudioMap *> m_baseAudioMaps;			// +0x1C
	_STL::vector<LargeGroupAudioAudioMap *> m_mapSpecificAudioMaps;	// +0x28
	Rva0020D98D *m_34;													// +0x34
	bool m_waitingForLevelLoad;											// +0x38
	bool m_39;															// +0x39
	bool m_needsToRegenerateAfterReload;								// +0x3A
	int m_3C;															// +0x3C
};

extern LargeGroupAudio *TheLargeGroupAudio;

LargeGroupAudio::LargeGroupAudio()
	: m_34(NULL), m_waitingForLevelLoad(true), m_39(false), m_needsToRegenerateAfterReload(false), m_3C(-1)
{
	m_34 = new Rva0020D98D;
}

Rva0020D98D::Rva0020D98D()
{
}

LargeGroupAudio::~LargeGroupAudio()
{
	if (TheSubsystemList)
		((Rva001B4E82 *)TheSubsystemList)->rva001B4E82(this);
	removeOverrides();
	for (_STL::vector<LargeGroupAudioAudioMap *>::iterator it = m_baseAudioMaps.begin(); it != m_baseAudioMaps.end(); ++it)
		::delete *it;
	if (m_34)
		::delete m_34;
}

bool LargeGroupAudio::vslot05()
{
	if (m_39)
	{
		m_39 = false;
		return true;
	}
	return false;
}

void LargeGroupAudio::reset()
{
	removeOverrides();
	for (_STL::vector<LargeGroupAudioAudioMap *>::iterator it = m_audioMaps.begin(), end = m_audioMaps.end(); it != end; ++it)
		((Rva003EDC16 *)*it)->rva003EDC16();
	m_waitingForLevelLoad = true;
}

void LargeGroupAudio::update()
{
	if (m_waitingForLevelLoad)
		return;
	if (m_needsToRegenerateAfterReload)
		((Rva0020DXXX *)this)->rva0020D834();
	bool changed = false;
	for (_STL::vector<LargeGroupAudioAudioMap *>::iterator it = m_audioMaps.begin(), end = m_audioMaps.end(); it != end; ++it)
		((Rva003EDDD4 *)*it)->rva003EDDD4((int)&changed);
}

// ?parseLargeGroupAudioMapDefinition@LargeGroupAudio@@SAXPAVINI@@@Z present-unmatched
void LargeGroupAudio::parseLargeGroupAudioMapDefinition(INI *ini)
{
	if (TheLargeGroupAudio == NULL)
		TheLargeGroupAudio = new LargeGroupAudio;

	AsciiString name(ini->getNextToken(NULL));

	_STL::vector<LargeGroupAudioAudioMap *>::iterator it;
	for (it = TheLargeGroupAudio->m_audioMaps.begin(); it != TheLargeGroupAudio->m_audioMaps.end(); ++it)
		if (((const StringBase<char> *)&(*it)->getName())->compareNoCase(*(const StringBase<char> *)&name) == 0)
			break;

	_STL::vector<LargeGroupAudioAudioMap *>::iterator baseIter;
	for (baseIter = TheLargeGroupAudio->m_baseAudioMaps.begin(); baseIter != TheLargeGroupAudio->m_baseAudioMaps.end(); ++baseIter)
		if (((const StringBase<char> *)&(*baseIter)->getName())->compareNoCase(*(const StringBase<char> *)&name) == 0)
			break;

	LargeGroupAudioAudioMap *audioMap;
	if (it == TheLargeGroupAudio->m_audioMaps.end())
	{
		audioMap = new LargeGroupAudioAudioMap(name);
		TheLargeGroupAudio->m_audioMaps.push_back(audioMap);
		if (ini->m_loadType == 2)
		{
			audioMap->markAsOverride();
			TheLargeGroupAudio->m_mapSpecificAudioMaps.push_back(audioMap);
		}
		else
		{
			TheLargeGroupAudio->m_baseAudioMaps.push_back(audioMap);
		}
	}
	else if (ini->m_loadType == 2)
	{
		audioMap = new LargeGroupAudioAudioMap(name);
		audioMap->rva003EE3FE(**it);
		audioMap->markAsOverride();
		(*it)->setNextOverride(audioMap);
		((Rva003EDC16 *)*it)->rva003EDC16();
		((Rva003EDDF5 *)*it)->rva003EDDF5(0);
		*it = audioMap;
	}
	else
	{
		audioMap = *it;
	}

	ini->initFromINI(audioMap, (const FieldParse *)Rva003EE6F7Get());
}
