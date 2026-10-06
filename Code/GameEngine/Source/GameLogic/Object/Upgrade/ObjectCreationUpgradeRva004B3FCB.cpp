// cl: /DNDEBUG /MD
// ?rva004B3FCB@UpdateModule@@QAEXXZ @0x004B3FCB 17B evidence vtable 0x0085762C slot 1 plus callers none plus base loadPostProcess plus StringBase validate
// Virtual slot 1 of ObjectCreationUpgrade's UpdateModule vtable at +8: calls
// UpdateModule::loadPostProcess on this, then tail-jmps to StringBase validate
// on this-8 (the UpgradeMux head). Layout from ObjectCreationUpgradeDtor.cpp:
// UpgradeMux at +0, UpdateModule at +8. Shape follows Rva005FED59Validate.cpp
// (friend-private validate via cast) with a preceding base call, giving
// push esi / mov esi,ecx / call / lea ecx,[esi-8] / pop esi / jmp at /O1.
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
	virtual void behaviorAnchor();

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
protected:
	virtual void loadPostProcess();
public:
	virtual ~UpdateModule();
	void rva004B3FCB();
};

template <typename T> class StringBase
{
	friend class UpdateModule;
	void validate() const;
};

class ObjectCreationUpgrade : public UpgradeMux, public UpdateModule
{
public:
	ObjectCreationUpgrade(Thing *thing, const ModuleData *moduleData);

protected:
	virtual ~ObjectCreationUpgrade();
};

void UpdateModule::rva004B3FCB()
{
	UpdateModule::loadPostProcess();
	return ((StringBase<unsigned short> *)((char *)this - 8))->validate();
}
