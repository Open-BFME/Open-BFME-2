// cl: /O1 /DNDEBUG /MD
//
// InheritUpgradeCreate::onBuildComplete, retail 0x004B96A9 (27 bytes): slot 1
// of the class's +0x10 create-module interface vftable 0x00C596E4 (the
// matched ctor's), so `this` is that subobject. The Zero Hour shape: nothing
// unless shouldDoOnBuildComplete (slot 3, the byte at +0x14 / interface +4),
// then that flag is cleared and the class's create work 0x004B959C runs on the
// primary this (tail call; pinned by address on this call site, the body the
// +0x10 slot-2 thunk 0x004B96C4 also reaches).
typedef bool Bool;
class ModuleData;
class Object;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};
class CreateModuleInterface
{
public:
	virtual void c00() = 0;
	virtual void onBuildComplete() = 0;
	virtual void c02() = 0;
	virtual Bool shouldDoOnBuildComplete() = 0;
};
class CreateModule : public ModuleBase, public BehaviorModuleInterface, public CreateModuleInterface
{
protected:
	Bool m_needToRunOnBuildComplete;	// +0x14
};
class InheritUpgradeCreate : public CreateModule
{
public:
	virtual void onBuildComplete();
	void rva004B959C();
};
void InheritUpgradeCreate::onBuildComplete()
{
	if (!shouldDoOnBuildComplete())
		return;
	m_needToRunOnBuildComplete = false;
	rva004B959C();
}
