// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RousingSpeechUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F551, 59 bytes. Dedicated TU: retail news 0x9C (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4ACF76. Class identity is the
// "RousingSpeechUpdate" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RousingSpeechUpdate
{
public:
	RousingSpeechUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x9C];
};

// ?friend_newModuleInstance@RousingSpeechUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RousingSpeechUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RousingSpeechUpdate(thing, moduleData));
}
