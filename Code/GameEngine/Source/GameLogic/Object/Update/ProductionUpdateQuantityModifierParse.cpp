// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva0049FDF9Parse@@YAXPAVINI@@PAVProductionUpdateModuleData@@@Z @0x0049FDF9 113B: INI parse of ProductionUpdateModuleData +0x1C QuantityModifier list entry AsciiString-plus-int 8-byte element; first token via getNextToken 0x2DF97 and second via getNextTokenOrNull 0x2DEED defaulting quantity to 1 else scanInt 0x2ECCF then StringBase set 0x55F5 and vector push_back 0x49FDC2 with releaseBuffer 0x36410 cleanup.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
#include "ascii_string.h"

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
	int scanInt(const char *token);
};

struct QuantityModifier
{
	AsciiString m_templateName;
	int m_quantity;
};

class ProductionUpdateModuleData
{
public:
	const void *m_vtable;
	int m_pad04;
	int m_numDoorAnimations;
	unsigned int m_doorOpeningTime;
	unsigned int m_doorWaitOpenTime;
	unsigned int m_doorClosingTime;
	unsigned int m_constructionCompleteDuration;
	_STL::vector<QuantityModifier, _STL::allocator<QuantityModifier> > m_quantityModifiers;
};

void Rva0049FDF9Parse(INI *ini, ProductionUpdateModuleData *data)
{
	const char *first = ini->getNextToken(0);
	const char *second = ini->getNextTokenOrNull(0);
	int qty;
	if (second != 0)
		qty = ini->scanInt(second);
	else
		qty = 1;
	QuantityModifier mod;
	mod.m_quantity = qty;
	mod.m_templateName.set(first);
	data->m_quantityModifiers.push_back(mod);
}
