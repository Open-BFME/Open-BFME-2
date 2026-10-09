// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /EHsc /MD
// Constructor4CBB..4DA9 is238B; native fields parent0/level4/name8/mapsC plus
// three float18/1C/20 and bool24/25 agree with named AptScrollBar::Impl setters
// and OnChanged487 body. WB15A8B40 supplies the same _OnPosChanged binding and
// argument stores but no constructor name; retain the existing neutral owner.
// Descriptor passed by value and full16-byte concat node retain native lifetimes.
// ??1Rva005D4913@@QAE@XZ @0x005D4913 54B: non-virtual dtor destroying AsciiString at +8 and Rva0052413E at +0xC. Evidence: EH prolog with two member-dtor calls in retail order plus deleting-dtor caller 0x005D49DD plus holder caller 0x005D4BE7.
#include "ascii_string.h"

class Rva0052413E
{
public:
	Rva0052413E();
 ~Rva0052413E();
 char storage[12];
};

class Rva005D4913
{
public:
	Rva005D4913(void *,int,const AsciiString &);
 ~Rva005D4913();
private:
	void *m_parent; int m_level;
	AsciiString m_08;
	Rva0052413E m_0C;
 float m_page18,m_line1C,m_pos20; bool m_enabled24,m_visible25;
};
Rva005D4913::~Rva005D4913()
{
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva000B3F84Pair { public: Rva000B3F84Pair() {} Rva000B3F84Pair *init(const char *); const char *m_ptr; int m_len; };
struct AsciiStringRef { const AsciiString *m_string; };
struct AsciiStringPlusString : AsciiStringRef { AsciiStringRef m_second; };
struct AsciiStringPlusStringText : AsciiStringPlusString {
    operator AsciiString(); Rva000B3F84Pair m_text;
};
inline AsciiStringPlusString operator+(const AsciiString &a,const AsciiString &b) {
    AsciiStringPlusString result; result.m_string=&a; result.m_second.m_string=&b; return result;
}
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left,const char *right) {
    Rva000B3F84Pair text; text.init(right); AsciiStringPlusStringText result;
    static_cast<AsciiStringPlusString &>(result)=left; result.m_text=text; return result;
}

class __single_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(const char *);
struct DelegateDesc {
    DelegateDesc(FunctorMethod f,FunctorTarget *p):object(p),method(f) {}
    FunctorTarget *object; FunctorMethod method;
};
struct FunctorHeader { void *vptr; int refs; };
class Rva00579E47 { public:
    Rva00579E47(const DelegateDesc &);
    Rva00579E47(const Rva00579E47 &r):ptr(r.ptr) { if(ptr) ++ptr->refs; }
    FunctorHeader *ptr;
};
template<class T> class AptRef : public Rva00579E47 { public:
    AptRef(DelegateDesc d):Rva00579E47(d) {}
    ~AptRef() { if(ptr) ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(ptr)); }
};
class AptCommandMap;
class AptCommandMapAdder { public:
    void AddCommandMap(const AsciiString &,AptRef<AptCommandMap>);
};
static __forceinline DelegateDesc MakeBinding(FunctorMethod f,FunctorTarget *p) { return DelegateDesc(f,p); }

class Rva005D4867 { public: void rva005D4867(const char *); };
Rva005D4913::Rva005D4913(void *parent,int level,const AsciiString &name)
 :m_parent(parent),m_level(level),m_08(name),m_page18(0),m_line1C(0),m_pos20(0),m_enabled24(false),m_visible25(true)
{
 AsciiString prefix; prefix.format("_level%u.",m_level);
 reinterpret_cast<AptCommandMapAdder *>(&m_0C)->AddCommandMap(prefix+m_08+"_OnPosChanged",
  AptRef<AptCommandMap>(MakeBinding(reinterpret_cast<FunctorMethod>(&Rva005D4867::rva005D4867),reinterpret_cast<FunctorTarget *>(this))));
}
