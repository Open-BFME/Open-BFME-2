// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004B92A0@PreorderCreate@@SA?AW4NameKeyType@@XZ @0x004B92A0
// (69B): cached pool-name key for PreorderCreate. The class
// identity comes from the pool-name string the body pushes
// ("PreorderCreate"); the body guards a function-local static
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

class PreorderCreate
{
public:
	static NameKeyType rva004B92A0();
};

// ?rva004B92A0@PreorderCreate@@SA?AW4NameKeyType@@XZ
NameKeyType PreorderCreate::rva004B92A0()
{
	static NameKeyType ThePreorderCreatePoolKey =
		TheNameKeyGenerator->nameToKey("PreorderCreate");
	return ThePreorderCreatePoolKey;
}
