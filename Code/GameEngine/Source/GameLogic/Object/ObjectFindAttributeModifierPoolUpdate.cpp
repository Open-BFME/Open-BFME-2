// cl: /O1 /DNDEBUG /MD /EHsc
// ?findAttributeModifierPoolUpdate@Object@@ABEPAVAttributeModifierPoolUpdate@@XZ @0x0028BDD7
// (84B): Object::findAttributeModifierPoolUpdate BFME1 ObjectContainQueries.cpp verbatim
// (private const member returning (AttributeModifierPoolUpdate*)findModule over a
// function-local NAMEKEY for "AttributeModifierPoolUpdate"). String at 0x007F4ED8
// proves class name. findModule resolves via its matched row IBE. Callers include
// Object::getShroudClearingRange 0x0028DE87 plus 25 others.

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
};

class Module
{
};

class Object
{
private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
protected:
	Module *findModule(NameKeyType key) const;
};

AttributeModifierPoolUpdate *Object::findAttributeModifierPoolUpdate() const
{
	static NameKeyType key_AttributeModifierPoolUpdate =
		TheNameKeyGenerator->nameToKey("AttributeModifierPoolUpdate");
	return (AttributeModifierPoolUpdate *)findModule(key_AttributeModifierPoolUpdate);
}
