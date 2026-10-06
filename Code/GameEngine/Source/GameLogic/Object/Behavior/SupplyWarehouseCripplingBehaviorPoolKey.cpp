// cl: /DNDEBUG /MD /EHsc
// ?rva000483A1C@SupplyWarehouseCripplingBehavior@@SA?AW4NameKeyType@@XZ @0x483a1c
// (69B): cached pool-name key for SupplyWarehouseCripplingBehavior. The class
// identity comes from the pool-name string the body pushes
// ("SupplyWarehouseCripplingBehavior"); the body guards a function-local static
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

class SupplyWarehouseCripplingBehavior
{
public:
	static NameKeyType rva000483A1C();
};

// ?rva000483A1C@SupplyWarehouseCripplingBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType SupplyWarehouseCripplingBehavior::rva000483A1C()
{
	static NameKeyType TheSupplyWarehouseCripplingBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("SupplyWarehouseCripplingBehavior");
	return TheSupplyWarehouseCripplingBehaviorPoolKey;
}

