// cl: /O1 /DNDEBUG /MD /EHsc
//
// ThingFactory::newOverride, retail 0x002D1AB4 (122B), from the WorldBuilder
// lead (ThingFactory.cpp) and Zero Hour's ThingFactory.cpp: copy the final
// override of a template into a new ThingTemplate (0x640 bytes; constructor
// 0x0033E1B8, copy assignment 0x002D1101), mark it copied-from-default and as
// an override, and chain it after the old final override.
//
// BFME2 difference carried from retail: a global byte at 0x00E01EA8 is raised
// around the copy (its identity is not established). The template comes
// through Overridable's inline friend_getFinalOverride, whose recursion is the
// rowed out-of-line copy at 0x001E35DF.

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	void setNextOverride(Overridable *next) { m_nextOverride = next; }
	void markAsOverride() { m_isOverride = true; }

private:
	Overridable *m_nextOverride;	// +0x04
	bool m_isOverride;		// +0x08
};

class ThingTemplate : public Overridable
{
public:
	ThingTemplate();
	ThingTemplate &operator=(const ThingTemplate &that);
	void setCopiedFromDefault();

private:
	unsigned char m_pad0C[0x640 - 0x0C];
};

extern bool g_00E01EA8;

class ThingFactory
{
public:
	ThingTemplate *newOverride(ThingTemplate *thingTemplate);
};

ThingTemplate *ThingFactory::newOverride(ThingTemplate *thingTemplate)
{
	ThingTemplate *child = (ThingTemplate *)thingTemplate->friend_getFinalOverride();
	ThingTemplate *newTemplate = new ThingTemplate;
	g_00E01EA8 = true;
	*newTemplate = *child;
	g_00E01EA8 = false;
	newTemplate->setCopiedFromDefault();
	newTemplate->markAsOverride();
	child->setNextOverride(newTemplate);
	return newTemplate;
}
