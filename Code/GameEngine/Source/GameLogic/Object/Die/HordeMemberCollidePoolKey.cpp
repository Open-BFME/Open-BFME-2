// cl: /DNDEBUG /MD /EHsc
// ?rva0004BC344@HordeMemberCollide@@SA?AW4NameKeyType@@XZ @0x4BC344
// (69B): cached pool-name key for HordeMemberCollide. The class
// identity comes from the pool-name string the body pushes
// ("HordeMemberCollide"); the body guards a function-local static
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

class HordeMemberCollide
{
public:
	static NameKeyType rva0004BC344();
};

// ?rva0004BC344@HordeMemberCollide@@SA?AW4NameKeyType@@XZ
NameKeyType HordeMemberCollide::rva0004BC344()
{
	static NameKeyType TheHordeMemberCollidePoolKey =
		TheNameKeyGenerator->nameToKey("HordeMemberCollide");
	return TheHordeMemberCollidePoolKey;
}
