// cl: /Oy- /EHsc /MD
// ?rva00395C80@@YAHPAVObject@@@Z, native 00395C80 (107B).
// Cached CastleMemberBehavior module-key veto. The static wrapper keeps EH
// state open over nameToKey; findModule is the existing 0028B6D6 provider.
// Native 395CC9 tests module byte +25; 395CCF loads its canonical ModuleData
// pointer at +4, and 395CD2 tests data byte +19. A missing module or either
// clear flag returns true. The data pointer is dereferenced unconditionally
// after the module flag succeeds. No linked-list interpretation is implied.
// Flags/derived layouts retain address-based view names; the key literal
// proves the lookup key, not original class or function identities.

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
// Rva00BF5CCC was the retail address (RVA 0x007F5CCC) of the "CastleMemberBehavior" text; the literal is the source.

#include "../../../../Include/Common/Module.h"

// Partial storage views, not recovered original derived/data class identities.
class Rva00395C80ModuleView : public Module
{
public:
    using Module::m_moduleData;
    char m_pad08[0x25 - 0x08];
    unsigned char m_flag25;
};

struct Rva00395C80ModuleDataView
{
    char m_pad00[0x19];
    unsigned char m_flag19;
};

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend int rva00395C80(Object *obj);
};

struct Rva00395C80Key
{
	NameKeyType key;
	__forceinline Rva00395C80Key(const char *name) { key = TheNameKeyGenerator->nameToKey(name); }
};

// ?rva00395C80@@YAHPAVObject@@@Z
int rva00395C80(Object *obj)
{
	static Rva00395C80Key s_key("CastleMemberBehavior");
	Module *module = obj->findModule(s_key.key);
	if (module != 0 && ((Rva00395C80ModuleView *)module)->m_flag25 != 0 && ((const Rva00395C80ModuleDataView *)((Rva00395C80ModuleView *)module)->m_moduleData)->m_flag19 != 0)
		return false;
	return true;
}
