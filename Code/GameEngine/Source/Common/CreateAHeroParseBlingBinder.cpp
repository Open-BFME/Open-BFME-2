// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// ?parseCreateAHeroBlingBinder@@YAXPAVINI@@PAX1PBX@Z
// Retail 0x0021DEAD..0x0021E050 (419 bytes; the compiled body also emits the
// int3 at 0x0021E050 after the final throw, which matches retail).
//
// The INI field parser named by its own messages ("... while parsing
// parseCreateAHeroBlingBinder."), the routine at FieldParse entry 0x009BA08C
// (WB twin 0x00B7FE20): builds a binder record (rowed 4-arg ctor 0x00219ABB:
// group key, then min / max / default value upgrade names, all "None"),
// fills it from the block through the field table at 0x00DB9EC8, rejects an
// invalid, "None" or empty group key (keys cached in function statics) and
// any missing upgrade name with INIException(3, ...), then hands the record
// to the instance through rowed 0x0021DE75. Record layout as in
// StringRecordInlineCopyBFME2.cpp; the per-name checks call StringBase's
// out-of-line isNone / isEmpty (0x00037DE0 / 0x00001E2F).
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class INI;

#include "../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;

typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
#include "../../Include/Common/INI/FieldParse.h"

#include "../../Include/Common/INI/INI.h"


// The bling binder record: a group key and three upgrade names.
#include "../../../Libraries/Source/WWVegas/WWLib/BfmeStringRecord00219B0B.h"

class Rva0021DE75
{
public:
	void *rva0021DE75(void *binder);	// 0x0021DE75
};

// Retail's table at RVA 0x009B9EC8 (raw .data, 80 bytes = four 16-byte records
// and one zero sentinel), transcribed from retail's own bytes: the record's
// group key is written through NameKeyGenerator::parseStringAsNameKeyType (rove
// 0x0148FBE) at offset 0 and its three upgrade names through
// INI::parseAsciiString (rowed 0x002F11E) at offsets 4, 8 and 0xC -- the same
// record layout BfmeStringRecord00219B0B declares. The `extern` on the
// definition keeps the object external; nothing else defines it and the shape
// matches the g_00C3BC20 / WeatherData tables elsewhere in Code/.
extern const FieldParse g_00DB9EC8[] =
{
	{"GroupName",            &NameKeyGenerator::parseStringAsNameKeyType, 0, 0},
	{"MinValueUpgrade",      &INI::parseAsciiString, 0, 4},
	{"MaxValueUpgrade",      &INI::parseAsciiString, 0, 8},
	{"DefaultValueUpgrade",  &INI::parseAsciiString, 0, 0xC},
	{0, 0, 0, 0}
};

// Retail calls StringBase's out-of-line isEmpty (0x00001E2F); the shared
// header's AsciiString::isEmpty inlines it.
#define IS_EMPTY(s) (((const StringBase<char> *)&(s))->isEmpty())

void parseCreateAHeroBlingBinder(INI *ini, void *instance, void *, const void *)
{
	BfmeStringRecord00219B0B binder(0, AsciiString("None"), AsciiString("None"), AsciiString("None"));
	ini->initFromINI(&binder, g_00DB9EC8);

	UnsignedInt groupKey = binder.word0;
	static NameKeyType noneKey = TheNameKeyGenerator->nameToKey("None");
	static NameKeyType emptyKey = TheNameKeyGenerator->nameToKey("");

	if (groupKey == NAMEKEY_INVALID || groupKey == (UnsignedInt)noneKey || groupKey == (UnsignedInt)emptyKey)
		throw INIException(3, "No group name specified  while parsing parseCreateAHeroBlingBinder.");
	if (binder.text0.isNone() || IS_EMPTY(binder.text0))
		throw INIException(3, "No minValueUpgradeName specified while parsing parseCreateAHeroBlingBinder.");
	if (binder.text1.isNone() || IS_EMPTY(binder.text1))
		throw INIException(3, "No maxValueUpgradeName specified while parsing parseCreateAHeroBlingBinder.");
	if (binder.text2.isNone() || IS_EMPTY(binder.text2))
		throw INIException(3, "No defaultValueUpgradeName specified while parsing parseCreateAHeroBlingBinder.");

	((Rva0021DE75 *)instance)->rva0021DE75(&binder);
}
