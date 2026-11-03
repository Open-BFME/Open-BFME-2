// Target facts (code addresses are RVAs, tables are VAs): constructor 0x0022C987 calls SubsystemInterface 0x001B4E63, stores 0x00BE74F0 at +0, constructs BitFlags<11> at +0x0C through 0x003B31AD and the list at +0x10 through 0x0035C9A6, then ORs 0x28 at +0x0C. Allocation 0x0022F3F0 pushes 0x14 before new at 0x0022F3F2 and constructor call 0x0022F405, proving sizeof 0x14. Destructor 0x0022C9F6 restores the same table, destroys the list through 0x004EC395 and calls SubsystemInterface 0x001B4E74; its scalar deleting wrapper is 0x0022C9DA. The base's 0x00BD77A0 table is installed during base construction and destruction, not a second AerialPathfinder table.
// Target facts: 0x00BE74F0 has 14 slots, with RVA targets [0022C9DA,000B3FD0,001B5384,000B3FD0,005CB9FF,0047A699,000D43D0,0047A69C,000B3FD0,0022C9D2,000B3FD0,005CB9FF,000B3FD0,0047A69C]; the next stored table begins at 0x00BE7528. Slot 9 at 0x0022C9D2 clears the list at +0x10 through 0x0023DAA5. Slots 4/11 return false with RET 4, 5 returns false, 6 returns zero, 7/13 use RET 4, and 1/3/8/10/12 return immediately. Named inherited slots follow the registered SubsystemInterface contract; the other slots retain neutral names.
// Target facts: base constructor 0x001B4E63 clears byte +4 and the string pointer +8; base destructor 0x001B4E74 destroys AsciiString at +8. Query 0x00375AF7 reads the circular list head at +0x10 and node payload PolygonTrigger* at +8 and float at +0x0C; insertion 0x00375BFF passes the same two-word payload to the list at +0x10. The list constructor 0x0035C9A6 allocates a 0x10-byte sentinel, self-links +0/+4 and stores its pointer at +0. field10 represents that single pointer; the list and flag members' original names are unknown. Method declarations follow the ledger rows at 0x00375A73, 0x00375AF7, 0x00375B7A, 0x00375C28, 0x00375DFF, 0x00375ED7 and 0x0037609C, keeping their bodies out of line.
#pragma once

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Object;
struct Coord3D;
class Rva00375A73Context;
struct Rva00375A73Coord;
class Rva00312C95;

class AerialPathfinder : public SubsystemInterface
{
public:
    AerialPathfinder();
    virtual ~AerialPathfinder();
    virtual void init();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
#endif
    virtual void reset();
    virtual void update();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);
#endif

    bool rva00375A73(Rva00375A73Context *, float, Rva00375A73Coord *);
    float getNoFlyZoneHeight(float, volatile float);
    float rva00375B7A(float, float);
    void rva00375BFF(unsigned int, float);
    bool rva00375C28(Object *, const Coord3D *, float *, Coord3D *);
    bool rva00375DFF(Object *, Rva00375A73Context *, float, float);
    int rva00375ED7(Object *, const Coord3D *, Coord3D *);
    bool computeAerialPath(void *, const Coord3D *, Rva00312C95 *, const unsigned char *, const unsigned char *, bool);

    unsigned int field0C;
    void *field10;
};
