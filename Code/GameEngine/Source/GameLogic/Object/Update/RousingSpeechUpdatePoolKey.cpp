// cl: /DNDEBUG /MD /EHsc
// ?rva0004ACED8@RousingSpeechUpdate@@SA?AW4NameKeyType@@XZ @0x4ACED8
// (69B): cached pool-name key for RousingSpeechUpdate. The class
// identity comes from the pool-name string the body pushes
// ("RousingSpeechUpdate"); the body guards a function-local static
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

class RousingSpeechUpdate
{
public:
	static NameKeyType rva0004ACED8();
};

// ?rva0004ACED8@RousingSpeechUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType RousingSpeechUpdate::rva0004ACED8()
{
	static NameKeyType TheRousingSpeechUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("RousingSpeechUpdate");
	return TheRousingSpeechUpdatePoolKey;
}
