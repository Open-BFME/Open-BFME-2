// cl: /DNDEBUG /MD
//
// Target evidence: the existing ModuleFactory callback pin and its registry
// dispatch establish this as a three-argument cdecl callback. At 0x00469B9F it
// forwards those arguments to the sibling callback 0x00467564, then walks the
// four-byte range beginning at argument 1 +0x218 and ending at +0x21C. Each
// element address is passed to the rowed ThingFactory::findTemplate through
// TheThingFactory (VA 0x00DFF000); a non-null result receives arguments 2 and 3
// at 0x0033CF34, the rowed ThingTemplate::GetAssetList. The range element type
// remains unresolved.

class AsciiString;
#include "../../../../Include/Common/ThingTemplate.h"

#include "../../../../Include/Common/ThingFactory.h"

extern ThingFactory *TheThingFactory;

void __cdecl ModuleFactoryHookAt00467564(void *owner, int value, void *context);

// Declared as well as defined below: 0x0047A6A4's body is a tail jump to it, and
// a carve of that row takes this file's declarations but never an
// external-linkage definition (tu_skeleton.carve).
void __cdecl ModuleFactoryHookAt00469B9F(void *owner, int value, void *context);

class ModuleFactoryHookRange
{
public:
	unsigned char m_pad000[0x218];
	unsigned char *m_begin;
	unsigned char *m_end;
};

class GameLODManager;
extern GameLODManager *TheGameLODManager;

class AI;
extern AI *TheAI;

void __cdecl ModuleFactoryHookAt00469B9F(void *owner, int value, void *context)
{
	ModuleFactoryHookAt00467564(owner, value, context);

	ModuleFactoryHookRange *range = (ModuleFactoryHookRange *)owner;
	unsigned char *element = range->m_begin;
	while (element != range->m_end) {
		const ThingTemplate *thingTemplate =
			TheThingFactory->findTemplate(*(const AsciiString *)element);
		if (thingTemplate)
			const_cast<ThingTemplate *>(thingTemplate)->GetAssetList(value, (int)context);
		element += 4;
	}
}
