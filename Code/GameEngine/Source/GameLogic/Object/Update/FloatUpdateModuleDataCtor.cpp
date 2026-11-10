// cl: /MD /O1 /GX /DNDEBUG
//
// ??0FloatUpdateModuleData@@QAE@XZ, retail 0x0048D7A6,
// 12 bytes. Frameless store-only ctor over table 0xC4C7A4 (Enabled@8).
// Identity is the rowed poolkey 0x48D761 (FloatUpdate), which ends
// exactly where this ctor begins, plus factory 0x24D0F1 (news 0xC, sole
// caller) plus proc 0x48D7B3 (same table).
// Vtable 0x00C4ED70 is the shared 31-slot ModuleData table (ICF-folded);
// canonical ModuleData.h declares ModuleData() __declspec(dllimport)
// __forceinline so this unit emits no ??0ModuleData@@QAE@XZ COMDAT and
// installs the 31-slot table.

#include "../../../../Include/Common/ModuleData.h"

class FloatUpdateModuleData : public ModuleData
{
public:
	FloatUpdateModuleData();

private:
	bool m_enabled;
};

// ??0FloatUpdateModuleData@@QAE@XZ @0x48D7A6
FloatUpdateModuleData::FloatUpdateModuleData()
{
	m_enabled = false;
}
