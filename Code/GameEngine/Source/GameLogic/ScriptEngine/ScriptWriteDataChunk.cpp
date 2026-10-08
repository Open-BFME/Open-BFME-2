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
class OrCondition { public: static void WriteOrConditionDataChunk(DataChunkOutput &,OrCondition *); };
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
// ?WriteScriptPlayerMask_Rva003B372D@@YAXAAVDataChunkOutput@@PBI@Z
static __declspec(noinline) void WriteScriptPlayerMask_Rva003B372D(DataChunkOutput &writer, const unsigned int *mask) {
 if(equalTag_Rva003B31C7(mask,&g_Va00E02D64,0)) {
  writer.writeAsciiString(*(const AsciiString *)&g_Va00E02D68);
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
