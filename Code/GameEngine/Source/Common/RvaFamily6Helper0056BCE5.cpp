// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Native56BCE5..56BD91 complete172B. Counted InGameSimpleHelp from region
// title and description getters. Return handle follows proven sibling56BABF.
// Original helper identity remains address-derived.
#include "unicode_string.h"

class Rva00220808;

struct TargetRef00217D4C
{
	void *m_vtbl;
	int m_refCount;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct RvaF6Ret
{
	RvaF6Ret(TargetRef00217D4C *p) : m_ptr(p)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
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

class Rva0020E89C {public:UnicodeString rva0020E89C();UnicodeString rva003F15D1();};
RvaF6Ret Helper0056BCE5(int v)
{
 Rva0020E89C *region=(Rva0020E89C*)v;
 return RvaF6Ret((TargetRef00217D4C*)new InGameSimpleHelp(region->rva0020E89C(),region->rva003F15D1()));
}
