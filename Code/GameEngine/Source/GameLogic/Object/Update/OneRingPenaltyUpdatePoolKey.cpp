// cl: /DNDEBUG /MD /EHsc
// ?rva0004999AC@OneRingPenaltyUpdate@@SA?AW4NameKeyType@@XZ @0x4999AC
// (69B): cached pool-name key for OneRingPenaltyUpdate. The class
// identity comes from the pool-name string the body pushes
// ("OneRingPenaltyUpdate"); the body guards a function-local static
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

class OneRingPenaltyUpdate
{
public:
	static NameKeyType rva0004999AC();
};

// ?rva0004999AC@OneRingPenaltyUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType OneRingPenaltyUpdate::rva0004999AC()
{
	static NameKeyType TheOneRingPenaltyUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("OneRingPenaltyUpdate");
	return TheOneRingPenaltyUpdatePoolKey;
}
