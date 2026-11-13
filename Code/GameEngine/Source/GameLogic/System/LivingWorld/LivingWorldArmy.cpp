// cl: /O1 /MD /EHsc /arch:SSE /G7 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
// LivingWorldArmy: WB constructor and destructor witnesses, retail 98-byte layout.
// Native ctor/EH and destructor/EH prove Snapshot, listener storage (+8), and
// the two-callback observer (+4) lifetimes. C0C82C/C0C824/C62A20 slots are
// bound below to real owners. Callback and unknown member names remain neutral.
// Scalar/pair wrappers preserve the witnessed initialization scheduling; they
// do not assert EA member type names. Existing provider spellings are retained.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "Coord2D.h"
void Rva00030830FreeAllocation(void*);
#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
class Rva003197EEListener;
namespace _STL {
template<>void allocator<Rva003197EEListener*>::deallocate(pointer p,size_type)const{if(p) Rva00030830FreeAllocation(p);}
template<>__declspec(nothrow) __declspec(noinline) _Vector_base<Rva003197EEListener*,allocator<Rva003197EEListener*> >::_Vector_base(const allocator<Rva003197EEListener*>&a):_M_start(0),_M_finish(0),_M_end_of_storage(a,0){}
}
struct ArmyListenerHeader:public _STL::_Vector_base<Rva003197EEListener*,_STL::allocator<Rva003197EEListener*> > {
 __forceinline ArmyListenerHeader():_STL::_Vector_base<Rva003197EEListener*,_STL::allocator<Rva003197EEListener*> >(_STL::allocator<Rva003197EEListener*>()){}
};

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}
class Rva003FDE1AHelper { public: void rva003FDE1A(int); };

class InGameSimpleHelp
{
public:
    InGameSimpleHelp(const UnicodeString &, const UnicodeString &);
private:
    char opaque[12];
};
#include "../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
// Inline-only storage reference: no imported call or out-of-line COMDAT is emitted.
class Rva003FE0B3 { public: void rva003FE0B3(TreeHintRef00217D4C); };


struct TWheelInfo;
#include "../../../../Include/GameClient/Drawable.h"

struct Elem003AF9E0
{
    virtual ~Elem003AF9E0();
    char opaque04[12];
    Elem003AF9E0();
    Elem003AF9E0(const Elem003AF9E0 &);
    Elem003AF9E0 &operator=(const Elem003AF9E0 &);
};
// Range erase is supplied by its independently rowed native owner.
namespace _STL {
template <> Elem003AF9E0 *vector<Elem003AF9E0, allocator<Elem003AF9E0> >::erase(Elem003AF9E0 *, Elem003AF9E0 *);
}

class Rva0031A02AImpl
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void setState(bool show, int flags);
};
struct Rva0031A02ASummary { char opaque00[0x1C]; int owner; };


#include "../../../../Include/Common/ThingTemplate.h"
#include "../../../../Include/GameLogic/Rva0040CB2CIndexedField.h"
#include "../../../../Include/Common/Rva0037DCA5.h"
class ExperienceLevelList;
class ExperienceLevelIterator {
public:
    ExperienceLevelIterator() {}
    ExperienceLevelIterator(const ExperienceLevelIterator &other) : m_node(other.m_node) {}
private: void *m_node;
};
struct ExperienceLevelHandle {
    ExperienceLevelHandle() {}
    ExperienceLevelHandle(const ExperienceLevelHandle &other) : m_list(other.m_list), m_iter(other.m_iter) {}
    ExperienceLevelList *m_list;
    ExperienceLevelIterator m_iter;
};
#include "../../../../Include/GameLogic/ExperienceLevelStore.h"
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
class Rva00E02D6C;
extern Rva00E02D6C *TheCampaignManager;
struct ArmySummaryEntryView {
    char pad00[8];
    float requiredExperience08;
    int level0C;
    char pad10[0xC0 - 0x10];
    int sourceC0;
};
struct ArmySummaryEntryRefView { void *control; ArmySummaryEntryView *entry; };
struct ArmySummaryView {
    char pad00[0x1C];
    int owner1C;
    char pad20[0x40 - 0x20];
    _STL::vector<ArmySummaryEntryRefView> entries40;
    int size() const { return entries40.size(); }
    int nativeSize() const { const ArmySummaryEntryRefView *last=entries40.end(); return last-entries40.begin(); }
};
class Rva00318C32Ret;
#include "../../../../Include/GameLogic/Rva00318C79Owner.h"
#include "../../../../Include/GameLogic/Rva003193EC.h"
#include "../../../../Include/Common/ArmySummaryEntry.h"
class Rva004F6093Holder { public: ArmySummaryEntry *entry; };

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
#include "../../../../Include/Common/Rva004F69C3Target.h"
struct Rva0040DD3ARef {
    Rva004F69C3Target *value;
    Rva0040DD3ARef(Rva004F69C3Target *p) : value(p) { if(value) ++value->ref.references; }
    Rva0040DD3ARef(const Rva0040DD3ARef &other) : value(other.value) { if(value) ++value->ref.references; }
    ~Rva0040DD3ARef() { if(value) ReleaseTreeHintRef00217D4C(&value->ref); }
};
class Rva002E2903Player;
#include "../../../../Include/GameLogic/Rva002BA8F1Logic.h"
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002E34A9 { public: void rva002E34A9(const Rva0040DD3ARef &,int); };
#include "../../../../Include/GameLogic/ArmySummary.h"
struct HeroTemplateKindView { char pad00[0x113]; unsigned char kind113; };
void __cdecl Rva00030830GameFree(void *);

class Rva003197EEListener
{
public:
 virtual void slot0(void *owner); virtual void slot1(void *); virtual void slot2(void *); virtual void slot3(void *); virtual void slot4(void *);
};

class Rva003197EEList : public ArmyListenerHeader
{
public:
 __declspec(noinline) Rva003197EEList();
 ~Rva003197EEList() {}
 void forEach(void (Rva003197EEListener::*notify)(void *), void *owner);
private:int index;
};
inline Rva003197EEList::Rva003197EEList(){index|=-1;}

// Retail's unwind map tracks three bases in construction order: Snapshot,
// the listener list (+8, null-checked conversion) and this observer (+4,
// table 0x00C0C824 reset to 0x00C62A20); MSVC lays the polymorphic
// observer out before the plain list.
class Rva00319D01ObserverBase
{
public:
	__forceinline ~Rva00319D01ObserverBase() {}
 virtual void rva003191E2(int,int) {}
 virtual void slot1(int,int) {}
};

class CreateAHeroData;
#include "../../../../Include/Common/Rva002B7250.h"

class LivingWorldRegion
{
public:
	void rva003F0FA3(void *army);
 void GetGarrisonArmyPlacementSpot(struct Rva003F0F13Elem*);
};

struct RegionPointerHandleView {
 LivingWorldRegion *value;
 __forceinline LivingWorldRegion *operator->()const {return value;}
};
struct Rva00319D01RegionOwner
{
	unsigned char m_pad00[0x2C];
	_STL::vector<RegionPointerHandleView> m_regions;	// +0x2C
};

struct Rva00319D01RegionHolder
{
	_STL::vector<RegionPointerHandleView> *regions()
	{
		if (m_owner)
			return &m_owner->m_regions;
		return 0;
	}
	unsigned char m_pad00[8];
	Rva00319D01RegionOwner *m_owner;		// +0x08
};

extern LivingWorldLogic *TheLivingWorldLogic;

#include "../../../../Include/Common/Rva000AD6F4.h"
// summary78 owns an ArmySummary.
__forceinline ArmySummaryView *heldSummary(const Rva000AD6F4 &holder) { return static_cast<ArmySummaryView *>(holder.m_ptr); }

class PlayingAudioUnknown0C {public: PlayingAudioUnknown0C(); void *words[2];};
class Rva00538F61
{
public:
 __forceinline Rva00538F61(){ ((PlayingAudioUnknown0C*)this)->PlayingAudioUnknown0C::PlayingAudioUnknown0C(); }
	~Rva00538F61();
private:
	int m_00;
	void *m_04;
};

class Rva00319D01Status
{
public:
	virtual ~Rva00319D01Status();
};

struct BfmeVectorRecord00319C84 { unsigned int words[4]; };
namespace _STL {
template<> vector<BfmeVectorRecord00319C84>::~vector();
}


class Rva00318BEB { public: void rva00318BEB(); };
struct ArmyDestructorLogicView { unsigned char pad00[0x1C]; Rva002B7250 registry1C; unsigned char pad2C[0xB0-0x2C]; Rva00319D01RegionHolder *regionsB0; };

class Rva00318C32Ret;
struct TWheelInfo;
struct Rva00318F42Record {char bytes[16];};
struct Rva00318F42View {Rva00318F42Record *first,*finish,*end;};
struct Rva00318F42Holder {char pad00[0x3C];Rva00318F42View view;};
struct MoveRecordStorage { char bytes[16]; };
struct MoveCoordView {
    float x,y;
    MoveCoordView() {}
    MoveCoordView(const Coord2D &pos) : x(pos.x),y(pos.y) {}
};
class Rva00318B5C;
struct Rva00538E43Result : public Snapshot {
public:
    Rva00538E43Result(const Coord2D &pos,int id) : position(pos),region(id) {}
    Rva00538E43Result(int id) : region(id) {}
    virtual ~Rva00538E43Result() {}
    virtual void loadPostProcess() {}
    virtual const char*GetSnapshotName()const{return "ArmyMoveCommand";}
    virtual void xfer(Xfer *);
    MoveCoordView position; int region;
};
#include "../../../../Include/Common/Rva00319F5A.h"

class Rva00538E22 { public: void rva00538ED1(int); void rva00538F10(const _STL::vector<BfmeE16> &,int); };
#include "../../../../Include/GameLogic/Rva003195C9Owner.h"
class Rva0020E89C;
#include "../../../../Include/Common/Rva00538CEF.h"
struct RegionMoveGroup { int word0,word4,region; Coord2D *start,*finish,*end; };
struct RegionMoveView { char pad00[0x12C]; int region; char pad130[0x1A8-0x130]; _STL::vector<RegionMoveGroup> groups; };
struct QueueCollectionView { _STL::vector<MoveRecordStorage> entries; };
struct MoveArmyView { char pad00[0x3C]; Coord2D destination; };

class Object;
#include "../../../../Include/Common/Rva00575674.h"

struct Rva002BA8F1Listener;
#include "../../../../Include/Common/Rva005A0B4CList.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
struct CtorArmyMinusOneWord { int word; __forceinline CtorArmyMinusOneWord(int v):word(v){_ReadWriteBarrier();} };
struct CtorArmyPair {float x,y; __forceinline CtorArmyPair():x(0),y(0){} };
struct CtorArmyLastPair {float x,y; __forceinline CtorArmyLastPair():x(0),y(0){_ReadWriteBarrier();} };

class SpawnArmy {public: bool rva00319CED(); void *rva004E23C1(); char pad00[4]; AsciiString a04,a08; char pad0C[12]; AsciiString a18; char pad1C[12]; AsciiString a28; char pad2C[24]; float f44; char pad48[4]; int source4C; AsciiString a50; bool b54;};
struct Rva002B6A04Player {char pad00[20];int id14;};
#include "../../../../Include/Common/LivingWorldArmyLine.h"
#include "../../../../Include/Common/Rva00318E8COut.h"
class Rva00318E8C {public:Rva00318E8COut *rva00318E8C(Rva00318E8COut*);};
struct Rva003F0F13Elem {float x,y;};

#include "../../../../Include/Common/Rva002104B6.h"
#include "../../../../Include/GameLogic/Rva00319AA0.h"
class Rva00318F64 {public:void rva00318F64();};

struct CtorArmyScalar {float x;__forceinline CtorArmyScalar(float v):x(v){} };


class Rva00220808; class Rva0040CFC7;
UnicodeString GetArmySummaryName(Rva00220808*);
UnicodeString GetArmySummaryDescription(Rva0040CFC7*,int);
class Rva00319924 {public:void clearFlags();};
#include "../../../../Include/Common/Rva003FE05E.h"
class Rva005392C2 {public:void rva005392C2();};

struct LivingWorldArmy : public Snapshot, public Rva003197EEList, public Rva00319D01ObserverBase {
public:
 void createVisualObjects(const AsciiString*);
    LivingWorldArmy();
 LivingWorldArmy(int,SpawnArmy*,Rva002B6A04Player*);
 __declspec(noinline) virtual ~LivingWorldArmy();
    virtual void rva003191E2(int,int);
    // Native primary table C0C82C has four slots: deleting dtor,
    // presentation/load phase, const name getter319E76, xfer31A6DB.
    virtual const char *GetSnapshotName() const; virtual void xfer(Xfer *); virtual void loadPostProcess();
    void UseArmySummary(SpawnArmy *source);
    void initiateMove(const Coord2D &,Rva00318C32Ret *,int);
    __declspec(noinline) Rva00318F42View *rva00318B83() const;
    void KillSummaryEntry(int index);
    void rva00319EF9(LivingWorldArmy *source,int key);
    void rva00319EA3(LivingWorldArmy *source,ArmySummaryEntry *entry);
    void TakeUnitFromArmy_Internal(LivingWorldArmy *source, const Rva004F6093Holder &entry);
    AsciiString name18,name1C;
    int owner20;
    AsciiString name24,name28;
    CtorArmyMinusOneWord v2C; int v30;
 CtorArmyPair pos34,pos3C,pos44; CtorArmyLastPair pos4C;
    int owner54;
    bool b58,b59;
 CtorArmyScalar f5C;
 int v60; bool b64,b65;
    UnicodeString text68,text6C;
    int v70;bool b74,b75;
    Rva000AD6F4 summary78;
    _STL::vector<BfmeVectorRecord00319C84> records7C;
    Rva00319D01Status *status88;
    int v8C;
    Rva00538F61 member90;
};
typedef char LivingWorldArmyExtentCheck[(sizeof(LivingWorldArmy)==0x98)?1:-1];

LivingWorldArmy::LivingWorldArmy(): v2C(-1),v30(0),owner54(-1),b58(true),b59(false),f5C(0),v60(1),b64(false),b65(false),v70(-1),b74(false),b75(false),status88(0),v8C(0) {
 ((Rva00575674*)&summary78)->rva00575674((Object*)new ArmySummary);
 ((Rva005A0B4CList*)((char*)TheLivingWorldLogic+0x1C))->append((Rva002BA8F1Listener*)(Rva00319D01ObserverBase*)this);
}

LivingWorldArmy::LivingWorldArmy(int owner,SpawnArmy *desc,Rva002B6A04Player *player):name18(desc->a50),name1C(desc->a18),name24(desc->a04),name28(desc->a08),v2C(-1),v30(0),owner54(-1),b58(true),b59(false),f5C(desc->f44),v60(1),b64(false),b65(false),v70(-1),b74(desc->b54),b75(false),status88(0),v8C(0) {
 _ReadWriteBarrier();
 owner20=owner;
 if(player)owner54=player->id14;
 if(!b74)((LivingWorldArmyLine*)&member90)->rva00539141();
 ((Rva00575674*)&summary78)->rva00575674((Object*)new ArmySummary);
 if(desc->rva00319CED())((LivingWorldArmy*)this)->UseArmySummary(desc);
 ((ArmySummaryView*)heldSummary(summary78))->owner1C=owner;
 ((AsciiString*)((char*)heldSummary(summary78)+0x20))->setCopyInline(name28);
 createVisualObjects(&desc->a04);
 ((Rva003193EC*)this)->rva003190E7(false);
 if(desc->a28.isEmpty()) {
  Rva00318E8COut pos;
  ((Rva00319AA0*)this)->rva00319AA0((Coord2D*)((Rva00318E8C*)desc)->rva00318E8C(&pos));
 } else {
  Rva002104B6 *store=(Rva002104B6*)*(void**)((char*)TheLivingWorldLogic+0xB0);
  _ReadWriteBarrier();
  LivingWorldRegion *region=(LivingWorldRegion*)store->rva002104B6(&desc->a28);
  Rva00318E8COut pos;
  ((Rva00318E8C*)desc)->rva00318E8C(&pos);
  if(region)region->GetGarrisonArmyPlacementSpot((Rva003F0F13Elem*)&pos);
  ((Rva00319AA0*)this)->rva00319AA0((Coord2D*)&pos);
 }
 ((Rva00318F64*)this)->rva00318F64();v30=0;
 ((Rva005A0B4CList*)((char*)TheLivingWorldLogic+0x1C))->append((Rva002BA8F1Listener*)(Rva00319D01ObserverBase*)this);
}


void LivingWorldArmy::UseArmySummary(SpawnArmy *source)
{
    if (!TheCampaignManager) return;
    void *summary = source->rva004E23C1();
    if (!summary) return;
    *reinterpret_cast<ArmySummary *>(heldSummary(summary78)) = *static_cast<ArmySummary *>(summary);
    heldSummary(summary78)->owner1C = owner20;
    int count = heldSummary(summary78)->size();
    for (int i = 0; i < count; ++i) {
        ArmySummaryEntryView *entry = reinterpret_cast<ArmySummaryEntryView *>(reinterpret_cast<Rva0040CB2CIndexedField *>(heldSummary(summary78))->get(i));
        ThingTemplate *thing = static_cast<ThingTemplate *>(reinterpret_cast<Rva0037DCA5 *>(entry)->GetThingTemplate());
        if (!thing) continue;
        int level = thing->rva0033B479();
        entry->level0C = level;
        ExperienceLevelHandle handle = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->rva00288E21(thing, level);
        if (reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->IsValid(handle))
            entry->requiredExperience08 = static_cast<float>(reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetRequiredExperience(handle));
        entry->sourceC0 = source->source4C;
    }
}

void LivingWorldArmy::TakeUnitFromArmy_Internal(LivingWorldArmy *source, const Rva004F6093Holder &entry)
{
    reinterpret_cast<ArmySummary *>(heldSummary(summary78))->AddArmyEntry(entry);
    if (reinterpret_cast<Rva00318C79Owner *>(this)->rva00318C32() != reinterpret_cast<Rva00318C79Owner *>(source)->rva00318C32())
        entry.entry->CancelUpgrades();
    reinterpret_cast<Rva003193EC *>(this)->rva003198B8(reinterpret_cast<Rva003193EC *>(source));
}

// ABI view: retail owns an army pointer vector; the existing ModuleData pointer
// instantiation supplies its folded reserve/push/erase calls, not element identity.
class ModuleData;
namespace _STL {
template<> void vector<const ModuleData *>::reserve(unsigned int);
template<> void vector<const ModuleData *>::push_back(const ModuleData * const &);
template<> vector<void *>::iterator vector<void *>::erase(iterator,iterator);
}

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"
class Xfer::Version { public: unsigned char current, minimum; Version(unsigned char a,unsigned char b):current(a),minimum(b){} };
void XferOwningLivingWorldArmyVec(Xfer *xfer, _STL::vector<const ModuleData *> *armies)
{
    Xfer::Version version(1,1);
    (*xfer == version);
    if (xfer->IsLoading()) {
        _STL::vector<void *> *pointerView = reinterpret_cast<_STL::vector<void *> *>(armies);
        pointerView->erase(pointerView->begin(), pointerView->end());
        int count;
        (*xfer == count);
        armies->reserve(count);
        for (int i=0; i<count; ++i) {
            const ModuleData *army=reinterpret_cast<const ModuleData *>(new LivingWorldArmy);
            (*xfer == *reinterpret_cast<Snapshot *>(const_cast<ModuleData *>(army)));
            armies->push_back(army);
        }
    } else {
        int count=armies->size();
        (*xfer == count);
        for (unsigned int i=0; i<armies->size(); ++i)
            (*xfer == *reinterpret_cast<Snapshot *>(const_cast<ModuleData *>((*armies)[i])));
    }
}

void LivingWorldArmy::KillSummaryEntry(int index)
{
    if (index < 0) return;
    Rva0040DD3ARef entry(reinterpret_cast<Rva004F69C3Target *>(reinterpret_cast<Rva0040CB2CIndexedField *>(heldSummary(summary78))->get(index)));
    void *thing = reinterpret_cast<Rva0037DCA5 *>(entry.value)->GetThingTemplate();
    if (thing && (static_cast<HeroTemplateKindView *>(thing)->kind113 & 4)) {
        Rva002E2903Player *player = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(owner54,0);
        if (!player) return;
        reinterpret_cast<Rva002E34A9 *>(player)->rva002E34A9(entry,1);
    }
    reinterpret_cast<ArmySummary *>(heldSummary(summary78))->RemoveEntry(index);
}

// Native319EF9..319F4F owns the returned reference through the transfer.
void LivingWorldArmy::rva00319EF9(LivingWorldArmy *source,int key)
{
 LivingWorldArmy *from=(source?source:source);
 Rva0040DD3ARef entry=reinterpret_cast<ArmySummary *>(heldSummary(from->summary78))->rva0040E672(key);
 TakeUnitFromArmy_Internal(from,*reinterpret_cast<const Rva004F6093Holder *>(&entry));
}

// Native319EA3..319EF9 is the owning transfer twin: the established50B
// pointer lookup40E6A4 replaces the integer-key lookup40E672. WB102B780
// confirms the common TakeUnitFromArmy_Internal and reference cleanup chain;
// the original wrapper name remains unknown.
void LivingWorldArmy::rva00319EA3(LivingWorldArmy *source,ArmySummaryEntry *entryToTake)
{
 LivingWorldArmy *from=(source?source:source);
 Rva0040DD3ARef entry=reinterpret_cast<ArmySummary *>(heldSummary(from->summary78))->rva0040E6A4(entryToTake);
 TakeUnitFromArmy_Internal(from,*reinterpret_cast<const Rva004F6093Holder *>(&entry));
}

// Native319D01..319E76 RET0; WB102A540 names the army destructor.
// Target fields and twelve-state unwind map establish the base/member order.
// The region span contains four-byte pointer handles; their accessor adds no
// ownership operation. Observer base has two callbacks and no virtual dtor.
LivingWorldArmy::~LivingWorldArmy()
{
	forEach(&Rva003197EEListener::slot0, this);
	reinterpret_cast<Rva00318BEB *>(this)->rva00318BEB();
	if (reinterpret_cast<ArmyDestructorLogicView *>(TheLivingWorldLogic)->regionsB0)
	{
		_STL::vector<RegionPointerHandleView> *regions = reinterpret_cast<ArmyDestructorLogicView *>(TheLivingWorldLogic)->regionsB0->regions();
		if (regions)
		{
			for (unsigned int i = 0; i < regions->size(); ++i)
				(*regions)[i]->rva003F0FA3(this);
		}
	}
	::delete status88;
	for (int i = heldSummary(summary78)->nativeSize() - 1; i >= 0; --i)
		KillSummaryEntry(i);
	reinterpret_cast<ArmyDestructorLogicView *>(TheLivingWorldLogic)->registry1C.rva002B7250(
		reinterpret_cast<CreateAHeroData *>(static_cast<Rva00319D01ObserverBase *>(this)));
}

// Native17B318B83: nullable +88 presentation holder exposes its +3C queue.
// The original getter name is unknown; the army receiver is witnessed by
// WB102ABC0 and this file's native movement entry. Same physical contract as
// the existing Rva00318F42 view; the body stays visible to preserve ECX.
Rva00318F42View *LivingWorldArmy::rva00318B83() const {
    return status88 ? &reinterpret_cast<Rva00318F42Holder *>(status88)->view : 0;
}

// WB102ABC0 initiateMove; complete native31A591..31A6DB RET12.
// Record vtable targets use the existing Rva00538E43Result provider.
void LivingWorldArmy::initiateMove(const Coord2D &position,Rva00318C32Ret *target,int flags)
{
    if (!target) return;
    const TWheelInfo *queue = reinterpret_cast<const TWheelInfo *>(rva00318B83());
    if (!queue) return;
    RegionMoveView *targetView=reinterpret_cast<RegionMoveView *>(target);
    int region=targetView->region;
    Rva00538E43Result destination(position,region);
    RegionMoveView *current;
    if (!(reinterpret_cast<const QueueCollectionView *>(queue)->entries.size()>0))
        current=reinterpret_cast<RegionMoveView *>(reinterpret_cast<Rva00318C79Owner *>(this)->rva00318C32());
    else
        current=reinterpret_cast<RegionMoveView *>(const_cast<Rva00538CEF *>(reinterpret_cast<const Rva00538CEF *>(queue))->rva00538CEF());
    _STL::vector<BfmeVectorRecord00319C84> moves;
    if(current) {
        int targetRegion=targetView->region;
        _STL::vector<RegionMoveGroup> *groups=&current->groups;
        _ReadWriteBarrier();
        RegionMoveGroup *first=groups->begin(),*last=groups->end();
        for(;first!=last;++first) {
            if(first->region==targetRegion) {
                const Coord2D *point=first->start,*end=first->finish;
                for(;point!=end;++point) {
                    Rva00538E43Result intermediate(region);
                    *reinterpret_cast<Coord2D *>(&intermediate.position)=*point;
                    reinterpret_cast<Rva00319F5A *>(&moves)->rva0031A129(reinterpret_cast<const Rva00318B5C&>(intermediate));
                }
                break;
            }
        }
    }
    reinterpret_cast<Rva00319F5A *>(&moves)->rva0031A129(reinterpret_cast<const Rva00318B5C&>(destination));
    const_cast<Rva00538E22 *>(reinterpret_cast<const Rva00538E22 *>(queue))->rva00538F10(*reinterpret_cast<_STL::vector<BfmeE16> *>(&moves),flags);
    reinterpret_cast<MoveArmyView *>(this)->destination=position;
    reinterpret_cast<Rva003195C9Owner *>(this)->rva003195C9();
    reinterpret_cast<Rva003197EEList *>(reinterpret_cast<char *>(this)+8)->forEach(&Rva003197EEListener::slot4,this);
}

void LivingWorldArmy::rva003191E2(int mode, int keepPresentation)
{
	switch (mode)
	{
	case 0:
		((Rva003193EC*)this)->rva003191B1();
		((ArmySummary*)heldSummary(summary78))->rva0040CC8F();
		((Rva003193EC*)this)->rva003190E7(true);
		break;
	case 1:
		((Rva00319924 *)this)->clearFlags();
		break;
	}
	if (keepPresentation == 0 && status88 != 0)
	{
		((Rva003193EC*)this)->rva003190E7(true);
		((Rva003FE05E*)status88)->rva003FE05E();
		text68 = GetArmySummaryName((Rva00220808 *)heldSummary(summary78));
		Rva0040CFC7 *army = (Rva0040CFC7 *)heldSummary(summary78);
		text6C = GetArmySummaryDescription(army, 1);
		((Rva005392C2 *)status88)->rva005392C2();
	}
}

void LivingWorldArmy::loadPostProcess()
{
    createVisualObjects(&name24);
    if (v70 != -1)
    {
        if (status88)
        {
            reinterpret_cast<Rva003FDE1AHelper *>(status88)->rva003FDE1A(v70);
            ((Rva0031A02AImpl*)status88)->setState(b65, 0);
            reinterpret_cast<Rva003FE0B3 *>(status88)->rva003FE0B3(
                TreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(new InGameSimpleHelp(text68, text6C))));
        }
    }
    else
        reinterpret_cast<Rva003193EC *>(this)->rva003190E7(true);
    if (!b74)
        ((LivingWorldArmyLine*)&member90)->rva00539141();
    reinterpret_cast<Rva00319AA0 *>(this)->rva00319AA0((const Coord2D*)&pos44);
    Rva0031A02ASummary *currentSummary = *(Rva0031A02ASummary *volatile *)&summary78.m_ptr;
    currentSummary->owner = *(volatile int*)&owner20;
    Rva00538E22 *wheel = reinterpret_cast<Rva00538E22 *>(const_cast<TWheelInfo *>(
        reinterpret_cast<const Drawable *>(this)->getWheelInfo()));
    if (wheel)
    {
        wheel->rva00538ED1(0);
        wheel->rva00538F10(reinterpret_cast<const _STL::vector<BfmeE16> &>(records7C), 0);
        _STL::vector<Elem003AF9E0> &pending = reinterpret_cast<_STL::vector<Elem003AF9E0>&>(records7C);
        pending.erase(pending.begin(), pending.end());
    }
    if (!b74)
        reinterpret_cast<Rva003195C9Owner *>(this)->rva003195C9();
}

const char *LivingWorldArmy::GetSnapshotName()const{return "LivingWorldArmy";}
