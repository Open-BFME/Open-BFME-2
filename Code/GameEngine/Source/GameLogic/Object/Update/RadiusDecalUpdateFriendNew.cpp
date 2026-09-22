// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RadiusDecalUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024E4B5, 56 bytes. Dedicated TU: retail news 0x34 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x39148A. Class identity is the
// "RadiusDecalUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RadiusDecalUpdate
{
public:
	RadiusDecalUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x34];
};

// ?friend_newModuleInstance@RadiusDecalUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RadiusDecalUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RadiusDecalUpdate(thing, moduleData));
}
