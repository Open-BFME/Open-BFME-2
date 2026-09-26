// cl: /O1 /GX /DNDEBUG /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
//
// ??1RandomSoundSelectorClientBehaviorModuleData@@UAE@XZ, retail 0x002578DE,
// 76 bytes. Virtual dtor over vtable 0x007F42A8 (slot 0 deleting dtor at
// 0x002578C2 calls this body). Destroys UnitSpecificSounds map at +0x1C8
// through the rowed _Rb_tree dtor at 0x0025742C then the 56-entry voice
// array at +0x08 through the rowed ehvec dtor at 0x00629110 (size 8 count
// 0x38 element dtor rowed ??1Rva002390CB at 0x004C9F38) then restores the
// Snapshot base vtable 0x00BBB554. Layout from the rowed ctor TU at
// 0x0025785C (news 0x1E0 vtable 0xBF42A8 array 0x1C0 via 0x00254FE4 map
// 0x0C via pinned 0x0024613C). Shape follows LargeGroupBonus and Passive
// ModuleData dtors (TU-local Snapshot with inline BBB554 restore novtable
// suppressing the entry derived store retail lacks). BFME1 donor
// RandomSoundSelectorClientBehaviorModuleDataDestructor.cpp proves the
// map-then-array teardown order.
#include <map>

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class Rva002390CB
{
public:
	~Rva002390CB();

private:
	void *m_00;
	void *m_04;
};

struct BfmeStringRecord002CF550;

namespace _STL
{
template <>
class _Rb_tree<BfmeStringRecord002CF550, BfmeStringRecord002CF550, _Identity<BfmeStringRecord002CF550>, less<BfmeStringRecord002CF550>, allocator<BfmeStringRecord002CF550> >
{
public:
	~_Rb_tree();

private:
	void *m_header;
	char m_pad04[8];
};
}

typedef _STL::_Rb_tree<BfmeStringRecord002CF550, BfmeStringRecord002CF550, _STL::_Identity<BfmeStringRecord002CF550>, _STL::less<BfmeStringRecord002CF550>, _STL::allocator<BfmeStringRecord002CF550> > BfmeStringRecordTree900;

class __declspec(novtable) RandomSoundSelectorClientBehaviorModuleData : public Snapshot
{
public:
	virtual ~RandomSoundSelectorClientBehaviorModuleData();

private:
	int m_pad04; // +0x04
	Rva002390CB m_voices[56]; // +0x08 (0x1C0 bytes)
	BfmeStringRecordTree900 m_unitSpecificSounds; // +0x1C8 (0x0C bytes)
	float m_chance; // +0x1D4
	int m_voicePriority; // +0x1D8
	bool m_unknown1DC; // +0x1DC
	bool m_rerollOnEveryFrame; // +0x1DD
	char m_pad1DE[2]; // +0x1DE pad to 0x1E0
};

RandomSoundSelectorClientBehaviorModuleData::~RandomSoundSelectorClientBehaviorModuleData()
{
}
