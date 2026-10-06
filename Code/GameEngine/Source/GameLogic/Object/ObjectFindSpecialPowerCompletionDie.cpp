// cl: /DNDEBUG /MD /EHsc
// ?findSpecialPowerCompletionDie@Object@@QBEPAVSpecialPowerCompletionDie@@XZ @0x28BE2B
// (84B): Object::findSpecialPowerCompletionDie, ZH Object.cpp verbatim
// (const member returning (SpecialPowerCompletionDie*)findModule over a
// function-local NAMEKEY for "SpecialPowerCompletionDie"). The const-ness
// (QBE) is donor-proven, not guessed. findModule resolves via its matched row
// (IBE pin spelling reproduced by the protected const decl); the C-cast emits
// no bytes. Callers: Weapon::fireWeaponToObjectOrPosition (sourceObj +
// projectile) and ObjectCreationList (transport/payload/container), same as ZH.

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

class SpecialPowerCompletionDie
{
};

class Module
{
};

class Object
{
public:
	SpecialPowerCompletionDie *findSpecialPowerCompletionDie() const;
protected:
	Module *findModule(NameKeyType key) const;
};

// ?findSpecialPowerCompletionDie@Object@@QBEPAVSpecialPowerCompletionDie@@XZ
SpecialPowerCompletionDie *Object::findSpecialPowerCompletionDie() const
{
	static NameKeyType key_SpecialPowerCompletionDie =
		TheNameKeyGenerator->nameToKey("SpecialPowerCompletionDie");
	return (SpecialPowerCompletionDie *)findModule(key_SpecialPowerCompletionDie);
}
