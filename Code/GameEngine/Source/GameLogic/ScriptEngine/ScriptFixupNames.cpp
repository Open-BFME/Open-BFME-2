// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "ascii_string.h"

// WB names fixupGroupName (0xAA7160) and fixupScriptName (0xAA91A0),
// Scripts.cpp lines 1913 and 2498. Both accept a ScriptList and a string.
// Retail uses the two 0x20-byte name tables at list+0xC and list+0x2C.
// The record layout and lookup spelling are independently rowed in
// ScriptListSubrecordRemove.cpp; the WB helper returns the release flag.
struct Rva003B675BRecord
{
    int m_previous;
    int m_next;
    AsciiString m_name;
    bool m_released;
    unsigned char m_pad;
    unsigned short m_references;
    void *m_nodes;
};

class Rva003B573E
{
public:
    int rva003B6633(const StringBase<char> &key);
    _STL::vector<void *> m_sorted;
    _STL::vector<Rva003B675BRecord> m_records;
    int m_freeHead;
    int m_tail;
};

class ScriptList
{
public:
    char m_prefix[0xC];
    Rva003B573E m_groups;
    Rva003B573E m_scripts;
};

static __declspec(noinline) bool rva003B6A1B(ScriptList *list, const AsciiString &name)
{
    int index = list->m_groups.rva003B6633(*(const StringBase<char> *)&name);
    if (index != -1)
        return list->m_groups.m_records[index].m_released;
    return true;
}

static __declspec(noinline) void fixupGroupName(ScriptList *list, AsciiString &name)
{
    if (!rva003B6A1B(list, name)) {
        AsciiString candidate;
        int suffix = 0;
        do {
            candidate.format("%s %d", name.str(), ++suffix);
        } while (!rva003B6A1B(list, candidate));
        name = candidate;
    }
}

static __declspec(noinline) bool rva003B6C6F(ScriptList *list, const AsciiString &name)
{
    int index = list->m_scripts.rva003B6633(*(const StringBase<char> *)&name);
    if (index != -1)
        return list->m_scripts.m_records[index].m_released;
    return true;
}

static __declspec(noinline) void fixupScriptName(ScriptList *list, AsciiString &name)
{
    if (!rva003B6C6F(list, name)) {
        AsciiString candidate;
        int suffix = 0;
        do {
            candidate.format("%s %d", name.str(), ++suffix);
        } while (!rva003B6C6F(list, candidate));
        name = candidate;
    }
}

// Compilation anchor for the internal functions; it has no retail address.
// ?emitGroupNameFixup absent-from-retail
void emitGroupNameFixup(ScriptList *list, AsciiString &group)
{
    fixupGroupName(list, group);
}

// ?emitScriptNameFixup absent-from-retail
void emitScriptNameFixup(ScriptList *list, AsciiString &script)
{
    fixupScriptName(list, script);
}
