// cl: /O1 /EHsc /MD /arch:SSE
// BuildAssistant.cpp -- BuildAssistant members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function;
// retail supplies the bytes. Zero Hour's isRemovableForConstruction
// (Common/System/BuildAssistant.cpp) with BFME2's second never-removable kind.
//
// Layout (target evidence): Object +0x04 is the thing template, whose kind-of
// bits start at +0x108; the effectively-dead flag is bit 0 at Object +0x438.
// Kind indices are read off the tested bytes: 89 (inert, +0x113 bit 1),
// 152 (+0x11B bit 0), 6 (shrubbery, +0x108 bit 6) and 51 (cleared by build,
// +0x10E bit 3); their BFME2 names are not recovered.

typedef bool Bool;

enum KindOfType
{
	KINDOF_SHRUBBERY = 6,
	KINDOF_CLEARED_BY_BUILD = 51,
	KINDOF_INERT = 89,
	KINDOF_152 = 152
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

class BuildAssistant
{
public:
	Bool isRemovableForConstruction(Object *obj);
};

// BuildAssistant::isRemovableForConstruction, retail 0x00391CE3.
Bool BuildAssistant::isRemovableForConstruction(Object *obj)
{
	if (obj == 0)
		return false;
	if (obj->isKindOf(KINDOF_INERT))
		return false;
	if (obj->isKindOf(KINDOF_152))
		return false;
	if (obj->isKindOf(KINDOF_SHRUBBERY))
		return true;
	if (obj->isKindOf(KINDOF_CLEARED_BY_BUILD))
		return true;
	if (obj->isEffectivelyDead())
		return true;
	return false;
}
