// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common /O1 /G7 /DNDEBUG /MD /EHsc
// platformsdk
// ?embedPristineMap@@YAXVAsciiString@@PAVXfer@@@Z (WorldBuilder name), retail 0x0041AD08, 248 bytes.
// Evidence: unlock lane, callers at 0x0041B35F/0x0041B3CA in 0x0041AFDA, callee openFile 0x00600C34,
// _bfmeFormatText 0x0060C36E, new[] 0x0002FDE0, delete[] 0x0002FD80, releaseBuffer 0x00036410,
// EmptyString g_Rva0107301CEmptyString, TheFileSystem, PristineMap literal, guard throw info.
// Static with TU-local caller for private register convention (ctx in edi from entry, shape lever 462).
#define NOMINMAX
#include <windows.h>
#include <new>
#include "ascii_string.h"

class File
{
public:
	virtual void f0();
	virtual void f1();
	virtual void close();
	virtual int read(void *buf, int size);
	virtual int write(const void *buf, int size);
	virtual int seek(int offset, int origin);
};

// The second parameter is the save game's Xfer, as in Zero Hour's and BFME 1's
// GameStateMap.cpp (static void embedPristineMap(AsciiString, Xfer *)); WB's
// twin asserts xfer.IsStoring(). Slots as the rowed BFME 2 Xfer views place
// them: beginBlock +0x14, endBlock +0x18, xferUser +0x24, xferUnsignedInt +0x78.
struct XferVersionInfo;
class GameInfo;
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
#include "../../Include/Common/BfmeXfer.h"

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int unk);
 bool doesFileExist(const char*)const;
};

extern FileSystem *TheFileSystem;
extern int g_guardTargetTypeThrowInfo;

struct BfmeFormattedText
{
	char *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *result, int tag, const char *format, ...);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

static void __cdecl embedPristineMap(AsciiString path, Xfer *xfer)
{
	char *t = *(char **)(void *)&path;
	const char *name = t ? t + 8 : "";
	File *file = TheFileSystem->openFile(name, 0x41, 0);
	if (!file)
	{
		BfmeFormattedText exceptionText;
		bfmeFormatText(&exceptionText, 5, (const char *)0);
		_CxxThrowException(&exceptionText, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	unsigned int size = file->seek(0, 2);
	file->seek(0, 0);
	char *buf = new char[size];
	if (!buf)
	{
		BfmeFormattedText exceptionText;
		bfmeFormatText(&exceptionText, 5, (const char *)0);
		_CxxThrowException(&exceptionText, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	int got = file->read(buf, size);
	if (got != size)
	{
		delete[] buf;
		BfmeFormattedText exceptionText;
		bfmeFormatText(&exceptionText, 5, (const char *)0);
		_CxxThrowException(&exceptionText, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	file->close();
	xfer->BeginBlock("PristineMap");
	*xfer == size;
	xfer->XferRawBytes(buf, size);
	xfer->EndBlock();
	delete[] buf;
}

// Native41AC98..41AD08 and WB132EDB0 replace a four-character map
// suffix with .wak, clearing the output if the remaining prefix is not positive.
// Retail DoXfer41AFDA passes its input reference in ECX and output on stack.
static void Rva0041AC98(const AsciiString &path,AsciiString &out) {
 int length=path.getLength()-4;
 if(length>0) { AsciiString prefix(path,0,length);prefix+=".wak";out=prefix; }
 else out="";
}

// ?Rva0041AD08Caller@@YAXVAsciiString@@PAVFile@@@Z present-unmatched (register key kept; the anchor takes the Xfer view)
void __cdecl Rva0041AD08Caller(AsciiString p, Xfer *xfer)
{
	// Existing source-only private-ABI driver; this is not a retail claim.
	AsciiString auxiliary;
	Rva0041AC98(p, auxiliary);
	embedPristineMap(p, xfer);
}

// ?embedInUseMap@@YAXVAsciiString@@PAVXfer@@@Z (WorldBuilder name), retail 0x0041AE00, 248 bytes:
// the same read for the "InUseMap" entry (callers 0x0041B3DA, 0x0041B435).
static void __cdecl embedInUseMap(AsciiString path, Xfer *xfer)
{
	char *t = *(char **)(void *)&path;
	const char *name = t ? t + 8 : "";
	File *file = TheFileSystem->openFile(name, 0x41, 0);
	if (!file)
	{
		BfmeFormattedText exceptionText;
		bfmeFormatText(&exceptionText, 5, (const char *)0);
		_CxxThrowException(&exceptionText, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	unsigned int size = file->seek(0, 2);
	file->seek(0, 0);
	char *buf = new char[size];
	if (!buf)
	{
		BfmeFormattedText exceptionText;
		bfmeFormatText(&exceptionText, 5, (const char *)0);
		_CxxThrowException(&exceptionText, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	int got = file->read(buf, size);
	if (got != size)
	{
		delete[] buf;
		BfmeFormattedText exceptionText;
		bfmeFormatText(&exceptionText, 5, (const char *)0);
		_CxxThrowException(&exceptionText, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	file->close();
	xfer->BeginBlock("InUseMap");
	*xfer == size;
	xfer->XferRawBytes(buf, size);
	xfer->EndBlock();
	delete[] buf;
}

// ?Rva0041AE00Caller@@YAXVAsciiString@@PAVFile@@@Z present-unmatched (register key kept; the anchor takes the Xfer view)
void __cdecl Rva0041AE00Caller(AsciiString p, Xfer *xfer)
{
	embedInUseMap(p, xfer);
}

// Native41AEF8..41AFDA / WB132E990 (GameStateMap.cpp:179..204)
// establish extractAndSaveMap. The BFME1 donor at874e38488 has the same
// transfer/write purpose; BFME2 uses FileSystem rather than CRT file IO.
// Xfer remains in ESI at its two calls from DoXfer; File::write is slot+10.
static void __cdecl extractAndSaveMap(AsciiString path, Xfer *xfer)
{
 char *t=*(char **)(void *)&path;
 const char *name=t?t+8:"";
 File *file=TheFileSystem->openFile(name,0x4a,0);
 if(!file){BfmeFormattedText exceptionText;bfmeFormatText(&exceptionText,5,(const char*)0);
 _CxxThrowException(&exceptionText,(const _s__ThrowInfo*)&g_guardTargetTypeThrowInfo);__assume(0);}
 xfer->BeginBlock("EmbeddedMap");
 unsigned int size;
 *xfer == size;
 char *buf=new char[size];
 if(!buf){BfmeFormattedText exceptionText;bfmeFormatText(&exceptionText,5,(const char*)0);
 _CxxThrowException(&exceptionText,(const _s__ThrowInfo*)&g_guardTargetTypeThrowInfo);__assume(0);}
 xfer->XferRawBytes(buf,size);
 int got=file->write(buf,size);
 if(got!=size){delete[]buf;BfmeFormattedText exceptionText;bfmeFormatText(&exceptionText,5,(const char*)0);
 _CxxThrowException(&exceptionText,(const _s__ThrowInfo*)&g_guardTargetTypeThrowInfo);__assume(0);}
 file->close();xfer->EndBlock();delete[]buf;
}
// ?Rva0041AEF8Caller@@YAXVAsciiString@@PAVXfer@@@Z present-unmatched
void Rva0041AEF8Caller(AsciiString path,Xfer*xfer){extractAndSaveMap(path,xfer);}
#include "unicode_string.h"
#include "GameLogicObjectLookupView.h"
struct XferVersionInfo {
 XferVersionInfo(unsigned char v,unsigned char c):version(v),currentVersion(c){}
 unsigned char version,currentVersion;
};
struct S6SaveMapRecord {
 void *vtable;
 AsciiString saveGameMapName,pristineMapName;
 char prefix0C[0x24-0x0C];
 int saveType;
};
class GameState {
public:
 AsciiString getMapLeafName(const AsciiString&)const;
 AsciiString realMapPathToPortableMapPath(const AsciiString&)const;
 AsciiString portableMapPathToRealMapPath(const AsciiString&)const;
 char prefix[0x24];S6SaveMapRecord saveGameInfo;
};
class Rva002DC74A {public:UnicodeString rva002DC74A(const UnicodeString&)const;};
class Rva002DC7C1 {public:bool rva002DC7C1(const UnicodeString&)const;};
class BfmeSelectionState {public:bool isSelectionLocked()const;};
class LivingWorldLogic;
class LinearCampaignManager;
class Rva001EB0B9 {public:unsigned char rva001EB0B9();};
extern LivingWorldLogic*TheLivingWorldLogic;
extern LinearCampaignManager*TheLinearCampaignManager;
extern GameState *TheGameState;
extern GameLogic *TheGameLogic;
class GlobalData {public:char prefix[0xC];AsciiString m_mapName;};
extern GlobalData*TheWritableGlobalData;
class GameClient {public:char prefix[0x2C];int drawableCounter;};
extern GameClient*TheGameClient;
class GameInfo {
public:
 GameInfo();virtual~GameInfo();
 virtual void slot04();virtual void slot08();virtual void slot0C();
 virtual void slot10();virtual void slot14();virtual void slot18();
 virtual void slot1C();virtual void slot20();virtual void slot24();
 virtual void reset();
 void init();void clearSlotList();
 char prefix[0xDC-4];
};
class SkirmishGameInfo:public GameInfo {
public:SkirmishGameInfo();virtual~SkirmishGameInfo();
 char rest[0xE3C-sizeof(GameInfo)];
};
class SkirmishGameInfo; extern SkirmishGameInfo *TheSkirmishGameInfo;
extern GameInfo*TheGameInfo;
void XferObjectID(Xfer*,ObjectID*);
void XferDrawableID(Xfer*,int*);
class GameStateMap {public:void DoXfer(Xfer*);void clearScratchPadMaps();};
// Target identity: WB132D380 GameStateMap.cpp357 and native41AFDA..41B603.
// BFME1 GameStateMap::xfer at874e38488 supplies save/load structure; target
// independently supplies the two mode words, both auxiliary .wak paths,
// selection/linear-campaign guards, and early object/drawable ID transfers.
void GameStateMap::DoXfer(Xfer*xfer) {
 if(xfer->IsLoading())*(bool*)((char*)TheGameLogic+0x6E)=true;
 XferVersionInfo version(1,2);
 *xfer == (Xfer::Version &)version;
 S6SaveMapRecord *saveGameInfo=&TheGameState->saveGameInfo;
 bool transferMap=true;
 bool firstSave=false;
 if(xfer->IsStoring()) {
  if((TheLivingWorldLogic && ((BfmeSelectionState*)TheLivingWorldLogic)->isSelectionLocked()) ||
     (TheLinearCampaignManager && ((Rva001EB0B9*)TheLinearCampaignManager)->rva001EB0B9())) {
   transferMap=false;AsciiString exceptionText;*xfer == exceptionText;
  } else {
   AsciiString mapLeafName=TheGameState->getMapLeafName(TheWritableGlobalData->m_mapName);
   saveGameInfo->saveGameMapName=AsciiString(((Rva002DC74A*)TheGameState)->rva002DC74A(UnicodeString(mapLeafName)));
   {AsciiString exceptionText=TheGameState->realMapPathToPortableMapPath(saveGameInfo->saveGameMapName);*xfer == exceptionText;}
   if(!((Rva002DC7C1*)TheGameState)->rva002DC7C1(UnicodeString(TheWritableGlobalData->m_mapName))) {
    saveGameInfo->pristineMapName=TheWritableGlobalData->m_mapName;firstSave=true;
   }
   {AsciiString exceptionText=TheGameState->realMapPathToPortableMapPath(saveGameInfo->pristineMapName);*xfer == exceptionText;}
  }
  int gameMode=TheGameLogic->m_110;*xfer == gameMode;
  int gameMode2=TheGameLogic->m_114;*xfer == gameMode2;
 } else {
  AsciiString exceptionText;*xfer == exceptionText;
  if(exceptionText.isEmpty()) {transferMap=false;TheWritableGlobalData->m_mapName="NOMAP";}
  else {
   saveGameInfo->saveGameMapName=TheGameState->portableMapPathToRealMapPath(exceptionText);
   if(!((Rva002DC7C1*)TheGameState)->rva002DC7C1(UnicodeString(saveGameInfo->saveGameMapName))) {
    BfmeFormattedText err;bfmeFormatText(&err,5,(const char*)0);
    _CxxThrowException(&err,(const _s__ThrowInfo*)&g_guardTargetTypeThrowInfo);__assume(0);
   }
   TheWritableGlobalData->m_mapName=saveGameInfo->saveGameMapName;
   *xfer == saveGameInfo->pristineMapName;
   saveGameInfo->pristineMapName=TheGameState->portableMapPathToRealMapPath(saveGameInfo->pristineMapName);
  }
  int gameMode;*xfer == gameMode;TheGameLogic->m_110=gameMode;
  int gameMode2;*xfer == gameMode2;TheGameLogic->m_114=gameMode2;
 }
 if(transferMap) {
  if(xfer->IsStoring()) {
   AsciiString auxiliary;
   if(firstSave==true) {
    embedPristineMap(saveGameInfo->pristineMapName,xfer);
    if(version.currentVersion>=2) {
     Rva0041AC98(saveGameInfo->pristineMapName,auxiliary);
     if(!auxiliary.isEmpty()) {
      bool exists=TheFileSystem->doesFileExist(auxiliary.str());*xfer == exists;
      if(exists)embedPristineMap(auxiliary,xfer);
     }
    }
   } else {
    embedInUseMap(saveGameInfo->saveGameMapName,xfer);
    if(version.currentVersion>=2) {
     Rva0041AC98(saveGameInfo->saveGameMapName,auxiliary);
     if(!auxiliary.isEmpty()) {
      bool exists=TheFileSystem->doesFileExist(auxiliary.str());*xfer == exists;
      if(exists)embedInUseMap(auxiliary,xfer);
     }
    }
   }
  } else {
   AsciiString auxiliary;Rva0041AC98(saveGameInfo->saveGameMapName,auxiliary);
   extractAndSaveMap(saveGameInfo->saveGameMapName,xfer);
   if(version.currentVersion>=2 && !auxiliary.isEmpty()) {
    bool exists=false;*xfer == exists;if(exists)extractAndSaveMap(auxiliary,xfer);
   }
  }
 }
 ObjectID highObjectID=*(ObjectID*)((char*)TheGameLogic+0x10C);
 XferObjectID(xfer,&highObjectID);*(ObjectID*)((char*)TheGameLogic+0x10C)=highObjectID;
 int highDrawableID=TheGameClient->drawableCounter;
 XferDrawableID(xfer,&highDrawableID);TheGameClient->drawableCounter=highDrawableID;
 if(TheGameLogic->m_110==2 || TheGameLogic->m_114==0) {
  if(!(*(GameInfo* *)&TheSkirmishGameInfo)) {
   (*(GameInfo* *)&TheSkirmishGameInfo)=new SkirmishGameInfo;
   TheGameInfo=(*(GameInfo* *)&TheSkirmishGameInfo);
   (*(GameInfo* *)&TheSkirmishGameInfo)->init();(*(GameInfo* *)&TheSkirmishGameInfo)->clearSlotList();(*(GameInfo* *)&TheSkirmishGameInfo)->reset();
  }
  *xfer == *(Snapshot *)((*(GameInfo* *)&TheSkirmishGameInfo));
 } else if((*(GameInfo* *)&TheSkirmishGameInfo)) {
  if(TheGameInfo==(*(GameInfo* *)&TheSkirmishGameInfo))TheGameInfo=0;
  ::delete (*(GameInfo* *)&TheSkirmishGameInfo);(*(GameInfo* *)&TheSkirmishGameInfo)=0;
 }
 if(xfer->IsLoading()) {
  if(TheGameLogic->m_110!=9 && saveGameInfo->saveType!=6 && saveGameInfo->saveType!=4)TheGameLogic->startNewGame(true);
  *(bool*)((char*)TheGameLogic+0x6E)=false;
 }
}
namespace _STL {
 template<class T>struct less{};template<class T>class allocator{};
 template<class K,class C,class A>class set {
 public:set();private:void*header;int count;int compare;
 };
 struct _Rb_tree_node_base {
 int color;_Rb_tree_node_base*parent,*left,*right;
 };
 template<class Dummy>struct _Rb_global {
 static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base*);
 };
}
struct S6SaveFileNode:public _STL::_Rb_tree_node_base {UnicodeString name;};
// Keep the established typed-fold construction and out-of-line cleanup
// used by GameStateIterateSaveFiles.cpp; no new constructor alias/pin.
class Rva0021C459:public _STL::set<AsciiString,_STL::less<AsciiString>,_STL::allocator<AsciiString> > {
public:~Rva0021C459();
 _STL::_Rb_tree_node_base *header()const{return *reinterpret_cast<_STL::_Rb_tree_node_base *const*>(this);}
};

// The file-list object is Rva0021DA13 (as AptSaveLoadRva0043684C.cpp spells
// it): its destructor is the 5-byte thunk 0x0021DA13 the unwind funclet
// jumps to; the normal path expands it into ~Rva0021C459 (0x0021D5D5).
class Rva0021DA13 : public Rva0021C459
{
};
class Rva006007DAFileSystem {};
void __stdcall Rva006007DAOpen(void *,void *,void *,void *);
// The whole 81B provider ignores incoming ECX and consumes four stack words.
// Keep the native caller's unused receiver and name the existing owner.
union NativeSaveEnumerationCall {
 void (__stdcall *target)(void *,void *,void *,void *);
 void (Rva006007DAFileSystem::*member)(const UnicodeString *,const UnicodeString *,Rva0021C459 *,bool);
};
typedef char SaveEnumerationPointerWidth[sizeof(NativeSaveEnumerationCall)==4 ? 1 : -1];
class Rva002DC267 {public:UnicodeString rva002DC267()const;};
AsciiString *Rva00300678Get();
class BFME2WideConcatPair {
public:
 struct ReferencePairTag {};
 __forceinline BFME2WideConcatPair(ReferencePairTag,const UnicodeString&unicodeString,const UnicodeString&b):left(&unicodeString),right(&b){}
 operator UnicodeString();
 const UnicodeString *left,*right;
};
// Native397B boundary41B603..41B790. Constructor41AC6A and destructor41B790
// share primary vtableC3ADD8 and Snapshot vtableC3ADC8: the latter carries
// the GameStateMap name getter41AC8A and DoXfer41AFDA. This independently
// establishes the owner. BFME1 clearScratchPadMaps supplies
// .map/.wak cleanup purpose; target uses wide FileSystem enumeration and
// also removes .lws. Existing wide-pair pin's UnicodeString ABI view keeps
// the canonical one-pointer return ownership rather than copying StringBase.
void GameStateMap::clearScratchPadMaps() {
 Rva0021DA13 files;
 {UnicodeString pattern(L"*");
 NativeSaveEnumerationCall enumeration={&Rva006007DAOpen};
 (reinterpret_cast<Rva006007DAFileSystem *>(TheFileSystem)->*enumeration.member)(
 &reinterpret_cast<const Rva002DC267*>(TheGameState)->rva002DC267(),&pattern,&files,false);}
 for(_STL::_Rb_tree_node_base *node=files.header()->left;node!=files.header();
 node=_STL::_Rb_global<bool>::_M_increment(node)) {
  static UnicodeString suffix((const UnicodeString&)BFME2WideConcatPair(BFME2WideConcatPair::ReferencePairTag(),UnicodeString(L"."),UnicodeString(*Rva00300678Get())));
  // Witness the iterator cell after static initialization: the native loop
  // reloads its node from the frame, rather than retaining it in EBX.
  UnicodeString &name=static_cast<S6SaveFileNode*>(reinterpret_cast<_STL::_Rb_tree_node_base *const volatile &>(node))->name;
  if(name.endsWithNoCase(L".map")||name.endsWithNoCase(L".wak")||name.endsWithNoCase(suffix))DeleteFileW(name.str());
 }
}
