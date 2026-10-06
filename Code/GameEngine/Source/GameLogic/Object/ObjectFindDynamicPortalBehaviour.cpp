// cl: /DNDEBUG /MD /EHsc
// ?rva004608E0@DynamicPortalBehaviour@@SAPAVModule@@PAVObject@@@Z @0x004608E0 108B: static DynamicPortalBehaviour lookup over an Object guards a function-local NameKeyType for DynamicPortalBehaviour through TheNameKeyGenerator then scans the null-terminated module list at +0x244 comparing virtual slot 0x10 and returns the match or null. Plain ret proves static member not thiscall. Class from string at 0x007F5AAC. Callers at 0x002CB44C 0x002EC7B6 0x002F2704 0x00345658 0x004C573F 0x004C5CF3 0x004C6035. Recipe WallUpgradeUpdateFind precedent 81B with inlined direct-return loop giving 108B.

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

class Module
{
public:
	virtual void _dtor() = 0;
	virtual void _r1() = 0;
	virtual void _r2() = 0;
	virtual void _r3() = 0;
	virtual NameKeyType getModuleNameKey() const = 0;
};

class Object
{
public:
	char pad[0x244];
	Module **m_modules;
};

class DynamicPortalBehaviour
{
public:
	static Module *rva004608E0(Object *obj);
};

Module *DynamicPortalBehaviour::rva004608E0(Object *obj)
{
	static NameKeyType key_DynamicPortalBehaviour =
		TheNameKeyGenerator->nameToKey("DynamicPortalBehaviour");
	for (Module **at = obj->m_modules; *at; ++at)
	{
		if ((*at)->getModuleNameKey() == key_DynamicPortalBehaviour)
		{
			return *at;
		}
	}
	return 0;
}
