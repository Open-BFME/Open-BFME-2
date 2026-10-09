// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /Oi- /Oy-
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
class OrCondition { public: static bool ParseOrConditionDataChunk(DataChunkInput &,DataChunkInfo *,void *); static void WriteOrConditionDataChunk(DataChunkOutput &,OrCondition *); };
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
struct Rva003B3536
{
    bool a, b;
    int value;
    bool c;
    AsciiString name;
    void rva003B3536(DataChunkInput &file, unsigned short version);
};
class ScriptAction
{
public:
    static bool ParseActionDataChunk(DataChunkInput &, DataChunkInfo *, void *);
    static bool ParseActionFalseDataChunk(DataChunkInput &, DataChunkInfo *, void *);
};
class Script
{
public:
    bool Rva003B79F1(DataChunkInput &file, unsigned short version);
private:
    int unknown;
    AsciiString m_strings[3];
    Rva003B3536 m_subrecord;
    int m_delay;
    unsigned int m_mask;
    bool m_active, m_easy, m_subroutine, m_normal, m_hard, m_flag;
    char m_between[0x40 - 0x2E];
    bool m_currentActive;
};
bool Script::Rva003B79F1(DataChunkInput &file, unsigned short version)
{
    m_strings[0] = file.readAsciiString();
    m_strings[1] = file.readAsciiString();
    m_strings[2] = file.readAsciiString();
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
        m_mask = ReadScriptPlayerMask_Rva003B5918(file).bits();
    }
    else
        m_mask = ScriptAllPlayersMask();
    file.registerParser(AsciiString("OrCondition"), AsciiString("Script"),
        (BfmeScriptParserCallback)&OrCondition::ParseOrConditionDataChunk, 0);
    file.registerParser(AsciiString("ScriptAction"), AsciiString("Script"),
        (BfmeScriptParserCallback)&ScriptAction::ParseActionDataChunk, 0);
    file.registerParser(AsciiString("ScriptActionFalse"), AsciiString("Script"),
        (BfmeScriptParserCallback)&ScriptAction::ParseActionFalseDataChunk, 0);
    return file.parse(this);
}
