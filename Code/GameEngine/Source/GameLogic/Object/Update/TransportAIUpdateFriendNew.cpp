// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@TransportAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024F192, 59 bytes. Dedicated TU: retail news 0x3E4 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4A9042. Class identity is the
// "TransportAIUpdate" literal ModuleFactory registers alongside this stub and the
// TransportAIUpdateModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class TransportAIUpdate
{
public:
	TransportAIUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x3E4];
};

// ?friend_newModuleInstance@TransportAIUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *TransportAIUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new TransportAIUpdate(thing, moduleData));
}
