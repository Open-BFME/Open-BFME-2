// ?StartPatchCheck@@YAXXZ
// partial score=0.97 date=2026-10-08
// cl: /O1 /Oa /G7 /arch:SSE /MD /EHs /DNDEBUG /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common
// stlport
// BFME1 34f59164 MainMenuUtils.cpp is the primary reference.
// WB158CC80 names startOnline and MainMenuUtils.cpp; native5BC887..5BCA60
// proves the target-specific enable calls and removal of the legacy login UI.
// The accept callback is BFME2 shutdown behavior, not the donor downloader.
// Shared AsciiString/UnicodeString and the existing MessageBox providers.

#include "ascii_string.h"
#include "unicode_string.h"
#include <list>
#include <string>
class QueuedDownload { public: AsciiString server,userName,password,file,localFile,regKey;bool tryResume; };
extern unsigned int g_Va00E0657C;
#include "MainMenuOnlineState.h"
#define online g_mainMenuOnlineState
#define downloads (*(_STL::list<QueuedDownload> *)&g_Va00E0657C)
class GameTextInterface {public:
virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();virtual void v13();virtual void v14();virtual UnicodeString fetch(const char *,bool *exists=0);};
extern GameTextInterface *TheGameText;
class GameWindow;
GameWindow *MessageBoxOk(UnicodeString,UnicodeString,void (*)());
void MessageBoxOkCancel(UnicodeString,UnicodeString,void (*)(),void (*)());
void MessageBoxYesNo(UnicodeString,UnicodeString,void (*)(),void (*)());
void b_00042a50();void Rva00516E92Enable();bool hasWriteAccess();
void patchBeforeOnlineCallback();void noPatchBeforeOnlineCallback();
class ScriptEngine {public:void rva00357DD2(const AsciiString &);};
extern ScriptEngine *TheScriptEngine;
extern char *TheShellHookNames[];
void SetUpGameSpy(const char *,const char *);
// ?startOnline@@YAXXZ @0x005BC887 473B
void startOnline()
{
 online.checking=false;
 if(online.cancel){b_00042a50();online.cancel=false;}
 if(online.cantConnect){
  MessageBoxOk(TheGameText->fetch("GUI:CannotConnectToServservTitle"),TheGameText->fetch("GUI:CannotConnectToServserv"),noPatchBeforeOnlineCallback);
  Rva00516E92Enable();return;
 }
 if(downloads.size()){
  if(!hasWriteAccess()) MessageBoxOk(TheGameText->fetch("GUI:Error"),TheGameText->fetch("GUI:MustHaveAdminRights"),noPatchBeforeOnlineCallback);
  else if(online.mustDownload) MessageBoxOkCancel(TheGameText->fetch("GUI:PatchAvailable"),TheGameText->fetch("GUI:MustPatchForOnline"),patchBeforeOnlineCallback,noPatchBeforeOnlineCallback);
  else MessageBoxYesNo(TheGameText->fetch("GUI:PatchAvailable"),TheGameText->fetch("GUI:CanPatchForOnline"),patchBeforeOnlineCallback,noPatchBeforeOnlineCallback);
  Rva00516E92Enable();return;
 }
 TheScriptEngine->rva00357DD2(TheShellHookNames[9]);
 SetUpGameSpy(online.motd,online.config);
 if(online.motd){delete[] online.motd;online.motd=0;}
 if(online.config){delete[] online.config;online.config=0;}
}

extern template void _STL::_List_base<QueuedDownload,_STL::allocator<QueuedDownload> >::clear();
void noPatchBeforeOnlineCallback() {
 downloads.clear();
 if(online.mustDownload || online.cantConnect) Rva00516E92Enable();
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
extern "C" void *__cdecl memcpy(void *,const void *,unsigned);
void *__cdecl operator new[](unsigned);
void __cdecl operator delete[](void *);
void b_00042a50();void startOnline();
enum GHTTPBool {GHTTPFalse,GHTTPTrue};
enum GHTTPResult {GHTTPSuccess};
GHTTPBool motdCallback(int request,GHTTPResult result,char *buffer,__int64 bufferLen,void *param)
{
 if((int)param!=online.run)return GHTTPTrue;
 if(online.motd){delete[] online.motd;online.motd=0;}
 if(buffer && bufferLen>0){
  online.motd=new char[(unsigned)bufferLen];
  memcpy(online.motd,buffer,(unsigned)bufferLen);
  online.motd[bufferLen-1]=0;
 }
 --online.checks;
 if(online.cancel && online.checks==0){b_00042a50();online.cancel=false;}
 if(online.checks==0)startOnline();
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
 if((int)param!=online.run)return GHTTPTrue;
 if(online.config){delete[] online.config;online.config=0;}
 if(result!=GHTTPSuccess || bufferLen<100){
  if(!online.checking)return GHTTPTrue;
  --online.checks;
  if(online.cancel && online.checks==0){b_00042a50();online.cancel=false;}
  online.cantConnect=true;
  if(online.checks==0)startOnline();
  return GHTTPTrue;
 }
 online.config=new char[(unsigned)bufferLen];
 memcpy(online.config,buffer,(unsigned)bufferLen);
 online.config[bufferLen-1]=0;
 AsciiString fname;
 fname.format("%s%s\\Config.txt",TheWritableGlobalData->rva002360DE().str(),"Online Files");
 File *fp=TheFileSystem->openFile(fname.str(),0x4A,0);
 if(fp){fp->write(online.config,(int)bufferLen);fp->close();}
 --online.checks;
 if(online.cancel && online.checks==0){b_00042a50();online.cancel=false;}
 if(online.checks==0)startOnline();
 return GHTTPTrue;
}

// BFME1 34f59164 configHeadCallback; native 5BCC77..5BCFFB (900B). A
// cached Config.txt of the advertised Content-Length is reloaded through
// TheFileSystem (its size from File::size) instead of fopen; otherwise the
// config is fetched blocking, as BFME2 passes GHTTPTrue to ghttpGet. The
// second open reuses the first fname (native 5BCE39 reads it, not the new
// one). /EHs: retail keeps EH states around the url strings' C free calls
// (5BCF20..5BCF62). /Oa: the donor's state is file-static, so retail loads
// File's vftable before storing the config pointer (5BCF83..5BCF8A).
extern "C" const char *__cdecl ghttpGetHeaders(int request);
typedef GHTTPBool (*ghttpCompletedCallback)(int,GHTTPResult,char *,__int64,void *);
extern "C" int __cdecl ghttpGetA(const char *URL,GHTTPBool blocking,ghttpCompletedCallback completedCallback,void *param);
namespace MainMenuCRT { extern "C" __declspec(dllimport) int __cdecl atoi(const char *); }
void FormatURLFromRegistry(_STL::string &gameURL,_STL::string &mapURL,_STL::string &configURL,_STL::string &motdURL);
GHTTPBool configHeadCallback(int request,GHTTPResult result,char *buffer,__int64 bufferLen,void *param)
{
 if((int)param!=online.run)return GHTTPTrue;
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
     --online.checks;
     if(online.cancel && online.checks==0){b_00042a50();online.cancel=false;}
     if(online.config){delete[] online.config;online.config=0;}
     AsciiString fname2;
     fname2.format("%s%s\\Config.txt",TheWritableGlobalData->rva002360DE().str(),"Online Files");
     fp=TheFileSystem->openFile(fname.str(),0x41,0);
     if(fp){
      fp->read(online.config=new char[fileLen],fileLen);
      online.config[fileLen-1]=0;
      fp->close();
      if(online.checks==0)startOnline();
      return GHTTPTrue;
     }
    }
   }
  }
 }
 _STL::string gameURL,mapURL;
 _STL::string configURL,motdURL;
 FormatURLFromRegistry(gameURL,mapURL,configURL,motdURL);
 ghttpGetA(configURL.c_str(),GHTTPTrue,configCallback,param);
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
 online.checking=false;
 online.checks=0;
 if(online.cancel){b_00042a50();online.cancel=false;}
 downloads.clear();
 if(online.motd){delete[] online.motd;online.motd=0;}
 if(online.config){delete[] online.config;online.config=0;}
}

// BFME1 34f59164 CancelPatchCheckCallbackAndReopenDropdown; native
// 5BD5D2..5BD5DC (10B), the dialog callback StartPatchCheck passes.
void CancelPatchCheckCallbackAndReopenDropdown()
{
 Rva00516E92Enable();
 CancelPatchCheckCallback();
}

// BFME1 34f59164 StartPatchCheck; native 5BD82E..5BD910 (226B). BFME2 shows
// the checking dialog as an untitled MessageBoxOk, takes the host to look up
// from the registry's online server URL (InternetCrackUrlA) and runs the
// async lookup through Rva005BC4CEStart.
struct MainMenuUrlComponents {
 unsigned long dwStructSize; char *lpszScheme; unsigned long dwSchemeLength; int nScheme;
 char *lpszHostName; unsigned long dwHostNameLength; unsigned short nPort;
 char *lpszUserName; unsigned long dwUserNameLength; char *lpszPassword; unsigned long dwPasswordLength;
 char *lpszUrlPath; unsigned long dwUrlPathLength; char *lpszExtraInfo; unsigned long dwExtraInfoLength;
};
extern "C" __declspec(dllimport) int __stdcall InternetCrackUrlA(const char *url,unsigned long length,unsigned long flags,MainMenuUrlComponents *components);
extern "C" void *__cdecl memset(void *,int,unsigned);
const char *GetRegistryOnlineServer();
int Rva005BC4CEStart(int hostName);
void reallyStartPatchCheck();
void StartPatchCheck()
{
 online.run++;
 online.cancel=true;
 online.checking=true;
 online.cantConnect=false;
 online.checks=0;
 MessageBoxOk(UnicodeString(L""),TheGameText->fetch("GUI:CheckingForPatches"),CancelPatchCheckCallbackAndReopenDropdown);
 g_00E06576=1;
 MainMenuUrlComponents components;
 char hostName[512];
 memset(&components,0,sizeof(components));
 components.dwStructSize=sizeof(components);
 components.lpszHostName=hostName;
 components.dwHostNameLength=sizeof(hostName);
 if(InternetCrackUrlA(GetRegistryOnlineServer(),0,0,&components)){
  switch(Rva005BC4CEStart((int)hostName)){
  case 1: break;
  case 2: reallyStartPatchCheck(); return;
  default: return;
  }
 }
 online.cantConnect=true;
 startOnline();
}
