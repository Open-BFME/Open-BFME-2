// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Native56BB8C..56BC3D complete177B. Counted InGameSimpleHelp from entry
// label28 title and description getters. Return handle follows proven sibling56BABF.
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

class Rva002DF9E9 {public:UnicodeString rva002DF9E9();};
class LivingWorldBuildingTemplate {public:UnicodeString rva002DFE36();};
struct Helper0056BB8CEntry {char unknown00[0x28];Rva002DF9E9 *label;};
RvaF6Ret Helper0056BB8C(int v)
{
 Helper0056BB8CEntry *entry=(Helper0056BB8CEntry*)v;
 return RvaF6Ret((TargetRef00217D4C*)new InGameSimpleHelp(entry->label->rva002DF9E9(),((LivingWorldBuildingTemplate*)entry->label)->rva002DFE36()));
}
