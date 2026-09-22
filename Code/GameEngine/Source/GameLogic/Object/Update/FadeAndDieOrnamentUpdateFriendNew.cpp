// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@FadeAndDieOrnamentUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024ED5F, 56 bytes. Dedicated TU: retail news 0x50 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x3A439D. Class identity is the
// "FadeAndDieOrnamentUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class FadeAndDieOrnamentUpdate
{
public:
	FadeAndDieOrnamentUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x50];
};

// ?friend_newModuleInstance@FadeAndDieOrnamentUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *FadeAndDieOrnamentUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new FadeAndDieOrnamentUpdate(thing, moduleData));
}
