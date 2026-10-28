// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@HordeTransportContain@@UBE?AW4NameKeyType@@XZ @0x477185
// (69B): cached pool-name key for HordeTransportContain. The class
// identity comes from the pool-name string the body pushes
// ("HordeTransportContain"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).


class Thing;
class Object;
class DamageInfo;
struct Rva0047727EObjectPositionView;
enum NameKeyType { NK_UNKNOWN = 0 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
enum ExitDoorType { DOOR_1 = 0 };

class OpenContain {
public:
	virtual void exitObjectViaDoor(Object *,ExitDoorType);
};

class TransportContain : public OpenContain {
public:
	virtual ~TransportContain();
	virtual UpdateSleepTime update();
};

// Retail stores no HordeTransportContain vptr (novtable): its dtor is a
// bare jmp to the TransportContain base dtor.
class __declspec(novtable) HordeTransportContain : public TransportContain {
public:
	virtual ~HordeTransportContain();
	virtual NameKeyType getModuleNameKey() const;
	virtual void onDie(const DamageInfo *damageInfo);
	virtual void exitObjectViaDoor(Object *,ExitDoorType);
	void rva004779F9();
	void rva0047778B();
	void rva004776E7(const struct Rva004776E7UpgradeMask *,bool);
	void rva0047727E(Thing *object);
	void rva0047748E();
private:
	unsigned char prefix04[4];
	Rva0047727EObjectPositionView *m_object;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// ?getModuleNameKey@HordeTransportContain@@UBE?AW4NameKeyType@@XZ
NameKeyType HordeTransportContain::getModuleNameKey() const
{
	static NameKeyType TheHordeTransportContainPoolKey =
		TheNameKeyGenerator->nameToKey("HordeTransportContain");
	return TheHordeTransportContainPoolKey;
}

