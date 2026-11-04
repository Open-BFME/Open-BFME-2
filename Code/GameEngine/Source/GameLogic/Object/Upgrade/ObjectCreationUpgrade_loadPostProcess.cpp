// cl: /DNDEBUG /MD
// ?loadPostProcess@ObjectCreationUpgrade@@MAEXXZ @0x004B3FCB 17B evidence vtable 0x0085762C slot 1 plus base loadPostProcess plus UpgradeMux hook
// ObjectCreationUpgrade::loadPostProcess: slot 1 of its UpdateModule vtable at
// +8, the loadPostProcess slot (198 of 223 named sibling tables). It is
// compiled with that subobject this: it calls
// UpdateModule::loadPostProcess on this, then tail-jmps to upgradeMuxLoadPostProcess
// on this-8 (the UpgradeMux head). Layout from ObjectCreationUpgradeDtor.cpp:
// UpgradeMux at +0, UpdateModule at +8. The mux hook is the rowed empty
// method at 0x000B3FD0, folded with other empty methods. The base calls give
// push esi / mov esi,ecx / call / lea ecx,[esi-8] / pop esi / jmp at /O1.
class Thing;
class ModuleData;

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"




enum NameKeyType
{
	NK_UNKNOWN = 0
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class Xfer;
class ObjectCreationUpgradeModuleData;
class Object;
class ObjectCreationUpgrade : public UpgradeMux, public UpdateModule
{
public:
	void rva004B463C();
	static NameKeyType rva004B3FF5();
protected:
	virtual void xfer(Xfer *xfer);
	virtual UpdateSleepTime update();
	const ObjectCreationUpgradeModuleData *getObjectCreationUpgradeModuleData() const { return (const ObjectCreationUpgradeModuleData *)getModuleData(); }
	Object *getObject() const { return m_object; }
public:
	ObjectCreationUpgrade(Thing *thing, const ModuleData *moduleData);
protected:
	virtual void loadPostProcess();
private:
	unsigned int m_status28; // +0x28
	bool m_flag2C; // +0x2C
	char m_pad2D[0x3];
};

void ObjectCreationUpgrade::loadPostProcess()
{
	UpdateModule::loadPostProcess();
	UpgradeMux::upgradeMuxLoadPostProcess();
}
