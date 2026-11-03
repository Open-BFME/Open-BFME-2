// Target facts (code addresses are RVAs, tables are VAs): factory 0x0024E854 pushes 0x140 at 0x0024E85F and calls ctor 0x0049E03A at 0x0024E87E. The ctor calls UpdateModule at 0x0049E053, stores base tables 0x00C513F0 at +0x20 and 0x00C1C780 at +0x24, then final tables 0x00C515BC/+0, 0x00C51500/+0x0C, 0x00C514F4/+0x10, 0x00C51478/+0x20 and 0x00C51470/+0x24 at 0x0049E07B..0x0049E096. Destructor 0x0049E1BF restores those same five tables at 0x0049E1D0..0x0049E1EB before calling UpdateModule destruction at 0x0049E262; UpdateModule's 0x0024A797 restores BehaviorModule's tables during base teardown. The initial pure tables are base construction, not competing ProductionUpdate layouts. The snapshot getter 0x0049E13C returns the ProductionUpdate string at 0x00BF5018; no registered complete class owns these bodies and tables.
// Target facts: 0x00C515BC has 13 slots, including deleting dtor 0x0049E34C, loadPostProcess 0x00497805, name 0x0049E13C, xfer 0x0049F91A and getModuleNameKey 0x0049E15E; slot 12 is inherited getUpdatePhase 0x0022C4CB. The 47-slot behavior table overrides getDie at slot 7 (0x003730FC, whole+0x24) and slot28 at slot 28 (0x004543A9, whole+0x20). The update table has update 0x0049E3B5, getDisabledTypesToProcess 0x0049E1A3 and inherited wake 0x0044DF8D. The 31-slot production table is bounded by 0x00C514F4; its rowed names and signatures are declared below, while slots 12 and 24..30 retain neutral names. Its slot 10 is 0x0049DC50, 17 is 0x0057E556, 21 is 0x0030F45F and 23 is 0x0049D617. The die table has only 0x0049CE63, which adjusts by -4 and calls production slot 16 with one stack argument. Both added interfaces have no virtual destructor; ProductionUpdate inherits its virtual destructor from UpdateModule.
// Target facts: ctor 0x0049E09D..0x0049E0A9 writes queue/head/tail, ID, count and completion frame at +0x28..+0x38; 0x0049E066..0x0049E0AC constructs four 0x10-byte door records at +0x3C. 0x0049E0B1..0x0049E0BF calls the 0x4C-byte zero constructor 0x00042526 at +0x7C/+0xC8. 0x0049E0CE..0x0049E10E writes byte +0x114, dword +0x118, bytes +0x11C/+0x11D, dword +0x120, dwords +0x128/+0x12C and byte +0x13C. 0x0049E0EC constructs list storage at +0x124; 0x0049E107 constructs vector storage at +0x130, and dtor 0x0049E248 calls the rowed vector<AsciiString> destructor. 0x0049CE71/0x0049CE99 write cancellation byte whole+0x11D. Zero Hour ProductionUpdate.h supplies the proven queue, ID, count, door and model-condition field names; remaining storage retains neutral offset names. Only constructor, destructor and other rowed methods are declared out of line.
#pragma once

#ifndef BFME2_PRODUCTIONUPDATECLASS_H
#define BFME2_PRODUCTIONUPDATECLASS_H

#include "UpdateModule.h"
#include "ProductionUpdateInterface.h"
#include "DieModuleInterface.h"

class ProductionUpdateModuleData;
class Rva0049CD4FArg;
struct Rva0049DF81Input;

class ProductionUpdate : public UpdateModule, public ProductionUpdateInterface, public DieModuleInterface
{
public:
    ProductionUpdate(Thing *thing, const ModuleData *moduleData);
    virtual ~ProductionUpdate();

    static Module *friend_newModuleInstance(Thing *thing, const ModuleData *moduleData);
    static ProductionUpdateInterface *getProductionUpdateInterfaceFromObject(Object *obj); // 0x0049CEFC

    virtual NameKeyType getModuleNameKey() const; // 0x0049E15E
    virtual UpdateSleepTime update(); // 0x0049E3B5
    virtual DisabledMaskType getDisabledTypesToProcess() const; // 0x0049E1A3
    virtual DieModuleInterface *getDie(); // 0x003730FC
    virtual void *slot28(); // 0x004543A9
    virtual void onDie(const DamageInfo *damageInfo); // 0x0049CE63

    virtual CanMakeType rva0049CFCD() const; // 0x0049CFCD
    virtual CanMakeType canQueueUpgrade(const UpgradeTemplate *upgrade) const; // 0x0049CFA9
    virtual ProductionID requestUniqueUnitID(); // 0x0049E142
    virtual bool queueUpgrade(const UpgradeTemplate *upgrade); // 0x0049D867
    virtual void cancelUpgrade(const UpgradeTemplate *upgrade); // 0x0049D9A2
    virtual void rva0049CC9D(const ThingTemplate *unitType, bool five); // 0x0049CC9D
    virtual bool isUpgradeInQueue(const UpgradeTemplate *upgrade) const; // 0x0049CDF9
    virtual unsigned int countUnitTypeInQueue(const ThingTemplate *unitType) const; // 0x0049CE28
    virtual bool queueCreateUnit(const ThingTemplate *unitType, int revivalIndex,
        ProductionID productionID, int, bool, const AsciiString &, bool); // 0x0049DA34
    virtual bool rva0049CC36(ProductionID productionID) const; // 0x0049CC36
    virtual void cancelUnitCreate(ProductionID productionID); // 0x0049DC50
    virtual void rva0049CC61(const ThingTemplate *unitType); // 0x0049CC61
    virtual void slot12(int); // 0x0049CCF0
    virtual void rva0049F8A9(const ThingTemplate *unitType, bool cancel); // 0x0049F8A9
    virtual void rva0049CC15(ProductionID productionID, int value); // 0x0049CC15
    virtual void cancelAndRefundAllProduction(); // 0x0049CE6E
    virtual void rva0049DEC8(); // 0x0049DEC8
    virtual unsigned int getProductionCount() const; // 0x0057E556
    virtual unsigned int rva0049CEAE(const ThingTemplate *unitType) const; // 0x0049CEAE
    virtual unsigned int rva0049CEE1(int value) const; // 0x0049CEE1
    virtual unsigned int rva0049D0DE(const Rva0049D0DEMask *mask) const; // 0x0049D0DE
    virtual const Rva0049D1B1 *firstProduction() const; // 0x0030F45F
    virtual const Rva0049D1B1 *nextProduction(const Rva0049D1B1 *p) const; // 0x0049E14C
    virtual void setHoldDoorOpen(ExitDoorType exitDoor, bool holdIt); // 0x0049D617
    virtual void slot24(bool); // 0x003BA5D0
    virtual bool slot25() const; // 0x002C8E83
    virtual float slot26(const ThingTemplate *); // 0x0049D1CA
    virtual float slot27(const ThingTemplate *); // 0x0049D244
    virtual float slot28(unsigned char); // 0x0049D2BE
    virtual float slot29(unsigned char); // 0x0049D33D
    virtual bool slot30() const; // 0x0049CF9E

    void rva0049D3BC(); // 0x0049D3BC
    void rva0049CD24(Object *obj); // 0x0049CD24
    void rva0049E368(); // 0x0049E368
    void rva0049CF25(); // 0x0049CF25
    void rva0049DF81(Rva0049DF81Input *input, Object *other); // 0x0049DF81
    int calcTotalProductionFrames(Rva0049CD4FArg *arg); // 0x0049CD4F
    const Rva0049D1B1 *GetEntryToProcess(); // 0x0049CFEB

protected:
    virtual void loadPostProcess(); // 0x00497805
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const; // 0x0049E13C
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer); // 0x0049F91A

    const ProductionUpdateModuleData *getProductionUpdateModuleData() const
    {
        return (const ProductionUpdateModuleData *)m_moduleData;
    }

    struct DoorInfo
    {
        unsigned int m_doorOpenedFrame;
        unsigned int m_doorWaitOpenFrame;
        unsigned int m_doorClosedFrame;
        bool m_holdOpen;
    };

    Rva0049D1B1 *m_productionQueue; // +0x28
    Rva0049D1B1 *m_productionQueueTail; // +0x2C
    unsigned int m_uniqueID; // +0x30
    unsigned int m_productionCount; // +0x34
    unsigned int m_constructionCompleteFrame; // +0x38
    DoorInfo m_doors[4]; // +0x3C
    unsigned int m_field7C[19]; // +0x7C
    unsigned int m_fieldC8[19]; // +0xC8
    bool m_flagsDirty; // +0x114
    unsigned int m_field118; // +0x118
    bool m_field11C; // +0x11C
    bool m_cancellingAll; // +0x11D
    unsigned int m_field120; // +0x120
    void *m_field124; // +0x124, list node storage
    unsigned int m_field128; // +0x128
    unsigned int m_field12C; // +0x12C
    AsciiString *m_field130[3]; // +0x130, vector start, finish and capacity
    bool m_field13C; // +0x13C
};

#endif
