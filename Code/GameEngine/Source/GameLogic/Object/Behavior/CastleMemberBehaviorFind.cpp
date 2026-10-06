// cl: /DNDEBUG /MD /EHsc
// ?rva000395708@CastleBehavior@@SAPAVModule@@PAVObject@@@Z @0x395708
// (81B): static CastleBehavior lookup over an Object: guards a function-local
// NameKeyType for "CastleMemberBehavior" through TheNameKeyGenerator, then
// returns obj->findModule(key) (matched row 0x28B6D6). __cdecl (caller-side
// push + pop ecx at all 5 call sites, plain ret) proves a static member, not
// a thiscall getter; the class comes from the pool string. Callers null-check
// the Module* and read +0x14/+0x18/+0x24. Object::findModule is protected
// const (IBE pin) so the TU-local Object befriends CastleBehavior (zero-cost).

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
};

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend class CastleBehavior;
};

class CastleBehavior
{
public:
	static Module *rva000395708(Object *obj);
};

// ?rva000395708@CastleBehavior@@SAPAVModule@@PAVObject@@@Z
Module *CastleBehavior::rva000395708(Object *obj)
{
	static NameKeyType TheCastleMemberBehaviorKey =
		TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
	return obj->findModule(TheCastleMemberBehaviorKey);
}
