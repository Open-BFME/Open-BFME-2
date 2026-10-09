// cl: /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHsc
// ??1Rva005D25F2@@UAE@XZ @0x005D25F2 91B: nonvirtual dtor, derived vtable 0x00875800 then base 0x008078DC.
// Evidence: array ??_M at +0x1C count 6 stride 0x1C via rowed 0x005D258E, rowed 0x0052413E at +0xC,
// rowed releaseBuffer 0x00036410 at +0x8, layout matches sibling Rva005D2664 header 0x1C + 6x0x1C,
// precedents Rva005794EDDtor Rva00579AB7Dtor Rva005FFBCBDtor, callers 0x00578532 0x0057866D 0x00578690.
#include "ascii_string.h"
#include <vector>
// stlport

class Rva0052413E
{
public:
	Rva0052413E();
	~Rva0052413E();
private:
	_STL::vector<AsciiString> m_names;
};

// Constructor5D2BD4..5D2EA1 has six bound callback names and a six-element
// command-slot array. WB15AD030 supplies a StrategicHUD source lead; the original
// constructor/class spelling remains unknown. Retail vtables C078DC/C75800 prove
// five native interface slots: getter24E5 / setter264D / clear2664 / clear269B /
// flash2B2F. Neither table contains a destructor. Direct parent25F2 and scalar
// cleanup578532 are separate native entry points. Preserve their ABI without
// placing a deleting destructor in the getter slot. The original virtual-dtor
// ledger spelling was inferred from vptr writes and is corrected here.
// Target offsets: level4/name8/owning-name-listC/current18, six1C slots at1C.
// Inline concatenation keeps six distinct16-byte returned nodes. Passing the
// binding descriptor by value preserves each native callback-address load.
// The constructor's6x1C iterator calls native25-byte zero initialization;
// the matching destructor5D258E..5D25F2 reverses five nontrivial members.
class Rva000AD6F4 { public: void clear(); };
class Rva00528FE6 { public: void rva00529009(); };
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct SlotClipOwner {
    void *ptr;
    SlotClipOwner() : ptr(0) {}
    ~SlotClipOwner() { reinterpret_cast<Rva000AD6F4 *>(this)->clear(); }
};
struct SlotFlashOwner {
    void *ptr;
    SlotFlashOwner() : ptr(0) {}
    ~SlotFlashOwner() { reinterpret_cast<Rva00528FE6 *>(this)->rva00529009(); }
};
struct SlotRefOwner {
    TargetRef00217D4C *ptr;
    SlotRefOwner() : ptr(0) {}
    ~SlotRefOwner() { if(ptr) ReleaseTreeHintRef00217D4C(ptr); }
};
struct Elem005D25F2 {
    SlotClipOwner frame00,subMenu04;
    SlotFlashOwner flash08;
    SlotRefOwner reference0C,help10;
    unsigned int lastTime14;
    int flashCount18;
    Elem005D25F2();
    ~Elem005D25F2();
};
Elem005D25F2::~Elem005D25F2() {}

extern const void *const g_00C75800[];
extern const void *const g_00C078DC[];

struct TreeHintRef00217D4C { TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &); void *ptr; };
class Rva005D25F2Base
{
public:
	virtual int rva005D24E5(int)=0;
 ~Rva005D25F2Base();
	virtual void rva005D264D(int,const TreeHintRef00217D4C &)=0;
	virtual void rva005D2664(int)=0;
	virtual void rva005D269B()=0;
	virtual void rva005D2B2F(int,float)=0;
};

// Native7-byte C078DC interface teardown at5D23FE is also the full standalone
// body emitted here; original base spelling remains structural inference.
inline Rva005D25F2Base::~Rva005D25F2Base()
{
	*(const void **)this = g_00C078DC;
}

class Rva005D25F2 : public Rva005D25F2Base
{
public:
	Rva005D25F2(int,const AsciiString &);
	virtual int rva005D24E5(int);
 ~Rva005D25F2();
 void *rva00578532(unsigned int);
	virtual void rva005D264D(int,const TreeHintRef00217D4C &);
	virtual void rva005D2664(int);
	virtual void rva005D269B();
	virtual void rva005D2B2F(int,float);
private:
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0C;
	int m_18;
	Elem005D25F2 m_1C[6];
};

Rva005D25F2::~Rva005D25F2()
{
}

class Rva002BED91 { public: void clear(); };
class Rva0057C22FByteChaseField { public: unsigned char get() const; };
class Rva005C3E79 { public: void rva005C3E79(); };
class Rva005D2664 { public:
    void rva005D2664(int); void rva005D26B2(const char *); void rva005D27BE(const char *);
    void rva005D28F4(const char *); void rva005D2A27(const char *);
};
namespace StrategicHUD { class CommandUIImpl { public:
    void OnSubMenuLoaded(const char *); void OnToggleFlashLoaded(const char *);
}; }

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
Rva005D25F2::Rva005D25F2(int level,const AsciiString &name)
    :m_04(level),m_08(name),m_18(-1)
{
    AsciiString prefix;
    prefix.format("_level%u.",level);
    reinterpret_cast<AptCommandMapAdder *>(&m_0C)->AddCommandMap(prefix+name+"_OnButtonFrameLoaded",
        AptRef<AptCommandMap>(MakeBinding(reinterpret_cast<FunctorMethod>(&Rva005D2664::rva005D26B2),reinterpret_cast<FunctorTarget *>(this))));
    reinterpret_cast<AptCommandMapAdder *>(&m_0C)->AddCommandMap(prefix+name+"_OnButtonFrameUnloaded",
        AptRef<AptCommandMap>(MakeBinding(reinterpret_cast<FunctorMethod>(&Rva005D2664::rva005D27BE),reinterpret_cast<FunctorTarget *>(this))));
    reinterpret_cast<AptCommandMapAdder *>(&m_0C)->AddCommandMap(prefix+name+"_OnSubMenuLoaded",
        AptRef<AptCommandMap>(MakeBinding(reinterpret_cast<FunctorMethod>(&StrategicHUD::CommandUIImpl::OnSubMenuLoaded),reinterpret_cast<FunctorTarget *>(this))));
    reinterpret_cast<AptCommandMapAdder *>(&m_0C)->AddCommandMap(prefix+name+"_OnSubMenuUnloaded",
        AptRef<AptCommandMap>(MakeBinding(reinterpret_cast<FunctorMethod>(&Rva005D2664::rva005D28F4),reinterpret_cast<FunctorTarget *>(this))));
    reinterpret_cast<AptCommandMapAdder *>(&m_0C)->AddCommandMap(prefix+name+"_OnToggleFlashLoaded",
        AptRef<AptCommandMap>(MakeBinding(reinterpret_cast<FunctorMethod>(&StrategicHUD::CommandUIImpl::OnToggleFlashLoaded),reinterpret_cast<FunctorTarget *>(this))));
    reinterpret_cast<AptCommandMapAdder *>(&m_0C)->AddCommandMap(prefix+name+"_OnToggleFlashUnloaded",
        AptRef<AptCommandMap>(MakeBinding(reinterpret_cast<FunctorMethod>(&Rva005D2664::rva005D2A27),reinterpret_cast<FunctorTarget *>(this))));
}

Elem005D25F2::Elem005D25F2():lastTime14(0),flashCount18(0) {}
void Rva005D25F2::rva005D264D(int i,const TreeHintRef00217D4C &ref)
{
    *reinterpret_cast<TreeHintRef00217D4C *>(&m_1C[i].reference0C)=ref;
}
void Rva005D25F2::rva005D269B()
{
    for(int i=0;i<6;++i) reinterpret_cast<Rva005D2664 *>(this)->rva005D2664(i);
}
void Rva005D25F2::rva005D2664(int i)
{
    Elem005D25F2 *e=&m_1C[i];
    reinterpret_cast<Rva002BED91 *>(&e->help10)->clear();
    reinterpret_cast<Rva002BED91 *>(&e->reference0C)->clear();
    if(!e->subMenu04.ptr) return;
    if(!reinterpret_cast<Rva0057C22FByteChaseField *>(e->subMenu04.ptr)->get()) return;
    reinterpret_cast<Rva005C3E79 *>(e->subMenu04.ptr)->rva005C3E79();
}

int Rva005D25F2::rva005D24E5(int i) { Elem005D25F2 *e=reinterpret_cast<Elem005D25F2 *>(reinterpret_cast<char *>(this)+(i+1)*0x1C); return e->help10.ptr || e->reference0C.ptr; }

void __cdecl operator delete(void *);
void *Rva005D25F2::rva00578532(unsigned int flags) { this->~Rva005D25F2(); if(flags&1)operator delete(this);return this; }
