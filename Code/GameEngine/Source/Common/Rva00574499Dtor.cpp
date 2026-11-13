// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// ??1Rva00574499@@QAE@XZ, retail 0x00574499, 68 bytes.
// Evidence: EH prolog unwind states 1..0 tear down two strings at +0x0C down to +0x08
// through the folded string release 0x00036410, then state -1 destroys the
// subobject at +0 through pinned 0x0022167C; deleting-dtor caller at 0x00574B4C
// proves ??1 identity; layout follows sibling Rva005CB3BE dtor precedent.

#include "string_base.h"

#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

// The counted handle (assignment 0x002174A4 rowed elsewhere).

// The help object InGameHotSpotSimpleHelp also builds (ctor 0x005398CD in
// GameClient/GUI/InGame/InGameSimpleHelp.cpp).
class InGameSimpleHelp
{
	char m_opaque[12];

public:
	InGameSimpleHelp(const UnicodeString &title, const UnicodeString &text);
};

// TheGameText viewed by slot: fetch(label, exists) at +0x38.
#include "../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;



class Rva0022167C
{
public:
	~Rva0022167C();

private:
	char m_bytes[8];
};

#include "../../Include/Common/Rva00574499.h"

Rva00574499::~Rva00574499()
{
}

// Native 005744DD..005745D8 (251B), hidden result pointer and ret 4.
// The two callers pass the same 16-byte globals whose teardown is rowed
// above. Native accesses establish labels +8/+C, GameText slot +38,
// the 12-byte InGameSimpleHelp provider, and refcount +4. The matched
// StrategicHUD CreateHelp supplies the algorithm; the original owner and
// method names here remain unknown.
TreeHintRef00217D4C Rva00574499::rva005744DD() const
{
    UnicodeString title;
    if (!((const StringBase<char> *)&m_at08)->isEmpty())
        title = TheGameText->fetch(m_at08, 0);
    UnicodeString text;
    if (!((const StringBase<char> *)&m_at0c)->isEmpty())
        text = TheGameText->fetch(m_at0c, 0);
    return TreeHintRef00217D4C((TargetRef00217D4C *)new InGameSimpleHelp(title, text));
}

extern unsigned g_Va00E062FC;
extern unsigned g_Va00E0630C;

