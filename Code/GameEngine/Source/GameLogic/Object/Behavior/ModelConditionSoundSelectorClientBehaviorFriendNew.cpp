// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@ModelConditionSoundSelectorClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00255C26, 56 bytes. Dedicated TU: retail news 0x10 (push-imm8) and
// runs the rowed behavior ctor (0x00254B82, Rva00252B68 base plus vtable
// re-stores) with the Thing plus ModuleData args. Operator new and
// __EH_prolog resolve via their rows. Recipe:
// PlayerHealSpecialPowerFriendNew.cpp. Class identity is the SoundSelector
// retail cluster (pool key rowed at 0x00254BAC starting exactly where the
// behavior ctor ends plus name getter rowed at 0x00254BF1 plus primary
// vtable 0x007F3220 with the class string adjacent; this factory is the
// sole raw caller of the behavior ctor).
class Thing;
class ModuleData;
class Module;

class ModelConditionSoundSelectorClientBehavior
{
public:
	ModelConditionSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x10];
};

// ?friend_newModuleInstance@ModelConditionSoundSelectorClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z @0x255C26
Module *ModelConditionSoundSelectorClientBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new ModelConditionSoundSelectorClientBehavior(thing, moduleData));
}
