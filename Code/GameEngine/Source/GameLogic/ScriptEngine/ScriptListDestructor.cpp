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

class Gen_0035B8A0
{
public:
	~Gen_0035B8A0();

private:
	unsigned char m_data[0x20];
};

class Gen_0035B960
{
public:
	~Gen_0035B960();

private:
	unsigned char m_data[0x20];
};

class ScriptGroupPoolObject
{
public:
	ScriptGroupPoolObject *next;
	void deleteInstance(int destroy);
};

class ScriptPoolObject
{
public:
	ScriptPoolObject *next;
	void deleteInstance(int destroy);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptListInterface
{
public:
	virtual void reset();
	~ScriptListInterface() {}
};

class ScriptListBase
{
public:
    ~ScriptListBase();

private:
	ScriptPoolObject *m_firstGroup;
	ScriptGroupPoolObject *m_firstScript;
};


class ScriptList : public ScriptListInterface, public ScriptListBase
{
public:
	~ScriptList();

private:
	Gen_0035B8A0 m_first;
	Gen_0035B960 m_second;
};

// ??1ScriptList@@QAE@XZ
ScriptList::~ScriptList()
{
}

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
unsigned char Rva003B242CGet();
struct DataChunkInfo { AsciiString label; };
class DataChunkInput;
bool Rva003B7836(DataChunkInput &, DataChunkInfo *, void *);
class UserParser;
class DataChunkInput {
public:
 UserParser *registerParser(const AsciiString &, const AsciiString &,
  bool (*)(DataChunkInput &, DataChunkInfo *, void *), void *);
 bool parse(void *);
};
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
     && !Rva003B242CGet() && !reinterpret_cast<unsigned char *>(TheWritableGlobalData)[0xd2f])
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


