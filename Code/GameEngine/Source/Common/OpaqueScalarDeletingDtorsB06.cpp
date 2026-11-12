// cl: /O1 /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /EHsc /Ireference/shims/bfmelist /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// Opaque scalar deleting destructors, batch B06: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner. Each destructor is declared, not defined, so the call
// resolves to its pin in reverse/symbols.csv (address names unless the
// destructor already carried one); the dummy tag constructors (no retail
// counterpart) only make this TU emit each vtable and with it the deleting
// destructor. Owner identities are not recovered, and these declarations
// model no layout (docs/reconstruction/deleting-destructor-identity-audit.md)
// beyond the secondary-base offsets their adjustor thunks prove. The
// wrappers whose classes are known (AptPalantir, GameState, AI, WaterSetting,
// GameMessage, SidesList, LuaScriptEngine, ThingTemplate, AIStateMachine,
// Anim2DCollection) and those whose destructor units emit them (0x0031861B,
// 0x0035ABA4, 0x003604AA) are rowed in the units that define their
// destructors.
//
//   wrapper     dtor        vtable#slot
//   0x002E2CF4  0x002E2AAE  0x00C04B50#0
//   0x0030DE92  0x0030DBD5  0x00C08A2C#0
//   0x0031EB7A  0x0031DCF0  0x00C0CC88#0
//   0x00328CDC  0x00328CF8  0x00C0D8D8#0
//   0x0032A0B2  0x0032989F  0x00C0D8FC#0
//   0x00355BBE  0x00355BDA  0x00C14E14#0
//   0x0035686D  0x003561BE  0x00C14EBC#0
//   0x0035978C  0x00359290  0x00C15398#0
//   0x0036027C  0x003601C5  0x00C16778#0
//   0x00362E73  0x00362CF2  0x00C16FE8#0
//   0x00362E8F  0x00362D6C  0x00C17068#0

typedef bool Bool;
#include "../../../../reference/shims/subsystem_bfme2/subsystem_interface.h"

struct EmitVtableTag;

class Rva0031DCF0 : public SubsystemInterface
{
public:
	Rva0031DCF0(EmitVtableTag *);
public:
	virtual ~Rva0031DCF0();
};

// ?<Rva0031DCF0::Rva0031DCF0> absent-from-retail
Rva0031DCF0::Rva0031DCF0(EmitVtableTag *)
{
}

class __declspec(novtable) Rva00328CF8Base0
{
public:
	virtual ~Rva00328CF8Base0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) in its vtable is target evidence for it.
class __declspec(novtable) Rva00328CF8BaseC
{
public:
	virtual ~Rva00328CF8BaseC();
};
class Rva00328CF8 : public Rva00328CF8Base0, public Rva00328CF8BaseC
{
public:
	Rva00328CF8(EmitVtableTag *);
public:
	virtual ~Rva00328CF8();
};

// ?<Rva00328CF8::Rva00328CF8> absent-from-retail
Rva00328CF8::Rva00328CF8(EmitVtableTag *)
{
}

class DataChunkInput;
struct DataChunkInfo;

class Rva0032989F
{
public:
	Rva0032989F(EmitVtableTag *);
public:
	virtual ~Rva0032989F();
	// Retail vftable 0x00C0D8FC slot 1 (0x00329906, defined in SidesListPlayerScriptsParse.cpp).
	virtual bool rva00329906(DataChunkInput &file, DataChunkInfo *info);
};

// ?<Rva0032989F::Rva0032989F> absent-from-retail
Rva0032989F::Rva0032989F(EmitVtableTag *)
{
}

class __declspec(novtable) Rva00355BDABase0
{
public:
	virtual ~Rva00355BDABase0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x00355BB6 in its vtable is target evidence for it.
class __declspec(novtable) Rva00355BDABaseC
{
public:
	virtual ~Rva00355BDABaseC();
};
class Rva00355BDA : public Rva00355BDABase0, public Rva00355BDABaseC
{
public:
	Rva00355BDA(EmitVtableTag *);
public:
	virtual ~Rva00355BDA();
};

// ?<Rva00355BDA::Rva00355BDA> absent-from-retail
Rva00355BDA::Rva00355BDA(EmitVtableTag *)
{
}

class Rva0035615D
{
public:
	Rva0035615D(EmitVtableTag *);
public:
	virtual ~Rva0035615D();
};

// ?<Rva0035615D::Rva0035615D> absent-from-retail
Rva0035615D::Rva0035615D(EmitVtableTag *)
{
}

class Rva00359290
{
public:
	Rva00359290(EmitVtableTag *);
public:
	virtual ~Rva00359290();
};

// ?<Rva00359290::Rva00359290> absent-from-retail
Rva00359290::Rva00359290(EmitVtableTag *)
{
}

class Rva003601C5
{
public:
	Rva003601C5(EmitVtableTag *);
public:
	virtual ~Rva003601C5();
};

// ?<Rva003601C5::Rva003601C5> absent-from-retail
Rva003601C5::Rva003601C5(EmitVtableTag *)
{
}



// Deleting destructor now emitted by its complete class constructor.



// Deleting destructor now emitted by its complete class constructor.

// AI::reset at 0x002FEB3A..0x002FEBB7. Source lead: GeneralsMD
// GameLogic/AI/AI.cpp at BFME1 donor revision 34f59164f6d1efd413c5fd37f4894ec834c3c0fe.
// Target facts: receiver +0x10 pathfinder; +0x14 group-list sentinel;
// +0x18 override-data head, whose next link is +0x100; +0x1C and +0x20
// are the reset counters. Matched AI::destroyGroup (0x002FE712) supports
// the group list and virtual deleteInstance(0) followed by scalar delete.
// The donor supplies the reset purpose and field roles; the complete AI
// and override-data layouts remain unrecovered. Retail returns at FEBB6,
// followed immediately by the independently pinned destructor FEBB7.
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::erase(list<int, allocator<int> >::iterator);
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
#include "../../Include/GameLogic/AIPathfind.h"
class AIGroup;
struct Rva002FEB3AData
{
    virtual void *deleteInstance(int flags);
    char opaque04[0x100 - 4];
    Rva002FEB3AData *next;
};
class AI
{
public:
    virtual void reset();
    void destroyGroup(AIGroup *);
private:
    char opaque04[0x10 - 4];
    Pathfinder *pathfinder;
    _STL::list<int> groups;
    Rva002FEB3AData *data;
    unsigned int nextGroupID;
    int nextFormationID;
};
void AI::reset()
{
    pathfinder->rva002F462C();
    while (data && data->next)
    {
        Rva002FEB3AData *cur = data;
        data = data->next;
        ::operator delete(cur ? cur->deleteInstance(0) : 0);
    }
    while (groups.size())
    {
        AIGroup *group = reinterpret_cast<AIGroup *>(groups.front());
        if (group)
            destroyGroup(group);
        else
            groups.pop_front();
    }
    nextGroupID = 0;
    nextFormationID = 0;
    ++nextFormationID;
}

// The complete 0x002D62AB..0x002D638E body decrements three flash
// timers (+0x12C, stride 8) and sends changed Boolean states to APT.
// Retail's data table names PlayerMagic, Objectives, PlanningMode. The
// generated event is Set<name>ButtonFlashEffectState, argument _show/_hide.
// Original member identity is unknown; no complete Palantir layout claimed.
#include "ascii_string.h"
#include "../../Include/Common/Rva000B3F84Pair.h"
struct AsciiStringRefWithChar { const AsciiString *m_string; char m_char; };
struct AsciiStringCharPlusText : AsciiStringRefWithChar { Rva000B3F84Pair m_right; };
#include "../../Include/Common/Rva005D2F96S16.h"
struct Rva005D2F96Base24 { int m0, m1, m2, m3, m4, m5; };
struct Rva005D2F96S24 : Rva005D2F96Base24 {};
Rva000B3F84Pair __cdecl Rva00108B93Make(const char *text);
AsciiStringCharPlusText __cdecl operator+(const AsciiStringRefWithChar &, const char *);
Rva005D2F96S24 __cdecl Rva005D2F96Build(const Rva005D2F96S16 &, const char *);
AsciiString __cdecl Rva002D56C3(const Rva005D2F96Base24 &);
class Rva00222A8BTarget;
int __cdecl Rva002D3409Invoke(Rva00222A8BTarget *, void *, const char *, const char *const &);
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
// The flash buttons' window names, retail .rdata 0x008031AC.
extern const char *const g_00C031AC[3] = { "PlayerMagic", "Objectives", "PlanningMode" };
struct Rva002D62ABFlashState { int timer; bool active; };
class Rva002D62AB
{
public:
    void updateButtonFlash();
private:
    char opaque00[0x5C];
    void *owner;
    char opaque60[0x12C - 0x60];
    Rva002D62ABFlashState flash[3];
};
void Rva002D62AB::updateButtonFlash()
{
    const char *const *name = g_00C031AC;
    Rva002D62ABFlashState *state = flash;
    for (; (int)name < (int)(g_00C031AC + 3); ++name, ++state)
    {
        if (state->timer > 0)
            --state->timer;
        bool active = state->timer > 0;
        if (active != state->active)
        {
            const char *argument = active ? "_show" : "_hide";
            Rva002D3409Invoke(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager), owner,
                Rva002D56C3((const Rva005D2F96Base24 &)Rva005D2F96Build(
                    (const Rva005D2F96S16 &)operator+(
                        (const AsciiStringRefWithChar &)Rva00108B93Make("Set"), *name),
                    "ButtonFlashEffectState")).str(), argument);
            state->active = active;
        }
    }
}

// Whole retail 0x002DF2F6..0x002DF3B0: resolve a wide save-file path,
// read metadata, return code 1 when that fails, otherwise dispatch a copied
// available-game record to 0x002DE3C1. ZH GameState::loadGame supplies the
// semantic lead; the record's DF4-byte extent and ownership come from the
// rowed 229811/229840/22D106 constructors and destructor, not ZH's layout.
#include "unicode_string.h"
#include "../../Include/GameClient/TreeHintOpaque0043671B.h"
#include "../../Include/Common/Rva002DC74A.h"
class GameState
{
public:
    bool getSaveGameInfoFromFile(UnicodeString filename, BfmeSubobject0022CE19 *);
    int rva002DE3C1(TreeHintOpaque0043671B gameInfo);
    int rva002DF2F6(const UnicodeString &filename);
};
int GameState::rva002DF2F6(const UnicodeString &filename)
{
    UnicodeString filepath = reinterpret_cast<const Rva002DC74A *>(this)->rva002DC74A(filename);
    TreeHintOpaque0043671B gameInfo;
    gameInfo.m_text = filename;
    gameInfo.m_wordDEC = 0;
    gameInfo.m_wordDF0 = 0;
    if (!getSaveGameInfoFromFile(filepath, &gameInfo.m_subobject))
        return 1;
    return rva002DE3C1(gameInfo);
}

// 0x002D638E..0x002D644C constructs the owner whose matched destructor
// is Rva002D3573 at 0x002D3573. That destructor proves the MI bases,
// vtables and +0x10 owned holder. WB Palantir::Palantir and Impl::Impl are
// source-name leads only. Retail allocates a 0x154-byte implementation after
// loading Apt\\ with the empty AsciiString cell at VA DFF030.
#include "Common/Snapshot.h"

#include "../../Include/Common/Rva000AD6F4.h"
class Rva002D3573 : public SubsystemInterface, public Snapshot
{
public:
    Rva002D3573();
    virtual ~Rva002D3573();
private:
    Rva000AD6F4 holder;
    unsigned int opaque14;
};
class Rva002D57B6
{
public:
    Rva002D57B6(Rva002D3573 *owner, int level);
private:
    char opaque[0x154];
};
class Rva00575674Sub { public: void rva00575674(void *); };
class Rva002D638EMovieSource
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual int load(AsciiString path, AsciiString prefix, int flags, int mode);
};
extern AsciiString g_Va00DFF030;	// the palantir's movie name, defined in AptPalantirConstructor.cpp
void setUiCallbackOwner(void *);
Rva002D3573::Rva002D3573()
{
    int level = reinterpret_cast<Rva002D638EMovieSource *>(g_bfmeAptWindowManager)->load(
        AsciiString("Apt\\"), g_Va00DFF030, 0, 0);
    setUiCallbackOwner(reinterpret_cast<void *>(level));
    reinterpret_cast<Rva00575674Sub *>(&holder)->rva00575674(new Rva002D57B6(this, level));
}

// Complete destructors the deleting destructors above call, bound to the rows at their retail
// addresses (the dtor column of the table at the top of this file).
#pragma comment(linker, "/alternatename:??1Rva00328CF8@@UAE@XZ=??1Rva00328CF8@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva003601C5@@UAE@XZ=?bfmeResetSF@BfmeThingSF@@QAEXXZ")
// Callees bound to their rows at retail's call targets (0x002D57B6, 0x00575674, 0x002D56C3).
#pragma comment(linker, "/alternatename:??0Rva002D57B6@@QAE@PAVRva002D3573@@H@Z=??0AptPalantir@@QAE@PAVRva002D3573@@H@Z")
#pragma comment(linker, "/alternatename:?rva00575674@Rva00575674Sub@@QAEXPAX@Z=?rva00575674@Rva00575674@@QAEXPAVObject@@@Z")
#pragma comment(linker, "/alternatename:?Rva002D56C3@@YA?AVAsciiString@@ABURva005D2F96Base24@@@Z=?Rva002D56C3Construct@@YA?AVAsciiString@@AAVRva002D4688@@@Z")
