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
// The native17B unsigned-max provider is owned by stlport_narrow_istream.cpp
// at0x13740. Declare it here instead of emitting a private compiler variant.
#include <stl/_algobase.h>
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

#include <vector>

enum ErrorCode
{
	ERROR_BASE = 0xdead0001,
	ERROR_BUG = (ERROR_BASE + 0x0000)
};

class SpecialPowerTemplate;

#include "../../../Include/Common/SpecialPowerStore.h"
extern SpecialPowerStore *TheSpecialPowerStore;

class Xfer;
enum INILoadType { INI_LOAD_INVALID, INI_LOAD_OVERWRITE };
#include "../../../Include/Common/INI/INI.h"

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

// WB E66400 IniLoad; native3397D8..33987B including catch and cleanup.
// EH state is reset for each file: catch(...) surrounds each load call.
// The6B entry33984F returns the continuation339855; it is a catch stub,
// not a standalone constant getter. INI size87C follows its rowed ctor.
struct IniLoadFileList {AsciiString name;AsciiString *begin,*end,*capacity;};
class SubsystemLegend {public:IniLoadFileList *rva001B49C4(AsciiString);};
extern SubsystemLegend *TheSubsystemLegend;
bool IniLoad(const char *block,void(*parse)(INI*))
{
 IniLoadFileList *files=TheSubsystemLegend->rva001B49C4(AsciiString(block));
 if(!files) return false;
 INI ini;
 for(AsciiString *asciiString=files->begin;asciiString!=files->end;++asciiString) {
  try {ini.load(*asciiString,INI_LOAD_OVERWRITE,0,parse);} catch(...) {return false;}
 }
 return true;
}
