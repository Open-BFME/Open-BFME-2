// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@DestroyEnvironmentUpdate@@UBE?AW4NameKeyType@@XZ @0x4AC686
// (69B): cached pool-name key for DestroyEnvironmentUpdate. The class
// identity comes from the pool-name string the body pushes
// ("DestroyEnvironmentUpdate"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType { NK_UNKNOWN = 0 };

class UpdateModule
{
public:
	virtual ~UpdateModule();
private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

enum UpdateSleepTime { UPDATE_SLEEP_INVALID = 0 };

// The update interface at +0x10: retail's DestroyEnvironmentUpdate table there (0x00C54D58)
// holds DestroyEnvironmentUpdate::update (rowed) in slot 0.
class DestroyEnvironmentUpdate_B2
{
public:
	virtual UpdateSleepTime update() = 0;
};

class DestroyEnvironmentUpdate : public UpdateModule, public MiBase1, public DestroyEnvironmentUpdate_B2
{
public:
	virtual ~DestroyEnvironmentUpdate();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();
	void rva004AC722();
private:
	char m_pad14[0x0C];
	unsigned int m_nextCallFrame;
	unsigned int m_objectID;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// ?getModuleNameKey@DestroyEnvironmentUpdate@@UBE?AW4NameKeyType@@XZ
NameKeyType DestroyEnvironmentUpdate::getModuleNameKey() const
{
	static NameKeyType TheDestroyEnvironmentUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("DestroyEnvironmentUpdate");
	return TheDestroyEnvironmentUpdatePoolKey;
}
