// Target facts (code addresses are RVAs; table addresses are VAs):
// Factory 0x0024E525 allocates 0x3E8 at 0x0024E530 and calls constructor 0x0049A7F3 at 0x0024E54F. That constructor calls AIUpdateInterface (0x0026E9BD) at 0x0049A80A; its registered extent is 0x3E4. The only additional storage is a four-byte interface at +0x3E4. Worker constructor 0x0049AD15 calls HordeAIUpdate at 0x0049AD2C and begins its fields at +0x3E8 (0x0049AD5F).
// Constructor 0x0049A819 installs the 20-purecall table 0x00C52EE8 at +0x3E4, as does the interface-only constructor 0x0049A642. Store 0x0049A848 replaces it with the class's 20-slot table 0x00C50868. The pure table is an interface construction state, not a competing HordeAIUpdate table or proof of the SupplyTruckAIInterface name; the interface name below describes its offset. It has no virtual destructor.
// Stores 0x0049A826..0x0049A848 install 0x00C505F8/+0, 0x00C50538/+0x0C, 0x00C5052C/+0x10, 0x00C50528/+0x20, 0x00C52F88/+0x24 and 0x00C50868/+0x3E4. Destructor 0x0049A64B restores all six at 0x0049A64B..0x0049A66D, then jumps to AIUpdateInterface's destructor at 0x0049A677. Primary slot 0 is deleting destructor 0x0049A864, which calls 0x0049A64B at 0x0049A867.
// Primary table 0x00C505F8 has the parent's 154 slots. Its changed slots are 0 (destructor), 1 (0x0049A7EE, forwarding to parent's loadPostProcess 0x002686A4), 2 (0x0049A6C1, Snapshot name literal "HordeAIUpdate" at 0x00BF5440), 3 (shared xfer 0x0049060D), 4 (getModuleNameKey 0x0049A67C), 13 (privateMoveToPosition 0x0049A93B) and 23 (bfmePrivateCommand42 0x0049AC5F). The +0x0C table has 47 slots; only slot 22 changes, to 0x0049A6C7, returning the +0x3E4 interface. The +0x10 and +0x20 tables override update (0x0049AB10, receiver -0x10) and aiDoCommand (0x0049A9A9, receiver -0x20); the six-slot +0x24 table is unchanged.
// Table 0x00C50868 occupies exactly 20 words before the next stored table 0x00C508B8. Slots 0, 1, 5 and 12 are the rowed isClearToApproach (0x0049A880), reserveApproachPosition (0x0049A8A1), getEnterPosition (0x0049A8FA) and rva0049A973 (0x0049A973). These bodies read the owner at receiver-0x3DC, proving their +0x3E4 receiver. Slot 12 is at 0x00C50898.
// Remaining +0x3E4 slots have neutral names: slot 2 is true/ret12 (0x0049A6D7); 3 is true/ret4 (0x005CB9FA); 4 is false/ret8 (0x0050B5F1); 6 and 7 tail-jump to slot 5 (0x005CB26F); 8..11, 13, 15 and 17 are ret4 (0x0047A69C); 14 and 18 are true/ret (0x0050B5C6); 16 is false/ret4 (0x005CB9FF); 19 is false/ret (0x0047A699). Unsigned parameters represent unknown stack words. The slot-6/7 forwarding declarations use slot 5's rowed signature.
// The ledger also names out-of-line commandCancelsPorcupineFormation (0x0049A6DC), porcupineFormationIgnoresCommand (0x0049A76C), instance factory 0x0024E525 and data factory 0x002541A3. No retail row or registered Snapshot identity identifies HordeAIUpdate with another registered class.
#pragma once
#ifndef __BFME2_HORDEAIUPDATE_H_
#define __BFME2_HORDEAIUPDATE_H_

#include "AIUpdate.h"

class INI;

class HordeAIUpdate3E4
{
public:
    virtual bool isClearToApproach(int) = 0;
    virtual bool reserveApproachPosition(int, Coord3D *, int *) = 0;
    virtual bool vslot3E4_02(unsigned int, unsigned int, unsigned int) = 0;
    virtual bool vslot3E4_03(unsigned int) = 0;
    virtual bool vslot3E4_04(unsigned int, unsigned int) = 0;
    virtual void getEnterPosition(int, Coord3D *) = 0;
    virtual void vslot3E4_06(int, Coord3D *) = 0;
    virtual void vslot3E4_07(int, Coord3D *) = 0;
    virtual void vslot3E4_08(unsigned int) = 0;
    virtual void vslot3E4_09(unsigned int) = 0;
    virtual void vslot3E4_10(unsigned int) = 0;
    virtual void vslot3E4_11(unsigned int) = 0;
    virtual bool rva0049A973(Object *, int) = 0;
    virtual void vslot3E4_13(unsigned int) = 0;
    virtual bool vslot3E4_14() = 0;
    virtual void vslot3E4_15(unsigned int) = 0;
    virtual bool vslot3E4_16(unsigned int) = 0;
    virtual void vslot3E4_17(unsigned int) = 0;
    virtual bool vslot3E4_18() = 0;
    virtual bool vslot3E4_19() = 0;
};

class HordeAIUpdate : public AIUpdateInterface, public HordeAIUpdate3E4
{
public:
    HordeAIUpdate(Thing *, const ModuleData *);
    virtual ~HordeAIUpdate();
    virtual NameKeyType getModuleNameKey() const;
    virtual UpdateSleepTime update();
    virtual void aiDoCommand(const AICommandParms *);
    virtual bool isClearToApproach(int);
    virtual bool reserveApproachPosition(int, Coord3D *, int *);
    virtual void getEnterPosition(int, Coord3D *);
    virtual bool rva0049A973(Object *, int);
    bool commandCancelsPorcupineFormation(const AICommandParms *);
    bool porcupineFormationIgnoresCommand(const AICommandParms *);
    static Module *friend_newModuleInstance(Thing *, const ModuleData *);
    static ModuleData *friend_newModuleData(INI *);

    virtual bool vslot3E4_02(unsigned int, unsigned int, unsigned int) { return true; }
    virtual bool vslot3E4_03(unsigned int) { return true; }
    virtual bool vslot3E4_04(unsigned int, unsigned int) { return false; }
    virtual void vslot3E4_06(int a, Coord3D *out) { getEnterPosition(a, out); }
    virtual void vslot3E4_07(int a, Coord3D *out) { getEnterPosition(a, out); }
    virtual void vslot3E4_08(unsigned int) {}
    virtual void vslot3E4_09(unsigned int) {}
    virtual void vslot3E4_10(unsigned int) {}
    virtual void vslot3E4_11(unsigned int) {}
    virtual void vslot3E4_13(unsigned int) {}
    virtual bool vslot3E4_14() { return true; }
    virtual void vslot3E4_15(unsigned int) {}
    virtual bool vslot3E4_16(unsigned int) { return false; }
    virtual void vslot3E4_17(unsigned int) {}
    virtual bool vslot3E4_18() { return true; }
    virtual bool vslot3E4_19() { return false; }

protected:
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
    virtual void privateMoveToPosition(const Coord3D *, float, CommandSourceType);
    virtual void bfmePrivateCommand42(Object *, CommandSourceType);
public:
    virtual void *slot22();
};

typedef char HordeAIUpdateParentExtent[sizeof(AIUpdateInterface) == 0x3E4 ? 1 : -1];
typedef char HordeAIUpdateExtent[sizeof(HordeAIUpdate) == 0x3E8 ? 1 : -1];

#endif
