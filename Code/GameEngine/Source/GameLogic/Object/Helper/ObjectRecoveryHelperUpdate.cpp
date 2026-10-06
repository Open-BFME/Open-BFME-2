// cl: /O1 /DNDEBUG /MD
//
// ObjectRecoveryHelper::update, retail 0x004DF84F (20 bytes): slot 0 of the
// class's +0x10 update-module interface table 0x00BFBD8C, so `this` is that
// subobject (the Object at -0x08). Runs slot 3 of the Object's body module
// (+0x254) and sleeps forever until woken again.
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class BodyModuleInterface
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void rvaSlot3() = 0;
};
class Object
{
public:
	BodyModuleInterface *getBodyModule() const { return m_body; }
private:
	unsigned char m_pad000[0x254];
	BodyModuleInterface *m_body;	// +0x254
};
class ModuleData;
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
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class ObjectHelper : public ModuleBase, public BehaviorModuleInterface, public UpdateModuleInterface
{
};
class ObjectRecoveryHelper : public ObjectHelper
{
public:
	virtual UpdateSleepTime update();
};
UpdateSleepTime ObjectRecoveryHelper::update()
{
	m_object->getBodyModule()->rvaSlot3();
	return UPDATE_SLEEP_FOREVER;
}
