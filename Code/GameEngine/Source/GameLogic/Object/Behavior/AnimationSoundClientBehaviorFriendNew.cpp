// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AnimationSoundClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00252B8A, 56 bytes. Dedicated TU: retail news 0x1C (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x4CA05A. Class identity is the
// "AnimationSoundClientBehavior" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class AnimationSoundClientBehavior
{
public:
	AnimationSoundClientBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x1C];
};

// ?friend_newModuleInstance@AnimationSoundClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AnimationSoundClientBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AnimationSoundClientBehavior(thing, moduleData));
}
