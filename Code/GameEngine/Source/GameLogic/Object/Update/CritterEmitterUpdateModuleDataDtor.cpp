// cl: /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
//
// ??1CritterEmitterUpdateModuleData@@UAE@XZ @0x004C8F49 75B.
// Dtor lane: ctor rowed at 0x004C8EFF in DynamicGeometryInfoUpdateCtor.cpp vtable
// 0x0085E988 with slot0 ??_G at 0x004C8F2D. Destroys twin E16 vectors at +8
// and +0x14 through inlined bfmealloc deallocate (two _free at 0x30830) then
// restores Snapshot base vtable 0x00BBB554. Layout follows ctor TU (+0 vtable
// +4 unused +8 vector +0x14 vector +0x20 int). Shape follows FloodUpdateModuleDataDtor
// (shared Snapshot base dtor plus novtable derived
// suppresses entry derived store). Two tracked members give states 1 then 0
// exactly as retail. Caller is ??_G at 0x004C8F2D. BFME1 donor is
// CritterEmitterUpdateModuleDataDestructorThunk.

#include <vector>
#include "Common/Snapshot.h"

struct BfmeE16 { float x, y, z, w; };

class __declspec(novtable) CritterEmitterUpdateModuleData : public Snapshot
{
public:
	virtual ~CritterEmitterUpdateModuleData();

private:
	int m_unused04; // +4
	_STL::vector<BfmeE16> m_a08; // +8
	_STL::vector<BfmeE16> m_b14; // +0x14
	int m_i20; // +0x20
};

CritterEmitterUpdateModuleData::~CritterEmitterUpdateModuleData()
{
}
