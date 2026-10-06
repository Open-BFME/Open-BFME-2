// cl: /DNDEBUG /MD /EHsc
// ?rva000403A61@AttributeModifierPoolUpdate@@SA?AW4NameKeyType@@XZ @0x403A61
// (69B): cached pool-name key for AttributeModifierPoolUpdate. The class
// identity comes from the pool-name string the body pushes
// ("AttributeModifierPoolUpdate"); the body guards a function-local static
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

class AttributeModifierPoolUpdate
{
public:
	static NameKeyType rva000403A61();
};

// ?rva000403A61@AttributeModifierPoolUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType AttributeModifierPoolUpdate::rva000403A61()
{
	static NameKeyType TheAttributeModifierPoolUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("AttributeModifierPoolUpdate");
	return TheAttributeModifierPoolUpdatePoolKey;
}
