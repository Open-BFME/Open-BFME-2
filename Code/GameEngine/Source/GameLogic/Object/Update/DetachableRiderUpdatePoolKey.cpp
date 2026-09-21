// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004AE832@DetachableRiderUpdate@@SA?AW4NameKeyType@@XZ @0x4AE832
// (69B): cached pool-name key for DetachableRiderUpdate. The class
// identity comes from the pool-name string the body pushes
// ("DetachableRiderUpdate"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key not a pool pointer) and returns it
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail no pins; nameToKey resolves via its matched row).

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

class DetachableRiderUpdate
{
public:
	static NameKeyType rva004AE832();
};

// ?rva004AE832@DetachableRiderUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType DetachableRiderUpdate::rva004AE832()
{
	static NameKeyType TheDetachableRiderUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("DetachableRiderUpdate");
	return TheDetachableRiderUpdatePoolKey;
}
