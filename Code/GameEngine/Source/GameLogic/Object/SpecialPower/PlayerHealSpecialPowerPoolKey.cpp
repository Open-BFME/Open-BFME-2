// cl: /DNDEBUG /MD /EHsc
// ?getModuleNameKey@PlayerHealSpecialPower@@UBE?AW4NameKeyType@@XZ @0x4C7EFB
// (69B): cached pool-name key for PlayerHealSpecialPower. The class
// identity comes from the pool-name string the body pushes
// ("PlayerHealSpecialPower"); the body guards a function-local static
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

class Object;
struct Coord3D;
class ModuleData;
struct PlayerHealSpecialPowerModuleData;

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

class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void doSpecialPower(unsigned int options) = 0;
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options) = 0;
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options) = 0;
};

class SpecialPowerModule : public ModuleBase, public BehaviorModuleInterface,
	public SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPower(unsigned int options);					// 0x0049490F
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);		// 0x0049495B
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);	// 0x004949D8
};

class PlayerHealSpecialPower : public SpecialPowerModule
{
public:
	virtual NameKeyType getModuleNameKey() const;
	virtual void doSpecialPower(unsigned int options);
	virtual void doSpecialPowerAtObject(Object *obj, unsigned int options);
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int options);
	void rva004C8095(const Coord3D *loc);
	void rva004C7F5C(Object *obj); // the per-object heal
	const PlayerHealSpecialPowerModuleData *getPlayerHealSpecialPowerModuleData() const
	{
		return (const PlayerHealSpecialPowerModuleData *)m_moduleData;
	}
};

// ?getModuleNameKey@PlayerHealSpecialPower@@UBE?AW4NameKeyType@@XZ
NameKeyType PlayerHealSpecialPower::getModuleNameKey() const
{
	static NameKeyType ThePlayerHealSpecialPowerPoolKey =
		TheNameKeyGenerator->nameToKey("PlayerHealSpecialPower");
	return ThePlayerHealSpecialPowerPoolKey;
}
