// ThingFactory: canonical BFME2 interface. Target facts (code addresses are RVAs; tables are VAs): constructor 0x002D0E14 calls SubsystemInterface 0x001B4E63 at 0x002D0E26 and stores 0x00C0233C at 0x002D0E34; destructor 0x002D0588 restores it at 0x002D0599, frees the database at 0x002D05A6, destroys the +0x14 member at 0x002D05B2 and calls parent 0x001B4E74 at 0x002D05BD. W3D constructor 0x0004CA01 calls 0x002D0E14 then stores 0x00BC4858; W3D destructor 0x0004CA13 restores that derived table before jumping to 0x002D0588. Parent table 0x00BD77A0 belongs to base lifetime. ThingFactory is polymorphic, with a SubsystemInterface base at +0.
// Target facts: allocation 0x00041DA2..0x00041DB8 reserves 0x28 bytes for W3DThingFactory, whose constructor adds only its vptr store. Constructor 0x002D0E3F clears the pointer +0x0C and 0x002D0E4E writes word +0x10=1; 0x002D1BD3 writes its incremented value. Member construction 0x002D0E3A calls 0x002D0C71 on +0x14 and 0x002D0E54 reserves buckets through 0x00212858; member wrapper 0x002D0C86 calls 0x002D0B5A, whose dword clear at 0x002D0B7E reaches factory +0x24, proving extent 0x28; destruction calls 0x002CFF2D. Lookup 0x002D06CA addresses +0x14; 0x002CF1FB reads the head at +0x0C and walks template +0x484 links, comparing word +0x5D8. Zero Hour ThingFactory.h proves m_firstTemplate, m_nextTemplateID and firstTemplate names; the +0x14 container's original concrete type remains unproved and its 0x14-byte storage stays opaque.
// Target facts: table 0x00C0233C has fourteen slots, ending at text 0x00C02374: 0=0x002D09F5 (calls destructor 0x002D0588), 1/8/10/12=0x000B3FD0 (ret), 2=0x001B5384 (SubsystemInterface::loadIniFilesFromLegend), 3=0x002CF5FF (postProcessLoad), 4=0x002CF172 (bool, ret 4), 5=0x002CEF14 (bool, ret), 6=0x000D43D0 (zero, ret), 7/13=0x0047A69C (ret 4), 9=0x002D05CF (reset), 11=0x002CEF6C (true, ret 4). Unnamed overrides retain the parent's neutral signatures. Out-of-line ledger rows prove findTemplate 0x002D06CA, rva002D06AA 0x002D06AA, rva000CEB48 0x000CEB48, newDrawable 0x002CF21B, newObject 0x002D0A23, newOverride 0x002D1AB4, newTemplate 0x002D1B2E, addTemplate 0x002D04A3, freeDatabase 0x002D0469 and parseObjectDefinition 0x002D1C01; findByTemplateID's name is from Zero Hour, its target body remains rowed as Rva002CF1FB.
#ifndef BFME2_THINGFACTORY_H
#define BFME2_THINGFACTORY_H

#if defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#error Include ThingFactory.h before the short SubsystemInterface definition.
#endif
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class ThingTemplate;
class Object;
class Team;
class INI;
struct CreateMask;
enum ObjectID;

class ThingFactory : public SubsystemInterface {
public:
    ThingFactory();
    virtual ~ThingFactory();
    virtual void init() {}
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual void reset();
    virtual void update() {}
    virtual bool vslot11(int);

    const ThingTemplate *firstTemplate() { return m_firstTemplate; }
    const ThingTemplate *findTemplate(const AsciiString &name);
    const ThingTemplate *findByTemplateID(unsigned short id);
    bool rva002D06AA(const AsciiString &name);
    const ThingTemplate *rva000CEB48(const AsciiString &name);
    Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, ObjectID id);
    void *newDrawable(void *tmplate, int statusBits, int randomValue);
    ThingTemplate *newOverride(ThingTemplate *tmplate);
    static void parseObjectDefinition(INI *ini, const AsciiString &name, const AsciiString &reskinFrom, const AsciiString &childOf);

private:
    ThingTemplate *newTemplate(const AsciiString &name);
    void addTemplate(ThingTemplate *tmplate);
    void freeDatabase();
    ThingTemplate *m_firstTemplate;
    unsigned short m_nextTemplateID;
    unsigned int field14[5];
};

extern ThingFactory *TheThingFactory;

#endif
