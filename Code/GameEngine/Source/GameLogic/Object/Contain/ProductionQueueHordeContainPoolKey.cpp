// cl: /DNDEBUG /MD /EHsc
// ?rva0004812B9@ProductionQueueHordeContain@@SA?AW4NameKeyType@@XZ @0x4812b9
// (69B): cached pool-name key for ProductionQueueHordeContain. The class
// identity comes from the pool-name string the body pushes
// ("ProductionQueueHordeContain"); the body guards a function-local static
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

class ProductionQueueHordeContain
{
public:
	static NameKeyType rva0004812B9();
};

// ?rva0004812B9@ProductionQueueHordeContain@@SA?AW4NameKeyType@@XZ
NameKeyType ProductionQueueHordeContain::rva0004812B9()
{
	static NameKeyType TheProductionQueueHordeContainPoolKey =
		TheNameKeyGenerator->nameToKey("ProductionQueueHordeContain");
	return TheProductionQueueHordeContainPoolKey;
}

