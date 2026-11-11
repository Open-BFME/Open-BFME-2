// ??1ScriptList@@UAE@XZ
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/ScriptEngine/ScriptListDestructor.cpp (donor
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// Compiled that way each body below places uniquely on unclaimed game.dat
// .text by masked whole-.text search, and ./build.sh reproduces it byte for
// byte: ScriptList::~ScriptList 0x003B774B (81B). Callee addresses are read
// off retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// partial score=0.93 date=2026-09-02
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc

// Retail table C1FAAC is deleting destructor / post-load / name / xfer.
// Copy constructor3B88DA independently establishes the same 4C-byte layout:
// Snapshot4 + two head pointers8 + two record sets32. The set lifetime
// providers are already recovered at3B766B and3B7167; donor addresses were
// only provisional names. Original nominal names of those records are unknown.
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva003B872ASet
{
public:
	~Rva003B872ASet();

private:
	unsigned char m_data[0x20];
};

class Rva003B8802Set
{
public:
	~Rva003B8802Set();
private:
	unsigned char m_data[0x20]; // +0x00
};

class Rva003B31DF { public: void clear(); };
class Rva003B3204 { public: void clear(); };

class ScriptListBase
{
public:
    ~ScriptListBase();

private:
	Rva003B31DF *m_firstGroup;
	Rva003B3204 *m_firstScript;
};


class ScriptList : public Snapshot, public ScriptListBase
{
public:
	ScriptList();
	~ScriptList();

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *);

private:
	Rva003B872ASet m_first;
	Rva003B8802Set m_second;
};

typedef char ScriptListExtent[(sizeof(ScriptList) == 0x4c) ? 1 : -1];

// ??1ScriptList@@UAE@XZ
ScriptList::~ScriptList()
{
}

void ScriptList::loadPostProcess() {}
const char *ScriptList::GetSnapshotName() const { return "ScriptList"; }

// Full native boundary3B793A..3B79F1 RET8; anchor3B7951 is an interior entry.
// ZH Scripts.cpp ParseScriptsDataChunk supplies the register/parse/copy semantics.
// BFME2 uses an unknown receiver with output list/count pointers at +0C/+10;
// ScriptEngine flag1A4DA and TheWritableGlobalData flagD2F establish the early gate.
// DataChunkInput::parse is now a verified provider. The registered callback
// 3B7836 consumes count+20 pointers; only count is initialized by this reader.
// Original receiver and method names are unknown: retain an address identity.
#include "ascii_string.h"
class ScriptList;
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
unsigned char isCorrectMapType();
#include "../../../Include/Common/DataChunkInfo.h"
class DataChunkInput;
bool Rva003B7836(DataChunkInput &, DataChunkInfo *, void *);
class UserParser;
#include "../../../Include/Common/DataChunk.h"
struct Rva003B793AReadInfo { int count; ScriptList *lists[20]; };
class Rva003B793A {
 char unknown00[12];
 ScriptList **lists;
 int *count;
public:
 bool read(DataChunkInput &, DataChunkInfo *);
};
bool Rva003B793A::read(DataChunkInput &file, DataChunkInfo *info)
{
 if (TheScriptEngine && reinterpret_cast<unsigned char *>(TheScriptEngine)[0x1a4da]
     && !isCorrectMapType() && !reinterpret_cast<unsigned char *>(TheWritableGlobalData)[0xd2f])
  return false;
 file.registerParser(AsciiString("ScriptList"), info->label, Rva003B7836, 0);
 Rva003B793AReadInfo readInfo;
 readInfo.count = 0;
 if (file.parse(&readInfo)) {
  *count = readInfo.count;
  for (int i = 0; i < *count; ++i) lists[i] = readInfo.lists[i];
  return true;
 }
 return false;
}



// Registered ScriptList callback3B7836..3B793A,260B RET0.
// The two existing parser-binding constructors own registration; scope exit
// restores their witnessed BC9574 base table and unlinks through306D7B.
#include <new>


class BfmeParserRegistryVE;
#include "../../../Include/GameLogic/Q1Forwardee0000871A.h"
extern "C" const void *const __identifier("??_7BfmeParserBindingBaseVE@@6B@")[];
class BfmeParserBindingBaseVE {
 const void *const *table;
 Q1Forwardee0000871A *registry;
 int token;
public:
 ~BfmeParserBindingBaseVE() { table=__identifier("??_7BfmeParserBindingBaseVE@@6B@"); registry->handle(token); }
};
class Rva003B3485 : public BfmeParserBindingBaseVE {
 void *a; void *b;
public:
 Rva003B3485(void *,void *,BfmeParserRegistryVE *,const AsciiString *);
};
class Rva003B37C8 : public BfmeParserBindingBaseVE {
 void *a; void *b;
public:
 Rva003B37C8(void *,void *,BfmeParserRegistryVE *,const AsciiString *);
};

class Debug;
extern Debug *theDebug;
bool bfmeRva000387C0();

// Use the already rowed Debug owner for this static member.
#include "../../Common/debug.h"
class Rva003B7836Stream {
public:
 virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
 virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
 virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
 virtual void s12();
 virtual Rva003B7836Stream *number(int);
 virtual Rva003B7836Stream *text(const char *);
 virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
 virtual Rva003B7836Stream *severity(int);
};
class Rva003B7836Debug {
public:
 virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
 virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
 virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
 virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
 virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
 virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
 virtual void callsite();
 virtual void s25(); virtual void s26();
 virtual Rva003B7836Stream *stream(int,int,int);
};
bool Rva003B7836(DataChunkInput &file, DataChunkInfo *info, void *data)
{
 Rva003B793AReadInfo *readInfo = static_cast<Rva003B793AReadInfo *>(data);
 if (readInfo->count >= 20) {
  if (bfmeRva000387C0()) {
   Debug::SkipNext(true);
   reinterpret_cast<Rva003B7836Debug *>(theDebug)->callsite();
   reinterpret_cast<Rva003B7836Debug *>(theDebug)->stream(0,0,0)
    ->text("Reading too many script lists.  Max is ")->number(20)->severity(2);
  }
  return false;
 }
 // Retail pool-style construction has no owning-new exception cleanup.
 void *memory = ::operator new(sizeof(ScriptList));
 ScriptList *list = memory ? &static_cast<ScriptList *>(memory)->ScriptList::ScriptList() : 0;
 readInfo->lists[readInfo->count] = list;
 ++readInfo->count;
 Rva003B3485 group(list, static_cast<ScriptListBase *>(list),
  reinterpret_cast<BfmeParserRegistryVE *>(&file), &info->label);
 Rva003B37C8 script(list, static_cast<ScriptListBase *>(list),
  reinterpret_cast<BfmeParserRegistryVE *>(&file), &info->label);
 // The now-dead userData argument supplies the native one-byte result home.
 bool &result = *new(reinterpret_cast<unsigned char *>(&data) + 3) bool;
 result = file.parse(0);
 return result;
}

// Native3B4071 owns the two recursive head cleanups in reverse member order.
// The complete destructor and its EH graph use this base at nullable this+4.
// Keep the definition after its callers, preserving the native out-of-line call.
ScriptListBase::~ScriptListBase()
{
 Rva003B3204 *script = m_firstScript;
 if (script) {
  script->clear();
  operator delete(script);
 }
 Rva003B31DF *group = m_firstGroup;
 if (group) {
  group->clear();
  operator delete(group);
 }
}






