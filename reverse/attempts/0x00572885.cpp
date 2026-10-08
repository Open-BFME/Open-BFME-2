// ??0Rva00572885@@QAE@PAVAptOnline@@@Z
// partial score=0.95 date=2026-10-08
// cl: /O1 /EHsc /MD /arch:SSE /G7 /Ireference/shims/bfme2_ascii
// Isolated reference-based port of BFME1 OnlineLoginConstructor.cpp at34f59164.
// Native572885..572C5A fixes60-byte base,44-byte preferences,tail and16B binding.
#include "ascii_string.h"
class AptOnline { public: class Login; };
class AptOnline::Login {
public:
    void LoginCallback(const char *);
    void RegisterCallback(const char *);
    void ServiceTerms(const char *);
    void AcceptLocale(const char *);
    void CancelLogin(const char *);
    void OfficialSite(const char *);
    void GameSpy(const char *);
    void InitGadgets(const char *,void *,void *);
};
void __stdcall bfmeGoELB(int);
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)();
template<class M> __forceinline FunctorMethod loginMethod(M specific) {
    union { M specific; unsigned word; } source;
    union { FunctorMethod generic; unsigned words[2]; } target;
    source.specific=specific;
    target.words[0]=source.word;
    target.words[1]=0;
    return target.generic;
}
struct FunctorBinding {
    FunctorBinding(FunctorMethod method,FunctorTarget *target) : m_target(target),m_method(method) {}
    FunctorTarget *m_target; unsigned m_pad; FunctorMethod m_method;
};
class Rva0057BC63FunctorHolder {
public:
    Rva0057BC63FunctorHolder(const FunctorBinding &binding);
    __forceinline Rva0057BC63FunctorHolder(FunctorBinding binding,int) { this->Rva0057BC63FunctorHolder::Rva0057BC63FunctorHolder(binding); }
    void *pointer;
};
class AptCommandMap;
class AptScreenInitGadgets;
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
template<class T> class AptRef {
public:
    AptRef(const FunctorBinding &binding) : holder(binding) {}
    AptRef(const AptRef &);
    ~AptRef() { if(holder.pointer) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)holder.pointer); }
private: Rva0057BC63FunctorHolder holder;
};
class AptCommandMapAdder {
public:
    void AddCommandMap(const AsciiString &,AptRef<AptCommandMap>);
    __forceinline void bind(const AsciiString &name,FunctorBinding binding) { AddCommandMap(name,binding); }
};
void _bfme_setAptScreenRef(const AsciiString &,AptRef<AptScreenInitGadgets>);
__forceinline void bindScreen(const AsciiString &name,FunctorBinding binding) { _bfme_setAptScreenRef(name,binding); }
class Rva0056DC4C { public: Rva0056DC4C(void *); };
class Rva0056DC6B { public: virtual ~Rva0056DC6B(); };
extern "C" const void *const vtbl_00C6DBBC[];
class LoginBaseScope {
public:
    __forceinline LoginBaseScope(AptOnline *shell) {
        ((Rva0056DC4C *)this)->Rva0056DC4C::Rva0056DC4C(shell);
        *(const void ***)this=(const void **)vtbl_00C6DBBC;
    }
    __forceinline ~LoginBaseScope() { ((Rva0056DC6B *)this)->~Rva0056DC6B(); }
private: unsigned storage[0x60/4];
};
class GameSpyLoginPreferences {
public: GameSpyLoginPreferences(); virtual ~GameSpyLoginPreferences();
private: unsigned char tail[0x40];
};
class IMEManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17();
};
extern IMEManager *TheIMEManager;
extern int g_Va00E062EC;
class Rva0056EE5F { public: unsigned char rva0056EE5F(); };
class Rva00572885 {
public: Rva00572885(AptOnline *shell);
private:
    LoginBaseScope base;
    GameSpyLoginPreferences preferences;
    void *controlA4,*controlA8,*controlAC,*controlB0,*controlB4;
    int untouchedB8,flagBC,zeroC0;
    unsigned char zeroC4,oneC5; unsigned char untouchedC6[2];
    int zeroC8;
    unsigned char zeroCC,oneCD,oneCE,zeroCF;
    unsigned char untouchedD0[2],zeroD2,untouchedD3;
    int zeroD4;
    AsciiString nameD8;
    unsigned char zeroDC,untouchedDD[3];
};
union LoginMethodBits { FunctorMethod method; void (__stdcall *function)(int); };
Rva00572885::Rva00572885(AptOnline *shell)
 : base(shell),controlA4(0),controlA8(0),controlAC(0),controlB0(0),controlB4(0),
   flagBC(1),zeroC0(0),zeroC4(0),oneC5(1),zeroC8(0),zeroCC(0),oneCD(1),oneCE(1),zeroCF(0),
   zeroD2(0),zeroD4(0),nameD8(),zeroDC(0)
{
    if(g_Va00E062EC==0) {
        g_Va00E062EC=(int)this;
        {
            FunctorMethod method=loginMethod(&AptOnline::Login::LoginCallback);
            AsciiString name("AptOnline::Login::Login");
            ((AptCommandMapAdder *)((char *)this+4))->bind(name,FunctorBinding(method,(FunctorTarget *)this));
        }
        {
            LoginMethodBits bits; bits.function=bfmeGoELB;
            AsciiString name("AptOnline::Login::DeleteNickname");
            ((AptCommandMapAdder *)((char *)this+4))->bind(name,FunctorBinding(bits.method,(FunctorTarget *)this));
        }
        {
            FunctorMethod method=loginMethod(&AptOnline::Login::RegisterCallback);
            AsciiString name("AptOnline::Login::Register");
            ((AptCommandMapAdder *)((char *)this+4))->bind(name,FunctorBinding(method,(FunctorTarget *)this));
        }
        {
            FunctorMethod method=loginMethod(&AptOnline::Login::ServiceTerms);
            AsciiString name("AptOnline::Login::ServiceTerms");
            ((AptCommandMapAdder *)((char *)this+4))->bind(name,FunctorBinding(method,(FunctorTarget *)this));
        }
        {
            FunctorMethod method=loginMethod(&AptOnline::Login::AcceptLocale);
            AsciiString name("AptOnline::Login::AcceptLocale");
            ((AptCommandMapAdder *)((char *)this+4))->bind(name,FunctorBinding(method,(FunctorTarget *)this));
        }
        {
            FunctorMethod method=loginMethod(&AptOnline::Login::CancelLogin);
            AsciiString name("AptOnline::Login::CancelLogin");
            ((AptCommandMapAdder *)((char *)this+4))->bind(name,FunctorBinding(method,(FunctorTarget *)this));
        }
        {
            FunctorMethod method=loginMethod(&AptOnline::Login::OfficialSite);
            AsciiString name("AptOnline::Login::OfficialSite");
            ((AptCommandMapAdder *)((char *)this+4))->bind(name,FunctorBinding(method,(FunctorTarget *)this));
        }
        {
            FunctorMethod method=loginMethod(&AptOnline::Login::GameSpy);
            AsciiString name("AptOnline::Login::GameSpy");
            ((AptCommandMapAdder *)((char *)this+4))->bind(name,FunctorBinding(method,(FunctorTarget *)this));
        }
        {
            FunctorMethod method=loginMethod(&AptOnline::Login::InitGadgets);
            AsciiString name("AptOnlineLogin::InitGadgets");
            bindScreen(name,FunctorBinding(method,(FunctorTarget *)this));
        }
        zeroCF=((Rva0056EE5F *)this)->rva0056EE5F();
        zeroD2=((Rva0056EE5F *)this)->rva0056EE5F();
        TheIMEManager->v17();
    }
}
