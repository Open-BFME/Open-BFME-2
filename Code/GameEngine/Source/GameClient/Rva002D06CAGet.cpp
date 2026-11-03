// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?findTemplate@ThingFactory@@QAEPBVThingTemplate@@ABVAsciiString@@@Z, retail 0x002D06CA (38B).
// ?rva002D06AA@ThingFactory@@QAE_NABVAsciiString@@@Z, retail 0x002D06AA (32B).
// Lookup in the embedded Rva00056F61 bucket table at +0x14 via rowed
// iterator find 0x0041534B. Returns payload at node+8 or null. Sibling of
// rowed 0x002130F6 (+0x26c) 0x0021311F (+0x280) 0x00213148 (+0x294) same
// recipe with 3-byte add encoding explaining 38B vs 41B. Callers at 0x001E0243
// and 0x001E052A via TheThingFactory (data 0x009FF000, ThingFactory) plus INI
// parse 0x0033947E and 209-function unlock fanout. WorldBuilder 0x00A95940 is
// ThingFactory::findTemplateInternal (ThingFactory.cpp:484) with the same +0x14
// table lookup; BFME 2 takes the name only. 0x002D06AA is the factory's
// existence test on the same table (ThingFactory::newTemplate asks it for
// DefaultThingTemplate, REL32 0x002D1B78).
#include "ascii_string.h"
class Rva00056F61;
class ThingTemplate;
#include "../../Include/GameClient/Rva0041534BIter.h"
class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
};
#include "../../Include/Common/ThingFactory.h"
const ThingTemplate *ThingFactory::findTemplate(const AsciiString &name)
{
	Rva0041534BIter it = reinterpret_cast<Rva00056F61 *>(field14)->rva0041534B(&name);
	if (it.m_node != 0)
		return *(const ThingTemplate **)((char *)it.m_node + 8);
	return 0;
}
bool ThingFactory::rva002D06AA(const AsciiString &name)
{
	Rva0041534BIter it = reinterpret_cast<Rva00056F61 *>(field14)->rva0041534B(&name);
	return it.m_node != 0;
}

// ?rva000CEB48@ThingFactory@@QAEPBVThingTemplate@@ABVAsciiString@@@Z,
// retail 0x000CEB48 (5B): a forwarder to the lookup above with the same
// name (a tail jump); no direct caller reaches it in retail.
const ThingTemplate *ThingFactory::rva000CEB48(const AsciiString &name)
{
	return findTemplate(name);
}
