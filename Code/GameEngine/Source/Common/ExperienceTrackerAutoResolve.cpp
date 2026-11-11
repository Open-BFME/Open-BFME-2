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
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
#include "../../Include/Common/ArmySummaryEntry.h"
class Rva004F6093Holder {
public:
    Rva004F6093Holder(const Rva004F6093Holder &);
    ~Rva004F6093Holder() { if (entry) ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(static_cast<Rva0007DF07 *>(entry))); }
    ArmySummaryEntry *entry;
};
class ExperienceTracker {
public:
    ExperienceTracker(const ThingTemplate *);
    virtual ~ExperienceTracker();
    virtual void loadPostProcess() = 0;
    virtual const char *GetSnapshotName() const=0;
    virtual void xfer(Xfer *);
    virtual void slot4(const Overridable *,bool)=0;
    int rva0039AC23(bool);
protected:
    char pad04[0x10-4]; float experience;
    char pad14[0x34-0x14];
};
class LivingWorldAutoResolveUnit { public: char pad[0x2C]; const ThingTemplate *type; };
#include "../../Include/GameLogic/Module/Rva003BD306Target.h"
#include "../../Include/Common/Rva005DB004.h"
class ExperienceTrackerAutoResolve : public ExperienceTracker {
public:
    ExperienceTrackerAutoResolve(LivingWorldAutoResolveUnit *,const Rva004F6093Holder &);
    virtual ~ExperienceTrackerAutoResolve();
    virtual const char *GetSnapshotName() const = 0;
    virtual void xfer(Xfer *) = 0;
    virtual void slot4(const Overridable *,bool) = 0;
private:
    LivingWorldAutoResolveUnit *parent;
    Rva004F6093Holder entry;
};
ExperienceTrackerAutoResolve::ExperienceTrackerAutoResolve(LivingWorldAutoResolveUnit *unit,const Rva004F6093Holder &source)
    : ExperienceTracker(unit->type),parent(unit),entry(source)
{
    experience=entry.entry->m_f08;
    int level=rva0039AC23(false);
    if (!level) reinterpret_cast<Rva003BD306Target *>(this)->rva0039B28F(0);
    reinterpret_cast<Rva005DB004 *>(this)->rva005DB004();
}
