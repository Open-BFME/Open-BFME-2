// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@RefundDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x0024C819, 56 bytes. Dedicated TU: retail news 0x14 (push-imm8)
// and runs the (Thing*,ModuleData*) ctor at 0x485262. Class identity is the
// "RefundDie" literal ModuleFactory registers alongside this stub.
// Recipe: RainOfFireUpdateFriendNew.cpp.

class Thing;
class ModuleData;
class Module;

class RefundDie
{
public:
	RefundDie(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	char m_pad[0x14];
};

// ?friend_newModuleInstance@RefundDie@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RefundDie::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return reinterpret_cast<Module *>(new RefundDie(thing, moduleData));
}
