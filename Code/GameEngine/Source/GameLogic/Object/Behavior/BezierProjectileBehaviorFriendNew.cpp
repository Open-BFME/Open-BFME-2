// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@BezierProjectileBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024B148, 59 bytes. Dedicated TU: retail news 0x88 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x45C850. Class identity is the
// "BezierProjectileBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class BezierProjectileBehavior
{
public:
	BezierProjectileBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x88];
};

// ?friend_newModuleInstance@BezierProjectileBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *BezierProjectileBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new BezierProjectileBehavior(thing, moduleData));
}
