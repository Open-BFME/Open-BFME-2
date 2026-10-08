// LivingWorldPlayer::HasArmyQueuedInAnyBuilding
// partial score=0.96 date=2026-10-08
// Named WB 0x00DE4CD0 and native 0x002E118E / 201 B: player +0x14,
// region owner +0x13C, logic->manager +0xB0->group +8, collection +0x2C.
// The null-preserving +0x2C adjustment supports the secondary-base model.
// First argument is forwarded unchanged; its original type is unresolved.
// Return-word provider 4E0625 preserves its established integer ABI; target
// and WB use that 32-bit word as the queue's virtual receiver at slot 11.
// cl: /O1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
class Rva002E118EQueue
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual bool contains(void *key);
};
class Rva004E0625
{
public:
    int rva004E0625() const;
};
class LivingWorldBuilding
{
public:
    unsigned char m_pad00[0x18];
    int m_key18;
};
class LivingWorldRegion
{
public:
    int rva003F05CE();
    LivingWorldBuilding *GetBuildingByIndex(int index) const;
    unsigned char m_pad00[0x13c];
    int m_ownerPlayerID;
};
struct Rva002E118ERegionCollection
{
    _STL::vector<LivingWorldRegion *> m_regions;
};
struct Rva002E118EGroupBase
{
    unsigned char m_pad00[0x2c];
};
struct Rva002E118ERegionGroup : Rva002E118EGroupBase, Rva002E118ERegionCollection
{
};
struct Rva002E118ERegionManager
{
    unsigned char m_pad00[8];
    Rva002E118ERegionGroup *m_group;
};
struct Rva002E118ELogicView
{
    unsigned char m_pad00[0xb0];
    Rva002E118ERegionManager *m_regionManager;
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class LivingWorldPlayer
{
public:
    bool HasArmyQueuedInAnyBuilding(void *key, int *outBuildingID, int excludedBuildingID);
private:
    unsigned char m_pad00[0x14];
    int m_playerID;
};
bool LivingWorldPlayer::HasArmyQueuedInAnyBuilding(void *key, int *outBuildingID, int excludedBuildingID)
{
    Rva002E118ERegionGroup *group =
        reinterpret_cast<Rva002E118ELogicView *>(TheLivingWorldLogic)->m_regionManager->m_group;
    Rva002E118ERegionCollection *collection = static_cast<Rva002E118ERegionCollection *>(group);
    if (collection == 0)
        return false;
    for (unsigned int i = 0; i < collection->m_regions.size(); ++i)
    {
        LivingWorldRegion *region = collection->m_regions[i];
        if (region->m_ownerPlayerID != m_playerID)
            continue;
        int count = region->rva003F05CE();
        for (int j = 0; j < count; ++j)
        {
            LivingWorldBuilding *building = region->GetBuildingByIndex(j);
            // The established provider returns the raw +0x40 word as int.
            // Both native and WB callers consume it as a virtual receiver.
            Rva002E118EQueue *queue = reinterpret_cast<Rva002E118EQueue *>(
                reinterpret_cast<Rva004E0625 *>(building)->rva004E0625());
            if (queue != 0 && building->m_key18 != excludedBuildingID && queue->contains(key))
            {
                if (outBuildingID != 0)
                    *outBuildingID = building->m_key18;
                return true;
            }
        }
    }
    return false;
}
