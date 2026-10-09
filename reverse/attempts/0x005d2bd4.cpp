// ??0Rva005D25F2@@QAE@HABVAsciiString@@@Z
// partial score=1.0 date=2026-10-10
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
class ObjectCreationList {public:ObjectCreationList();char data[12];};class Rva0052413E {public:~Rva0052413E();};class AptCommandMapAdder {public:void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);ObjectCreationList state;~AptCommandMapAdder(){((Rva0052413E*)this)->Rva0052413E::~Rva0052413E();}};
class Rva000B3F84Pair {public:Rva000B3F84Pair(){} Rva000B3F84Pair *init(const char*); const char *ptr; int len;};
struct AsciiStringRef {const AsciiString *m_string;};
struct AsciiStringPlusString:AsciiStringRef {AsciiStringRef m_second;};
struct AsciiStringPlusStringText:AsciiStringPlusString {operator AsciiString();Rva000B3F84Pair m_right;};
static __forceinline AsciiStringPlusString operator+(const AsciiString&a,const AsciiString&b){AsciiStringPlusString r;r.m_string=&a;r.m_second.m_string=&b;return r;}
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left,const char *right){Rva000B3F84Pair text;text.init(right);AsciiStringPlusStringText result;static_cast<AsciiStringPlusString&>(result)=left;result.m_right=text;return result;}
struct Rva005EF5CA:AsciiStringPlusStringText {operator AsciiString();AsciiStringRef fourth;};
Rva005EF5CA operator+(const AsciiStringPlusStringText&,const AsciiString&);

class Rva005D2575 {public:Rva005D2575();~Rva005D2575();private:char data[28];};
class Rva005D2664 {public:void rva005D26B2(const char*);void rva005D27BE(const char*);void rva005D28F4(const char*);void rva005D2A27(const char*);};
namespace StrategicHUD {class CommandUIImpl {public:void OnSubMenuLoaded(const char*);void OnToggleFlashLoaded(const char*);};}
class Rva005D25F2Base {public:~Rva005D25F2Base();virtual int rva005D24E5(int)=0;virtual void rva005D264D(int,const void*)=0;virtual void rva005D2664(int)=0;virtual void rva005D269B()=0;virtual void rva005D2B2F(int,float)=0;};
class Rva005D25F2:public Rva005D25F2Base {public:Rva005D25F2(int,const AsciiString&);~Rva005D25F2();virtual int rva005D24E5(int);virtual void rva005D264D(int,const void*);virtual void rva005D2664(int);virtual void rva005D269B();virtual void rva005D2B2F(int,float);
private:int level;AsciiString name;AptCommandMapAdder commands;int current;Rva005D2575 slots[6];};
Rva005D25F2::Rva005D25F2(int inputLevel,const AsciiString&inputName):level(inputLevel),name(inputName),current(-1){
 AsciiString prefix;prefix.format("_level%u.",inputLevel);
 commands.AddCommandMap(prefix+inputName+"_OnButtonFrameLoaded",AptRef<AptCommandMap>(MakeDelegate(this,&Rva005D2664::rva005D26B2)));
 commands.AddCommandMap(prefix+inputName+"_OnButtonFrameUnloaded",AptRef<AptCommandMap>(MakeDelegate(this,&Rva005D2664::rva005D27BE)));
 commands.AddCommandMap(prefix+inputName+"_OnSubMenuLoaded",AptRef<AptCommandMap>(MakeDelegate(this,&StrategicHUD::CommandUIImpl::OnSubMenuLoaded)));
 commands.AddCommandMap(prefix+inputName+"_OnSubMenuUnloaded",AptRef<AptCommandMap>(MakeDelegate(this,&Rva005D2664::rva005D28F4)));
 commands.AddCommandMap(prefix+inputName+"_OnToggleFlashLoaded",AptRef<AptCommandMap>(MakeDelegate(this,&StrategicHUD::CommandUIImpl::OnToggleFlashLoaded)));
 commands.AddCommandMap(prefix+inputName+"_OnToggleFlashUnloaded",AptRef<AptCommandMap>(MakeDelegate(this,&Rva005D2664::rva005D2A27)));
}
