// ?rva003EE23C@LargeGroupAudioAudioMap@@QAE_NPAVXfer@@PAUVersionPair@@@Z
// partial score=0.8 date=2026-10-08
// cl: /O1 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// LargeGroupAudioAudioMap's xfer, retail 0x003EE23C (422B; thiscall, ret 8).
//
// Identity (target): LargeGroupAudio::xfer 0x0020DBBF calls it once per
// "AudioMap" block with the Xfer and the version it read, and counts the
// loads it reports as complete. Its WorldBuilder twin 0x1035D30 has the same
// callees in the same order. It writes the pair count, then each pair's name
// and id ahead of a "SoundKeyPair" block. On load, it finds each saved pair by
// name and checks the id; it skips the block and reports false when either
// misses, or when the saved count differs.
// The element class name LargeGroupAudioAudioMap and the pair class name
// LargeGroupAudioSoundKeyPair are WorldBuilder's; the pair vector at +0x1C is
// the range the rowed Rva0020DXXXElem workers 0x003EDF69/0x003EDFD8 walk.
// Retail reads the pair's callees at their REL32s:
// - the name getter 0x00568BE2 and the id sum 0x00568991, under their ledger
//   owners;
// - the pair xfer 0x00569BBC, under its address-derived name.
#include <vector>
#include "ascii_string.h"

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

// The ledger keeps the pair's getters under their address-derived owners.
class BitRange
{
public:
	AsciiString rva00568BE2();	// 0x00568BE2
};

class Rva005688D2
{
public:
	int rva00568991();			// 0x00568991
};

class LargeGroupAudioSoundKeyPair
{
public:
	AsciiString getName() { return ((BitRange *)this)->rva00568BE2(); }
	int getID() { return ((Rva005688D2 *)this)->rva00568991(); }
	void rva00569BBC(Xfer *xfer, VersionPair *version);	// 0x00569BBC
};

class LargeGroupAudioAudioMap
{
public:
	bool rva003EE23C(Xfer *xfer, VersionPair *version);

private:
	unsigned char m_pad00[0x1C];
	_STL::vector<LargeGroupAudioSoundKeyPair *> m_soundKeyPairs;	// +0x1C
};

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

			LargeGroupAudioSoundKeyPair **it = m_soundKeyPairs.begin();
			while (it != m_soundKeyPairs.end())
			{
				if ((*it)->getName() == name)
					break;
				++it;
			}

			if (it != m_soundKeyPairs.end() && (*it)->getID() == id)
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
		for (LargeGroupAudioSoundKeyPair **it = m_soundKeyPairs.begin(); it != m_soundKeyPairs.end(); ++it)
		{
			LargeGroupAudioSoundKeyPair *pair = *it;
			AsciiString name = pair->getName();
			xfer->xferAsciiString(&name);
			int id = pair->getID();
			xfer->xferInt(&id);
			xfer->BeginBlock("SoundKeyPair");
			pair->rva00569BBC(xfer, version);
			xfer->EndBlock();
		}
	}

	return complete;
}
