// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@PropagandaTowerBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C1E3, 56 bytes. Dedicated TU: retail news 0x30 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4819CF. Class identity is the
// "PropagandaTowerBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class PropagandaTowerBehavior
{
public:
	PropagandaTowerBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x30];
};

// ?friend_newModuleInstance@PropagandaTowerBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *PropagandaTowerBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new PropagandaTowerBehavior(thing, moduleData));
}
