// cl: /O1 /EHsc /MD /arch:SSE /G7 /Ireference/shims/bfme2_ascii
// BFME1 OnlineLoginRegister.cpp34f59164 supplies registration-tool behavior.
// BFME2 WB150B150 names OnBttnRegisterFESL and AptOnlineLogin.cpp.
// Native56E849..56E998 owns the guard, removes donor's eight UI toggles,
// uses ShellExecuteW and verifies the fetch slot at3C.
#include "ascii_string.h"
#include "unicode_string.h"
extern "C" __declspec(dllimport) void *__stdcall ShellExecuteW(void *,const unsigned short *,const unsigned short *,const unsigned short *,const unsigned short *,int);
bool GetStringFromRegistry(AsciiString,AsciiString,AsciiString &);
void GSMessageBoxOk(UnicodeString,UnicodeString,void (*)());
void bfmeMinimizeCurrentThreadWindow();
class BfmeObjELB { public: void bfmeTailELB(bool); };
extern BfmeObjELB *g_bfmeObjELB;
class GameTextInterface {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual UnicodeString fetch(const char *,bool *exists=0);
};
extern GameTextInterface *TheGameText;
class AptOnlineLogin {
public: void OnBttnRegisterFESL(const char *);
};
void AptOnlineLogin::OnBttnRegisterFESL(const char *)
{
    if(g_bfmeObjELB) {
        AsciiString path("");
        if(GetStringFromRegistry("","InstallPath",path) && !path.isEmpty()) {
            path.concat("\\SUPPORT\\EREG.EXE");
            int result=(int)ShellExecuteW(0,L"open",UnicodeString(path).str(),L"",0,5);
            if(result<=31)
                GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"),TheGameText->fetch("GUI:EREGError"),0);
            else
                bfmeMinimizeCurrentThreadWindow();
        } else {
            GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"),TheGameText->fetch("GUI:EREGError"),0);
        }
    }
}
