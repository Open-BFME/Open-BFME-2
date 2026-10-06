// cl: /DNDEBUG /MD /EHsc
// ?rva000486598@FXListDie@@SA?AW4NameKeyType@@XZ @0x486598
// (69B): cached pool-name key for FXListDie. The class
// identity comes from the pool-name string the body pushes
// ("FXListDie"); the body guards a function-local static
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

class FXListDie
{
public:
	static NameKeyType rva000486598();
};

// ?rva000486598@FXListDie@@SA?AW4NameKeyType@@XZ
NameKeyType FXListDie::rva000486598()
{
	static NameKeyType TheFXListDiePoolKey =
		TheNameKeyGenerator->nameToKey("FXListDie");
	return TheFXListDiePoolKey;
}
