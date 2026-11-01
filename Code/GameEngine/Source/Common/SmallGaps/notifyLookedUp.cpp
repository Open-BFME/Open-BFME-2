// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/SmallGaps/notifyLookedUp.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?notifyLookedUp@@YAXPAURva0020AA00Owner@@HH@Z 0x0045F48D (53B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// ?notifyLookedUp@@YAXPAURva0020AA00Owner@@HH@Z
// The callees are the rowed ThingFactory::findTemplate (0x002D06CA) and
// ThingTemplate::GetAssetList (0x0033CF34); each element is a template name.
class AsciiString;
#include "../../../Include/Common/ThingTemplate.h"
// TheThingFactory is EA's ThingFactory singleton, defined once in
// Common/Thing/ThingFactory.cpp.
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &name); };
extern ThingFactory* TheThingFactory;
struct Rva0020AA00Owner { char m_pad[0x20]; int* m_begin; int* m_end; };
void notifyLookedUp(Rva0020AA00Owner* owner, int a, int b)
{
	for (int* it = owner->m_begin; it != owner->m_end; ++it) {
		const ThingTemplate* thingTemplate = TheThingFactory->findTemplate(*(const AsciiString *)it);
		if (thingTemplate)
			const_cast<ThingTemplate *>(thingTemplate)->GetAssetList(a, b);
	}
}
