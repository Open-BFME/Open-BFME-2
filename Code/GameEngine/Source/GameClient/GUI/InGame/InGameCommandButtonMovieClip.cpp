// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// InGameCommandButtonMovieClip::Impl construction, native005C7D4A..005C802B.
// WorldBuilder names the constructor and callback wiring; the existing
// destructor and callbacks independently prove fields10/1C/34/40/4C/50/54/55.
// Real RegistryAsciiPath string materializers plus their complete length/write
// chain preserve the native temporary lifetimes. Individual materializers
// alone leave ten stack-home differences; no fabricated padding is needed.
// See reverse/attempt_evidence/0x005c7d4a_visibility.txt.
#include "ascii_string.h"
class __single_inheritance AptDelegateTarget;
typedef void (AptDelegateTarget::*AptDelegateMethod)(void);
#include "../../../../Include/Common/DelegateDesc.h"
template<class T,class M> static __forceinline DelegateDesc MakeDelegate(T*object,M method) {DelegateDesc desc(object,method);return desc;}
struct TargetRef00217D4C;void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);Rva00579E47(const Rva00579E47&);void *ptr;};
template<class T> class AptRef:public Rva00579E47 {public:AptRef(DelegateDesc d):Rva00579E47(d){}~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}};
class AptCommandMap;

#include "../../../../Include/Common/Rva000B3F84Pair.h"
#include "../../../../Include/Common/AsciiStringRef.h"
struct AsciiStringPlusString:AsciiStringRef {int length()const;int write(char *);AsciiStringRef m_second;};
struct AsciiStringPlusStringText:AsciiStringPlusString {int write(char *);operator AsciiString();Rva000B3F84Pair m_right;};
static __forceinline AsciiStringPlusString operator+(const AsciiString&a,const AsciiString&b){AsciiStringPlusString r;r.m_string=&a;r.m_second.m_string=&b;return r;}
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left,const char *right){Rva000B3F84Pair text;text.init(right);AsciiStringPlusStringText result;static_cast<AsciiStringPlusString&>(result)=left;result.m_right=text;return result;}
struct Rva005EF5CA:AsciiStringPlusStringText {operator AsciiString();AsciiStringRef fourth;};
Rva005EF5CA operator+(const AsciiStringPlusStringText&,const AsciiString&);

#include "unicode_string.h"
struct TargetRef00217D4C;void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
class ObjectCreationList {public:ObjectCreationList();char data[12];};
class Rva005242D7 {public:~Rva005242D7();};class Rva00524349 {public:~Rva00524349();};
class AptCommandMapAdder {public:__declspec(dllimport) __forceinline AptCommandMapAdder(){}void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);ObjectCreationList state;~AptCommandMapAdder();};
class Rva00524415 {public:Rva00524415();char data[24];};class Rva00524436{public:~Rva00524436();};
class AptOverButtonHandler;
class AptOverButtonHandlerAdder {public:void AddOverButtonHandler(int,const AsciiString&,AptRef<AptOverButtonHandler>);Rva00524415 state;~AptOverButtonHandlerAdder(){((Rva00524436*)this)->Rva00524436::~Rva00524436();}};
class CustomStorage {public:ObjectCreationList state;~CustomStorage(){((Rva005242D7*)this)->Rva005242D7::~Rva005242D7();}};
struct Init005E1260{int a,b;};class Rva005E1260 {public:Rva005E1260&rva005E1260(const Init005E1260*);};
class AptTimer;
template<> class AptRef<AptTimer> {public:AptRef(DelegateDesc desc){((Rva005E1260*)this)->rva005E1260((const Init005E1260*)&desc);}AptRef(const AptRef&);~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}private:void*ptr;};
class AptTimerAdder {public:__declspec(dllimport) __forceinline AptTimerAdder(){}void AddTimer(const AsciiString&,AptRef<AptTimer>);ObjectCreationList state;~AptTimerAdder();};
class AptMovieClipFrame {public:bool CreateContentMovieClip(const AsciiString&,const AsciiString&,int*,AsciiString*);};

namespace AptUtils {AsciiString DotPath2SlashPath(const char*);}
struct AsciiStringRefWithChar:AsciiStringRef {int write(char *);operator AsciiString();char m_char;};
inline AsciiStringRefWithChar operator+(const AsciiString&a,char c){AsciiStringRefWithChar r;r.m_string=&a;r.m_char=c;return r;}
#include "../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager*g_bfmeAptWindowManager;
#include "../../../../Include/GameClient/InGameCommandButtonMovieClip.h"
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

__declspec(noinline) inline AsciiStringPlusStringText::operator AsciiString(){AsciiString tmp;int extra=m_right.m_len;write(((StringBase<char> *)&tmp)->getBufferForRead(extra+AsciiStringPlusString::length()));return tmp;}
__declspec(noinline) inline AsciiStringRefWithChar::operator AsciiString(){AsciiString tmp;write(((StringBase<char> *)&tmp)->getBufferForRead(m_string->getLength()+1));return tmp;}
__declspec(noinline) inline int Rva000B3F84Pair::write(char *dst){memcpy(dst,m_ptr,m_len);return m_len;}
__declspec(noinline) inline int AsciiStringRef::write(char *dst){int len=m_string->getLength();memcpy(dst,m_string->str(),len);return len;}
__declspec(noinline) inline int AsciiStringRefWithChar::write(char *dst){int n=AsciiStringRef::write(dst);dst[n]=m_char;return n+1;}
__declspec(noinline) inline int AsciiStringPlusString::length()const{return m_string->getLength()+m_second.m_string->getLength();}
__declspec(noinline) inline int AsciiStringPlusString::write(char *dst){int n=AsciiStringRef::write(dst);return n+m_second.write(dst+n);}
__declspec(noinline) inline int AsciiStringPlusStringText::write(char *dst){int n=AsciiStringPlusString::write(dst);return n+m_right.write(dst+n);}
// Rva000B3F84Pair::init is defined by its row's unit, WinMainPairUnicode.cpp.
