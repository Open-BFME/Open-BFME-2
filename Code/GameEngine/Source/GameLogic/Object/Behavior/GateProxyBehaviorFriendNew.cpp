// cl: /O1 /GX /DNDEBUG /MD
//
// ?friend_newModuleInstance@GateProxyBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z,
// retail 0x00253F70, 65 bytes. Dedicated TU: retail news 0x50 and runs the
// rowed GateProxyBehavior ctor (0x24E2CC, MI over the GateOpenAndClose base
// plus the derived int at +0x4C) with the Thing plus ModuleData args, then
// returns the new behavior as the secondary Module interface at +4 through a
// null-safe derived-to-base conversion (retail neg-sbb-and). Operator new and
// __EH_prolog resolve via their rows. Recipe: the 65B GateOpenAndClose
// behavior factory with the MI-mirror class from the rowed 53B proxy ctor TU.
// Class identity is the GateProxyBehavior pool key (rowed at 0x24E30E).

class Thing;
class ModuleData;

class Module
{
public:
	virtual ~Module();
};

class PrimaryModuleBase
{
public:
	virtual ~PrimaryModuleBase();
};

class ProxyPad8
{
public:
	unsigned char m_pad[8];
};

class GateProxyBehavior : public PrimaryModuleBase, public Module, public ProxyPad8
{
public:
	GateProxyBehavior(Thing *thing, const ModuleData *moduleData);
	static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_pad2[0x4C - 0x10];
	int m_unk4C;
};

// ?friend_newModuleInstance@GateProxyBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GateProxyBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *moduleData)
{
	return new GateProxyBehavior(thing, moduleData);
}
