// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva0049FDF9Parse@@YAXPAVINI@@PAVProductionUpdateModuleData@@@Z @0x0049FDF9 113B: INI parse of ProductionUpdateModuleData +0x1C QuantityModifier list entry AsciiString-plus-int 8-byte element; first token via getNextToken 0x2DF97 and second via getNextTokenOrNull 0x2DEED defaulting quantity to 1 else scanInt 0x2ECCF then StringBase set 0x55F5 and vector push_back 0x49FDC2 with releaseBuffer 0x36410 cleanup.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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
