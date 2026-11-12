// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Native56BCE5..56BD91 complete172B. Counted InGameSimpleHelp from region
// title and description getters. Return handle follows proven sibling56BABF.
// Original helper identity remains address-derived.
#include "unicode_string.h"

class Rva00220808;

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
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

#include "../../Include/GameClient/Rva0020E89C.h"
RvaF6Ret Helper0056BCE5(int v)
{
 Rva0020E89C *region=(Rva0020E89C*)v;
 return RvaF6Ret((TargetRef00217D4C*)new InGameSimpleHelp(region->rva0020E89C(),region->rva003F15D1()));
}
