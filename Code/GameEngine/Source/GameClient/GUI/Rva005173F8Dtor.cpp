// ??1Rva005173F8@@UAE@XZ
// Exact225B after /EHs keeps game-free unwind and a local vector reference
// at erase reuses EDI for end/start. Prior bank supplied layout and donor lead;
// these two changes are established by current native bytes and EH verification.
// cl: /O1 /G7 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// WB AptOnlineShell::~AptOnlineShell at 0x0145BAD0 supplies the identity
// lead and member order. Retail 0x005173F8 independently proves the two
// vptrs at 0/218, screens at 280, strings at 28C/294, record at 29C,
// and the singleton cleanup calls. Keep the already pinned opaque ABI
// owner until the complete class identity is reconciled with its other views.
// Base prefixes and record layout reuse their separately matched destructors.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)();
struct FunctorBinding {
 FunctorBinding(FunctorMethod m,FunctorTarget*t):target(t),method(m){}
 FunctorTarget*target; unsigned unused; FunctorMethod method;
};
struct TargetRef00217D4C { void *vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class Rva0057BC63FunctorHolder {
public:
 Rva0057BC63FunctorHolder(const FunctorBinding&);
 Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder&r):ptr(r.ptr){if(ptr)++ptr->references;}
 TargetRef00217D4C*ptr;
};
template<class T>class AptRef:public Rva0057BC63FunctorHolder {
public:
 AptRef(FunctorBinding b):Rva0057BC63FunctorHolder(b){}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
class AptCommandMap;class AptExternHandler;
class AptCommandMapAdder { public:void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>); _STL::vector<AsciiString> names; };
class AptExternHandlerAdder { public:void AddExternHandler(const AsciiString&,int,AptRef<AptExternHandler>); _STL::vector<AsciiString> names; };


struct AptOnlineSubScreen;
namespace _STL {
template <> AptOnlineSubScreen **vector<AptOnlineSubScreen *, allocator<AptOnlineSubScreen *> >::erase(AptOnlineSubScreen **, AptOnlineSubScreen **);
}

class GameWindow {
public: GameWindow();
protected: virtual ~GameWindow();
private: unsigned char unknown[0x218 - 4];
};
class Rva005248D0 {
public: virtual ~Rva005248D0();
public:
    AptCommandMapAdder m_commandMaps;
    AptExternHandlerAdder m_externHandlers;
private: unsigned char unknown[0x58 - 0x1c];
};
class _bfme_AptGameWindow : public GameWindow, public Rva005248D0 {
public: _bfme_AptGameWindow(void *); virtual ~_bfme_AptGameWindow();
private: AsciiString filename270;
};
class AptOnline:public _bfme_AptGameWindow {
public:
 void OnInitialized(const char*);
 void ShellLoadScreen(const char*);void ShellUnloadScreen(const char*);
 void Options(const char*);void ShellExit(const char*);
 const char *rva00517207(int);
};

struct Rva00416088 {
    Rva00416088() : m_00(-1), m_04(-1) {}
    unsigned int m_00, m_04;
    AsciiString m_08, m_0C;
    ~Rva00416088();
};

struct Rva0051719B {
    Rva0051719B() : buddyId(-1), mode(-1), inviteState(0) {}
    unsigned int buddyId;
    Rva00416088 record;
    int mode, inviteState;
    ~Rva0051719B() {}
};

struct AptOnlineSubScreen {
    virtual void *deleteInstance(int flags);
    virtual void v1();
    virtual void v2();
    unsigned char m_pad04[0x5C - 4];
    const char *m_name;
};

struct LANGameInfo;
extern LANGameInfo *g_Rva00E02EEC;
extern int g_Va00E04904;
void __cdecl TearDownGameSpy();
void __cdecl Rva00511F73Run();

class BfmeAptWindowManager {public:void bfmeSetText(const AsciiString&,const UnicodeString&,bool);};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class GameTextInterface {
public:
#define SLOT(n) virtual void s##n();
 SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
 SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14)
#undef SLOT
 virtual UnicodeString fetch(const char*,bool *exists=0);
};
extern GameTextInterface *TheGameText;
void __cdecl Rva00512069Register();
void __cdecl Rva005118F3Show(int,bool);

class Rva005173F8 : public _bfme_AptGameWindow {
public:
    Rva005173F8(void *);
    virtual ~Rva005173F8();
private:
    unsigned char m_pad274[0x280 - 0x274];
    _STL::vector<AptOnlineSubScreen *> m_screens;
    AsciiString m_pendingScreen;
    AptOnlineSubScreen *m_currentScreen;
    AsciiString m_currentName;
    Rva0051719B m_invite;
    int m_mode;
    bool m_ready;
};

Rva005173F8::~Rva005173F8()
{
    for (_STL::vector<AptOnlineSubScreen *>::iterator i = m_screens.begin(); i != m_screens.end(); ++i) {
        AptOnlineSubScreen *screen = (AptOnlineSubScreen *)*i;
        void *allocation = 0;
        if (screen) allocation = screen->deleteInstance(0);
        ::operator delete(allocation);
    }
    _STL::vector<AptOnlineSubScreen *> &screens = m_screens;
    screens.erase(screens.begin(), screens.end());
    if (g_Va00E04904 == (int)this) {
        TearDownGameSpy();
        g_Rva00E02EEC = 0;
        g_Va00E04904 = 0;
        Rva00511F73Run();
    }
}

// WB AptOnlineShell.cpp:112 and retail 0x0051795C..0x00517CC7 establish
// this constructor and its seven named bindings. Their typed reference
// registration reuses the verified AptOnlineStatsConstructor.cpp pattern.
// The two vtables and class layout agree with the separately verified
// destructor. Keep that existing opaque ABI owner until the other class
// views are reconciled. Registration 0x00512069 remains an unrowed callee.
Rva005173F8::Rva005173F8(void *context):_bfme_AptGameWindow(context),m_currentScreen(0),m_currentName("OnlineLogin"),m_mode(0),m_ready(false)
{
 if(g_Va00E04904)return;
 g_Va00E04904=(int)this;
 {
  FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptOnline::OnInitialized);
  AsciiString name("AptOnline::OnInitialized");
  m_commandMaps.AddCommandMap(name,AptRef<AptCommandMap>(FunctorBinding(method,reinterpret_cast<FunctorTarget*>(this))));
 }
 {
  FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptOnline::ShellLoadScreen);
  AsciiString name("AptOnline::ShellLoadScreen");
  m_commandMaps.AddCommandMap(name,AptRef<AptCommandMap>(FunctorBinding(method,reinterpret_cast<FunctorTarget*>(this))));
 }
 {
  FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptOnline::ShellUnloadScreen);
  AsciiString name("AptOnline::ShellUnloadScreen");
  m_commandMaps.AddCommandMap(name,AptRef<AptCommandMap>(FunctorBinding(method,reinterpret_cast<FunctorTarget*>(this))));
 }
 {
  FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptOnline::Options);
  AsciiString name("AptOnline::Options");
  m_commandMaps.AddCommandMap(name,AptRef<AptCommandMap>(FunctorBinding(method,reinterpret_cast<FunctorTarget*>(this))));
 }
 {
  FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptOnline::ShellExit);
  AsciiString name("AptOnline::ShellExit");
  m_commandMaps.AddCommandMap(name,AptRef<AptCommandMap>(FunctorBinding(method,reinterpret_cast<FunctorTarget*>(this))));
 }
 {
  FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptOnline::rva00517207);
  AsciiString name("OnlineShellStartScreen");
  m_externHandlers.AddExternHandler(name,0,AptRef<AptExternHandler>(FunctorBinding(method,reinterpret_cast<FunctorTarget*>(this))));
 }
 {
  FunctorMethod method=reinterpret_cast<FunctorMethod>(&AptOnline::rva00517207);
  AsciiString name("OnlineAdvMode");
  m_externHandlers.AddExternHandler(name,1,AptRef<AptExternHandler>(FunctorBinding(method,reinterpret_cast<FunctorTarget*>(this))));
 }
 g_bfmeAptWindowManager->bfmeSetText("APT:OnlineOrNetwork",TheGameText->fetch("APT:Online"),false);
 Rva00512069Register();
 Rva005118F3Show(true,true);
}
