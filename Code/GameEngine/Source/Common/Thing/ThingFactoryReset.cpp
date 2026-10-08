// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
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
    virtual void slot08(); virtual void slot09();
    virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13();
    virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17();
    virtual Rva000B4BED *slot18() const;
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
    char m_pad00C[0x64 - 0x0C];
    AsciiString m_name;
    char m_pad068[0x11F - 0x68];
    unsigned char m_flags11F;
    char m_pad120[0x2F0 - 0x120];
    ModuleInfo m_modules;
    char m_pad2FC[0x484 - 0x2FC];
    ThingTemplate *m_nextTemplate;
};

// Existing row 0x00223429: erase by pointer to the four-byte AsciiString.
class Rva000427195
{
public:
    int rva00223429(const AsciiString *key);
    void *m_unused;
    void **m_beginBuckets, **m_endBuckets, **m_storageEnd;
    unsigned int m_numElements;
};

class ThingFactory : public SubsystemInterface
{
public:
    virtual void reset();
private:
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
