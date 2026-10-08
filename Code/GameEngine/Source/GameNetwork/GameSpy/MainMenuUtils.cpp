// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common
// stlport
// BFME1 34f59164 MainMenuUtils.cpp is the primary reference.
// WB158CC80 names startOnline and MainMenuUtils.cpp; native5BC887..5BCA60
// proves the target-specific enable calls and removal of the legacy login UI.
// The accept callback is BFME2 shutdown behavior, not the donor downloader.
// Shared AsciiString/UnicodeString and the existing MessageBox providers.

#include "ascii_string.h"
#include "unicode_string.h"
#include <list>
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
