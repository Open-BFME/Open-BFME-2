// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// AIEconomyBuilder::getFarmTemplateName (WorldBuilder name, AIEconomyBuilder.cpp lines 99..101: the +0x14 player through 0x002A8AB1).
#include "ascii_string.h"

struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *x);
};

extern Rva002A8F24 *g_00DFEEF8;

#include "../GameLogic/SkirmishAI/AIEconomyBuilder/AIEconomyBuilderFarmLibrary.h"

AsciiString AIEconomyBuilder::getFarmTemplateName()
{
	Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(m_14);
	void *p160 = *(void **)((char *)rec + 0x160);
	AsciiString *src = (AsciiString *)((char *)p160 + 0x24);
	return *src;
}
