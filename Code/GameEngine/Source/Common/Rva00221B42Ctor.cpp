// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD
// ??0Rva00221B42@@QAE@ABVAsciiString@@ABVRva00221A58@@PAVINI@@@Z @0x00221B42 75B
// Ctor: Rva00221A58 at +0 via rowed copy 0x00221A58 plus AsciiString at +0x1C
// via StringBase copy 0x000365F0 plus INI::initFromINI 0x0002DE78 with table
// g_00BE6BD8. Chain after 0x00221A58; caller 0x00221C15 passes same 3 args to
// member at +8. Evidence: retail bytes and callers.
#include "ascii_string.h"

#include "../../Include/Common/Rva0022185A.h"

#include "../../Include/Common/Rva00221A58.h"

struct FieldParse;

#include "../../Include/Common/INI/INI.h"
#include "../../Include/Common/GlobalLanguageClass.h"

#include "../../Include/Common/INI/FieldParse.h"

// Retail's own five-record table, transcribed from .rdata at RVA 0x007E6BD8 (VA
// 0x00BE6BD8, file offset 0x007E0FD8): Title, OpenAudio and Icon with
// INI::parseAsciiString at +0/+4/+8, MessageFont with
// GlobalLanguage::parseFontDesc at +0xC, and MessageColor with
// INI::parseColorInt at +0x18, then the zero terminator. `extern` on the
// definition keeps the table external.
extern const FieldParse g_00BE6BD8[];
const FieldParse g_00BE6BD8[] =
{
	{ "Title", &INI::parseAsciiString, 0, 0 },
	{ "OpenAudio", &INI::parseAsciiString, 0, 4 },
	{ "Icon", &INI::parseAsciiString, 0, 8 },
	{ "MessageFont", &GlobalLanguage::parseFontDesc, 0, 12 },
	{ "MessageColor", &INI::parseColorInt, 0, 24 },
	{ 0, 0, 0, 0 }
};

#include "../../Include/Common/Rva00221B42.h"

Rva00221B42::Rva00221B42(const AsciiString &asciiString, const Rva00221A58 &b, INI *ini)
	: m_00(b)
	, m_1C(asciiString)
{
	ini->initFromINI(this, g_00BE6BD8);
}
