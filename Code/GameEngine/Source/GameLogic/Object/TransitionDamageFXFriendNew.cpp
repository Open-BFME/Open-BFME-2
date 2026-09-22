// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@TransitionDamageFX@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00250D4F, 59 bytes. Dedicated TU: retail news 0xE0 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4BA3EA. Class identity is the
// "TransitionDamageFX" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class TransitionDamageFX
{
public:
	TransitionDamageFX(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0xE0];
};

// ?friend_newModuleInstance@TransitionDamageFX@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *TransitionDamageFX::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new TransitionDamageFX(thing, moduleData));
}
