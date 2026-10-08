// ?initiateMove@LivingWorldArmy@@QAEXABVCoord2D@@PAVRva00318C32Ret@@H@Z
// partial score=0.85 date=2026-10-08
// cl: /O1 /MD /EHsc /arch:SSE /G7 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata /ICode/Libraries/Include/Lib
// stlport
// Target: 0031942B..00319517; WB names UseArmySummary, assertions 691..705.
// This is a target field view, not a claim about the complete army/summary layout.
// Existing address-derived providers retain their ledger spellings.
#include <vector>
class ThingTemplate { public: int rva0033B479() const; };
class Rva00319CED { public: void *rva004E23C1(); char pad00[0x4C]; int source4C; };
struct Rva003F40EFRecord {
    Rva003F40EFRecord &operator=(const Rva003F40EFRecord &);
    char bytes[104];
};
class Rva0040CB2CIndexedField { public: int get(int) const; };
class Rva0037DCA5 { public: void *rva0037DC52(); };
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
class ExperienceLevelStore {
public:
    ExperienceLevelHandle rva00288E21(const ThingTemplate *, int) const;
    bool IsValid(ExperienceLevelHandle) const;
    int GetRequiredExperience(ExperienceLevelHandle) const;
};
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
};
class Rva00318C32Owner { public: int rva00318C32(); };
class Rva003193EC { public: void rva003198B8(Rva003193EC *); };
class ArmySummaryEntry { public: void CancelUpgrades(); };
class Rva004F6093Holder { public: ArmySummaryEntry *entry; };
struct TargetRef00217D4C { void *vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva004F69C3Target { char pad00[0xAC]; TargetRef00217D4C ref; };
struct Rva0040DD3ARef {
    Rva004F69C3Target *value;
    Rva0040DD3ARef(Rva004F69C3Target *p) : value(p) { if(value) ++value->ref.references; }
    Rva0040DD3ARef(const Rva0040DD3ARef &other) : value(other.value) { if(value) ++value->ref.references; }
    ~Rva0040DD3ARef() { if(value) ReleaseTreeHintRef00217D4C(&value->ref); }
};
class Rva002E2903Player;
class Rva002BA8F1Logic { public: Rva002E2903Player *find(int,unsigned int *); };
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002E34A9 { public: void rva002E34A9(const Rva0040DD3ARef &,int); };
class ArmySummary { public: int AddArmyEntry(const Rva004F6093Holder &); Rva0040DD3ARef RemoveEntry(int); };
struct HeroTemplateKindView { char pad00[0x113]; unsigned char kind113; };

#include "Common/Snapshot.h"
#include "Coord2D.h"
class Rva00318C32Ret;
struct TWheelInfo;
class Drawable { public: const TWheelInfo *getWheelInfo() const; };
struct MoveRecordStorage { char bytes[16]; };
struct BfmeVectorRecord00319C84 { char bytes[16]; BfmeVectorRecord00319C84(); BfmeVectorRecord00319C84(const BfmeVectorRecord00319C84 &); };
namespace _STL { template<> vector<BfmeVectorRecord00319C84>::~vector(); }
struct MoveCoordView {
    float x,y;
    MoveCoordView() {}
    MoveCoordView(const Coord2D &pos) : x(pos.x),y(pos.y) {}
};
class Rva00318B5C : public Snapshot {
public:
    Rva00318B5C(const Coord2D &pos,int id) : position(pos),region(id) {}
    Rva00318B5C(int id) : region(id) {}
    virtual ~Rva00318B5C() {}
    virtual void loadPostProcess(); virtual void crc(Xfer *); virtual void xfer(Xfer *);
    MoveCoordView position; int region;
};
struct Rva00319F5A { void rva0031A129(const Rva00318B5C &); };
struct BfmeE16 { char bytes[16]; };
class Rva00538E22 { public: void rva00538F10(const _STL::vector<BfmeE16> &,int); };
class Rva003195C9Owner { public: void rva003195C9(); };
class Rva0020E89C;
class Rva00538CEF { public: Rva0020E89C *rva00538CEF(); };
class Rva003197EEListener {
public: virtual void slot0(void *); virtual void slot1(void *); virtual void slot2(void *); virtual void slot3(void *); virtual void slot4(void *);
};
class Rva003197EEList { public: void forEach(void(Rva003197EEListener::*)(void *),void *); };
struct RegionMoveGroup { int word0,word4,region; Coord2D *start,*finish,*end; };
struct RegionMoveView { char pad00[0x12C]; int region; char pad130[0x1A8-0x130]; _STL::vector<RegionMoveGroup> groups; };
struct QueueCollectionView { _STL::vector<MoveRecordStorage> entries; };
struct MoveArmyView { char pad00[0x3C]; Coord2D destination; };
class LivingWorldArmy {
public:
    void UseArmySummary(Rva00319CED *source);
    void initiateMove(const Coord2D &position, Rva00318C32Ret *target, int flags);
    void KillSummaryEntry(int index);
    void TakeUnitFromArmy_Internal(LivingWorldArmy *source, const Rva004F6093Holder &entry);
    char pad00[0x20];
    int owner20;
    char pad24[0x4C - 0x24];
    int source4C;
    char pad50[4];
    int owner54;
    char pad58[0x78 - 0x58];
    ArmySummaryView *summary78;
};




// ABI view: retail owns an army pointer vector; the existing ModuleData pointer
// instantiation supplies its folded reserve/push/erase calls, not element identity.
class ModuleData;
namespace _STL {
template<> void vector<const ModuleData *>::reserve(unsigned int);
template<> void vector<const ModuleData *>::push_back(const ModuleData * const &);
template<> vector<void *>::iterator vector<void *>::erase(iterator,iterator);
}
class Rva0031A257 {
public: Rva0031A257(); char bytes[0x98];
};
class Xfer {
public:
    struct Version { unsigned char current, minimum; Version(unsigned char a,unsigned char b):current(a),minimum(b){} };
    virtual void slot00();
    virtual bool IsLoading() const;
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual Xfer &xferVersion(Version &);
    virtual void slot11();
    virtual Xfer &xferSnapshot(void *);
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual Xfer &xferInt(int &);
};




void LivingWorldArmy::initiateMove(const Coord2D &position,Rva00318C32Ret *target,int flags)
{
    if (!target) return;
    const TWheelInfo *queue = reinterpret_cast<Drawable *>(this)->getWheelInfo();
    if (!queue) return;
    RegionMoveView *targetView=reinterpret_cast<RegionMoveView *>(target);
    int region=targetView->region;
    Rva00318B5C destination(position,region);
    RegionMoveView *current;
    if (!reinterpret_cast<const QueueCollectionView *>(queue)->entries.empty())
        current=reinterpret_cast<RegionMoveView *>(reinterpret_cast<Rva00318C32Owner *>(this)->rva00318C32());
    else
        current=reinterpret_cast<RegionMoveView *>(const_cast<Rva00538CEF *>(reinterpret_cast<const Rva00538CEF *>(queue))->rva00538CEF());
    _STL::vector<BfmeVectorRecord00319C84> moves;
    if(current) {
        int targetRegion=targetView->region;
        RegionMoveGroup *first=current->groups.begin(),*last=current->groups.end();
        for (;first!=last;++first) if(first->region==targetRegion) break;
        if(first!=last) {
            const Coord2D *point=first->start,*end=first->finish;
            for(;point!=end;++point) {
                Rva00318B5C intermediate(region);
                *reinterpret_cast<Coord2D *>(&intermediate.position) = *point;
                reinterpret_cast<Rva00319F5A *>(&moves)->rva0031A129(intermediate);
            }
        }
    }
    reinterpret_cast<Rva00319F5A *>(&moves)->rva0031A129(destination);
    const_cast<Rva00538E22 *>(reinterpret_cast<const Rva00538E22 *>(queue))->rva00538F10(*reinterpret_cast<_STL::vector<BfmeE16> *>(&moves),flags);
    reinterpret_cast<MoveArmyView *>(this)->destination=position;
    reinterpret_cast<Rva003195C9Owner *>(this)->rva003195C9();
    reinterpret_cast<Rva003197EEList *>(reinterpret_cast<char *>(this)+8)->forEach(&Rva003197EEListener::slot4,this);
}
