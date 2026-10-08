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
class UserPreferences { public: virtual ~UserPreferences(); virtual bool write(); };
class GameSpyMiscPreferences: public UserPreferences {
public: GameSpyMiscPreferences(); virtual ~GameSpyMiscPreferences();
    int rva00559782();
    unsigned char rest[0x10];
};
class Rva00222A8BTarget { public:
    int invoke(void *,const char *,int,const char *,void *,void *,void *,void *);
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;
class Rva0056DCBF { public: void rva0056DCBF(bool); };
struct AptOnlineLoginOwner { unsigned char pad[0x274]; void *movie; };
class AptOnlineLogin {
public:
    void OnBttnRegisterFESL(const char *);
    void rva00572632(const char *);
private:
    unsigned char pad00[0x58]; AptOnlineLoginOwner *owner;
    unsigned char pad5c[0xD0-0x5C]; bool closeLocale;
    unsigned char padD1[3]; int locale;
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

// Registered as AptOnline::Login::Login in native 572885. BFME1 donor
// 34f59164 OnlineLoginLogin.cpp supplies purpose and control flow;
// native 572632..572766 verifies fields 58/D0/D4 and all callees.
// The target callback's method name remains address-derived.
void AptOnlineLogin::rva00572632(const char *)
{
    if(g_bfmeObjELB) {
        { void *movie=owner->movie;
          TheRva00222A8BTarget->invoke(movie,"CallChild",1,"DisableButtonDeleteNickname",0,0,0,0); }
        { void *movie=owner->movie;
          TheRva00222A8BTarget->invoke(movie,"CallChild",1,"DisableButtonCreate",0,0,0,0); }
        { void *movie=owner->movie;
          TheRva00222A8BTarget->invoke(movie,"CallChild",1,"DisableButtonLogin",0,0,0,0); }
        { void *movie=owner->movie;
          TheRva00222A8BTarget->invoke(movie,"CallChild",1,"DisableButtonServiceTerms",0,0,0,0); }
        GameSpyMiscPreferences preferences;
        if(preferences.rva00559782()>=1 && preferences.rva00559782()<=0x25) {
            locale=preferences.rva00559782();
            g_bfmeObjELB->bfmeTailELB(false);
            return;
        }
        closeLocale=false;
        void *movie=owner->movie;
        TheRva00222A8BTarget->invoke(movie,"CallChild",1,"DoOpenLocale",0,0,0,0);
        ((Rva0056DCBF *)this)->rva0056DCBF(false);
    }
}
