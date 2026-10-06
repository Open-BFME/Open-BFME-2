// cl: /DNDEBUG /MD /EHsc
// ?rva00045BFD9@BezierProjectileBehavior@@SA?AW4NameKeyType@@XZ @0x45BFD9
// (69B): cached pool-name key for BezierProjectileBehavior. The class
// identity comes from the pool-name string the body pushes
// ("BezierProjectileBehavior"); the body guards a function-local static
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

class BezierProjectileBehavior
{
public:
	static NameKeyType rva00045BFD9();
};

// ?rva00045BFD9@BezierProjectileBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType BezierProjectileBehavior::rva00045BFD9()
{
	static NameKeyType TheBezierProjectileBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("BezierProjectileBehavior");
	return TheBezierProjectileBehaviorPoolKey;
}
