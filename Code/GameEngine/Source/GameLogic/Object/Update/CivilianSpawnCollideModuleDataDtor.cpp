// cl: /DNDEBUG /MD /GX
//
// ??1CivilianSpawnCollideModuleData@@UAE@XZ, retail 0x004BD72A, 48 bytes.
// ModuleData dtor: tears down the filter at +0x08 through the folded 0x360D26
// body (canonical Rva003623E5Member destructor), then restores the Snapshot base vtable
// 0x00BBB554. Empty derived body with EH state 0 (EH prolog 0xB8F889, no base
// call since Snapshot dtor is inline). Shape follows the landed
// PillageModuleDataDtor/SpecialEnemySenseUpdateModuleDataDtor (TU-local Snapshot
// with inline BBB554-restoring dtor, novtable derived to suppress own store,
// empty body). Layout from the rowed ctor 0x004BD651 (vtable 0xC5AAB8 at +0,
// filter at +0x08 via 0x3623E5, size 0x0C via factory 0x00251324 pushing 0xC)
// and table 0xC5AB48. Caller is the slot-0 ??_G at 0x004BD70E (vtable 0xC5AAB8).
// Donor: BFME1 CivilianSpawnCollideModuleDataCtorThunk.cpp virtual dtor.


class Xfer;

#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"


// The ctor uses this same four-byte handle at +0x08. Its canonical
// destructor pin and the former private Filter name both resolve to 0x360D26.
#include "../../../../Include/GameLogic/Module/Rva003623E5Member.h"

class __declspec(novtable) CivilianSpawnCollideModuleData : public Snapshot
{
public:
	virtual ~CivilianSpawnCollideModuleData();

private:
	int m_unused04; // +0x04 tag
	Rva003623E5Member m_filter; // +0x08
};

CivilianSpawnCollideModuleData::~CivilianSpawnCollideModuleData()
{
}
