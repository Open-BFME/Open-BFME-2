// cl: /DNDEBUG /MD
//
// ??1ObjectCreationUpgrade@@MAE@XZ, retail 0x004B3F90, 36 bytes.
// ObjectCreationUpgrade behavior dtor: four vptr stores (+0x00 0x857660
// +0x08 0x85762C +0x14 0x857570 +0x18 0x857560, DIR32) then tail-jmp to the
// UpdateModule base dtor (pin ??1UpdateModule@@UAE@XZ at 0x0024A797).
// Layout is UpgradeMux base at +0 (vptr plus bool) plus UpdateModule base
// at +8 (BehaviorModule 0x0C plus two interface vptrs at +0x14/+0x18).
// UpgradeMux dtor is trivial bool so only the UpdateModule call remains.
// Identity is the ObjectCreationUpgrade cluster: dtor 0x004B3F90 plus name
// 0x004B3FB4 returning ObjectCreationUpgrade plus pool key 0x004B3FF5 plus
// ctor 0x004B40A6 plus deleting dtor 0x004B40EA calling here. Donor is ZH
// ObjectCreationUpgrade.cpp:79 trivial dtor. Shape follows ArmorUpgradeDtor
// (four vptrs plus tail-jmp, protected virtual MAE).

class Thing;
class ModuleData;

class UpgradeMux
{
public:
	virtual void muxAnchor();

private:
	bool m_executed;
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();

private:
	unsigned char m_data[8];
};

class BehaviorModuleInterface
{
public:
	virtual void ifaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual void updateAnchor();
};

class UpdateModule : public BehaviorModule,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();
};

class ObjectCreationUpgrade : public UpgradeMux, public UpdateModule
{
public:
	ObjectCreationUpgrade(Thing *thing, const ModuleData *moduleData);

protected:
	virtual ~ObjectCreationUpgrade();
};

// ??1ObjectCreationUpgrade@@MAE@XZ @0x004B3F90
ObjectCreationUpgrade::~ObjectCreationUpgrade()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?ifaceAnchor@BehaviorModuleInterface@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?muxAnchor@UpgradeMux@@UAEXXZ=?Is_Valid@RegistryClass@@QAE_NXZ")
