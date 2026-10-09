// cl: /Ireference/shims/bfme2_ascii /GX /MD /O1 /G7
// Complete native004ADCE8..004ADD8D RET4; WB1229290 same four callees.
// Mounted module-data field table proves SynchronizeTimerOnSpecialPower +D4.
#include "ascii_string.h"
class SpecialPowerTemplate;
class Rva00493BD4 { public: void rva00493BD4(Rva00493BD4 *); };
class SpecialPowerModuleInterface {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
    virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22();
    virtual Rva00493BD4 *slot23();
};
class Object { public: SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *) const; };
class SpecialPowerStore { public: const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString); };
extern SpecialPowerStore *TheSpecialPowerStore;
struct MountedPowerNames {
    AsciiString *begin,*end,*capacity;
    bool empty() const { return begin==end; }
};
struct MountedTimerModuleDataView { char pad[0xD4]; MountedPowerNames names; };
class Rva004ADCE8 {
public:
    int opaque; MountedTimerModuleDataView *data; Object *owner;
    void rva004ADCE8(const Object *replacement);
};
void Rva004ADCE8::rva004ADCE8(const Object *replacement)
{
    MountedTimerModuleDataView *moduleData=data;
    if (moduleData->names.empty()) return;
    Object *original=owner;
    for (AsciiString *name=moduleData->names.begin;name!=moduleData->names.end;++name) {
        const SpecialPowerTemplate *power=TheSpecialPowerStore->findSpecialPowerTemplate(*name);
        if (!power) continue;
        SpecialPowerModuleInterface *source=original->getSpecialPowerModule(power);
        SpecialPowerModuleInterface *destination=replacement->getSpecialPowerModule(power);
        if (source && destination && source->slot23() && destination->slot23())
            destination->slot23()->rva00493BD4(source->slot23());
    }
}

