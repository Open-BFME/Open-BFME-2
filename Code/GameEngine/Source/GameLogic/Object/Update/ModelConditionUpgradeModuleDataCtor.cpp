// cl: /O1 /MD /DNDEBUG /arch:SSE /EHs-c-
//
// ??0ModelConditionUpgradeModuleData@@QAE@XZ, retail 0x004B6428, 89 bytes
// (frameless, no EH at all): base call into the rowed Rva00253487Base
// 0x253487, explicit vtable store at +0 (folded 0xBF2558, DIR32-masked),
// explicit init calls into 0x42526 for the two 0x4C condition members at
// +0x118/+0x164 (TU-spelling alias pin; the call order must follow the
// vtable store, so auto-init is impossible), 0x4C memsets, or-ff at +0x1B0,
// float zero at +0x1B4. The owning factory at 0x00250546 (news 0x1B8) is
// the sole caller. Row supersedes the ctor pin.
extern "C" const void *const vtbl_00BF2558[];  // ??_7WeaponSetUpgradeModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BF2558=??_7WeaponSetUpgradeModuleData@@6B@")

#include <cstring>

class Rva00253487Base
{
public:
	Rva00253487Base();

protected:
	unsigned char m_pad[0x118];
};

struct CondStore
{
	void init();

	unsigned char m_data[0x4C];
};

class ModelConditionUpgradeModuleData : public Rva00253487Base
{
public:
	ModelConditionUpgradeModuleData();

	CondStore m_118;
	CondStore m_164;
	int m_1B0;
	float m_1B4;
};

ModelConditionUpgradeModuleData::ModelConditionUpgradeModuleData()
	: Rva00253487Base()
{
	CondStore *stor118 = &m_118;
	*(unsigned int *)this = ((unsigned int)vtbl_00BF2558);
	stor118->init();
	CondStore *stor164 = &m_164;
	stor164->init();
	memset(stor118, 0, 0x4C);
	memset(stor164, 0, 0x4C);
	m_1B0 |= -1;
	m_1B4 = 0.0f;
}
