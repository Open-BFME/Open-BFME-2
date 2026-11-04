// cl: /Ireference/shims/bfme2_ascii /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
// ??1CallHelpOnDamageModuleData@@UAE@XZ @ 0x004BB517 48B
// Implicit virtual dtor called by the rowed deleting dtor 0x004BB4FB (vtable slot 0):
// destroys the ValidObjects filter at +0x18 through the pinned
// Rva003623E5Filter dtor 0x00360D26, then restores the UpdateModuleData
// vtable 0x00BBB554 with no base call. Layout from the ctor 0x004BB3A7
// (Rva004bb3a7Finish.cpp). Byte-identical to, but not folded with, the
// TerrainResourceBehaviorModuleData dtor at 0x00482275, whose
// TerrainResourceBehaviorModuleDataDtor.cpp shape and flags this follows.
class BfmeFixedStorage0004543D;
class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();
	void applyFilter(BfmeFixedStorage0004543D storage);
private:
	int m_x; // +0x00
};
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Include/Common/BfmeModuleData.h"
// Retail teardown restores Snapshot's table. The intermediate update-data
// base contributes only the +4 name-key field, retained below.
inline ModuleData::~ModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }

class CallHelpOnDamageModuleData : public ModuleData
{
public:
	CallHelpOnDamageModuleData();
// Implicit virtual dtor (never declared, never defined)
private:
	int m_gap04;
	unsigned int m_mask;			// +8
	float m_callRadius;			// +0xC
	int m_callDelay;			// +0x10
	bool m_moveToAttacker;			// +0x14
	Rva003623E5Filter m_validObjects;	// +0x18
};
// The qualified call emits the implicit dtor without this TU defining the
// ctor (rowed in Rva004bb3a7Finish.cpp) or the vtable.
void destroyCallHelpOnDamageModuleData(CallHelpOnDamageModuleData *callHelpOnDamageModuleData)
{
	callHelpOnDamageModuleData->CallHelpOnDamageModuleData::~CallHelpOnDamageModuleData();
}
