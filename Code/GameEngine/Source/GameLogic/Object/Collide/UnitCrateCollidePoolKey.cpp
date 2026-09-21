// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva00004BCC5C@UnitCrateCollide@@SA?AW4NameKeyType@@XZ @0x4BCC5C
// (69B): cached pool-name key for UnitCrateCollide. The class
// identity comes from the pool-name string the body pushes
// ("UnitCrateCollide"); the body guards a function-local static
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

class UnitCrateCollide
{
public:
	static NameKeyType rva00004BCC5C();
};

// ?rva00004BCC5C@UnitCrateCollide@@SA?AW4NameKeyType@@XZ
NameKeyType UnitCrateCollide::rva00004BCC5C()
{
	static NameKeyType TheUnitCrateCollidePoolKey =
		TheNameKeyGenerator->nameToKey("UnitCrateCollide");
	return TheUnitCrateCollidePoolKey;
}
