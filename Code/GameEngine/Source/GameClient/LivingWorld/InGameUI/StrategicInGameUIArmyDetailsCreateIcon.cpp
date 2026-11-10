// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native 0x005E4CA3..0x005E4DAF, WB015F8020 CreateIcon, source line489.
// The returned four-byte counted reference retains its existing SBServer ABI
// spelling; no GameSpy role is asserted. Target icon constructors establish
// the +10/+1C reference views and shared virtual-base adjustment.
// Keep reference assignment bodies visible: even when called out of line,
// their no-escape behavior preserves the local reference in ESI across copy.
// The setter receiver is a typed view at offset zero in the shared base.
// No original class relationship is inferred from that view decomposition.
#include "../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct SBServer {
 void *m_handle;
 SBServer():m_handle(0){}
 // Retail's copy (0x005E3B2D, stlport_map_int_sbserver.cpp) spelled the same way.
 inline __declspec(noinline) SBServer(const SBServer &src) {void *handle=src.m_handle; m_handle=handle; if(handle!=0){void *slot=*(void **)handle; char *obj=(char *)((void **)slot)[1]+(unsigned int)handle; ++*(int *)(obj+4);}}
 ~SBServer(){if(m_handle)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)m_handle+((int **)m_handle)[0][1]));}
 SBServer &operator=(const SBServer &);
 void Rva005E3B9E();
 void Rva005E3E8A(void *);
};
#include <map>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> SBServer & map<int, SBServer, less<int>, allocator<pair<int const, SBServer> > >::operator[](int const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, SBServer>, _Nonconst_traits<pair<int const, SBServer> > >, bool> _Rb_tree<int, pair<int const, SBServer>, _Select1st<pair<int const, SBServer> >, less<int>, allocator<pair<int const, SBServer> > >::insert_unique(pair<int const, SBServer> const &); }
// bfme link decl-only end


// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
class Rva005F22D2 { public: void rva005F2295(int); };
class ArmySummary;
struct Rva005E4300Entry;
#include "../../../../Include/Common/ArmySummaryEntry.h"
struct Rva005E3967Template;
class ThingTemplate;
#include "../../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;
namespace StrategicInGameUI {
static __declspec(noinline) Rva005E3967Template *Rva005E3967(const Rva005E4300Entry *e) {
 return (Rva005E3967Template *)TheThingFactory->findTemplate(*(const AsciiString *)((const char *)e+4));
}}
class Rva005F3F73
{
public:
	Rva005F3F73(void *, void *) throw();
private:
	char storage[0x18];
};

#include "../../../../Include/Common/Rva005F4096.h"

class Rva005F3F41Outer {public:virtual ~Rva005F3F41Outer(){} void set(unsigned char);};
class Rva005F4179Base:public Rva005F3F41Outer
{
public:
	Rva005F4179Base() : m_04(0) {}
	virtual ~Rva005F4179Base() {}
protected:
	int m_04;
};

class ArmyHeroIconMovieClip;

class Rva005F4179 : public Rva005F4179Base
{
public:
	Rva005F4179(void *clip);
	virtual ~Rva005F4179();
	virtual void DoUpdate();
	virtual void CreateMovieClip(ArmyHeroIconMovieClip *);
	virtual void rva005F4254();
private:
	Rva005F4096 m_08;
};

struct Rva005F38D8Ref
{
	void *m_ptr;
	~Rva005F38D8Ref();
};

class Rva005F38D8
{
public:
	Rva005F38D8Ref rva005F38D8(int position);
	void *unknown00;
	void *implementation;
};

struct Rva005E39F3Arg
{
	char m_pad[0x10];
	void *m_10;
	char m_pad14[0x4];
	Rva005F38D8 *m_18;
};

class Rva005E39F3 : public virtual Rva005F4179
{
public:
	Rva005E39F3(Rva005E39F3Arg *arg, void *clip, int count);
	virtual void DoUpdate();
private:
	Rva005E39F3Arg *m_04;
	int m_08;
	Rva005F38D8Ref m_0c;
};

class ArmyHeroIconMovieClip;

namespace StrategicInGameUI
{
class ArmyHeroIcon : public virtual Rva005F4179
{
public:
	ArmyHeroIcon(void *owner, void *clip, void *entry);
	virtual ~ArmyHeroIcon();
	virtual void DoUpdate();
	virtual void CreateMovieClip(ArmyHeroIconMovieClip *);
	virtual void rva005F4254();
private:
	void *m_owner;
	void *m_hero;
	void *m_clip;
};
}

// ArmyDetailsPanel icon ctor family member 2: retail 0x005E3BD5 (146B,
// RET 0x14). ArmyHeroIcon base at +0, virtual Rva005E39F3 at +0x10 and the
// shared virtual Rva005F4179 base at +0x24 (vtordisp +0x20). The ctor
// constructs the shared virtual base first, then the ArmyHeroIcon base from
// the arg's +0x10 owner, then the icon base.
class Rva005E3BD5 : public StrategicInGameUI::ArmyHeroIcon, public Rva005E39F3
{
public:
	Rva005E3BD5(Rva005E39F3Arg *arg, void *clip, int count, void *entry);
	virtual void DoUpdate();
};


struct UnitView;
namespace StrategicInGameUI {
class ArmyUnitIcon:public virtual Rva005F4179 {
public:
 ArmyUnitIcon(void*,void*,UnitView*);
 virtual ~ArmyUnitIcon();
 virtual void DoUpdate();
private:char storage[0x18];
};
}
class Rva005E3C90:public StrategicInGameUI::ArmyUnitIcon,public Rva005E39F3 {
public:
 Rva005E3C90(Rva005E39F3Arg*,void*,int,UnitView*);
 virtual void DoUpdate();
};
class Rva005F2278 {public:bool rva005F2278(int) const;};

namespace StrategicInGameUI {
class ArmyDetailsPanel {
public:
 class Impl {
 public:
  virtual void OnRemovingEntryFromArmySummary(const ArmySummary &,int);
  SBServer CreateIcon(int,ArmySummaryEntry *);
 private:
  char prefix[0xC-4]; void *clip;void *army;Rva005F22D2 *selected; char gap[4];
  _STL::map<int,SBServer> icons; int selectedID;
 };
};
}
SBServer StrategicInGameUI::ArmyDetailsPanel::Impl::CreateIcon(int entryID,ArmySummaryEntry *entry) {
 SBServer icon;
 const ThingTemplate *type=(const ThingTemplate *)StrategicInGameUI::Rva005E3967((const Rva005E4300Entry *)entry);

 if(*(const unsigned int *)((const char *)type+0x110)&(1u<<26)) {
  Rva005E3BD5 *p=new Rva005E3BD5((Rva005E39F3Arg *)this,clip,entryID,entry);
  icon.Rva005E3E8A(static_cast<Rva005E39F3 *>(p));
 } else {
  Rva005E3C90 *p=new Rva005E3C90((Rva005E39F3Arg *)this,clip,entryID,(UnitView *)entry);
  icon.Rva005E3E8A(static_cast<Rva005E39F3 *>(p));
 }

 icons[entryID]=icon;
 if(((Rva005F2278 *)selected)->rva005F2278(entryID)) {
  ((Rva005E39F3 *)icon.m_handle)->set(1);
 }
 return icon;
}

inline __declspec(noinline) void SBServer::Rva005E3B9E()
{
    void *handle = m_handle;
    if (handle != 0) {
        void *slot = *(void **)handle;
        char *obj = (char *)((void **)slot)[1] + (unsigned int)handle;
        ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)obj);
        m_handle = 0;
    }
}

inline __declspec(noinline) void SBServer::Rva005E3E8A(void *newHandle)
{
    if (newHandle != m_handle) {
        Rva005E3B9E();
        m_handle = newHandle;
        if (newHandle != 0) {
            void *slot = *(void **)newHandle;
            char *obj = (char *)((void **)slot)[1] + (unsigned int)newHandle;
            ++*(int *)(obj + 4);
        }
    }
}

inline __declspec(noinline) SBServer &SBServer::operator=(const SBServer &src)
{
    if (this != &src) {
        void *shandle = src.m_handle;
        if (shandle != 0) {
            void *slot = *(void **)shandle;
            char *obj = (char *)((void **)slot)[1] + (unsigned int)shandle;
            ++*(int *)(obj + 4);
        }
        void *h = m_handle;
        if (h != 0) {
            void *slot2 = *(void **)h;
            char *obj2 = (char *)((void **)slot2)[1] + (unsigned int)h;
            ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)obj2);
        }
        m_handle = src.m_handle;
    }
    return *this;
}

