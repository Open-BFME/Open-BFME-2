// cl: /DNDEBUG /MD /EHsc
// ?rva0004A393C@InvisibilityUpdate@@SA?AW4NameKeyType@@XZ @0x4A393C
// (69B): cached pool-name key for InvisibilityUpdate. The class
// identity comes from the pool-name string the body pushes
// ("InvisibilityUpdate"); the body guards a function-local static
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

class InvisibilityUpdate
{
public:
	static NameKeyType rva0004A393C();
	static NameKeyType rva0004A38BF();
};

// ?rva0004A393C@InvisibilityUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType InvisibilityUpdate::rva0004A393C()
{
	static NameKeyType TheInvisibilityUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("InvisibilityUpdate");
	return TheInvisibilityUpdatePoolKey;
}

// ?rva0004A38BF@InvisibilityUpdate@@SA?AW4NameKeyType@@XZ @0x4A38BF
// (69B): the same cached key shape over the same "InvisibilityUpdate"
// literal with its own static; this is the copy slot 4 of
// ??_7InvisibilityUpdate 0x00C52534 holds (the slot the other modules'
// pool-name keys occupy). Address name: which of the two is which member
// is not established.
NameKeyType InvisibilityUpdate::rva0004A38BF()
{
	static NameKeyType TheInvisibilityUpdateSlotKey =
		TheNameKeyGenerator->nameToKey("InvisibilityUpdate");
	return TheInvisibilityUpdateSlotKey;
}
