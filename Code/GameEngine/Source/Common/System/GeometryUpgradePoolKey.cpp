// cl: /DNDEBUG /MD /EHsc
// ?rva0004B6ABF@GeometryUpgrade@@SA?AW4NameKeyType@@XZ @0x4B6ABF
// (69B): cached pool-name key for GeometryUpgrade. The class
// identity comes from the pool-name string the body pushes
// ("GeometryUpgrade"); the body guards a function-local static
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

class GeometryUpgrade
{
public:
	static NameKeyType rva0004B6ABF();
};

// ?rva0004B6ABF@GeometryUpgrade@@SA?AW4NameKeyType@@XZ
NameKeyType GeometryUpgrade::rva0004B6ABF()
{
	static NameKeyType TheGeometryUpgradePoolKey =
		TheNameKeyGenerator->nameToKey("GeometryUpgrade");
	return TheGeometryUpgradePoolKey;
}
