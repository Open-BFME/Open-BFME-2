// cl: /DNDEBUG /MD
//
// ObjectRecoveryHelper::update, retail 0x004DF84F (20 bytes): slot 0 of the
// class's +0x10 update-module interface table 0x00BFBD8C, so `this` is that
// subobject (the Object at -0x08). Runs slot 3 of the Object's body module
// (+0x254) and sleeps forever until woken again.
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class BodyModuleInterface
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void rvaSlot3() = 0;
};
#include "../object.h"
class ModuleData;
#include "../../../../Include/GameLogic/Module/ModuleBase.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"
class ObjectHelper : public ModuleBase, public BehaviorModuleInterface, public UpdateModuleInterface
{
};
class ObjectRecoveryHelper : public ObjectHelper
{
public:
	virtual UpdateSleepTime update();
};
UpdateSleepTime ObjectRecoveryHelper::update()
{
	m_object->getBodyModule()->rvaSlot3();
	return UPDATE_SLEEP_FOREVER;
}
