// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004B8EC1@SupplyWarehouseCreate@@SA?AW4NameKeyType@@XZ @0x004B8EC1
// (69B): cached pool-name key for SupplyWarehouseCreate. The class
// identity comes from the pool-name string the body pushes
// ("SupplyWarehouseCreate"); the body guards a function-local static
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

class SupplyWarehouseCreate
{
public:
	static NameKeyType rva004B8EC1();
};

// ?rva004B8EC1@SupplyWarehouseCreate@@SA?AW4NameKeyType@@XZ
NameKeyType SupplyWarehouseCreate::rva004B8EC1()
{
	static NameKeyType TheSupplyWarehouseCreatePoolKey =
		TheNameKeyGenerator->nameToKey("SupplyWarehouseCreate");
	return TheSupplyWarehouseCreatePoolKey;
}
