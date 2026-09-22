// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@PorcupineFormationBodyModule@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x002517CF, 59 bytes. Dedicated TU: retail news 0x100 (push-imm32)
// and runs the (Thing*,ModuleData*) ctor at 0x4C1FE6. Class identity is the
// "PorcupineFormationBodyModule" literal ModuleFactory registers alongside this stub and the
// PorcupineFormationBodyModuleData::friend_newModuleData row. Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class PorcupineFormationBodyModule
{
public:
	PorcupineFormationBodyModule(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x100];
};

// ?friend_newModuleInstance@PorcupineFormationBodyModule@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *PorcupineFormationBodyModule::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new PorcupineFormationBodyModule(thing, moduleData));
}
