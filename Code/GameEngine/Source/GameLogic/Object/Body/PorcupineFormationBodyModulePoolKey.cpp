// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva0004C2034@PorcupineFormationBodyModule@@SA?AW4NameKeyType@@XZ @0x4C2034
// (69B): cached pool-name key for PorcupineFormationBodyModule. The class
// identity comes from the pool-name string the body pushes
// ("PorcupineFormationBodyModule"); the body guards a function-local static
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

class PorcupineFormationBodyModule
{
public:
	static NameKeyType rva0004C2034();
};

// ?rva0004C2034@PorcupineFormationBodyModule@@SA?AW4NameKeyType@@XZ
NameKeyType PorcupineFormationBodyModule::rva0004C2034()
{
	static NameKeyType ThePorcupineFormationBodyModulePoolKey =
		TheNameKeyGenerator->nameToKey("PorcupineFormationBodyModule");
	return ThePorcupineFormationBodyModulePoolKey;
}
