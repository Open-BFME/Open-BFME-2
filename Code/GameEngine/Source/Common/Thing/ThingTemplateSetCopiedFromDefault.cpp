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
class ModuleInfo
{
public:
	void setCopiedFromDefault(bool copied);
private:
	void *m_begin;
	void *m_end;
	void *m_storage;
};

class ThingTemplate
{
public:
	void setCopiedFromDefault();
    void copyFrom(const ThingTemplate *that);
    ThingTemplate &operator=(const ThingTemplate &that);
private:
	char m_pad0[0x64];
    AsciiString m_name;
    char m_pad068[0x2E4-0x68];
	ModuleInfo m_behaviorModuleInfo; // +0x2E4
	ModuleInfo m_drawModuleInfo; // +0x2F0
	ModuleInfo m_clientUpdateModuleInfo; // +0x2FC
	ModuleInfo m_extraModuleInfo; // +0x308 measured retail fourth slot name unproven
	char m_pad314[0x358-0x314];
    TemplateOwnedArmorRecord *m_armorBegin, *m_armorEnd, *m_armorCapacity;
    char m_pad364[0x484-0x364];
    ThingTemplate *m_nextTemplate;
    char m_pad488[0x5D8-0x488];
    unsigned short m_templateID;
    char m_pad5DA[0x5E9-0x5DA];
	bool m_armorCopiedFromDefault; // +0x5E9
	bool m_weaponsCopiedFromDefault; // +0x5EA
};

void ThingTemplate::setCopiedFromDefault()
{
	m_armorCopiedFromDefault = true;
	m_weaponsCopiedFromDefault = true;
	m_behaviorModuleInfo.setCopiedFromDefault(true);
	m_drawModuleInfo.setCopiedFromDefault(true);
	m_clientUpdateModuleInfo.setCopiedFromDefault(true);
	m_extraModuleInfo.setCopiedFromDefault(true);
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
    ThingTemplate *next = m_nextTemplate;
    unsigned short id = m_templateID;
    AsciiString name = m_name;
    g_00E01EA8 = true;
    *this = *that;
    for (TemplateRecordIterator<TemplateOwnedArmorRecord> record(m_armorBegin); record!=TemplateRecordIterator<TemplateOwnedArmorRecord>(m_armorEnd); ++record)
        record->owner = this;
    g_00E01EA8 = false;
    m_nextTemplate = next;
    m_templateID = id;
    m_name = name;
}
