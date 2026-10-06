// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RainOfFireUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F3B3, 56 bytes. Dedicated TU: retail news 0x38 (push-imm8)
// and runs the pinned Update ctor (0x4AC0A8, UpdateModule base plus table
// slot plus frame plus float state; 0.9 partial stash banked) with the Thing
// plus ModuleData args. Operator new and __EH_prolog resolve via their rows.
// Recipe: AIGateUpdateFriendNew.cpp. Class identity is the RainOfFireUpdate
// retail cluster (pool key at 0x4AC172, ModuleData triple rowed at
// 0x4AC03D/0x4AC097/0x24F3EB).

class Thing;
class ModuleData;
class Module;

class RainOfFireUpdate
{
public:
	RainOfFireUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x38];
};

// ?friend_newModuleInstance@RainOfFireUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RainOfFireUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RainOfFireUpdate(thing, moduleData));
}
