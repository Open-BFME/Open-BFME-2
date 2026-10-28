// cl: /DNDEBUG /MD /EHsc
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
public:
	bool rva00403382(int id, float *value, int index);
};

#include "../../../Include/Common/Module.h"

struct Rva0028CE7BTemplateView
{
	char pad00[0x5fa];
	signed char m_crushable;
	char pad5fb;
	signed char m_alternateCrushable;
};

class Object
{
public:
	signed char rva0028CE7B() const;
private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
	char pad00[4];
	const Rva0028CE7BTemplateView *m_template;
	char pad08[0x124 - 0x08];
	unsigned m_flags124;
protected:
	Module *findModule(NameKeyType key) const;
};

AttributeModifierPoolUpdate *Object::findAttributeModifierPoolUpdate() const
{
	static NameKeyType key_AttributeModifierPoolUpdate =
		TheNameKeyGenerator->nameToKey("AttributeModifierPoolUpdate");
	return (AttributeModifierPoolUpdate *)findModule(key_AttributeModifierPoolUpdate);
}

// Retail 0x0028CE7B (84 bytes): alternate crush byte, else the crush byte when
// that byte is -1 or bit 22 of the flag word is clear, plus modifier 0x19.
signed char Object::rva0028CE7B() const
{
	const Rva0028CE7BTemplateView *tpl = m_template;
	const Rva0028CE7BTemplateView *live = tpl;
	float bonus;
	signed char add = 0;
	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (pool && pool->rva00403382(0x19, &bonus, 0))
		add = (signed char)(int)bonus;
	signed char level = live->m_alternateCrushable;
	unsigned char bit = (unsigned char)(m_flags124 >> 22);
	if (level == -1 || (bit & 1) == 0)
		level = (add ? live->m_crushable : live->m_crushable);
	return level + add;
}
