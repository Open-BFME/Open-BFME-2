// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
extern unsigned char g_00E01EA8;
class ThingTemplate;
template<class T> struct TemplateRecordIterator { T *p; TemplateRecordIterator(T *v):p(v) {} TemplateRecordIterator(const TemplateRecordIterator &v):p(v.p) {} TemplateRecordIterator &operator++(){++p;return *this;} T *operator->()const{return p;} };
template<class T> inline bool operator!=(const TemplateRecordIterator<T> &a,const TemplateRecordIterator<T> &b){return a.p!=b.p;}
struct TemplateOwnedArmorRecord { ThingTemplate *owner; char m_opaque[0x368-4]; };
// ?setCopiedFromDefault@ThingTemplate@@QAEXXZ @0x0033B539 71B
// Evidence: callers in ThingFactory 0x002D1B10 0x002D1BC4 0x002D1D48 (newTemplate->setCopiedFromDefault);
// 2 bools at +0x5E9/+0x5EA plus 4 ModuleInfos at +0x2E4/+0x2F0/+0x2FC/+0x308 via rowed ModuleInfo::setCopiedFromDefault 0x0033B18A.
// ModuleInfo::setCopiedFromDefault @0x0033B18A 67B is ZH's in-class loop over the 20-byte nugget
// vector (copiedFromDefault at +0x10, idiv-by-20 size per iteration); this unit's four calls are
// its only retail callers, so it is emitted here rather than by ThingTemplate.cpp.
class ModuleData;
#include "../../../Include/Common/ModuleInfoClass.h"

inline void ModuleInfo::setCopiedFromDefault(bool value)
{
	for (int i = 0; i < static_cast<unsigned int>(getCount()); ++i)
		m_begin[i].copiedFromDefault = value;
}

#include "../../../Include/Common/ThingTemplate.h"

void ThingTemplate::setCopiedFromDefault()
{
	m5E9 = true;
	m5EA = true;
	reinterpret_cast<ModuleInfo *>(m_behaviorModuleInfo)->setCopiedFromDefault(true);
	reinterpret_cast<ModuleInfo *>(m_drawModuleInfo)->setCopiedFromDefault(true);
	reinterpret_cast<ModuleInfo *>(m_clientUpdateModuleInfo)->setCopiedFromDefault(true);
	reinterpret_cast<ModuleInfo *>(m_clientBehaviorModuleInfo)->setCopiedFromDefault(true);
}

// Identity: WB ThingFactory::parseObjectDefinition calls its same template
// receiver at bc9f40 for both DefaultThingTemplate inheritance and reskin copy.
// ZH ThingTemplate::copyFrom preserves name/ID/list links. Retail boundary
// 0033EBEB..0033EC93 adds the self guard and resets each copied record owner.
// 0x358/0x35C and 0x368 stride are target facts; record and iterator types
// model those operations without claiming the original source spellings.
void ThingTemplate::copyFrom(const ThingTemplate *that)
{
    if (!that || this == that) return;
    ThingTemplate *next = reinterpret_cast<ThingTemplate *&>(m484);
    unsigned short id = m5D8;
    AsciiString name = m_nameString;
    g_00E01EA8 = true;
    *this = *that;
    for (TemplateRecordIterator<TemplateOwnedArmorRecord> record(
            reinterpret_cast<TemplateOwnedArmorRecord *const *>(m_armorTemplateSets)[0]);
         record!=TemplateRecordIterator<TemplateOwnedArmorRecord>(reinterpret_cast<TemplateOwnedArmorRecord *const *>(m_armorTemplateSets)[1]);
         ++record)
        record->owner = this;
    g_00E01EA8 = false;
    reinterpret_cast<ThingTemplate *&>(m484) = next;
    m5D8 = id;
    m_nameString = name;
}
