// cl: /O1 /G7 /arch:SSE /MD /EHsc
//
// ??0ExperienceTrackerAutoResolve@@QAE@PAVLivingWorldAutoResolveUnit@@ABVRva004F6093Holder@@@Z, retail 0x005db08f, 113 bytes. Banked partial (score 0.99) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Native5DB08F..5DB100 RET8. WB15C58B0 names the class and base ctor.
// This is a trial of the real hierarchy; destructor/vtable ownership must
// be reconciled with the existing neutral providers before landing.
class ThingTemplate;
class Xfer;
class Overridable;
struct TargetRef00217D4C { virtual void *destroy(unsigned); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct ArmySummaryEntry { char pad[8]; float experience; char rest[0xAC-0x0C]; TargetRef00217D4C reference; };
class Rva004F6093Holder {
public:
    Rva004F6093Holder(const Rva004F6093Holder &);
    ~Rva004F6093Holder() { if (entry) ReleaseTreeHintRef00217D4C(&entry->reference); }
    ArmySummaryEntry *entry;
};
class ExperienceTracker {
public:
    ExperienceTracker(const ThingTemplate *);
    virtual ~ExperienceTracker();
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const=0;
    virtual void xfer(Xfer *);
    virtual void slot4(const Overridable *,bool)=0;
    int rva0039AC23(bool);
protected:
    char pad04[0x10-4]; float experience;
    char pad14[0x34-0x14];
};
class LivingWorldAutoResolveUnit { public: char pad[0x2C]; const ThingTemplate *type; };
class Rva003BD306Target { public: void rva0039B28F(int); };
class Rva005DB004 { public: void rva005DB004(); };
class ExperienceTrackerAutoResolve : public ExperienceTracker {
public:
    ExperienceTrackerAutoResolve(LivingWorldAutoResolveUnit *,const Rva004F6093Holder &);
    virtual ~ExperienceTrackerAutoResolve();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
    virtual void slot4(const Overridable *,bool);
private:
    LivingWorldAutoResolveUnit *parent;
    Rva004F6093Holder entry;
};
ExperienceTrackerAutoResolve::ExperienceTrackerAutoResolve(LivingWorldAutoResolveUnit *unit,const Rva004F6093Holder &source)
    : ExperienceTracker(unit->type),parent(unit),entry(source)
{
    experience=entry.entry->experience;
    int level=rva0039AC23(false);
    if (!level) reinterpret_cast<Rva003BD306Target *>(this)->rva0039B28F(0);
    reinterpret_cast<Rva005DB004 *>(this)->rva005DB004();
}
