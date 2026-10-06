// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1RespawnUpdateModuleData@@UAE@XZ, retail 0x004AFBFF, 96 bytes.
// Virtual dtor restoring Snapshot base vtable 0x00BBB554: AsciiString at
// +0x11C (state 3) then +0x118 (state 2) via pinned 0x00036410, RespawnRule
// 20B set at +0x10C (state 1) via rowed 0x004AF46E, filter at +0x08
// (state 0) via rowed 0x00360D26. Layout from size 0x120 via factory
// 0x0024F92E, tree at +0x10C per RespawnUpdateParseRules (rules tree at
// module offset 0x10C), strings at +0x118/+0x11C, filter at +0x08.
// Caller is the slot-0 ??_G at 0x004AFBE3. Shape follows
// GettingBuiltBehaviorModuleDataDtor (strings plus filter plus BBB554)
// and MissileUpdateModuleDataDtor (0x120 class with exhaust string at
// +0x11C plus BBB554, novtable suppressing the entry store).
#include <set>
#include "Common/Snapshot.h"

#include "ascii_string.h"

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

struct BfmePod20
{
	unsigned a[5];
};

inline bool operator<(const BfmePod20 &x, const BfmePod20 &y)
{
	return x.a[0] < y.a[0];
}

typedef _STL::_Rb_tree<BfmePod20, BfmePod20, _STL::_Identity<BfmePod20>, _STL::less<BfmePod20>, _STL::allocator<BfmePod20> > UBfmePod20SetTree;

class __declspec(novtable) RespawnUpdateModuleData : public Snapshot
{
public:
	virtual ~RespawnUpdateModuleData();

private:
	unsigned char m_pad04[0x08 - 4]; // +0x04
	Rva00360D26Member m_filter; // +0x08
	unsigned char m_pad0C[0x10C - 0x0C]; // +0x0C..+0x10B
	UBfmePod20SetTree m_rules; // +0x10C
	AsciiString m_str118; // +0x118
	AsciiString m_str11C; // +0x11C
};

RespawnUpdateModuleData::~RespawnUpdateModuleData()
{
}
