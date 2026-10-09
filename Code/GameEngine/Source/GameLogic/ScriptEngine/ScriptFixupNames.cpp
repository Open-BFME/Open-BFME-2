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

struct Rva003B8337Node;

class Rva003B573E
{
public:
    Rva003B8337Node *rva003B8337(int key);
    int rva003B6633(const StringBase<char> &key);
    _STL::vector<void *> m_sorted;
    _STL::vector<Rva003B675BRecord> m_records;
    int m_freeHead;
    int m_tail;
};

struct Rva0034F9D0Head;
struct Rva0034F9D0Node;

struct BfmeNodeXZ { BfmeNodeXZ *m_next; };
struct BfmeHeadXZ { void *m_first; BfmeNodeXZ *m_second; };
class Rva003BScriptReference;

class ScriptList
{
public:
    Rva003BScriptReference *rva003B83B1(const StringBase<char> &key);
    void addScriptRef(BfmeHeadXZ *, BfmeNodeXZ *, BfmeNodeXZ *);
    void addGroupRef(Rva0034F9D0Head *head, Rva0034F9D0Node *node, Rva0034F9D0Node *after);
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

// ?read@Rva003B3485@@QAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z retail
// 0x003B8589..0x003B8699 (272 bytes): slot 1 of ??_7Rva003B3485@@6B@
// (0x0081F41C) -- the "ScriptGroup" chunk binding's read (WB 0x00AA6FB0).
// Reads the group name (DataChunkInput::readAsciiString) and makes it unique
// through fixupGroupName (static here: ScriptList in ecx and the name in edi)
// then takes a group node (rowed 0x003B8337) and its record (rowed
// captureGroup 0x003B40A1); the active byte goes to +0xC and from chunk
// version 2 the subroutine byte to +0xD. The node is linked after the last
// entry of the owner's list (inlined tail walk) through 0x003B23DE (WB
// ScriptList::addGroupRef; retail loads ecx with the list). Nested
// "ScriptGroup" and "Script" bindings (rowed ctors 0x003B3485 and
// 0x003B37C8) cover the group's sub-chunks while DataChunkInput::parse runs.
class DataChunkInput
{
public:
    AsciiString readAsciiString();
    unsigned char readByte();
    bool parse(void *userData);
};

struct DataChunkInfo
{
    AsciiString label;
    AsciiString parentLabel;
    unsigned short version;
    int dataSize;
};

class Rva003B40A1Holder
{
public:
    void *captureGroup(void *node);
};

struct Rva0034F9D0Node
{
    Rva0034F9D0Node *m_next;
};

struct Rva0034F9D0Head
{
    Rva0034F9D0Node *m_first;
};

struct ScriptGroupRecordView
{
    void *m_00;
    Rva0034F9D0Node m_links;
    char m_08[4];
    bool m_isGroupActive;
    bool m_isGroupSubroutine;
};

class BfmeParserRegistryVE;
class Q1Forwardee0000871A { public: void handle(int); };
extern const void *const g_00BC9574[];

class BfmeParserBindingBaseVE
{
    const void *const *table;
    Q1Forwardee0000871A *registry;
    int token;
public:
    ~BfmeParserBindingBaseVE() { table = g_00BC9574; registry->handle(token); }
};

class Rva003B37C8 : public BfmeParserBindingBaseVE
{
    void *a;
    void *b;
public:
    Rva003B37C8(void *, void *, BfmeParserRegistryVE *, const AsciiString *);
    bool read(DataChunkInput &file, DataChunkInfo *info);
};

class Rva003B3485 : public BfmeParserBindingBaseVE
{
    ScriptList *m_list;
    Rva0034F9D0Head *m_groups;
public:
    Rva003B3485(void *, void *, BfmeParserRegistryVE *, const AsciiString *);
    bool read(DataChunkInput &file, DataChunkInfo *info);
};

bool Rva003B3485::read(DataChunkInput &file, DataChunkInfo *info)
{
    AsciiString name = file.readAsciiString();
    fixupGroupName(m_list, name);
    Rva003B8337Node *node = reinterpret_cast<Rva003B573E *>(m_list)->rva003B8337((int)&name);
    ScriptGroupRecordView *group = (ScriptGroupRecordView *)reinterpret_cast<Rva003B40A1Holder *>(m_list)->captureGroup(node);
    group->m_isGroupActive = file.readByte() != 0;
    if (info->version >= 2)
        group->m_isGroupSubroutine = file.readByte() != 0;
    Rva0034F9D0Node *last = m_groups->m_first;
    if (last)
    {
        for (Rva0034F9D0Node *next = last->m_next; next; next = next->m_next)
            last = next;
    }
    m_list->addGroupRef(m_groups, (Rva0034F9D0Node *)node, last);
    Rva003B3485 groups(m_list, &group->m_links, reinterpret_cast<BfmeParserRegistryVE *>(&file), &info->label);
    Rva003B37C8 scripts(m_list, &group->m_links, reinterpret_cast<BfmeParserRegistryVE *>(&file), &info->label);
    bool result = file.parse(0);
    return result;
}

class Script
{
public:
    bool Rva003B79F1(DataChunkInput &file, unsigned short version);
};
class Rva003B40B6Holder
{
public:
    void *captureGroup(void *node);
};
// WB AA9050 names ScriptDataChunkParser::parse; the parser binding owner
// keeps its established target token. New dependencies are independently
// verified bodies; BF1/ZH list parser supplies purpose and append semantics.
bool Rva003B37C8::read(DataChunkInput &file, DataChunkInfo *info)
{
    AsciiString name = file.readAsciiString();
    fixupScriptName((ScriptList *)a, name);
    Rva003BScriptReference *node = ((ScriptList *)a)->rva003B83B1(*(const StringBase<char> *)&name);
    ((Script *)((Rva003B40B6Holder *)a)->captureGroup(node))->Rva003B79F1(file, info->version);
    BfmeHeadXZ *head = (BfmeHeadXZ *)b;
    BfmeNodeXZ *last = head->m_second;
    if (last)
    {
        for (BfmeNodeXZ *next = last->m_next; next; next = next->m_next)
            last = next;
    }
    ((ScriptList *)a)->addScriptRef(head, (BfmeNodeXZ *)node, last);
    return true;
}
