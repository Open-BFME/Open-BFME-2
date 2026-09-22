// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@CitadelSlaughterHordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C0C5, 59 bytes. Dedicated TU: retail news 0x9F0 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x48059F. Class identity is the
// "CitadelSlaughterHordeContain" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class CitadelSlaughterHordeContain
{
public:
	CitadelSlaughterHordeContain(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x9F0];
};

// ?friend_newModuleInstance@CitadelSlaughterHordeContain@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *CitadelSlaughterHordeContain::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new CitadelSlaughterHordeContain(thing, moduleData));
}
