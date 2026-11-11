// cl: /O1 /arch:SSE /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva0033C247@MyRecord@@QAEXPAX@Z at 0x0033C247 (18B). The LINK BONUS pins this name; retail delegates to INI::initFromINI with this record and the global FieldParse table.

struct FieldParse;

#include "../../../Include/Common/INI/INI.h"
#include "../../../Include/Common/Rva0033AFBB.h"

#include "../../../Include/Common/INI/FieldParse.h"

// Retail's own three-record table, transcribed from .rdata at RVA 0x00810550 (VA
// 0x00C10550, file offset 0x0080F950): Conditions through Rva0033AFBB::parseFromINI
// at +0, Armor through INI::parseAsciiString at +4 and DamageFX through
// INI::parseDamageFX at +8, then the zero terminator. All three parse targets are
// rowed bodies, and the preceding extern keeps the table external - a plain const
// array at namespace scope takes MSVC internal linkage.
extern const FieldParse g_00C10550[];
const FieldParse g_00C10550[] =
{
	{ "Conditions", &Rva0033AFBB::parseFromINI, 0, 0 },
	{ "Armor", &INI::parseAsciiString, 0, 4 },
	{ "DamageFX", &INI::parseDamageFX, 0, 8 },
	{ 0, 0, 0, 0 }
};

class MyRecord
{
public:
	void rva0033C247(void *ini);
};

void MyRecord::rva0033C247(void *ini)
{
	((INI *)ini)->initFromINI(this, g_00C10550);
}
