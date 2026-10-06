// cl: /DNDEBUG /MD /EHsc
// ?rva00049B5DC@AttributeModifierAuraUpdate@@SA?AW4NameKeyType@@XZ @0x49B5DC
// (69B): cached pool-name key for AttributeModifierAuraUpdate. The class
// identity comes from the pool-name string the body pushes
// ("AttributeModifierAuraUpdate"); the body guards a function-local static
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

class AttributeModifierAuraUpdate
{
public:
	static NameKeyType rva00049B5DC();
};

// ?rva00049B5DC@AttributeModifierAuraUpdate@@SA?AW4NameKeyType@@XZ
NameKeyType AttributeModifierAuraUpdate::rva00049B5DC()
{
	static NameKeyType TheAttributeModifierAuraUpdatePoolKey =
		TheNameKeyGenerator->nameToKey("AttributeModifierAuraUpdate");
	return TheAttributeModifierAuraUpdatePoolKey;
}
