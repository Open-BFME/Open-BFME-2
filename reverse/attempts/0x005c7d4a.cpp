// ??0Impl@InGameCommandButtonMovieClip@@QAE@PAV1@PAVAptMovieClipFrame@@ABVAsciiString@@@Z
// partial score=0.9845744313869788 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
class __single_inheritance AptDelegateTarget;
typedef void (AptDelegateTarget::*AptDelegateMethod)(void);
struct DelegateDesc {
 template<class T,class M> DelegateDesc(T*object,M method):m_object(reinterpret_cast<AptDelegateTarget*>(object)),m_method(reinterpret_cast<AptDelegateMethod>(method)){}
 AptDelegateTarget *m_object; AptDelegateMethod m_method;
};
template<class T,class M> static __forceinline DelegateDesc MakeDelegate(T*object,M method) {DelegateDesc desc(object,method);return desc;}
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);Rva00579E47(const Rva00579E47&);~Rva00579E47();private:void *ptr;};
template<class T> class AptRef:public Rva00579E47 {public:AptRef(DelegateDesc d):Rva00579E47(d){}};
class AptCommandMap;

class Rva000B3F84Pair {public:Rva000B3F84Pair(){} Rva000B3F84Pair *init(const char*); const char *ptr; int len;};
struct AsciiStringRef {const AsciiString *m_string;};
struct AsciiStringPlusString:AsciiStringRef {AsciiStringRef m_second;};
struct AsciiStringPlusStringText:AsciiStringPlusString {operator AsciiString();Rva000B3F84Pair m_right;};
static __forceinline AsciiStringPlusString operator+(const AsciiString&a,const AsciiString&b){AsciiStringPlusString r;r.m_string=&a;r.m_second.m_string=&b;return r;}
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left,const char *right){Rva000B3F84Pair text;text.init(right);AsciiStringPlusStringText result;static_cast<AsciiStringPlusString&>(result)=left;result.m_right=text;return result;}
struct Rva005EF5CA:AsciiStringPlusStringText {operator AsciiString();AsciiStringRef fourth;};
Rva005EF5CA operator+(const AsciiStringPlusStringText&,const AsciiString&);

#include "unicode_string.h"
struct TargetRef00217D4C;void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class ObjectCreationList {public:ObjectCreationList();char data[12];};
class Rva0052413E {public:~Rva0052413E();};class Rva005242D7 {public:~Rva005242D7();};class Rva00524349 {public:~Rva00524349();};
class AptCommandMapAdder {public:void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);ObjectCreationList state;~AptCommandMapAdder(){((Rva0052413E*)this)->Rva0052413E::~Rva0052413E();}};
class Rva00524415 {public:Rva00524415();char data[24];};class Rva00524436{public:~Rva00524436();};
class AptOverButtonHandler;
class AptOverButtonHandlerAdder {public:void AddOverButtonHandler(int,const AsciiString&,AptRef<AptOverButtonHandler>);Rva00524415 state;~AptOverButtonHandlerAdder(){((Rva00524436*)this)->Rva00524436::~Rva00524436();}};
class CustomStorage {public:ObjectCreationList state;~CustomStorage(){((Rva005242D7*)this)->Rva005242D7::~Rva005242D7();}};
struct Init005E1260{int a,b;};class Rva005E1260 {public:Rva005E1260&rva005E1260(const Init005E1260*);};
class AptTimer;
template<> class AptRef<AptTimer> {public:AptRef(DelegateDesc desc){((Rva005E1260*)this)->rva005E1260((const Init005E1260*)&desc);}AptRef(const AptRef&);~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}private:void*ptr;};
class AptTimerAdder {public:void AddTimer(const AsciiString&,AptRef<AptTimer>);ObjectCreationList state;~AptTimerAdder(){((Rva00524349*)this)->Rva00524349::~Rva00524349();}};
class AptMovieClipFrame {public:bool CreateContentMovieClip(const AsciiString&,const AsciiString&,int*,AsciiString*);};

namespace AptUtils {AsciiString DotPath2SlashPath(const char*);}
struct AsciiStringRefWithChar:AsciiStringRef {operator AsciiString();char m_char;};
inline AsciiStringRefWithChar operator+(const AsciiString&a,char c){AsciiStringRefWithChar r;r.m_string=&a;r.m_char=c;return r;}
class BfmeAptWindowManager {public:void bfmeSetText(const AsciiString&,const UnicodeString&,bool);};extern BfmeAptWindowManager*g_bfmeAptWindowManager;
class InGameCommandButtonMovieClip {public:class Impl;virtual ~InGameCommandButtonMovieClip();virtual void NotifyTimer();};
class InGameCommandButtonMovieClip::Impl {public:Impl(InGameCommandButtonMovieClip*,AptMovieClipFrame*,const AsciiString&);void OnInitialized(const char*);void OnPress(const char*);void OnOverButton(const char*);
private:InGameCommandButtonMovieClip*owner;AptMovieClipFrame*frame;int level;AsciiString name;AptCommandMapAdder commands;AptOverButtonHandlerAdder overHandlers;CustomStorage renders;AptTimerAdder timers;bool initialized;int mode;bool flash,overlay;void*image,*unknown5C;};
InGameCommandButtonMovieClip::Impl::Impl(InGameCommandButtonMovieClip*parent,AptMovieClipFrame*parentFrame,const AsciiString&args):owner(parent),frame(parentFrame),level(-1),initialized(false),mode(0),flash(false),overlay(false),image(0),unknown5C(0){
 frame->CreateContentMovieClip(AsciiString("CommandButton"),args,&level,&name);
 AsciiString prefix;prefix.format("_level%u.",level);
 commands.AddCommandMap(prefix+name+"_OnInitialized",AptRef<AptCommandMap>(MakeDelegate(this,&Impl::OnInitialized)));
 commands.AddCommandMap(prefix+name+"_OnPress",AptRef<AptCommandMap>(MakeDelegate(this,&Impl::OnPress)));
 timers.AddTimer(prefix+name+"_Timer",AptRef<AptTimer>(MakeDelegate(owner,&InGameCommandButtonMovieClip::NotifyTimer)));
 overHandlers.AddOverButtonHandler(level,AptUtils::DotPath2SlashPath(name.str())+'/',AptRef<AptOverButtonHandler>(MakeDelegate(this,&Impl::OnOverButton)));
 AsciiString countKey;countKey.format("APT:_level%u.%s_ProductionCount",level,name.str());
 g_bfmeAptWindowManager->bfmeSetText(countKey,UnicodeString(L" "),false);
}
