// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// iniParseSpecialPowerTemplateVector, retail 0x00339CCA (92B), from the
// WorldBuilder lead (inihelp.cpp): an INI field parser that appends each
// named special power template (SpecialPowerStore::findSpecialPowerTemplate,
// name by value) to the vector<const SpecialPowerTemplate *> it is given,
// skipping unknown names; without TheSpecialPowerStore (0x00E02D4C) it throws
// ERROR_BUG (0xDEAD0001) as Zero Hour's INI parsers do.

#include "ascii_string.h"
#include <vector>

enum ErrorCode
{
	ERROR_BASE = 0xdead0001,
	ERROR_BUG = (ERROR_BASE + 0x0000)
};

class SpecialPowerTemplate;

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};
extern SpecialPowerStore *TheSpecialPowerStore;

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);
};

void iniParseSpecialPowerTemplateVector(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	if (!TheSpecialPowerStore)
		throw ERROR_BUG;
	_STL::vector<const SpecialPowerTemplate *> *v = (_STL::vector<const SpecialPowerTemplate *> *)store;
	for (const char *token = ini->getNextTokenOrNull(); token; token = ini->getNextTokenOrNull())
	{
		const SpecialPowerTemplate *sp = TheSpecialPowerStore->findSpecialPowerTemplate(AsciiString(token));
		if (sp)
			v->push_back(sp);
	}
}
