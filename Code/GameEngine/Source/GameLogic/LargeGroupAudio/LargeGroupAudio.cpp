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
private:
	void *m_next04;
	unsigned char m_alloc08;
	int m_extra0C;
};

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

	virtual void init();
	virtual bool rva0020DB09(int reason);
	virtual void reset();
	virtual void update();

protected:
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);

private:
	_STL::vector<LargeGroupAudioAudioMap *> m_audioMaps;	// +0x10
	_STL::vector<LargeGroupAudioAudioMap *> m_vec1C;		// +0x1C
	_STL::vector<LargeGroupAudioAudioMap *> m_vec28;		// +0x28
	Rva0020D98D *m_34;										// +0x34
	bool m_waitingForLevelLoad;								// +0x38
	bool m_39;												// +0x39
	bool m_needsToRegenerateAfterReload;					// +0x3A
	int m_3C;												// +0x3C
};

LargeGroupAudio::LargeGroupAudio()
	: m_34(NULL), m_waitingForLevelLoad(true), m_39(false), m_needsToRegenerateAfterReload(false), m_3C(-1)
{
	m_34 = new Rva0020D98D;
}

Rva0020D98D::Rva0020D98D()
{
}
