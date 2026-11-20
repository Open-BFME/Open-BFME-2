// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
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

#include <vector>

#include "../../../Include/Common/ThingFactory.h"

enum ScienceType;

// The first vector has 12-byte records, with the name at +0x08.
class ProductionPrerequisite
{
public:
    void resolveNames();

private:
    struct PrereqUnitRec
    {
        const ThingTemplate *unit;
        int flags;
        AsciiString name;
    };

    _STL::vector<PrereqUnitRec> m_prereqUnits;
    _STL::vector<ScienceType> m_prereqSciences;
    _STL::vector<unsigned int> m_prereqUpgrades;
};

class BFMERetailAsciiString
{
public:
	void releaseBuffer();
};

void ProductionPrerequisite::resolveNames()
{
	for (int i = 0; i < m_prereqUnits.size(); i++)
	{
		m_prereqUnits[i].unit =
			TheThingFactory->findTemplate(m_prereqUnits[i].name);
		((BFMERetailAsciiString *)&m_prereqUnits[i].name)->releaseBuffer();
	}
}
