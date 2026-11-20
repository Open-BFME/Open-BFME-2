// cl: /MD
//
// ??1MonsterDockUpdate@@MAE@XZ, retail 0x004A13F4, 32 bytes. Protected
// virtual destructor completing the MonsterDockUpdate file-unit (ctor rowed
// at 0x4A139A in MonsterDockUpdateCtor.cpp, pool-key getter rowed at
// 0x4A1414, vtable 0x00851D74). Donor: BFME1
// MonsterDockUpdateDestructor.cpp protected virtual ~MonsterDockUpdate.
// The body restores the four vtable pointers of the complete object -- the
// derived slot at +0x00 (0x851D74) plus the +0x0C (0x851B20), +0x10
// (0x851D68) and +0x20 (0x851D18) secondary slots -- then tail-jumps to
// ~DockUpdate (0x0058A0F4).
// Those four vptrs are UpdateModule's three and DockUpdateInterface's, the
// DockUpdate view SupplyWarehouseDockUpdate.cpp compiles against
// (SupplyWarehouseDockUpdateNative.h, whose SupplyWarehouseDockUpdate tables
// are retail's). MonsterDockUpdate declares only its destructor here.
// Caller: scalar deleting dtor at 0x004A1459.

#include "DockUpdate/SupplyWarehouseDockUpdateNative.h"

class MonsterDockUpdate : public DockUpdate
{
protected:
	virtual ~MonsterDockUpdate();
};

MonsterDockUpdate::~MonsterDockUpdate()
{
}
