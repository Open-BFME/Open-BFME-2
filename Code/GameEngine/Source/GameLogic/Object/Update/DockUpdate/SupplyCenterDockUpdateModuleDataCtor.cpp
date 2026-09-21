// cl: /O1 /arch:SSE /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS
//
// SupplyCenterDockUpdateModuleData constructor 40B @0x4A10D5.
// BFME1 donor: Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/
// SupplyCenterDockUpdateModuleDataConstructorThunk.cpp (m_valueMultiplier 1.0,
// m_bonusScienceMultiplier 1.0, m_bonusScience -1) plus BFME2 table
// 0xC51A80 (ValueMultiplier@0x10 BonusScience@0x14 BonusScienceMultiplier@0x18)
// and factory 0x24EA14 (news 0x1C). Base DockUpdateModuleData ctor pinned at
// 0x5896B0. Vtable 0xC4ED70 is ICF-folded shared (DeletionUpdate, SlotToLock,
// ReflectDamage); DIR32-masked, no pin.

class DockUpdateModuleData
{
public:
	DockUpdateModuleData();
	virtual ~DockUpdateModuleData();
private:
	unsigned char m_basePad[0x0c];
};

class SupplyCenterDockUpdateModuleData : public DockUpdateModuleData
{
public:
	SupplyCenterDockUpdateModuleData();
	virtual ~SupplyCenterDockUpdateModuleData();
private:
	float m_valueMultiplier;
	int m_bonusScience;
	float m_bonusScienceMultiplier;
};

SupplyCenterDockUpdateModuleData::SupplyCenterDockUpdateModuleData()
{
	m_valueMultiplier = 1.0f;
	m_bonusScienceMultiplier = 1.0f;
	m_bonusScience = -1;
}
