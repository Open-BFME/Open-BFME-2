// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common
// platformsdk
// stlport
// BFME1 34f59164 MainMenuUtils.cpp is the primary reference.
// WB158CC80 names startOnline and MainMenuUtils.cpp; native5BC887..5BCA60
// proves the target-specific enable calls and removal of the legacy login UI.
// The accept callback is BFME2 shutdown behavior, not the donor downloader.
// Shared AsciiString/UnicodeString and the existing MessageBox providers.

// Retail string storage is released by the game allocator, not CRT free.
// Its C++ throwing contract also preserves the native cleanup states.
#include <stdlib.h>
void __cdecl Rva00030830GameFree(void *);
#define free Rva00030830GameFree
#include "ascii_string.h"
#include "unicode_string.h"
#include <list>
#include <string.h>
#include <new>
#include <windows.h>
#include <WinInet.h>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
class QueuedDownload { public: AsciiString server,userName,password,file,localFile,regKey;bool tryResume;
 // ?QueuedDownload::QueuedDownload present-unmatched
 QueuedDownload() {} QueuedDownload(const QueuedDownload &); ~QueuedDownload(); };
extern unsigned int g_Va00E0657C;
// Native MainMenuUtils state consists of independent file-local variables.
// Their addresses and widths are proven by the callbacks and DNS entry.
// Keeping the consumers here lets cl distinguish them from a fetched vptr;
// an external aggregate prevented StartPatchCheck from matching its stores.
// VA E0655C: checking; E06560/E06564: checks/run; E06568/E06569: must/cant;
// E0656C/E06570: owned buffers; E06574: cancellation flag.
static bool checkingForPatchBeforeGameSpy;
static int checksLeftBeforeOnline,timeThroughOnline;
static bool mustDownloadPatch,cantConnectBeforeOnline;
static char *motdBeforeOnline,*configBeforeOnline;
static bool cancelBeforeOnline;

#define downloads (*(_STL::list<QueuedDownload> *)&g_Va00E0657C)
class GameTextInterface {public:
virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void v14();virtual UnicodeString fetch(const char *,bool *exists=0);};
extern GameTextInterface *TheGameText;
class GameWindow;
void MessageBoxOk(UnicodeString,UnicodeString,void (*)());
void MessageBoxOkCancel(UnicodeString,UnicodeString,void (*)(),void (*)());
void MessageBoxYesNo(UnicodeString,UnicodeString,void (*)(),void (*)());
void b_00042a50();void Rva00516E92Enable();bool hasWriteAccess();
void patchBeforeOnlineCallback();void noPatchBeforeOnlineCallback();
#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;
extern char *TheShellHookNames[];
void SetUpGameSpy(const char *,const char *);
// ?startOnline@@YAXXZ @0x005BC887 473B
void startOnline()
{
 checkingForPatchBeforeGameSpy=false;
 if(cancelBeforeOnline){b_00042a50();cancelBeforeOnline=false;}
 if(cantConnectBeforeOnline){
  MessageBoxOk(TheGameText->fetch("GUI:CannotConnectToServservTitle"),TheGameText->fetch("GUI:CannotConnectToServserv"),noPatchBeforeOnlineCallback);
  Rva00516E92Enable();return;
 }
 if(downloads.size()){
  if(!hasWriteAccess()) MessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:MustHaveAdminRights"),noPatchBeforeOnlineCallback);
  else if(mustDownloadPatch) MessageBoxOkCancel(TheGameText->fetch("GUI:PatchAvailable"),TheGameText->fetch("GUI:MustPatchForOnline"),patchBeforeOnlineCallback,noPatchBeforeOnlineCallback);
  else MessageBoxYesNo(TheGameText->fetch("GUI:PatchAvailable"),TheGameText->fetch("GUI:CanPatchForOnline"),patchBeforeOnlineCallback,noPatchBeforeOnlineCallback);
  Rva00516E92Enable();return;
 }
 TheScriptEngine->rva00357DD2(TheShellHookNames[9]);
 SetUpGameSpy(motdBeforeOnline,configBeforeOnline);
 if(motdBeforeOnline){delete[] motdBeforeOnline;motdBeforeOnline=0;}
 if(configBeforeOnline){delete[] configBeforeOnline;configBeforeOnline=0;}
}

extern template void _STL::_List_base<QueuedDownload,_STL::allocator<QueuedDownload> >::clear();
void noPatchBeforeOnlineCallback() {
 downloads.clear();
 if(mustDownloadPatch || cantConnectBeforeOnline) Rva00516E92Enable();
 else startOnline();
}

// WB158D390 is the callback passed by native startOnline.
// Native5BC495..5BC4AE quits through GameEngine slot50 then exits with
// launcher code123456789; its noreturn terminator is the final INT3.
class GameEngine { public:
#define SLOT(N) virtual void slot##N();
 SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
 SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18)
#undef SLOT
 virtual int getFramesPerSecondLimit();virtual void setQuitting(bool);
};
extern GameEngine *TheGameEngine;
namespace MainMenuCRT {
extern "C" __declspec(dllimport) __declspec(noreturn) void __cdecl exit(int);
}
void patchBeforeOnlineCallback()
{
 TheGameEngine->setQuitting(true);
 MainMenuCRT::exit(123456789);
}

// BFME1 34f59164 MOTD behavior; WB158DAF0 supplies the proper callback
// identity and signed64 byte-count ABI. Native5BCA60..5BCAF1 proves the
// whole145-byte body. The shared-state C++ decrement emits native DEC.
void b_00042a50();void startOnline();
enum GHTTPBool {GHTTPFalse,GHTTPTrue};
enum GHTTPResult {GHTTPSuccess};
GHTTPBool motdCallback(int request,GHTTPResult result,char *buffer,__int64 bufferLen,void *param)
{
 if((int)param!=timeThroughOnline)return GHTTPTrue;
 if(motdBeforeOnline){delete[] motdBeforeOnline;motdBeforeOnline=0;}
 if(buffer && bufferLen>0){
  motdBeforeOnline=new char[(unsigned)bufferLen];
  memcpy(motdBeforeOnline,buffer,(unsigned)bufferLen);
  motdBeforeOnline[bufferLen-1]=0;
 }
 --checksLeftBeforeOnline;
 if(cancelBeforeOnline && checksLeftBeforeOnline==0){b_00042a50();cancelBeforeOnline=false;}
 if(checksLeftBeforeOnline==0)startOnline();
 return GHTTPTrue;
}

// BFME1 34f59164 configCallback; native 5BCAF1..5BCC77 (390B) keeps the
// donor flow with BFME2's signed64 byte count, the MOTD callback's cancel
// handling, and the file written through TheFileSystem into the user-data
// "Online Files" directory rather than through fopen.
class File { public:
 virtual ~File();virtual bool open(const char *,int);virtual void close();
 virtual int read(void *,int);virtual int write(const void *,int);
 virtual void seek();virtual void nextLine();virtual void scanInt();virtual void scanReal();
 virtual void scanString();virtual void print();virtual int size();
};
class FileSystem { public: File *openFile(const char *filename,int access,int bufferSize); };
extern FileSystem *TheFileSystem;
class GlobalData { public: AsciiString rva002360DE(void) const; };
extern GlobalData *TheWritableGlobalData;
GHTTPBool configCallback(int request,GHTTPResult result,char *buffer,__int64 bufferLen,void *param)
{
 if((int)param!=timeThroughOnline)return GHTTPTrue;
 if(configBeforeOnline){delete[] configBeforeOnline;configBeforeOnline=0;}
 if(result!=GHTTPSuccess || bufferLen<100){
  if(!checkingForPatchBeforeGameSpy)return GHTTPTrue;
  --checksLeftBeforeOnline;
  if(cancelBeforeOnline && checksLeftBeforeOnline==0){b_00042a50();cancelBeforeOnline=false;}
  cantConnectBeforeOnline=true;
  if(checksLeftBeforeOnline==0)startOnline();
  return GHTTPTrue;
 }
 configBeforeOnline=new char[(unsigned)bufferLen];
 memcpy(configBeforeOnline,buffer,(unsigned)bufferLen);
 configBeforeOnline[bufferLen-1]=0;
 AsciiString fname;
 fname.format("%s%s\\Config.txt",TheWritableGlobalData->rva002360DE().str(),"Online Files");
 File *fp=TheFileSystem->openFile(fname.str(),0x4A,0);
 if(fp){fp->write(configBeforeOnline,(int)bufferLen);fp->close();}
 --checksLeftBeforeOnline;
 if(cancelBeforeOnline && checksLeftBeforeOnline==0){b_00042a50();cancelBeforeOnline=false;}
 if(checksLeftBeforeOnline==0)startOnline();
 return GHTTPTrue;
}

// BFME1 34f59164 CancelPatchCheckCallback; native 5BCFFB..5BD060 (101B).
// BFME2 has no cancel window: it re-enables the menu, clears the checking
// state and closes the pending dialog through the cancel flag.
extern unsigned char g_00E06576;
void CancelPatchCheckCallback()
{
 g_00E06576=0;
 Rva00516E92Enable();
 checkingForPatchBeforeGameSpy=false;
 checksLeftBeforeOnline=0;
 if(cancelBeforeOnline){b_00042a50();cancelBeforeOnline=false;}
 downloads.clear();
 if(motdBeforeOnline){delete[] motdBeforeOnline;motdBeforeOnline=0;}
 if(configBeforeOnline){delete[] configBeforeOnline;configBeforeOnline=0;}
}

// BFME1 34f59164 CancelPatchCheckCallbackAndReopenDropdown; native
// 5BD5D2..5BD5DC (10B), the dialog callback StartPatchCheck passes.
void CancelPatchCheckCallbackAndReopenDropdown()
{
 Rva00516E92Enable();
 CancelPatchCheckCallback();
}

// Complete named list providers5BC6D3/5BC6FE share the MainMenu O1/G7 settings.
// The former byte-footprint views are removed from the generic list units.


namespace _STL {template <> void _Construct<QueuedDownload>(QueuedDownload *,const QueuedDownload &);}
template <> _STL::_List_node<QueuedDownload> *_STL::list<QueuedDownload>::_M_create_node(const QueuedDownload &x){
 _STL::_List_node<QueuedDownload> *p=(_STL::_List_node<QueuedDownload> *)_STL::allocator<char>::allocate(sizeof(_STL::_List_node<QueuedDownload>),0);
 _STL::_Construct(&p->_M_data,x);return p;
}
template _STL::list<QueuedDownload>::iterator _STL::list<QueuedDownload>::insert(_STL::list<QueuedDownload>::iterator,const QueuedDownload &);

// BFME1 MainMenu downloader donor and WB158C240 source identity.
// Native5BD0A7..5BD1F1 is the complete330-byte body. Named copy131 and
// owned download/list providers preserve the native queue draining order.
extern template void _STL::list<QueuedDownload>::pop_front();
class DownloadManager {public:
 void queueFileForDownload(AsciiString,AsciiString,AsciiString,AsciiString,AsciiString,AsciiString,bool);
 long downloadNextQueuedFile();
};
extern DownloadManager *TheDownloadManager;
class WindowLayout {public:
 virtual void runInit(void *);
 virtual void slot04();virtual void slot08();virtual void slot0C();
 virtual void hide(bool);virtual void bringForward();
};
class GameWindowManager {public:
#define SLOT(N) virtual void slot##N();
 SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
 SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
 SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
#undef SLOT
 virtual WindowLayout *winCreateLayout(AsciiString);
};
extern GameWindowManager *TheWindowManager;
void Rva00516E92Enable();
void StartDownloadingPatches()
{
 if(downloads.empty()){Rva00516E92Enable();return;}
 WindowLayout *layout=TheWindowManager->winCreateLayout("Menus/DownloadMenu.wnd");
 layout->runInit(0);layout->hide(false);layout->bringForward();
 Rva00516E92Enable();
 if(!TheDownloadManager)return;
 _STL::list<QueuedDownload>::iterator it=downloads.begin();
 while(it!=downloads.end()){
  QueuedDownload q=*it;
  TheDownloadManager->queueFileForDownload(q.server,q.userName,q.password,q.file,q.localFile,q.regKey,q.tryResume);
  downloads.pop_front();it=downloads.begin();
 }
 TheDownloadManager->downloadNextQueuedFile();
}


// BFME1 queuePatch is the primary parser guide. Retail5BD1F1..5BD425
// confirms the native FTP fallback strings and duplicate local-file check.
// The local unused mandatory parameter is optimized out with its caller.
namespace MainMenuCRT {extern "C" __declspec(dllimport) int __cdecl atoi(const char *);}

static void queuePatch(bool mandatory,AsciiString downloadURL){
 QueuedDownload q;bool success=true;
 AsciiString connectionType;success &= downloadURL.nextToken(&connectionType,":");
 AsciiString server;success &= downloadURL.nextToken(&server,":/");
 AsciiString user;success &= downloadURL.nextToken(&user,":@");
 AsciiString pass;success &= downloadURL.nextToken(&pass,"@/");
 AsciiString filePath;success &= downloadURL.nextToken(&filePath,"");
 if(!success && !user.isEmpty()){filePath=user;user="anonymous";pass="ccgenerals";success=true;}
 AsciiString fileStr=filePath;const char *slash=((const StringBase<char> &)(filePath)).reverseFind('/');if(slash)fileStr=slash+1;
 AsciiString fileName="patches\\";fileName.concat(fileStr);
 if(!success)return;
 q.file=filePath;q.localFile=fileName;q.password=pass;q.regKey="";q.server=server;q.tryResume=true;q.userName=user;
 _STL::list<QueuedDownload>::iterator it=downloads.begin();
 while(it!=downloads.end()){if(it->localFile==q.localFile)return;++it;}
 downloads.push_back(q);
}

GHTTPBool gamePatchCheckCallback(int request,GHTTPResult result,char *buffer,__int64 bufferLen,void *param){
 if((int)param!=timeThroughOnline)return GHTTPTrue;
 --checksLeftBeforeOnline;
 if(result!=GHTTPSuccess){
  if(!checkingForPatchBeforeGameSpy)return GHTTPTrue;
  cantConnectBeforeOnline=true;
  if(!checksLeftBeforeOnline)startOnline();
  return GHTTPTrue;
 }
 AsciiString message=buffer,line;
 while(message.nextToken(&line,"\r\n")){
  AsciiString type,req,url;bool ok=true;
  ok &= line.nextToken(&type," ");
  ok &= line.nextToken(&req," ");
  ok &= line.nextToken(&url," ");
  if(ok && type.compare("patch")==0){
   queuePatch(MainMenuCRT::atoi(req.str()),url);
   if(MainMenuCRT::atoi(req.str()))mustDownloadPatch=true;
  }else if(ok && type.compare("server")==0){}
 }
 if(!checksLeftBeforeOnline)startOnline();
 return GHTTPTrue;
}





// BFME1 34f59164 StartPatchCheck; native 5BD82E..5BD910 (226B). BFME2 shows
// the checking dialog as an untitled MessageBoxOk, takes the host to look up
// from the registry's online server URL (InternetCrackUrlA) and runs the
// async lookup through Rva005BC4CEStart.
const char *GetRegistryOnlineServer();
int Rva005BC4CEStart(int hostName);
void rva005BD6A7();
void StartPatchCheck()
{
 // Native writes this flag before loading GameText's vtable. Order this
 // write as native does.
 *(volatile bool *)&cancelBeforeOnline=true;
 checkingForPatchBeforeGameSpy=true;
 cantConnectBeforeOnline=false;
 checksLeftBeforeOnline=0;
 timeThroughOnline++;
 MessageBoxOk(UnicodeString(L""),TheGameText->fetch("GUI:CheckingForPatches"),CancelPatchCheckCallbackAndReopenDropdown);
 g_00E06576=1;
 URL_COMPONENTSA components;
 char hostName[512];
 memset(&components,0,sizeof(components));
 components.dwStructSize=sizeof(components);
 components.lpszHostName=hostName;
 components.dwHostNameLength=sizeof(hostName);
 if(InternetCrackUrlA(GetRegistryOnlineServer(),0,0,&components)){
  switch(Rva005BC4CEStart((int)hostName)){
  case 1: break;
  case 2: rva005BD6A7(); return;
  default: return;
  }
 }
 cantConnectBeforeOnline=true;
 startOnline();
}

// The native three-pointer STL string view already verified in the request
// helper also serves configHeadCallback. Constructors bind to the existing
// string providers; native cleanup uses the game free wrapper.
// This keeps the original class identity and 12-byte layout without emitting
// unrelated STL helper copies at this unit's compiler settings.
namespace _STL {
template<class C> class char_traits;
template<class C,class T,class A> class basic_string {
 C *start,*finish,*storageEnd;
public:
 basic_string(); basic_string(const basic_string &); basic_string(const C *,const A &);
 ~basic_string(){if(start)Rva00030830GameFree(start);}
 const C *c_str()const{return start;}
 bool empty()const{return start==finish;}
};
}

typedef _STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > PatchString;
typedef GHTTPBool (*PatchHttpComplete)(int,GHTTPResult,char*,__int64,void*);
extern "C" int ghttpGetA(const char*,GHTTPBool,PatchHttpComplete,void*);
extern "C" int ghttpHeadA(const char*,GHTTPBool,PatchHttpComplete,void*);
extern "C" int ghttpSetProxy(const char*);
void FormatURLFromRegistry(PatchString&,PatchString&,PatchString&,PatchString&);
bool GetStringFromRegistry(PatchString,PatchString,PatchString&);
GHTTPBool configHeadCallback(int,GHTTPResult,char*,__int64,void*);
void rva005BD64D();void Rva005BD5F3Add();
extern "C" const char *__cdecl ghttpGetHeaders(int request);
// BFME1 reallyStartPatchCheck supplies the HTTP categories and proxy flow.
// Native5BD6A7..5BD82E proves the blocking calls and run/check ownership.
// Rehomed with its original file-local state; the native STL string layout
// and game allocator preserve the separately verified 391-byte body.
void rva005BD6A7(){
 checksLeftBeforeOnline=4;
 unsigned char allocatorStorage[sizeof(_STL::allocator<char>)];
 const _STL::allocator<char>&allocator=*new(allocatorStorage)_STL::allocator<char>();
 PatchString gameURL,mapURL,configURL,motdURL;
 FormatURLFromRegistry(gameURL,mapURL,configURL,motdURL);
 PatchString proxy;
 if(GetStringFromRegistry(PatchString("",allocator),PatchString("Proxy",allocator),proxy)&&!proxy.empty())ghttpSetProxy(proxy.c_str());
 ghttpGetA(gameURL.c_str(),GHTTPTrue,gamePatchCheckCallback,(void*)timeThroughOnline);
 ghttpGetA(mapURL.c_str(),GHTTPTrue,gamePatchCheckCallback,(void*)timeThroughOnline);
 ghttpHeadA(configURL.c_str(),GHTTPTrue,configHeadCallback,(void*)timeThroughOnline);
 ghttpGetA(motdURL.c_str(),GHTTPTrue,motdCallback,(void*)timeThroughOnline);
 rva005BD64D();Rva005BD5F3Add();
}

// BFME1 configHeadCallback, native5BCC77..5BCFFB (900B). The second open
// uses the first filename, as native does. Game-free calls retain the EH
// states formerly obtained in a separate /EHs companion.
GHTTPBool configHeadCallback(int request,GHTTPResult result,char *buffer,__int64 bufferLen,void *param)
{
 if((int)param!=timeThroughOnline)return GHTTPTrue;
 if(result==GHTTPSuccess){
  AsciiString headers(ghttpGetHeaders(request));
  AsciiString line;
  while(headers.nextToken(&line,"\n\r")){
   AsciiString key,val;
   line.nextToken(&key,": ");
   line.nextToken(&val,": \r\n");
   if(key.compare("Content-Length")==0 && !val.isEmpty()){
    int serverLen=MainMenuCRT::atoi(val.str());
    int fileLen=0;
    AsciiString fname;
    fname.format("%s%s\\Config.txt",TheWritableGlobalData->rva002360DE().str(),"Online Files");
    File *fp=TheFileSystem->openFile(fname.str(),0x41,0);
    if(fp){fileLen=fp->size();fp->close();}
    if(serverLen==fileLen){
     --checksLeftBeforeOnline;
     if(cancelBeforeOnline && checksLeftBeforeOnline==0){b_00042a50();cancelBeforeOnline=false;}
     if(configBeforeOnline){delete[] configBeforeOnline;configBeforeOnline=0;}
     AsciiString fname2;
     fname2.format("%s%s\\Config.txt",TheWritableGlobalData->rva002360DE().str(),"Online Files");
     fp=TheFileSystem->openFile(fname.str(),0x41,0);
     if(fp){
      fp->read(configBeforeOnline=new char[fileLen],fileLen);
      configBeforeOnline[fileLen-1]=0;
      fp->close();
      if(checksLeftBeforeOnline==0)startOnline();
      return GHTTPTrue;
     }
    }
   }
  }
 }
 PatchString gameURL,mapURL;
 PatchString configURL,motdURL;
 FormatURLFromRegistry(gameURL,mapURL,configURL,motdURL);
 ghttpGetA(configURL.c_str(),GHTTPTrue,configCallback,param);
 return GHTTPTrue;
}

