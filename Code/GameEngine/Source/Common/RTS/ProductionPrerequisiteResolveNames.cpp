// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/RTS/ProductionPrerequisiteResolveNames.cpp (donor
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// Compiled that way each body below places uniquely on unclaimed game.dat
// .text by masked whole-.text search, and ./build.sh reproduces it byte for
// byte: ProductionPrerequisite::resolveNames 0x004F4B6D (83B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.
//
// ProductionPrerequisite::resolveNames uses the BFME one-argument factory
// facade and releases each source name through the retail AsciiString body.
// The ABI views below are deliberately local to this TU: the tagged string
// release symbol is pinned only to the retail 0x00887940 body and does not
// reuse ProductionPrerequisite::PrereqUnitRec's distinct weak destructor
// instances used by the existing vector callers.

#include "PreRTS.h"

#include "Common/ProductionPrerequisite.h"
#include "Common/Player.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/Object.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"

// The template lookup is the rowed ThingFactory::findTemplate (0x002D06CA); BFME 2
// takes the name only, so this unit declares the factory instead of ZH ThingFactory.h.
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class BFMERetailAsciiString
{
public:
	void releaseBuffer();
};

void ProductionPrerequisite::resolveNames()
{
	for (Int i = 0; i < m_prereqUnits.size(); i++)
	{
		m_prereqUnits[i].unit =
			TheThingFactory->findTemplate(m_prereqUnits[i].name);
		((BFMERetailAsciiString *)&m_prereqUnits[i].name)->releaseBuffer();
	}
}
