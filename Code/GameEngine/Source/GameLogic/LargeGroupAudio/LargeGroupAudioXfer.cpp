// cl: /O1 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
//
// LargeGroupAudio::xfer, retail 0x0020DBBF (410B; ret 4), Snapshot slot 3.
//
// Identity (target): slot 3 of LargeGroupAudio's Snapshot vtable (the +0x0C
// table at 0x007E4090, whose slot 0 is the -0x0C deleting-dtor thunk
// 0x0020DDFB). Its WorldBuilder twin 0xB514E0 has the same callees in the same
// order. The wb_members asserts in LargeGroupAudio::onLevelLoad name
// m_waitingForLevelLoad (+0x38) and m_needsToRegenerateAfterReload (+0x3A).
// The vector at +0x10 is the one LargeGroupAudio::removeOverrides refills,
// and the lookup 0x0020DB91 searches it by the element name at +0x18.
// Each element is written as an "AudioMap" block by 0x003EE23C (thiscall,
// ret 8; its own blocks are "SoundKeyPair"), which returns whether the load
// found every entry. The element class name LargeGroupAudioAudioMap is
// WorldBuilder's (wb_members asserts in LargeGroupAudioAudioMap::update);
// tying it to this vector is a structural inference from the block name.
// The canonical Snapshot header keeps the Zero Hour spelling xfer(Xfer *) for
// slot 3, so the body is named that way; the exports spell the same slot
// DoXfer(Xfer &). As an overrider of the second base's virtual, it receives
// the Snapshot subobject, so the members are read at -0x0C.
typedef bool Bool;
#include <vector>
#include "ascii_string.h"
#include "subsystem_interface.h"
#include "Common/Snapshot.h"

// Retail keeps the minimum/current version bytes in xfer's dead argument slot.
struct VersionPair
{
	VersionPair(unsigned char min, unsigned char cur) : minimum(min), current(cur) {}
	unsigned char minimum, current;
};

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
#include "../../../Include/Common/BfmeXfer.h"

class LargeGroupAudioAudioMap
{
public:
	bool rva003EE23C(Xfer *xfer, VersionPair *version);	// 0x003EE23C

	unsigned char m_pad00[0x18];
	AsciiString m_name;		// +0x18
};

// The name lookup 0x0020DB91 keeps its address-derived owner in the ledger.
struct Rva0020DB91Item;
class Rva0020DB91
{
public:
	void *rva0020DB91(const AsciiString &arg);
	char m_pad00[0x10];
private:
	Rva0020DB91Item **m_begin10; // +0x10
	Rva0020DB91Item **m_end14; // +0x14
};

class LargeGroupAudio : public SubsystemInterface, public Snapshot
{
public:
	LargeGroupAudioAudioMap *findAudioMap(const AsciiString &name)
	{
		return (LargeGroupAudioAudioMap *)((Rva0020DB91 *)this)->rva0020DB91(name);
	}

protected:
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);

private:
	_STL::vector<LargeGroupAudioAudioMap *> m_audioMaps;	// +0x10
	_STL::vector<LargeGroupAudioAudioMap *> m_vec1C;		// +0x1C
	_STL::vector<void *> m_vec28;							// +0x28
	void *m_34;												// +0x34
	bool m_waitingForLevelLoad;								// +0x38
	bool m_39;												// +0x39
	bool m_needsToRegenerateAfterReload;					// +0x3A
	int m_3C;												// +0x3C
};

void LargeGroupAudio::xfer(Xfer *xfer)
{
	if (xfer->IsCRC())
		return;

	VersionPair version(1, 5);
	*xfer == (Xfer::Version &)version;

	*xfer == m_waitingForLevelLoad;
	if (m_waitingForLevelLoad)
		return;

	if (version.current >= 2)
	{
		*xfer == m_3C;
		*xfer == m_needsToRegenerateAfterReload;
	}
	if (version.current >= 4)
		*xfer == m_39;

	int count = m_audioMaps.size();
	*xfer == count;
	int processed = 0;
	for (int i = 0; i < count; ++i)
	{
		if (xfer->IsLoading())
		{
			AsciiString name;
			*xfer == name;
			LargeGroupAudioAudioMap *audioMap = findAudioMap(name);
			if (audioMap == NULL)
			{
				xfer->SkipBlock("AudioMap");
			}
			else
			{
				xfer->BeginBlock("AudioMap");
				if (audioMap->rva003EE23C(xfer, &version))
					++processed;
				xfer->EndBlock();
			}
		}
		else
		{
			LargeGroupAudioAudioMap *audioMap = m_audioMaps[i];
			AsciiString name(audioMap->m_name);
			*xfer == name;
			xfer->BeginBlock("AudioMap");
			audioMap->rva003EE23C(xfer, &version);
			xfer->EndBlock();
		}
	}

	if (xfer->IsLoading() && processed != m_audioMaps.size())
		m_needsToRegenerateAfterReload = true;
}
