// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AIGateUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024FA2C, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the rowed Update ctor (0x4B08E8, UpdateModule base plus zeroed
// state) with the Thing plus ModuleData args. Operator new and __EH_prolog
// resolve via their rows. Recipe: PrisonDockUpdateFriendNew.cpp. Class
// identity is the AIGateUpdate retail cluster (pool key rowed at 0x4B087C,
// ModuleData triple rowed at 0x4B08C1/0x4B08D7/0x24FA64).

class Thing;
class ModuleData;
class Module;

class AIGateUpdate
{
public:
	AIGateUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@AIGateUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AIGateUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AIGateUpdate(thing, moduleData));
}
