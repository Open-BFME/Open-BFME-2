// cl: /O1 /DNDEBUG /MD
//
// ?rva0045F2D5@UpgradeMuxData@@QBEXAAUUpgradeMaskType@@0@Z, retail 0x0045F2D5,
// 35 bytes, and
// ?getUpgradeActivationMasks@SpawnBehavior@@MBEXAAUUpgradeMaskType@@0@Z,
// retail 0x0045F45F, 11 bytes.
//
// 0x0045F45F is slot 11 of SpawnBehavior's UpgradeMux vftable 0x00842550
// (slots 1 and 5 are the rowed UpgradeMux attemptUpgrade and
// forceRefreshUpgrade), the getUpgradeActivationMasks slot of the siblings in
// UpgradeMuxSlotOverrides.cpp. `this` is the UpgradeMux at SpawnBehavior +0x30,
// so the module data is [this-0x2C] and its UpgradeMuxData block sits at
// +0x5C (SpawnBehavior::update reads the same two masks there). Where those
// siblings copy the masks inline, this override tail-jumps to an out-of-line
// copy of the same two 0x80-byte masks, 0x0045F2D5. That copy is also the
// tail target of AudioLoopUpgrade's slot 11 (0x004B7E0E), so it is one shared
// UpgradeMuxData member; its real name is unknown, hence the address name.

class Object;
class ModuleData;

struct UpgradeMaskType
{
	unsigned int m_bits[32];
};

class UpgradeMuxData
{
public:
	void rva0045F2D5(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;

	UpgradeMaskType m_activation; // +0x00
	UpgradeMaskType m_conflicting; // +0x80
};

// ?rva0045F2D5@UpgradeMuxData@@QBEXAAUUpgradeMaskType@@0@Z @0x0045F2D5
void UpgradeMuxData::rva0045F2D5(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const
{
	activation = m_activation;
	conflicting = m_conflicting;
}

template <int N> class UpgradeMuxSlots : public UpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class UpgradeMuxSlots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

class SpawnBehaviorView
{
public:
	virtual ~SpawnBehaviorView();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x30 - 0x0C];
};

#include "../../../../Include/GameLogic/Module/SpawnBehaviorModuleData.h"

class SpawnBehavior : public SpawnBehaviorView, public UpgradeMux
{
protected:
	virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;
private:
	const SpawnBehaviorModuleData *getSpawnBehaviorModuleData() const { return (const SpawnBehaviorModuleData *)m_moduleData; }
};

// ?getUpgradeActivationMasks@SpawnBehavior@@MBEXAAUUpgradeMaskType@@0@Z @0x0045F45F
void SpawnBehavior::getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const
{
	reinterpret_cast<const UpgradeMuxData *>(&getSpawnBehaviorModuleData()->m_slot5C)->rva0045F2D5(activation, conflicting);
}
