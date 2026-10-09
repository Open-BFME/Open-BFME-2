// ?xfer@ScriptList@@MAEXPAVXfer@@@Z
// partial score=0.97 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /Oi-
// Real C++ for the complete retail script writer and its private mask helper.
// Target identity: WriteScriptListDataChunk calls 0x003B5994 with the writer,
// list and first-script handle. That body calls the mask writer at 0x003B372D.
// Donor: GeneralsMD ScriptEngine/Scripts.cpp, reviewed at BFME1 revision
// dae380faa5f6fa536eec8d6ebbe877321d4cb51d. The donor supplies chunk semantics;
// retail supplies the handle/capture split, offsets, version 4, subrecord,
// player-mask output and unified action writer. Layout views are structural
// inferences from those accesses, not claims of donor class equivalence.
// The static comparator retains the existing row's spelling and unused third
// argument. Its visible body lets MSVC eliminate that private argument. The
// mask pointer likewise travels in EDI; only the writer remains on the stack.
// Global identities come from the data ledger and their constructor bodies:
// E02D64 is the initialized all-bits mask, E02D68 is the AsciiString "ALL".
#include "ascii_string.h"
class DataChunkOutput;
class Script;
class ScriptList;
class ScriptAction;
class DataChunkInput;
struct DataChunkInfo;
class OrCondition { public: OrCondition *duplicate() const; static bool ParseOrConditionDataChunk(DataChunkInput &,DataChunkInfo *,void *); static void WriteOrConditionDataChunk(DataChunkOutput &,OrCondition *); };
class DataChunkOutput { public:
 void openDataChunk(char *, unsigned short);
 void writeAsciiString(const AsciiString &);
 void writeByte(unsigned char);
 void writeInt(int);
 void closeDataChunk();
};
extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
// ?equalTag_Rva003B31C7@@YA_NPBX0H@Z present-unmatched
static __declspec(noinline) bool equalTag_Rva003B31C7(const void *record, const void *tag, int) {
 return memcmp(record,tag,4)==0;
}
extern unsigned int g_Va00E02D64;
extern unsigned int g_Va00E02D68;
extern const char *g_Va00DD263CNames[8];
inline const unsigned int &ScriptAllPlayersMask() { return g_Va00E02D64; }
inline const AsciiString &ScriptAllPlayersName() { return *(const AsciiString *)&g_Va00E02D68; }
// ?WriteScriptPlayerMask_Rva003B372D@@YAXAAVDataChunkOutput@@PBI@Z
static __declspec(noinline) void WriteScriptPlayerMask_Rva003B372D(DataChunkOutput &writer, const unsigned int *mask) {
 if(equalTag_Rva003B31C7(mask,&ScriptAllPlayersMask(),0)) {
  writer.writeAsciiString(ScriptAllPlayersName());
 } else {
  AsciiString text;
  bool first=true;
  for(int i=0;i<7;++i) {
   if(mask[(unsigned int)i>>5] & (1u<<(i&31))) {
    if(first) first=false;
    else text += " ";
    text += g_Va00DD263CNames[i];
   }
  }
  writer.writeAsciiString(text);
 }
}
struct ScriptSubRecord { unsigned char a,b; int value; unsigned char c; AsciiString name; };
struct ScriptInput { Script *next; int nameIndex; };
struct ScriptNameEntry { unsigned char pad[8]; AsciiString name; unsigned char tail[8]; };
struct ScriptListView { unsigned char pad[0x38]; ScriptNameEntry *names; };
struct ScriptReal {
 int unknown;
 AsciiString strings[3];
 ScriptSubRecord subrecord;
 int value;
 unsigned int mask;
 unsigned char flags[6];
 OrCondition *condition;
 ScriptAction *actions[2];
};
class Rva003B48B9Holder { public: int skipScript(void *); };
class Rva003B40B6Holder { public: void *captureGroup(void *); };
void WriteScriptSubRecord_Rva003B24F2(DataChunkOutput &,const ScriptSubRecord *);

void WriteActionDataChunk(char *,DataChunkOutput &,ScriptAction *);
void WriteScriptDataChunk(DataChunkOutput &writer,ScriptList *list,Script *script) {
 for(;script;script=((ScriptInput *)script)->next) {
  ScriptInput *input=(ScriptInput *)script;
  if((unsigned char)((Rva003B48B9Holder *)list)->skipScript(input)) continue;
  ScriptReal *real=(ScriptReal *)((Rva003B40B6Holder *)list)->captureGroup(input);
  writer.openDataChunk("Script",4);
  writer.writeAsciiString(((ScriptListView *)list)->names[input->nameIndex].name);
  writer.writeAsciiString(real->strings[0]);
  writer.writeAsciiString(real->strings[1]);
  writer.writeAsciiString(real->strings[2]);
  writer.writeByte(real->flags[0]);
  writer.writeByte(real->flags[1]);
  writer.writeByte(real->flags[3]);
  writer.writeByte(real->flags[4]);
  writer.writeByte(real->flags[5]);
  writer.writeByte(real->flags[2]);
  writer.writeInt(real->value);
  WriteScriptSubRecord_Rva003B24F2(writer,&real->subrecord);
  WriteScriptPlayerMask_Rva003B372D(writer,&real->mask);
  if(real->condition) OrCondition::WriteOrConditionDataChunk(writer,real->condition);
  for(int i=0;i<2;++i) {
   if(real->actions[i]) WriteActionDataChunk(i==1?"ScriptActionFalse":"ScriptAction",writer,real->actions[i]);
  }
  writer.closeDataChunk();
 }
}

// Reader family: BFME1 f989 ScriptRva0035C0C0Parse provides the instance
// reader rather than ZH's static allocation wrapper. BFME2 owns the +10
// subrecord and version4 player mask. The mask helper has private ABI in
// native3B5918..3B5994: input ECX and hidden output ESI, selected by MSVC
// from this visible internal function and its only caller.
class BfmeFixedStorage002CF0F0
{
    char m_bytes[4];
public:
    __declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &);
    BfmeFixedStorage002CF0F0() {}
    unsigned int bits() const { return *(const unsigned int *)m_bytes; }
};
class Rva003B44EE
{
public:
    void rva003B5624(AsciiString text);
};
class DataChunkInput;
class UserParser;
struct DataChunkInfo;
typedef bool (__cdecl *BfmeScriptParserCallback)(DataChunkInput &, DataChunkInfo *, void *);
class DataChunkInput
{
public:
    AsciiString readAsciiString();
    unsigned char readByte();
    int readInt();
    UserParser *registerParser(const AsciiString &, const AsciiString &, BfmeScriptParserCallback, void *);
    bool parse(void *);
};
extern "C" void *memset(void *, int, unsigned int);
static __declspec(noinline) BfmeFixedStorage002CF0F0 ReadScriptPlayerMask_Rva003B5918(DataChunkInput &file)
{
    AsciiString text = file.readAsciiString();
    if (text.compare(ScriptAllPlayersName()) == 0)
        return *(const BfmeFixedStorage002CF0F0 *)&ScriptAllPlayersMask();
    BfmeFixedStorage002CF0F0 mask;
    memset(&mask, 0, 4);
    ((Rva003B44EE *)&mask)->rva003B5624(text);
    return mask;
}
class Rva003B3536
{
public:
    Rva003B3536() : a(false), b(false), value(0), c(true) {}
    Rva003B3536(const Rva003B3536 &);
    bool a, b;
    int value;
    bool c;
    AsciiString name;
    void rva003B3536(DataChunkInput &file, unsigned short version);
};
class ScriptAction
{
public:
    ScriptAction *duplicate() const;
    static bool ParseActionDataChunk(DataChunkInput &, DataChunkInfo *, void *);
    static bool ParseActionFalseDataChunk(DataChunkInput &, DataChunkInfo *, void *);
};
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
class Script : public Snapshot
{
public:
    Script();
    Script(const Script &other);
    Script *duplicate() const;
    bool Rva003B79F1(DataChunkInput &file, unsigned short version);
protected:
    virtual ~Script();
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
private:
    AsciiString m_text0, m_text1, m_text2;
    Rva003B3536 m_subrecord;
    int m_delay;
    BfmeFixedStorage002CF0F0 m_mask;
    bool m_active, m_easy, m_subroutine, m_normal, m_hard, m_flag;
    OrCondition *m_condition;
    ScriptAction *m_actions[2];
    int m_frame;
    bool m_currentActive, m_otherFlag;
    AsciiString m_runtimeName44;
    float m_conditionTime, m_currentTime;
    int m_conditionExecutedCount;
};
bool Script::Rva003B79F1(DataChunkInput &file, unsigned short version)
{
    m_text0 = file.readAsciiString();
    m_text1 = file.readAsciiString();
    m_text2 = file.readAsciiString();
    bool on = file.readByte() != 0;
    m_currentActive = on;
    m_active = on;
    m_easy = file.readByte() != 0;
    m_normal = file.readByte() != 0;
    m_hard = file.readByte() != 0;
    m_flag = file.readByte() != 0;
    m_subroutine = file.readByte() != 0;
    if (version >= 2)
        m_delay = file.readInt();
    if (version >= 3)
        m_subrecord.rva003B3536(file, version);
    if (version >= 4)
    {
        *(unsigned int *)&m_mask = ReadScriptPlayerMask_Rva003B5918(file).bits();
    }
    else
        *(unsigned int *)&m_mask = ScriptAllPlayersMask();
    file.registerParser(AsciiString("OrCondition"), AsciiString("Script"),
        (BfmeScriptParserCallback)&OrCondition::ParseOrConditionDataChunk, 0);
    file.registerParser(AsciiString("ScriptAction"), AsciiString("Script"),
        (BfmeScriptParserCallback)&ScriptAction::ParseActionDataChunk, 0);
    file.registerParser(AsciiString("ScriptActionFalse"), AsciiString("Script"),
        (BfmeScriptParserCallback)&ScriptAction::ParseActionFalseDataChunk, 0);
    return file.parse(this);
}

// ZH Script default initialization supplies semantics; target adds player
// mask24 and the measured16B subrecord10. Native destructor3B35B1 calls
// string cleanup on44; timer field meanings follow the ZH lead. Snapshot identity:
// vtable81F424 slot2 returns the native literal "Script" at81F434.
Script::Script()
    : m_subrecord(), m_delay(0),
      m_mask(*(const BfmeFixedStorage002CF0F0 *)&ScriptAllPlayersMask()),
      m_active(true), m_easy(true), m_subroutine(false),
      m_normal(true), m_hard(true), m_flag(true),
      m_condition(0), m_frame(0), m_currentActive(true), m_otherFlag(false),
      m_conditionTime(0.0f), m_currentTime(0.0f), m_conditionExecutedCount(0)
{
    for (int i = 0; i < 8; ++i) ((unsigned char *)m_actions)[i] = 0;
}

// ZH duplicate semantics; target copyctor/duplicate establish the84B extent,
// deep condition/action providers and reset of the runtime fields.
Script::Script(const Script &other)
    : Snapshot(other), m_text0(other.m_text0), m_text1(other.m_text1),
      m_text2(other.m_text2), m_subrecord(other.m_subrecord),
      m_delay(other.m_delay), m_mask(other.m_mask),
      m_active(other.m_active), m_easy(other.m_easy), m_subroutine(other.m_subroutine),
      m_normal(other.m_normal), m_hard(other.m_hard), m_flag(other.m_flag),
      m_condition(other.m_condition ? other.m_condition->duplicate() : 0),
      m_frame(0), m_currentActive(other.m_currentActive), m_otherFlag(false),
      m_conditionTime(0.0f), m_currentTime(0.0f), m_conditionExecutedCount(0)
{
    for (int i = 0; i < 2; ++i)
        m_actions[i] = other.m_actions[i] ? other.m_actions[i]->duplicate() : 0;
}

// ZH ScriptList::xfer supplies the recovery semantics and singleton name.
// Target version2 transfers scripts via the indexed20B set, then groups;
// unlike ZH it has no final group sink. Singleton identity and the set
// offsets are established by native3B4716..3B4826.
struct ScriptListXferVersion { unsigned char version, maximum; };
template<int N> class ScriptListXferSlots : public ScriptListXferSlots<N - 1>
{ public: virtual void gap(char (*)[N]); };
template<> class ScriptListXferSlots<0> {};
class Xfer : public ScriptListXferSlots<10>
{
public:
    virtual void transferVersion(ScriptListXferVersion *);
    virtual void gap11();
    virtual void transferSnapshot(Snapshot *);
    virtual void gap13(); virtual void gap14(); virtual void gap15();
    virtual void gap16(); virtual void gap17(); virtual void gap18();
    virtual void gap19(); virtual void gap20(); virtual void gap21();
    virtual void gap22(); virtual void gap23(); virtual void gap24();
    virtual void gap25(); virtual void gap26(); virtual void gap27();
    virtual void gap28(); virtual void gap29(); virtual void gap30();
    virtual void gap31();
    virtual void transferUnsignedShort(unsigned short *);
};
struct ScriptListXferRecord
{
    int previous, next;
    AsciiString name;
    unsigned char flag;
    unsigned short references;
    void *node;
};
struct ScriptListXferSet
{
    unsigned int *sortedBegin, *sortedEnd, *sortedStorageEnd;
    ScriptListXferRecord *recordsBegin, *recordsEnd, *recordsStorageEnd;
    int freeHead, head;
};
class ScriptList : public Snapshot
{
public:
    virtual ~ScriptList();
protected:
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
private:
    void *groupHead, *scriptHead;
    ScriptListXferSet groups, scripts;
};
static Script *s_mtScript = 0;
void ScriptList::xfer(Xfer *xfer)
{
    unsigned short groupCount;
    ScriptListXferVersion version = { 1, 2 };
    xfer->transferVersion(&version);
    unsigned short count = (unsigned short)(scripts.sortedEnd - scripts.sortedBegin);
    xfer->transferUnsignedShort(&count);
    for (int index = scripts.head; index != -1;
         index = scripts.recordsBegin[index].previous) {
        void *node = scripts.recordsBegin[index].node;
        xfer->transferSnapshot((Snapshot *)((char *)node + 4));
        if (--count == 0)
            break;
    }
    if (count > 0) {
        if (!s_mtScript)
            s_mtScript = new Script;
        while (count) {
            xfer->transferSnapshot(s_mtScript);
            --count;
        }
    }
    if (version.maximum >= 2) {
        groupCount = (unsigned short)(groups.sortedEnd - groups.sortedBegin);
        xfer->transferUnsignedShort(&groupCount);
        for (int index = groups.head; index != -1;
             index = groups.recordsBegin[index].previous) {
            void *node = groups.recordsBegin[index].node;
            xfer->transferSnapshot((Snapshot *)((char *)node + 4));
            if (--groupCount == 0)
                break;
        }
    }
}
