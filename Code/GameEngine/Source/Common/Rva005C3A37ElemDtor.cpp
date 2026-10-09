// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DBFME_ASCII_DTOR_DECL /EHsc /MD
// Native005C39DE..005C39EB is a 13B three-word zero constructor.
// Native005C39EB..005C3A37 is a complete 76B EH destructor: counted
// words0/8 use the rowed7DEEF release; owning word4 uses rowed AD6F4.
// Native005C3A37..005C3A86 is a complete79B parent destructor, using
// vector-dtor iterator629110 with stride12/count3 at+20 then the rowed
// command-map-adder52413E at+C and AsciiString36410 at+8.
// Original identities remain neutral. These layout/lifetime facts come
// from target bytes and callback references, independent of donor names.
#include "ascii_string.h"
struct TargetRef00217D4C { virtual void *destroy(unsigned); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
 TargetRef00217D4C *m_ptr;
 TreeHintRef00217D4C(const TreeHintRef00217D4C &);
 TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &);
 ~TreeHintRef00217D4C() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
struct Rva005C39DERef {
 TargetRef00217D4C *ptr;
 Rva005C39DERef():ptr(0) {}
 ~Rva005C39DERef() { if(ptr) ReleaseTreeHintRef00217D4C(ptr); }
};
class Rva000AD6F4 {
public:
 void *ptr;
 Rva000AD6F4():ptr(0) {}
 ~Rva000AD6F4();
 void clear();
};
class Rva005C39DEMember {
public:
 ~Rva005C39DEMember();
public:
 Rva005C39DERef first;
 Rva000AD6F4 middle;
 Rva005C39DERef last;
};
Rva005C39DEMember::~Rva005C39DEMember() {}
struct DelegateDesc;
class Rva00579E47 {public: Rva00579E47(const DelegateDesc &); Rva00579E47(const Rva00579E47 &); ~Rva00579E47() {if(ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)ptr);} private: void *ptr;};
class AptCommandMap;
template<class T> class AptRef : public Rva00579E47 {public: AptRef(DelegateDesc);};
class AptCommandMapAdder {
public:
 char unknown00[0xC];
public:
 AptCommandMapAdder();
 ~AptCommandMapAdder();
 void AddCommandMap(const AsciiString &, AptRef<AptCommandMap>);
 __forceinline void AddCommandMapBinding(const AsciiString &n, DelegateDesc d);
};
class Rva005C3DE1Owner { public: virtual void unknown0(); virtual void unknown1(); virtual void finish(); };
class Rva005C3F02;
class Rva005C3A37Elem {
 Rva005C3DE1Owner *owner;
 void *unknown04;
 AsciiString name;
 AptCommandMapAdder commands;
 bool active;
 char unknown19[3];
 int count;
 Rva005C39DEMember members[3];
 bool pending;
 bool reload;
 char unknown46[2];
public:
 Rva005C3A37Elem(Rva005C3F02 *,void *,void *);
 ~Rva005C3A37Elem();
 void rva005C3DE1(int);
 void Add(TreeHintRef00217D4C);
 void rva005C3B3E();
};
Rva005C3A37Elem::~Rva005C3A37Elem() {}

// Native005C3DE1..005C3E31 RET4. Guard44 is cleared before checking18;
// count1C is decremented at least once then the selected12B element's
// holders are cleared in reverse order. Positive remaining count repeats;
// the owner0 virtual slot8 is called after disabling18. Argument is unread.
struct Rva002BED91 { void clear(); };
void Rva005C3A37Elem::rva005C3DE1(int)
{
 if(pending) {
  pending=false;
  if(active) {
   do {
    --count;
    Rva005C39DEMember *member=&members[count];
    reinterpret_cast<Rva002BED91 *>(&member->last)->clear();
    member->middle.clear();
    reinterpret_cast<Rva002BED91 *>(&member->first)->clear();
   } while(count>0);
   active=false;
   owner->finish();
  }
 }
}

// Native005C3A86..005C3ACD EH RET4. A counted value parameter is
// assigned into the next12B element's first holder then count1C advances.
// The parameter cleanup and its EH state are generated from its lifetime.
void Rva005C3A37Elem::Add(TreeHintRef00217D4C hint)
{
 reinterpret_cast<TreeHintRef00217D4C &>(members[count++].first)=hint;
}

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheTarget;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *,void *,const char *,const char *);
class Rva005C39C4 { public: TreeHintRef00217D4C rva005C39C4(int); };
class Rva005C3B3EUpdateView { public: virtual void unknown0(); virtual void update(); };
// Native005C3B3E..005C3C0B EH RET0: requested fading dispatches
// FadeOut through the existing AptCall wrapper; each populated source
// holder constructs its missing output through native39C4 then releases
// the source. Existing output handles update through virtualslot1.
void Rva005C3A37Elem::rva005C3B3E()
{
 if(reload) {
  if(active && !pending) {
   Rva00524EF4AptCall(TheTarget,unknown04,name.str(),"FadeOut");
   pending=true;
  }
  reload=false;
 }
 for(int i=0;i<count;++i) {
  Rva005C39DEMember &member=members[i];
  Rva005C3B3EUpdateView *output;
  if(member.middle.ptr && member.first.ptr) {
   output=reinterpret_cast<Rva005C3B3EUpdateView *>(member.last.ptr);
   if(!output) {
    reinterpret_cast<TreeHintRef00217D4C &>(member.last)=
     reinterpret_cast<Rva005C39C4 *>(member.first.ptr)->rva005C39C4((int)member.middle.ptr);
    reinterpret_cast<Rva002BED91 *>(&member.first)->clear();
    output=reinterpret_cast<Rva005C3B3EUpdateView *>(member.last.ptr);
   }
  } else output=reinterpret_cast<Rva005C3B3EUpdateView *>(member.last.ptr);
  if(output) output->update();
 }
}

class Rva005C3C0B {public: void rva005C3C0B(const char *);};
class Rva005C3D5F {public: void rva005C3D5F(const char *);};
struct DelegateDesc {
 void *object;
 void (Rva005C3A37Elem::*method)(const char *);
 template<class T> DelegateDesc(Rva005C3A37Elem *p,void (T::*f)(const char *)):object(p),method(reinterpret_cast<void (Rva005C3A37Elem::*)(const char *)>(f)) {}
 DelegateDesc(Rva005C3A37Elem *p,void (Rva005C3A37Elem::*f)(int)):object(p),method(reinterpret_cast<void (Rva005C3A37Elem::*)(const char *)>(f)) {}
};
// ?AptRef::AptRef present-unmatched (inline delegate adapter; no unique retail body)
template<class T> __forceinline AptRef<T>::AptRef(DelegateDesc d):Rva00579E47(d) {}
__forceinline void AptCommandMapAdder::AddCommandMapBinding(const AsciiString &n,DelegateDesc d) {AddCommandMap(n,d);}
class Rva000B3F84Pair {public: Rva000B3F84Pair() {} Rva000B3F84Pair *init(const char *); const char *ptr; int size;};
struct AsciiStringRef {const AsciiString *m_string;};
struct AsciiStringPlusString : AsciiStringRef {AsciiStringRef m_second;};
struct AsciiStringPlusStringText : AsciiStringPlusString {operator AsciiString(); Rva000B3F84Pair m_right;};
static __forceinline AsciiStringPlusString operator+(const AsciiString &a,const AsciiString &b) {AsciiStringPlusString t;t.m_string=&a;t.m_second.m_string=&b;return t;}
// ?operator+(AsciiStringPlusString,text) present-unmatched (inline; byte-and-relocation fold to existing109CFD owner)
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left,const char *right) {Rva000B3F84Pair text;text.init(right);AsciiStringPlusStringText result;static_cast<AsciiStringPlusString &>(result)=left;result.m_right=text;return result;}
// Native005C3F2C..005C40E7 EH443/RET12; stores opaque owner0 and level4,
// copies supplied AsciiString8, constructs command-map listC and array3x12.
// Default array callback independently equals13B005C39DE; established
// lifecycle/layout and all three registered callback addresses are target facts.
// Prefix and suffix concat pattern follows verified Palantir/HUD siblings.
Rva005C3A37Elem::Rva005C3A37Elem(Rva005C3F02 *p,void *q,void *r)
 :owner(reinterpret_cast<Rva005C3DE1Owner *>(p)),unknown04(q),name(*static_cast<const AsciiString *>(r)),active(false),count(0),pending(false),reload(false)
{
 AsciiString prefix;
 prefix.format("_level%u.",unknown04);
 commands.AddCommandMapBinding(prefix+name+"_OnButtonFrameLoaded",DelegateDesc(this,&Rva005C3C0B::rva005C3C0B));
 commands.AddCommandMapBinding(prefix+name+"_OnButtonFrameUnloaded",DelegateDesc(this,&Rva005C3D5F::rva005C3D5F));
 commands.AddCommandMapBinding(prefix+name+"_OnClosed",DelegateDesc(this,&Rva005C3A37Elem::rva005C3DE1));
}
