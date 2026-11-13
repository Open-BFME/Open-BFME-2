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
#include "../../../Include/Common/DataChunkOutput.h"
#include <string.h>
// ?equalTag_Rva003B31C7@@YA_NPBX0H@Z present-unmatched
static __declspec(noinline) bool equalTag_Rva003B31C7(const void *record, const void *tag, int) {
 return memcmp(record,tag,4)==0;
}
extern unsigned int g_Va00E02D64;
extern AsciiString g_Va00E02D68;
extern const char *g_Va00DD263CNames[8];
inline const unsigned int &ScriptAllPlayersMask() { return g_Va00E02D64; }
inline const AsciiString &ScriptAllPlayersName() { return g_Va00E02D68; }
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
class Rva003B48B9Holder
{
public:
	int skipScript(void *record);
	char m_pad00[0x38];
private:
	char *m_table; // +0x38
};
#include "../../../Include/GameLogic/Rva003B40B6Holder.h"
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
#include "../../../Include/Common/BfmeFixedStorage002CF0F0.h"
class Rva003B44EE
{
public:
	bool rva003B44EE(const char *token, bool *foundNormal, bool *foundAddOrSub);
	void rva003B5624(AsciiString text);
};
class DataChunkInput;
class UserParser;
struct DataChunkInfo;
typedef bool (__cdecl *BfmeScriptParserCallback)(DataChunkInput &, DataChunkInfo *, void *);
#include "../../../Include/Common/DataChunk.h"
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
#include "../../../Include/GameLogic/ScriptAction.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../Include/GameLogic/ScriptClass.h"
bool Script::parse(DataChunkInput &file, unsigned short version)
{
    m_text0 = file.readAsciiString();
    m_text1 = file.readAsciiString();
    m_text2 = file.readAsciiString();
    bool on = file.readByte() != 0;
    m_isActive = on;
    m_active = on;
    m_isOneShot = file.readByte() != 0;
    m_easy = file.readByte() != 0;
    m_normal = file.readByte() != 0;
    m_hard = file.readByte() != 0;
    m_isSubroutine = file.readByte() != 0;
    if (version >= 2)
        m_delayEvaluationSeconds = file.readInt();
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
    : m_subrecord(), m_delayEvaluationSeconds(0),
      m_mask(*(const BfmeFixedStorage002CF0F0 *)&ScriptAllPlayersMask()),
      m_active(true), m_isOneShot(true), m_isSubroutine(false),
      m_easy(true), m_normal(true), m_hard(true),
      m_condition(0), m_frame(0), m_isActive(true), m_field41(false),
      m_conditionTime(0.0f), m_field4C(0.0f), m_conditionExecutedCount(0)
{
    for (int i = 0; i < 8; ++i) ((unsigned char *)m_actions)[i] = 0;
}

// ZH duplicate semantics; target copyctor/duplicate establish the84B extent,
// deep condition/action providers and reset of the runtime fields.
Script::Script(const Script &other)
    : Snapshot(other), m_text0(other.m_text0), m_text1(other.m_text1),
      m_text2(other.m_text2), m_subrecord(other.m_subrecord),
      m_delayEvaluationSeconds(other.m_delayEvaluationSeconds), m_mask(other.m_mask),
      m_active(other.m_active), m_isOneShot(other.m_isOneShot), m_isSubroutine(other.m_isSubroutine),
      m_easy(other.m_easy), m_normal(other.m_normal), m_hard(other.m_hard),
      m_condition(other.m_condition ? other.m_condition->duplicate() : 0),
      m_frame(0), m_isActive(other.m_isActive), m_field41(false),
      m_conditionTime(0.0f), m_field4C(0.0f), m_conditionExecutedCount(0)
{
    for (int i = 0; i < 2; ++i)
        m_actions[i] = other.m_actions[i] ? other.m_actions[i]->duplicate() : 0;
}

// ZH ScriptList::xfer supplies the recovery semantics and singleton name.
// Target version2 transfers scripts via the indexed20B set, then groups;
// unlike ZH it has no final group sink. Singleton identity and the set
// offsets are established by native3B4716..3B4826.
// A four-byte version local with individually initialized version bytes
// preserves native EBP-8/-7; groupCount occupies EBP-4. Padding is neither
// read nor transferred. Whole body and the existing Script EH family match.
struct ScriptListXferVersion { unsigned char version, maximum; unsigned short padding; };
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../Include/Common/BfmeXfer.h"
#include "../../../Include/GameClient/Drawable.h"
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
    ScriptListXferVersion version;
    version.version = 1;
    version.maximum = 2;
    xfer->operator==(reinterpret_cast<Xfer::Version &>(version));
    unsigned short count = (unsigned short)(scripts.sortedEnd - scripts.sortedBegin);
    xfer->operator==(count);
    for (int index = scripts.head; index != -1;
         index = scripts.recordsBegin[index].previous) {
        void *node = scripts.recordsBegin[index].node;
        xfer->operator==(*((Snapshot *)((char *)node + 4)));
        if (--count == 0)
            break;
    }
    if (count > 0) {
        if (!s_mtScript)
            s_mtScript = new Script;
        while (count) {
            xfer->operator==(*(s_mtScript));
            --count;
        }
    }
    if (version.maximum >= 2) {
        groupCount = (unsigned short)(groups.sortedEnd - groups.sortedBegin);
        xfer->operator==(groupCount);
        for (int index = groups.head; index != -1;
             index = groups.recordsBegin[index].previous) {
            void *node = groups.recordsBegin[index].node;
            xfer->operator==(*((Snapshot *)((char *)node + 4)));
            if (--groupCount == 0)
                break;
        }
    }
}

// The all-players name. Retail builds it last in the Scripts.cpp TU's .text$yc run
// (0x007AF7FE, after the unit's Drawable.h copy 0x007AF7DD and the all-players mask
// 0x007AF7ED, before the pool-init marker 0x007AF819) through the out-of-line
// AsciiString(const char *) 0x0000654A. Address name kept; the original name is unknown.
#pragma inline_depth( 0 )
AsciiString g_Va00E02D68("ALL");
#pragma inline_depth()
