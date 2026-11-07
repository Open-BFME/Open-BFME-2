// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// ?onBuildComplete@LockWeaponCreate@@UAEXXZ
// retail 0x004B8CC9, 21 bytes: slot 1 of LockWeaponCreate's create-interface table
// 0x00C592EC (installed by its constructor 0x004B8C0E and destructor 0x004B8C3E).
// Zero Hour's LockWeaponCreate::onBuildComplete: the inline CreateModule base call
// clears m_needToRunOnBuildComplete (+0x14), then the object's weapon slot from the
// module data (+8) is locked permanently (2) through the rowed Object::setWeaponLock.
class Thing;
class ModuleData;
class Xfer;
#include "../../Include/GameLogic/Module/LockWeaponCreate.h"
enum WeaponLockType { LOCKED_PERMANENTLY = 2 };
#include "../GameLogic/Object/object.h"

void LockWeaponCreate::onBuildComplete()
{
	CreateModule::onBuildComplete();
	getObject()->setWeaponLock( getLockWeaponCreateModuleData()->m_slotToLock, LOCKED_PERMANENTLY );
}
