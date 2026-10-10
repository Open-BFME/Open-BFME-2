// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Retail 5CDA63..5CDB43: complete 224B constructor, RET16 including the
// compiler virtual-base flag. WorldBuilder 15BFB20 independently names
// PlanningPhaseGarrisonSelection::DetailsPanel::DetailsPanel and records
// this source file at assertions 110..125. Native C75028 slot0 points to
// scalar 5CDB6C / complete destructor 5CD9C0, whose established neutral
// owner and exact shared virtual-base graph are retained here.
// Target observations: owner link from input+10 stored at this+1C; link+C
// points back to this; army+78 holds summary; summary slots40/44 have stride8;
// skip entries with nonzero B8, then add entry ID through the second interface.
// Remaining opaque field and interface names are layout observations rather
// than recovered declarations from the original source.
struct RvaSmallVtableZeroBase { void *m_04; };
class Rva0007DF07 : public RvaSmallVtableZeroBase
{
public:
    Rva0007DF07() { m_04 = 0; }
    virtual ~Rva0007DF07() {}
};
class Rva005CC5E5 : public virtual Rva0007DF07
{
public:
    __declspec(nothrow) Rva005CC5E5();
    virtual void slot0();
    virtual ~Rva005CC5E5() {}
};
class Rva005E3AE1 : public virtual Rva0007DF07
{
public:
    Rva005E3AE1();
    virtual void slot0() = 0;
    virtual ~Rva005E3AE1();
};
struct _Rva005E4AE2In;
class Rva005E4AE2
{
public:
    Rva005E4AE2(void *, _Rva005E4AE2In *, int);
private:
    char storage[0x30];
};
class Rva005E4B9D
{
public:
    Rva005E4B9D(Rva005E4AE2 *v) : value(v) {}
    ~Rva005E4B9D() { clear(); }
    void clear();
    Rva005E4AE2 *value;
};
class Rva005E4F6D : public Rva005CC5E5, public Rva005E3AE1
{
public:
    Rva005E4F6D(_Rva005E4AE2In *, int);
    virtual ~Rva005E4F6D();
    virtual void slot0();
    virtual void slot1();
private:
    Rva005E4B9D child;
};
// The constructor 5E6ED6 calls the 12-byte polymorphic base at 0 and
// Rva005E4F6D at C. Its shared counted base moves to24; the second owned
// pointer at20 is independently cleared in the native102-byte teardown.
class Rva005F64F5
{
public:
    virtual ~Rva005F64F5();
private:
    void *data4;
    void *owned8;
};
class Rva005E6D90
{
public:
    ~Rva005E6D90() { clear(); }
    void clear();
private:
    void *value;
};
class Rva005E6F9D : public Rva005F64F5, public Rva005E4F6D
{
public:
    virtual ~Rva005E6F9D();
private:
    Rva005E6D90 child20;
};




class AsciiString;
namespace StrategicHUD {
class ArmyDetailsMovieClip {public:
    ArmyDetailsMovieClip(int,const AsciiString &,int,bool);
    virtual ~ArmyDetailsMovieClip();
    virtual void notifyBackButtonClicked();
    virtual void notifyIconListBackgroundClicked();
private: class Impl *m_impl;
}; }
class Rva005E54AE:public StrategicHUD::ArmyDetailsMovieClip {public:Rva005E54AE(int,const AsciiString &,bool);virtual ~Rva005E54AE();};
class Rva005E54F7:public Rva005E54AE,public Rva005E4F6D {public:Rva005E54F7(int,const AsciiString &,void*);virtual ~Rva005E54F7();};

class Rva000425C4PtrChaseField { public: int get() const; };
class Rva0040CB2CIndexedField { public: int get(int) const; };
class Rva0040CC0EIndexedField { public: int get(int) const; };
class Rva005E508F { public: void rva005E508F(int); };
struct GarrisonSummarySlot { int id; void *entry; };
struct GarrisonSummary { char prefix[0x40]; GarrisonSummarySlot *begin; GarrisonSummarySlot *end; };
struct GarrisonArmy { char prefix[0x78]; GarrisonSummary *summary; };
struct GarrisonEntry { char prefix[0xB8]; int fieldB8; };
struct Rva005CD9C0Link { char prefix[0xC]; void *owner; };
struct GarrisonPhase { char prefix[0x10]; Rva005CD9C0Link *link; };
class Rva005CD9C0 : public Rva005E54F7 {
public:
    Rva005CD9C0(int, const AsciiString &, void *);
    virtual ~Rva005CD9C0();
private: Rva005CD9C0Link *link1C;
};
Rva005CD9C0::Rva005CD9C0(int level, const AsciiString &name, void *phase)
    : Rva005E54F7(level, name, phase), link1C(static_cast<GarrisonPhase *>(phase)->link)
{
    link1C->owner = this;
    GarrisonArmy *army = reinterpret_cast<GarrisonArmy *>(reinterpret_cast<Rva000425C4PtrChaseField *>(link1C)->get());
    GarrisonSummary *summary = army->summary;
    if (summary) {
        int count = summary->end - summary->begin;
        for (int i = 0; i < count; ++i) {
            GarrisonEntry *entry = reinterpret_cast<GarrisonEntry *>(reinterpret_cast<Rva0040CB2CIndexedField *>(summary)->get(i));
            if (entry->fieldB8 == 0) {
                int id = reinterpret_cast<Rva0040CC0EIndexedField *>(summary)->get(i);
                reinterpret_cast<Rva005E508F *>(static_cast<Rva005CC5E5 *>(this))->rva005E508F(id);
            }
        }
    }
}
