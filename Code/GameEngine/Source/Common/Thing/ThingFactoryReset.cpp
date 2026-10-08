// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /Ireference/shims/iniexception
/* Copyright 2025 Electronic Arts Inc. SPDX-License-Identifier: GPL-3.0-or-later */
// Semantic donor: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/Common/Thing/ThingFactory_reset.cpp, itself from ZH.
// Identity: WB ThingFactory.cpp:368..402 reset, matched to retail's subsystem
// vtable reset slot. Retail boundary: 0x002D05CF..0x002D06AA (219 bytes).
// Target layout: first template +0x0C, name +0x64, next template +0x484;
// SubsystemInterface is the shared BFME2 twelve-byte base, not ZH's eight.
// Target-only behavior: bit 0x40 at template +0x11F selects the ModuleInfo
// at +0x2F0. Each nonnull module's slot 18 returns the cache cleared by the
// existing 0x000B4AE4 worker. The flag and slot's semantic names remain open.
#include "ascii_string.h"

class Rva00056F61;
struct Rva0041534BIter {
    void *m_node; Rva00056F61 *m_table;
    Rva0041534BIter(void *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
};
class Rva00056F61 { public:
    __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *);
};
class Rva002CFEA5 { public: void *rva002CFEA5(const AsciiString *); };
extern bool g_flag1;
// Retail VA 0x00DBC864 starts FF FF 00 00. The addTemplate body reads
// its complete storage word but decrements and compares only the low ID.
// Counter purpose and field names are structural; no original global name is claimed.
union TemplateReplacementCounter { unsigned short nextID; unsigned int storage; };
TemplateReplacementCounter g_replacementTemplateCounter = {65535};

#include "Common/INIException.h"
typedef bool Bool;
#include "subsystem_interface.h"

class Overridable
{
public:
    virtual ~Overridable();
    Overridable *deleteOverrides();
    Overridable *m_nextOverride;
    bool m_isOverride;
};

class Rva000B4BED
{
public:
    void rva000B4AE4();
};

// Call-only view; no vtable or slot implementation is emitted here.
class ModuleData
{
public:
    virtual void slot00(); virtual void slot01();
    virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07();
    virtual bool slot08() const; virtual void slot09();
    virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13();
    virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17();
    virtual Rva000B4BED *slot18() const;
    char m_pad004[0x86 - 4];
    bool m_flag86;
};

struct ModuleInfoRecord { char m_opaque[20]; };
class ModuleInfo
{
public:
    const ModuleData *getNthData(int i) const;
    ModuleInfoRecord *m_start, *m_end, *m_capacity;
};

// Keep the target stride calculation local; other ModuleInfo views emit
// different getCount copies. This helper is completely inlined.
static __forceinline int moduleRecordCount(const ModuleInfo *info)
{
    return ((const char *)info->m_end - (const char *)info->m_start) / 20;
}

class ThingTemplate : public Overridable
{
public:
    unsigned int m_matchingReplacementCount;
    char m_pad010[0x64 - 0x10];
    AsciiString m_name;
    char m_pad068[0x11F - 0x68];
    unsigned char m_flags11F;
    char m_pad120[0x2E4 - 0x120];
    ModuleInfo m_behaviorModules;
    ModuleInfo m_modules;
    char m_pad2FC[0x484 - 0x2FC];
    ThingTemplate *m_nextTemplate;
    char m_pad488[0x5D8 - 0x488];
    unsigned short m_templateID;
    void resolveNames();
};

// Existing row 0x00223429: erase by pointer to the four-byte AsciiString.
class Rva000427195
{
public:
    int rva00223429(const AsciiString *key);
    void rva003A2A41();
    void *m_unused;
    void **m_beginBuckets, **m_endBuckets, **m_storageEnd;
    unsigned int m_numElements;
};

class ThingFactory : public SubsystemInterface
{
public:
    virtual void reset();
    virtual void postProcessLoad();
private:
    void freeDatabase();
    void addTemplate(ThingTemplate *tmplate);
    ThingTemplate *m_firstTemplate;
    unsigned short m_nextTemplateID, m_unused12;
    Rva000427195 m_templateHashMap;
};

void ThingFactory::reset()
{
    for (ThingTemplate *t = m_firstTemplate; t; )
    {
        bool possibleAdjustment = false;
        ThingTemplate *nextT = t->m_nextTemplate;
        if (t == m_firstTemplate)
            possibleAdjustment = true;

        AsciiString templateName = t->m_name;
        Overridable *stillValid = t->deleteOverrides();
        if (!stillValid && possibleAdjustment)
            m_firstTemplate = nextT;

        if (t->m_flags11F & 0x40)
        {
            int count = moduleRecordCount(&t->m_modules);
            for (int i = 0; i < count; ++i)
            {
                const ModuleData *data = t->m_modules.getNthData(i);
                if (data)
                {
                    Rva000B4BED *cache = data->slot18();
                    if (cache)
                        cache->rva000B4AE4();
                }
            }
        }
        if (!stillValid)
            m_templateHashMap.rva00223429(&templateName);
        t = nextT;
    }
}

// Existing target workers; their semantic class names are not claimed here.
class Rva0033A920
{
public:
    void rva0033A920(const void *arg);
};
void Rva00361439Resolve();

// WB ThingFactory::postProcessLoad: same template traversal, ModuleInfo
// +0x2E4, containment predicate slot8 and required-status byte +0x86.
// Retail 0x002CF5FF..0x002CF6B0 retains the full INIException message and
// initializes the template's +0x520 threat state through existing row 33A920.
void ThingFactory::postProcessLoad()
{
    for (ThingTemplate *t = m_firstTemplate; t; t = t->m_nextTemplate)
    {
        t->resolveNames();
        int count = moduleRecordCount(&t->m_behaviorModules);
        for (int i = 0; i < count; ++i)
        {
            const ModuleData *data = t->m_behaviorModules.getNthData(i);
            if (data && data->slot08() && !data->m_flag86)
                throw INIException(3,
                    "ENTRY MISSING: ObjectStatusOfContained entry required within ContainModule for %s.",
                    t->m_name.str());
        }
        ((Rva0033A920 *)((char *)t + 0x520))->rva0033A920(t);
    }
    Rva00361439Resolve();
}

void bfmeGoEBL();

// BFME1 ba7ddda7e8 ThingFactoryFreeDatabase donor, reconciled to the target
// +0x0C head / +0x484 link and existing BFME2 table-clear worker.
// WB a937f0 uses the global-delete path; native 002D0469..002D04A3 retains
// the null guard, virtual destructor with flag0, and separate global delete.
void ThingFactory::freeDatabase()
{
    while (m_firstTemplate)
    {
        ThingTemplate *tmpl = m_firstTemplate;
        m_firstTemplate = m_firstTemplate->m_nextTemplate;
        ::delete tmpl;
    }
    m_templateHashMap.rva003A2A41();
    bfmeGoEBL();
}

// BFME1 cac38f/ZH addTemplate supplies insertion semantics; WB a93870 and
// retail 2D04A3..2D0583 supply replacement path, ID and count behavior.
void ThingFactory::addTemplate(ThingTemplate *tmplate)
{
    const AsciiString *name = &tmplate->m_name;
    Rva0041534BIter found = ((Rva00056F61 *)&m_templateHashMap)->rva0041534B(name);
    if (found.m_node && m_flag) {
        ThingTemplate *old = *(ThingTemplate **)((char *)found.m_node + 8);
        tmplate->m_templateID = old->m_templateID;
        unsigned int replacementID = g_replacementTemplateCounter.storage;
        --g_replacementTemplateCounter.nextID;
        old->m_templateID = (unsigned short)replacementID;
        m_templateHashMap.rva00223429(name);
        *(ThingTemplate **)((Rva002CFEA5 *)&m_templateHashMap)->rva002CFEA5(name) = tmplate;
        tmplate->m_nextTemplate = m_firstTemplate;
        m_firstTemplate = tmplate;
        old->m_matchingReplacementCount = 0;
        tmplate->m_matchingReplacementCount = 0;
        ThingTemplate *t=m_firstTemplate;
        g_flag1 = true;
        for (; t; t=t->m_nextTemplate) {
            if (t->m_templateID >= g_replacementTemplateCounter.nextID && t->m_name.compare(*name) == 0)
                ++t->m_matchingReplacementCount;
        }
    } else {
        tmplate->m_nextTemplate = m_firstTemplate;
        m_firstTemplate = tmplate;
        *(ThingTemplate **)((Rva002CFEA5 *)&m_templateHashMap)->rva002CFEA5(name) = tmplate;
    }
}
