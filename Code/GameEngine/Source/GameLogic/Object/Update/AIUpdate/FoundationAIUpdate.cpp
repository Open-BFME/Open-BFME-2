// cl: /O1 /EHsc /MD /arch:SSE
// FoundationAIUpdate.cpp -- FoundationAIUpdate members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function; retail supplies the bytes. The same test as Zero Hour's
// BuildAssistant::isRemovableForConstruction (see
// Common/System/BuildAssistant.cpp for the layout evidence): inert never,
// shrubbery and cleared-by-build always, else the effectively-dead bit.

typedef bool Bool;

enum KindOfType
{
	KINDOF_SHRUBBERY = 6,
	KINDOF_CLEARED_BY_BUILD = 51,
	KINDOF_INERT = 89
};

class ThingTemplate
{
public:
	__forceinline Bool isKindOf(KindOfType t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

private:
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x20];		// +0x108
};

class Object
{
public:
	__forceinline Bool isKindOf(KindOfType t) const { return m_template->isKindOf(t); }
	Bool isEffectivelyDead() const { return m_isEffectivelyDead; }

private:
	unsigned char m_pad000[4];
	const ThingTemplate *m_template;	// +0x004
	unsigned char m_pad008[0x438 - 8];
	Bool m_isEffectivelyDead : 1;		// +0x438 bit 0
};

class FoundationAIUpdate
{
public:
	Bool isRemovableForConstruction(Object *obj);
};

// FoundationAIUpdate::isRemovableForConstruction, retail 0x00455241.
Bool FoundationAIUpdate::isRemovableForConstruction(Object *obj)
{
	if (obj == 0)
		return false;
	if (obj->isKindOf(KINDOF_INERT))
		return false;
	if (obj->isKindOf(KINDOF_SHRUBBERY))
		return true;
	if (obj->isKindOf(KINDOF_CLEARED_BY_BUILD))
		return true;
	if (obj->isEffectivelyDead())
		return true;
	return false;
}
