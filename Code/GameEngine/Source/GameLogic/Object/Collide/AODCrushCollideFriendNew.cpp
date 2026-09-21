// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AODCrushCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0025101E, 56 bytes. Dedicated TU: retail news 0x30 (push-imm8)
// and runs the rowed behavior ctor (0x004BC00D, UpdateModule base plus
// CrushCollide-level stores) with the Thing plus ModuleData args. Operator
// new and __EH_prolog resolve via their rows. Recipe:
// SalvageCrateCollideFriendNew.cpp. Class identity is the AODCrush retail
// cluster (pool key rowed at 0x004BBF44, behavior ctor rowed at 0x004BC00D
// as the sole callee here).
class Thing;
class ModuleData;
class Module;

class AODCrushCollide
{
public:
	AODCrushCollide(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x30];
};

// ?friend_newModuleInstance@AODCrushCollide@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AODCrushCollide::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AODCrushCollide(thing, moduleData));
}
