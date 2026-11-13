// cl: /DNDEBUG /MD
//
// ??1ReplaceSelfUpgrade@@MAE@XZ, retail 0x004B70EB, 5 bytes.
// ReplaceSelfUpgrade behavior dtor: trivial tail-jmp to the UpgradeModule
// base dtor (twin pin ??1UpgradeModule@@MAE@XZ at 0x0046089D, ICF-folded
// under the rowed ??1FireWeaponWhenDeadBehavior@@MAE@XZ there).
// No vptr stores: novtable suppresses the derived store retail lacks.
// Identity is vtable 0x00858B10 of the rowed ctor 0x004B7045 plus sole caller
// ??_G 0x004B70CF slot 0. Shape follows ArmorUpgradeDtor (UpgradeModule
// multi-inheritance, protected virtual MAE, trivial donor ZH ArmorUpgrade).

class Thing;
class ModuleData;

class Player;
#include "../object.h"

#include "../../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

class ControlBar;
extern ControlBar *TheControlBar;
struct ControlBarView
{
	unsigned char m_pad00[0x28];
	bool m_uiDirty;
};

#include "../../../../Include/GameLogic/Module/UpgradeModule.h"

#include "../../../../Include/GameLogic/Module/Rva004B70F0Iface1C.h"

class __declspec(novtable) ReplaceSelfUpgrade : public UpgradeModule, public Rva004B70F0Iface1C
{
public:
	ReplaceSelfUpgrade(Thing *thing, const ModuleData *moduleData);
	virtual void rva004B70F0();

protected:
	virtual ~ReplaceSelfUpgrade();
};

ReplaceSelfUpgrade::~ReplaceSelfUpgrade()
{
}

// ?rva004B70F0@ReplaceSelfUpgrade@@UAEXXZ @0x004B70F0
void ReplaceSelfUpgrade::rva004B70F0()
{
	Player *localPlayer = ThePlayerList->getLocalPlayer();
	if (localPlayer == m_object->getControllingPlayer())
		((ControlBarView *)TheControlBar)->m_uiDirty = true;
}
