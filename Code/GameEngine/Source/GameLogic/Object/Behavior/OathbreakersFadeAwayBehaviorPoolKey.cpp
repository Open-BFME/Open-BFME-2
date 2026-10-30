// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@OathbreakersFadeAwayBehavior@@UBE?AW4NameKeyType@@XZ @0x004B89DD
// (69B): cached pool-name key for OathbreakersFadeAwayBehavior. The class
// identity comes from the pool-name string the body pushes
// ("OathbreakersFadeAwayBehavior"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../../Include/Common/ObjectModule.h"

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual void updateSlot(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class OathbreakersFadeAwayBehavior : public UpdateModule
{
public:
	const char *name() const;
	virtual NameKeyType getModuleNameKey() const;
	void rva004B8B0F();

protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_20;
	float m_24;
};

// ?getModuleNameKey@OathbreakersFadeAwayBehavior@@UBE?AW4NameKeyType@@XZ
NameKeyType OathbreakersFadeAwayBehavior::getModuleNameKey() const
{
	static NameKeyType TheOathbreakersFadeAwayBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("OathbreakersFadeAwayBehavior");
	return TheOathbreakersFadeAwayBehaviorPoolKey;
}
