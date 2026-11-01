// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Native56BC3D..56BCE5 complete168B. WB1449940 names StrategicInGameUI::CreateHelpFor
// and source file. Counted help return follows verified56BABF; translated title
// receives the entry pointer even though the retail getter does not use it.
#include "unicode_string.h"

class Rva00220808;

#include "../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct RvaF6Ret
{
	RvaF6Ret(TargetRef00217D4C *p) : m_ptr(p)
	{
		if (m_ptr)
			++m_ptr->references;
	}
	~RvaF6Ret()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	TargetRef00217D4C *m_ptr;
};

class InGameSimpleHelp
{
public:
	InGameSimpleHelp(const UnicodeString &title, const UnicodeString &text);
private:
	char m_opaque[12];
};

typedef bool Bool;
#include "../../../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

class Rva005E2338Elem;
UnicodeString Rva005C95CAGet(const Rva005E2338Elem *);
namespace StrategicInGameUI { RvaF6Ret CreateHelpFor(const Rva005E2338Elem *); }
RvaF6Ret StrategicInGameUI::CreateHelpFor(const Rva005E2338Elem *entry)
{
 UnicodeString help=TheGameText->fetch("STRATEGICHUD:BuildPlotHelp");
 return RvaF6Ret((TargetRef00217D4C*)new InGameSimpleHelp(Rva005C95CAGet(entry),help));
}
