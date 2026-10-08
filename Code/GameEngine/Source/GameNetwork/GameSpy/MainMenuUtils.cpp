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
