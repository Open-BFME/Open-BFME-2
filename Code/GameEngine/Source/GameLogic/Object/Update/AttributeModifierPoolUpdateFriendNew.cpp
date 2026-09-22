// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@AttributeModifierPoolUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z.
// Identity: ModuleFactory registers this instance factory under "AttributeModifierPoolUpdate"
// (addModule pairs the name with it). news 0xA8 and runs the declared-only
// module ctor, pinned at 0x00403BEF.

class Thing;
class ModuleData;
class Module;

class AttributeModifierPoolUpdate
{
public:
	AttributeModifierPoolUpdate(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0xA8];
};

// ?friend_newModuleInstance@AttributeModifierPoolUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AttributeModifierPoolUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new AttributeModifierPoolUpdate(thing, moduleData));
}
