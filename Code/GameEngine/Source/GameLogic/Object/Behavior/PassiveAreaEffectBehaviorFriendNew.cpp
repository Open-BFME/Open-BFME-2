// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@PassiveAreaEffectBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C6EC, 56 bytes. Dedicated TU: retail news 0x28 (push-imm8) and
// runs the rowed behavior ctor (0x00484A67, sole caller is this factory) with
// the Thing plus ModuleData args. Operator new and __EH_prolog resolve via
// their rows. Recipe: InvisibilityUpdateFriendNew.cpp. Class identity is the
// PassiveAreaEffectBehavior retail cluster (pool key rowed at 0x00484ADD,
// ModuleData triple rowed at 0x0048490E/0x00484DF4/0x0024C724).
class Thing;
class ModuleData;
class Module;

class PassiveAreaEffectBehavior
{
public:
	PassiveAreaEffectBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x28];
};

// ?friend_newModuleInstance@PassiveAreaEffectBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *PassiveAreaEffectBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new PassiveAreaEffectBehavior(thing, moduleData));
}
