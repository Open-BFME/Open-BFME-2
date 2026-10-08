// cl: /O1 /MD /EHsc /arch:SSE /G7 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
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
class ArmySummary { public: int AddArmyEntry(const Rva004F6093Holder &); };
class LivingWorldArmy {
public:
    void UseArmySummary(Rva00319CED *source);
    void TakeUnitFromArmy_Internal(LivingWorldArmy *source, const Rva004F6093Holder &entry);
    char pad00[0x20];
    int owner20;
    char pad24[0x4C - 0x24];
    int source4C;
    char pad50[0x78 - 0x50];
    ArmySummaryView *summary78;
};
void LivingWorldArmy::UseArmySummary(Rva00319CED *source)
{
    if (!TheCampaignManager) return;
    void *summary = source->rva004E23C1();
    if (!summary) return;
    *reinterpret_cast<Rva003F40EFRecord *>(summary78) = *static_cast<Rva003F40EFRecord *>(summary);
    summary78->owner1C = owner20;
    int count = summary78->size();
    for (int i = 0; i < count; ++i) {
        ArmySummaryEntryView *entry = reinterpret_cast<ArmySummaryEntryView *>(reinterpret_cast<Rva0040CB2CIndexedField *>(summary78)->get(i));
        ThingTemplate *thing = static_cast<ThingTemplate *>(reinterpret_cast<Rva0037DCA5 *>(entry)->rva0037DC52());
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
    reinterpret_cast<ArmySummary *>(summary78)->AddArmyEntry(entry);
    if (reinterpret_cast<Rva00318C32Owner *>(this)->rva00318C32() != reinterpret_cast<Rva00318C32Owner *>(source)->rva00318C32())
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
void XferOwningLivingWorldArmyVec(Xfer *xfer, _STL::vector<const ModuleData *> *armies)
{
    Xfer::Version version(1,1);
    xfer->xferVersion(version);
    if (xfer->IsLoading()) {
        _STL::vector<void *> *pointerView = reinterpret_cast<_STL::vector<void *> *>(armies);
        pointerView->erase(pointerView->begin(), pointerView->end());
        int count;
        xfer->xferInt(count);
        armies->reserve(count);
        for (int i=0; i<count; ++i) {
            const ModuleData *army=reinterpret_cast<const ModuleData *>(new Rva0031A257);
            xfer->xferSnapshot(const_cast<ModuleData *>(army));
            armies->push_back(army);
        }
    } else {
        int count=armies->size();
        xfer->xferInt(count);
        for (unsigned int i=0; i<armies->size(); ++i)
            xfer->xferSnapshot(const_cast<ModuleData *>((*armies)[i]));
    }
}
