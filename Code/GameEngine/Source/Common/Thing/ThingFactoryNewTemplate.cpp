// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc
// ThingFactory::newTemplate, retail 0x002D1B2E (211 bytes):
// ?newTemplate@ThingFactory@@AAEPAVThingTemplate@@ABVAsciiString@@@Z
// Identity (target): WorldBuilder's debug ThingFactory.cpp
// ThingFactory::newTemplate builds the "DefaultThingTemplate" name and calls,
// in retail's order, operator new(0x640), ThingTemplate::ThingTemplate,
// the factory's existence test 0x002D06AA, findTemplate, the copy
// assignment, ThingTemplate::setCopiedFromDefault, StringBase::set and
// ThingFactory::addTemplate (WB-named, 0x002D04A3).
// Donor (Zero Hour ThingFactory::newTemplate): copy the default template
// when present, give the template the next id and the name, add it.
// BFME 2 deltas (target): the default is first tested with 0x002D06AA; the
// copy is bracketed by the 0x00E01EA8 flag as in newOverride; the id is the
// counter's value before the increment (factory +0x10, a 16-bit field;
// template id +0x5D8, name +0x64).
// Shape (inference): retail registers no unwind state for the name
// temporaries around the two lookups, reproduced by declaring them throw();
// /G7 drops the zero-extension before the 16-bit counter load.
#include "ascii_string.h"

#include "../../../Include/Common/ThingTemplate.h"

// g_00E01EA8 is only an alias of the owned global g_00E01EA8 (ledger names column); this unit reads the owner through its own view type.
extern unsigned char g_00E01EA8;
#define g_00E01EA8 (*(bool *)&g_00E01EA8)

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name) throw();
	bool rva002D06AA(const AsciiString &name) throw();

private:
	ThingTemplate *newTemplate(const AsciiString &name);
	void addTemplate(ThingTemplate *tmplate);

	unsigned char m_pad00[0x10];
	unsigned short m_nextTemplateID; // +0x10
};

ThingTemplate *ThingFactory::newTemplate(const AsciiString &name)
{
	ThingTemplate *newTemplate = new ThingTemplate;

	// if the default template is present, copy it into the new template
	if (rva002D06AA(AsciiString("DefaultThingTemplate")))
	{
		const ThingTemplate *defaultT = findTemplate(AsciiString("DefaultThingTemplate"));
		g_00E01EA8 = true;
		*newTemplate = *defaultT;
		g_00E01EA8 = false;
		newTemplate->setCopiedFromDefault();
	}

	// give template a unique identifier
	newTemplate->friend_setTemplateID(m_nextTemplateID++);
	// set the name in the template
	newTemplate->friend_setTemplateName(name);
	// add to list
	addTemplate(newTemplate);
	return newTemplate;
}
