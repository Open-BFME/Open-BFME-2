// cl: /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB  -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// platformsdk
// stlport
// Target candidate BuddyThreadClass::Thread_Function552027..552BD2 (2987B),
// with separate catch funclet552BD2 and twelve-case jump table552BD8.
// Donor: reference/open-bfme-1/game/GameEngine/Source/GameNetwork/GameSpy/
// Thread/BuddyThreadClassThreadFunction.cpp at a0e8f345a9b22b4b42088e402962287d7015e3c2.
// Target identity: C6AC0C vtable slot2 in constructor550F01; WB named lead;
// direct native callees and request dispatch independently read in game.dat.
// Native adaptations: BFME2 FESL strings and46F0 selector; lotrbme2r;
// fifth callback; request11 invite; three348B PeerResponse objects, vector100,
// full account enumeration with case-insensitive nick match and two type23
// peer responses. Globals reuse existing listener flags; E05FC4 facade is
// distinct native storage. Address-derived FESL views retain uncertain names.
// Main 2987B and catch funclet/jump table (3041B raw) byte-exact: the
// GPConnection pointer `con` is declared after lastStatusString (WB keeps a
// separate con local next to lastStatusString) and used by every gp* call
// from there on; gpInitialize/gpSetCallback take &gpCon directly. Declaring
// it earlier overlaps callbackWrapper's EDI and evicts the EBX zero; case-4
// scope or &gpCon everywhere loses the EDI copy across connect/info-mask.
// Callback ownership is the native clearing-and-delete lifetime at55076F;
// the existing provider is reconciled as its real destructor rather than
// std::auto_ptr. Original holder type name remains unknown.
#define __PLACEMENT_VEC_NEW_INLINE
#include <windows.h>
#include <stdlib.h>
void Rva00030830GameFree(void*);
#include <string>
// String storage goes to the game free, as in registry.cpp.
namespace _STL { template <> __declspec(dllimport) __forceinline void
_STLP_alloc_proxy<char *, char, allocator<char> >::deallocate(char *p, size_t)
{ if (p != 0) Rva00030830GameFree((void *)p); } }
// Keep the vendor base cleanup inline while binding any outlined call to
// the common STLport provider; no competing game-free copy is emitted.
namespace _STL { template <> __declspec(dllimport) __forceinline
_String_base<char, allocator<char> >::~_String_base() throw() { _M_deallocate_block(); } }
#include <memory>
#include <vector>
#include "ascii_string.h"
namespace _STL { template<> void vector<AsciiString>::push_back(const AsciiString&); }
#include <string.h>
#include "mutex.h"
// Suppress this TU's non-retail copy of ?assign@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@PBD0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<char,char_traits<char>,allocator<char> > & basic_string<char,char_traits<char>,allocator<char> >::assign(char const *,char const *); }
// Suppress this TU's non-retail copy of ?copy@?$__char_traits_base@DH@_STL@@SAPADPADPBDI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * __char_traits_base<char,int>::copy(char *,char const *,unsigned int); }
// Suppress this TU's non-retail copy of ??4?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV01@PBD@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<char,char_traits<char>,allocator<char> > & basic_string<char,char_traits<char>,allocator<char> >::operator=(char const *); }
// Suppress this TU's non-retail copy of ?move@?$__char_traits_base@DH@_STL@@SAPADPADPBDI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * __char_traits_base<char,int>::move(char *,char const *,unsigned int); }
// Suppress this TU's non-retail copy of ?erase@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEPADPAD0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * basic_string<char,char_traits<char>,allocator<char> >::erase(char *,char *); }
// Suppress this TU's non-retail copy of ??0?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<char,char_traits<char>,allocator<char> >::basic_string(); }


// The native cleanup at 0x0055076F clears its one owned word before
// ordinary scalar delete; it is the same owned-pointer lifetime already viewed
// by Rva00575F38Dtor.cpp, rather than std::auto_ptr's non-clearing destructor.
class Rva0055076F
{
public:
    explicit Rva0055076F(void *value) : m_owned(value) {}
    ~Rva0055076F() { void *owned = m_owned; m_owned = 0; ::operator delete(owned); }
    void *get() const { return m_owned; }
private:
    void *m_owned;
};

class GPConnection { public: void *m_handle; };  // GameSpy GP connection handle (a class, as BuddyThread.cpp and the callbackWrapper row)
typedef void (*Rva00438CD0Callback)(GPConnection *,void *,void *);
void callbackWrapper(GPConnection *,void *,void *);
extern "C" {
int GSIStartAvailableCheckA(const char *);
int GSIAvailableCheckThink();
int gpInitialize(GPConnection *,int,int);
void gpDestroy(GPConnection *);
int gpSetCallback(GPConnection *,int,Rva00438CD0Callback,void *);
int gpProcess(GPConnection *);
int gpConnectA(GPConnection *,const char *,const char *,const char *,int,int,Rva00438CD0Callback,void *);
int gpConnectNewUserA(GPConnection *,const char *,const char *,const char *,const char *,const char *,int,int,Rva00438CD0Callback,void *);
int gpConnectPreAuthenticatedA(GPConnection *,const char *,const char *,int,int,Rva00438CD0Callback,void *);
void gpDisconnect(GPConnection *);
int gpDeleteProfile(GPConnection *);
int gpSetInfoMask(GPConnection *,int);
int gpSendBuddyMessageA(GPConnection *,int,const char *);
int gpSendBuddyRequestA(GPConnection *,int,const char *);
int gpDeleteBuddy(GPConnection *,int);
int gpAuthBuddyRequest(GPConnection *,int);
int gpDenyBuddyRequest(GPConnection *,int);
int gpInvitePlayerA(GPConnection *,int,int,const char *);
int gpSetStatusA(GPConnection *,int,const char *,const char *);
}
std::string WideCharStringToMultiByte(const unsigned short *);

class BuddyRequest
{
public:
    int kind;
    union {
        struct {
            char nick[31], email[51], password[31];
            bool hasFirewall;
            char m_76[0x200];
            char cdkey[65];
            bool m_2b7;
        } login;
        struct { int id; unsigned short text[128]; } message;
        struct { int status; char text[256], location[256]; } status;
        char storage[0x2b4];
    } arg;
};
enum Rva0063EB00Kind { RvaKind1=1, RvaKind5=5 };
enum Rva0063EB00Result { RvaResult4=4 };
enum Rva0063EB00Fatal { RvaFatal1=1 };
class BuddyResponse
{
public:
    Rva0063EB00Kind m_00;
    int m_04;
    Rva0063EB00Result m_08;
    int m_0c, m_10;
    char m_14[0x80];
    Rva0063EB00Fatal m_94;
    char m_98[0x7cc];
};
class GameSpyBuddyMessageQueueInterface
{
public:
    virtual ~GameSpyBuddyMessageQueueInterface();
    virtual void startThread();
    virtual void endThread();
    virtual bool isThreadRunning();
    virtual bool isConnected();
    virtual bool isConnecting();
    virtual void addRequest(const BuddyRequest &);
    virtual bool getRequest(BuddyRequest &);
    virtual void addResponse(const BuddyResponse &);
};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

class Rva00550918 { public: Rva00550918() {} virtual void rva00550921(int,unsigned int,const int*); };
class Rva007E8810Message { public: bool hasError(); int getError(); };
class BfmeMsgVJH { char opaque[0x30]; public:
 BfmeMsgVJH(char*,int); virtual ~BfmeMsgVJH();
 bool hasError() { return ((Rva007E8810Message*)this)->hasError(); }
 int error() { return ((Rva007E8810Message*)this)->getError(); }
};
// Retail constructs and destroys a 0x330-byte frame object through the ledger's
// PeerResponse ctor/dtor (0x004DAB40/0x004DAC70 via ILT 0x00042069/0x00044733)
// and never reads it; only the size is modelled.
class PeerResponse { public:
 PeerResponse(); ~PeerResponse();
 int kind; char unknown04[0xfc]; std::vector<AsciiString> names;
 char unknown10c[0x348-0x10c];
};
typedef char CheckPeer[sizeof(PeerResponse)==0x348?1:-1];
typedef char CheckVec[sizeof(std::vector<AsciiString>)==12?1:-1];
class GameSpyPeerMessageQueueInterface { public:
 virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
 virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
 virtual void addResponse(const PeerResponse&);
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
class BfmeQ1279;
class BfmeA1279
{
public:
    BfmeA1279(BfmeQ1279 *a);
    BfmeQ1279 *m_bfme00;
    char m_bfme04[0x100];
    char m_bfme104[0x100];
};
class Rva007E9240SubAccounts
{
public:
    BfmeMsgVJH *m_msg;
    int m_count;
    Rva007E9240SubAccounts(BfmeMsgVJH *message) : m_msg(message), m_count(0) {}
    bool get(char *,int);
};
class Rva0063EB00ServicePump
{
public:
    virtual void slot0();
    virtual void slot1(BfmeMsgVJH *,BfmeMsgVJH *,int);
};
struct Rva007E9D70Cached
{
    virtual void slot0();
    virtual Rva0063EB00ServicePump *slot1();
    virtual void slot2();
    virtual void slot3(BfmeMsgVJH *,const char *,const char *,int,int);
    virtual void slot4();
    virtual void slot5(BfmeMsgVJH *,const char *);
    virtual void slot6(BfmeMsgVJH *,const char *);
    virtual void slot7(); virtual void slot8(); virtual void slot9();
    virtual void slot10(); virtual void slot11(); virtual void slot12();
    virtual void slot13(); virtual void slot14();
    virtual void slot15(BfmeMsgVJH *,const char *);
    virtual void slot16();
    virtual void slot17(BfmeMsgVJH *);
    virtual void slot18();
    virtual void slot19(BfmeMsgVJH *);
};
class Rva007E9D70 { public: Rva007E9D70Cached *get(); };
class Rva007EB6F0Object { public: void invoke(void *,int); };
class Rva007EB700Object { public: void invoke(void *); };
class Rva006573B0Holder { public: void set(const char *,const char *,const char *); };
class Rva00657CA0 { public: void rva00657CA0(int); };
class Rva006575F0 { public: void rva006575F0(); };
class Rva006572A0 { public: void rva006572A0(); };
struct Rva007E9B70Obj { virtual void slot0(); virtual void slot1(int); };
int Rva00656B60Get();
int Rva00658200Get();
int Rva007EB650Shutdown(int);
void Rva007EB270Shutdown();
class ServiceHubImpl;
ServiceHubImpl *createServiceHubImpl(void *,void *,void *,void *,void *,void *);
Rva007E9D70 *g_buddyFeslService;
extern bool g_buddyFeslReady, g_buddyFeslFailed;
class Rva00550995Owner { void *p; public: void clearLock(); };

class BuddyThreadClass
{
public:
    virtual ~BuddyThreadClass();
    virtual void Execute();
protected:
    virtual void Thread_Function();
private:
    char m_unmodelled04[0x4c];
    bool m_isNewAccount, m_isConnecting, m_isConnected;
    int m_profileID, m_lastErrorCode;
    bool m_isDeleting;
    std::string m_nick, m_email, m_password, m_84, m_90;
    MutexClass *m_networkLock;
    CriticalSectionClass m_criticalSection;
    Rva00550995Owner m_ownedLock;
};

void BuddyThreadClass::Thread_Function()
{
    m_ownedLock.clearLock();
    Rva0055076F callback(new Rva00550918);
    if (g_buddyFeslService == 0)
    {
        createServiceHubImpl((void*)"bfme2-retail",(void*)"15123",(void*)"en_US",(void*)"1.0",0,0);
        g_buddyFeslService = (Rva007E9D70*)Rva00658200Get();
        ((Rva007EB6F0Object*)g_buddyFeslService->get())->invoke(callback.get(),0);
        ((Rva006573B0Holder*)g_buddyFeslService)->set("bfme2.fesl.ea.com","","");
    }
    try
    {
        char game[12]; // Eight explicit retail stores; four following stack bytes are unused.
        game[0]='l'; game[1]='o'; game[2]='t'; game[3]='r';
        game[4]='b'; game[5]='m'; game[6]='e'; game[7]='2'; game[8]='r'; game[9]=0;
        GSIStartAvailableCheckA(game);
        int available;
        while ((available = GSIAvailableCheckThink()) == 0) Sleep(10);
        if (available == 1)
        {
            GPConnection gpCon;

            gpInitialize(&gpCon,0x2911,1);
            m_isConnected = m_isConnecting = false;
            gpSetCallback(&gpCon,0,callbackWrapper,(void*)1);
            gpSetCallback(&gpCon,3,callbackWrapper,(void*)2);
            gpSetCallback(&gpCon,1,callbackWrapper,(void*)3);
            gpSetCallback(&gpCon,2,callbackWrapper,(void*)4);
            gpSetCallback(&gpCon,4,callbackWrapper,(void*)5);
            int lastStatus = 0;
            std::string lastStatusString;
            GPConnection *con = &gpCon;
            BuddyRequest request;
            for (;;)
            {
                MutexClass::LockClass lock(*m_networkLock,1);
                if (!lock.Failed()) break;
                if (TheGameSpyBuddyMessageQueue->getRequest(request))
                {
                    switch (request.kind)
                    {
                    case 0:
                    {
                        m_isConnecting = true;
                        m_nick = request.arg.login.nick;
                        m_email = request.arg.login.email;
                        m_password = request.arg.login.password;
                        bool m_2b7 = request.arg.login.m_2b7;
                        __int64 start = timeGetTime();
                        ((Rva00657CA0*)g_buddyFeslService )->rva00657CA0(0x46f0);
                        while (!g_buddyFeslReady)
                        {
                            ((Rva006575F0*)Rva00658200Get())->rva006575F0();
                            ((Rva007E9B70Obj*)Rva00656B60Get())->slot1(0x21);
                            __int64 now = timeGetTime();
                            if (now-start > 15000)
                            {
                                BuddyResponse timedOut;
                                timedOut.m_00=RvaKind1; timedOut.m_08=RvaResult4; timedOut.m_10=0x101; timedOut.m_94=RvaFatal1;
                                TheGameSpyBuddyMessageQueue->addResponse(timedOut);
                                break;
                            }
                        }
                        if (!g_buddyFeslReady) break;
                        if (g_buddyFeslFailed)
                        {
                            m_isConnecting=m_isConnected=false;
                            BuddyResponse failed;
                            failed.m_00=RvaKind1; failed.m_08=RvaResult4; failed.m_10=6; failed.m_94=RvaFatal1;
                            TheGameSpyBuddyMessageQueue->addResponse(failed);
                            break;
                        }
                        char requestData[1024], resultData[1024], extraData[1024];
                        BfmeMsgVJH serviceRequest(requestData,1024);
                        BfmeMsgVJH serviceResult(resultData,1024);
                        BfmeMsgVJH extraRequest(extraData,1024);
                        char email[256] = {0};
                        char password[256] = {0};
                        strncpy(email,m_email.c_str(),255);
                        strncpy(password,m_password.c_str(),255);
                        g_buddyFeslService->get()->slot3(&serviceRequest,email,password,0,0);
                        g_buddyFeslService->get()->slot1()->slot1(&serviceRequest,&serviceResult,10000);
                        PeerResponse unusedResponse;
                        if (serviceResult.hasError())
                        {
                            m_isConnecting=m_isConnected=false;
                            BuddyResponse failed;
                            failed.m_00=RvaKind5; failed.m_08=RvaResult4; failed.m_0c=serviceResult.error(); failed.m_94=RvaFatal1;
                            TheGameSpyBuddyMessageQueue->addResponse(failed);
                            break;
                        }
                        g_buddyFeslService->get()->slot17(&extraRequest);
                        g_buddyFeslService->get()->slot1()->slot1(&extraRequest,&serviceResult,10000);
                        bool found = false;
                        if (!serviceResult.hasError())
                        {
                            Rva007E9240SubAccounts accounts(&serviceResult);
                            char name[32] = {0};
                            PeerResponse response;
                            response.kind=23;
                            while (accounts.get(name,32)) {
                                response.names.push_back(AsciiString(name));
                                if (_strcmpi(m_nick.c_str(),name)==0) found=true;
                            }
                            TheGameSpyPeerMessageQueue->addResponse(response);
                        }
                        if (m_2b7)
                        {
                            if (!found)
                            {
                                BuddyResponse failed;
                                failed.m_00=RvaKind5; failed.m_08=RvaResult4; failed.m_0c=0x26ac; failed.m_94=RvaFatal1;
                                TheGameSpyBuddyMessageQueue->addResponse(failed);
                                break;
                            }
                            g_buddyFeslService->get()->slot6(&extraRequest,m_nick.c_str());
                            g_buddyFeslService->get()->slot1()->slot1(&extraRequest,&serviceResult,10000);
                            if (serviceResult.hasError())
                            {
                                BuddyResponse failed;
                                failed.m_00=RvaKind5; failed.m_08=RvaResult4; failed.m_0c=serviceResult.error(); failed.m_94=RvaFatal1;
                                TheGameSpyBuddyMessageQueue->addResponse(failed);
                                break;
                            }
                            BuddyResponse failed;
                            failed.m_00=RvaKind5; failed.m_08=RvaResult4; failed.m_0c=0x26ad; failed.m_94=RvaFatal1;
                            TheGameSpyBuddyMessageQueue->addResponse(failed);
                            break;
                        }
                        if (!found)
                        {
                            g_buddyFeslService->get()->slot5(&extraRequest,m_nick.c_str());
                            g_buddyFeslService->get()->slot1()->slot1(&extraRequest,&serviceResult,10000);
                            if (serviceResult.hasError())
                            {
                                BuddyResponse failed;
                                failed.m_00=RvaKind5; failed.m_08=RvaResult4; failed.m_0c=serviceResult.error(); failed.m_94=RvaFatal1;
                                TheGameSpyBuddyMessageQueue->addResponse(failed);
                                break;
                            }
                            PeerResponse response;
                            response.kind=23;
                            response.names.push_back(AsciiString(m_nick.c_str()));
                            TheGameSpyPeerMessageQueue->addResponse(response);
                        }
                        g_buddyFeslService->get()->slot15(&serviceRequest,m_nick.c_str());
                        g_buddyFeslService->get()->slot1()->slot1(&serviceRequest,&serviceResult,10000);
                        if (serviceResult.hasError())
                        {
                            m_isConnecting=m_isConnected=false;
                            BuddyResponse failed;
                            failed.m_00=RvaKind5; failed.m_08=RvaResult4; failed.m_0c=serviceResult.error(); failed.m_94=RvaFatal1;
                            TheGameSpyBuddyMessageQueue->addResponse(failed);
                            break;
                        }
                        g_buddyFeslService->get()->slot19(&serviceRequest);
                        g_buddyFeslService->get()->slot1()->slot1(&serviceRequest,&serviceResult,10000);
                        BfmeA1279 authentication((BfmeQ1279 *)&serviceResult);
                        m_84 = authentication.m_bfme04;
                        m_90 = authentication.m_bfme104;
                        if (gpConnectPreAuthenticatedA(con,authentication.m_bfme04,authentication.m_bfme104,
                                request.arg.login.hasFirewall?1:0,0,callbackWrapper,0))
                        {
                            BuddyResponse failed;
                            m_isConnecting=false;
                            failed.m_00=RvaKind1; failed.m_08=RvaResult4; failed.m_10=0x107; failed.m_94=RvaFatal1;
                            TheGameSpyBuddyMessageQueue->addResponse(failed);
                        }
                        break;
                    }
                    case 1:
                        m_isConnecting=true;
                        m_isConnected=(gpConnectA(con,m_nick.c_str(),m_email.c_str(),m_password.c_str(),1,1,callbackWrapper,0)==0);
                        m_isConnecting=false;
                        break;
                    case 10:
                        m_isDeleting=true;
                        gpDeleteProfile(con);
                        break;
                    case 2:
                        m_isConnecting=m_isConnected=false;
                        gpDisconnect(con);
                        break;
                    case 3:
                    {
                        std::string message=WideCharStringToMultiByte(request.arg.message.text);
                        gpSendBuddyMessageA(con,request.arg.message.id,message.c_str());
                        break;
                    }
                    case 4:
                    {
                        m_isConnecting=true;
                        m_nick=request.arg.login.nick;
                        m_email=request.arg.login.email;
                        m_password=request.arg.login.password;
                        m_isNewAccount=true;
                        m_isConnected=(gpConnectNewUserA(con,request.arg.login.nick,request.arg.login.nick,
                            request.arg.login.email,request.arg.login.password,request.arg.login.cdkey,
                            request.arg.login.hasFirewall?1:0,1,callbackWrapper,0)==0);
                        if (m_isNewAccount) gpSetInfoMask(con,0);
                        m_isConnecting=false;
                        break;
                    }
                    case 11: gpInvitePlayerA(con,request.arg.message.id,0x2911,(const char*)request.arg.message.text); break;
                    case 5:
                    {
                        std::string message=WideCharStringToMultiByte(request.arg.message.text);
                        gpSendBuddyRequestA(con,request.arg.message.id,message.c_str());
                        break;
                    }
                    case 6: gpDeleteBuddy(con,request.arg.message.id); break;
                    case 7: gpAuthBuddyRequest(con,request.arg.message.id); break;
                    case 8: gpDenyBuddyRequest(con,request.arg.message.id); break;
                    case 9:
                        if (lastStatus==2 && lastStatusString=="Loading" && request.arg.status.status==1) break;
                        gpSetStatusA(con,request.arg.status.status,request.arg.status.text,request.arg.status.location);
                        lastStatus=request.arg.status.status;
                        lastStatusString=request.arg.status.text;
                        break;
                    }
                }
                gpProcess(con);
                if (g_buddyFeslService) ((Rva006575F0*)g_buddyFeslService)->rva006575F0();
            }
            gpDestroy(con);
        }
    }
    catch (...) {}
    if (g_buddyFeslService)
    {
        ((Rva007EB700Object*)g_buddyFeslService->get())->invoke(callback.get());
        ((Rva006572A0*)g_buddyFeslService)->rva006572A0();
        Rva007EB650Shutdown(0);
        Rva007EB270Shutdown();
        g_buddyFeslFailed=0;
        g_buddyFeslReady=0;
        g_buddyFeslService=0;
    }
}
