// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva000253DB2@HordeNotifyTargetsOfImminentProbableCrushingUpdate@@SA?AW4NameKeyType@@XZ @0x253DB2
// (69B): cached pool-name key for HordeNotifyTargetsOfImminentProbableCrushingUpdate. The class
// identity comes from the pool-name string the body pushes
// ("HordeNotifyTargetsOfImminentProbableCrushingUpdate"); the body guards a function-local static
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

class HordeNotifyTargetsOfImminentProbableCrushingUpdate
{
public:
	static NameKeyType rva000253DB2();
};

// ?rva000253DB2@HordeNotifyTargetsOfImminentProbableCrushingUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType HordeNotifyTargetsOfImminentProbableCrushingUpdate::rva000253DB2()
{
	static NameKeyType TheHordeNotifyTargetsOfImminentProbableCrushingUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("HordeNotifyTargetsOfImminentProbableCrushingUpdate");
	return TheHordeNotifyTargetsOfImminentProbableCrushingUpdatePoolKey;
}
