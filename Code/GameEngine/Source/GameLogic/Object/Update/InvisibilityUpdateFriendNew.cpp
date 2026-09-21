// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@InvisibilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024ECB4, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8) and
// runs the rowed Update ctor (0x004A382D, UpdateModule base plus vtable
// re-stores plus owner stealth byte) with the Thing plus ModuleData args.
// Operator new and __EH_prolog resolve via their rows. Recipe:
// PrisonDockUpdateFriendNew.cpp via DestroyEnvironmentUpdateFriendNew.cpp.
// Class identity is the InvisibilityUpdate retail cluster (pool key rowed at
// 0x004A393C, ModuleData triple rowed at 0x004A381C/0x0025553A/0x00255474-pin).
class Thing;
class ModuleData;
class Module;

class InvisibilityUpdate
{
public:
	InvisibilityUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@InvisibilityUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *InvisibilityUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new InvisibilityUpdate(thing, moduleData));
}
