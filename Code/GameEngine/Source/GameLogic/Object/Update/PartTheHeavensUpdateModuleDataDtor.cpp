// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1PartTheHeavensUpdateModuleData@@UAE@XZ, retail 0x004ACCCD, 105 bytes.
// PartTheHeavensUpdateModuleData dtor: frees the three 44B member payloads
// at +0x70 +0x44 +0x18 through inlined bfmealloc deallocate (three _free at
// 0x30830, states 3/2/1) then destroys the AsciiString at +0x08 through the
// pinned 0x36410 body (state 0) then restores the Snapshot base vtable
// 0x00BBB554. Layout from the pinned ctor 0x4ACBF8 (base 4 plus +4 unused
// plus +8/+0xC string pair plus 44B members at +0x10 +0x3C +0x68 total 0x94
// matching the factory 0x24F4FD news) and the chained table 0x00C54DD8
// (Texture Radius Color Opacity Angle). Identity via vtable 0x00854E38 slot
// 0 deleting dtor 0x004ACCB1 calling here. Shape follows
// CritterEmitterUpdateModuleDataDtor (TU-local Snapshot with inline
// BBB554-restoring dtor plus novtable derived plus vector members).

#include <vector>
#include "Common/Snapshot.h"

struct BfmeE16 { float x, y, z, w; };

#include "ascii_string.h"

struct Member44
{
	int m_pad0;
	int m_pad4;
	_STL::vector<BfmeE16> m_vec;
	int m_rest[6];
};

class __declspec(novtable) PartTheHeavensUpdateModuleData : public Snapshot
{
public:
	virtual ~PartTheHeavensUpdateModuleData();

private:
	int m_unused04; // +4
	AsciiString m_str08; // +8
	int m_0c; // +0x0C
	Member44 m_10; // +0x10
	Member44 m_3c; // +0x3C
	Member44 m_68; // +0x68
};

PartTheHeavensUpdateModuleData::~PartTheHeavensUpdateModuleData()
{
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva002BB6BE20Rec@@QAE@XZ=??1Member44@@QAE@XZ")
