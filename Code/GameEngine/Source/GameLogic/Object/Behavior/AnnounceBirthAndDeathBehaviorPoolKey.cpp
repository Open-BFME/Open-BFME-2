// cl: /DNDEBUG /MD /EHsc
// ?rva000485163@AnnounceBirthAndDeathBehavior@@SA?AW4NameKeyType@@XZ @0x485163
// (69B): cached pool-name key for AnnounceBirthAndDeathBehavior. The class
// identity comes from the pool-name string the body pushes
// ("AnnounceBirthAndDeathBehavior"); the body guards a function-local static
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

class AnnounceBirthAndDeathBehavior
{
public:
	static NameKeyType rva000485163();
};

// ?rva000485163@AnnounceBirthAndDeathBehavior@@SA?AW4NameKeyType@@XZ
NameKeyType AnnounceBirthAndDeathBehavior::rva000485163()
{
	static NameKeyType TheAnnounceBirthAndDeathBehaviorPoolKey =
		TheNameKeyGenerator->nameToKey("AnnounceBirthAndDeathBehavior");
	return TheAnnounceBirthAndDeathBehaviorPoolKey;
}

