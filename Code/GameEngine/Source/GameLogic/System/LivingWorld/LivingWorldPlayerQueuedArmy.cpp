// LivingWorldPlayer::HasArmyQueuedInAnyBuilding, retail 0x002E118E..0x002E1257
// (201 bytes, ret12). Target identity: WB 0x00DE4C60 names the method
// with callgraph2 and LivingWorldPlayer.cpp:748 assert evidence. Native
// extraction2E2F44 calls it with record+A4 and two zero argument words.
// Target layout: player id+14; logic region manager+B0 -> group+8 ->
// collection+2C; region owner+13C; building id+18. These are accessed
// offset views, not evidence of class inheritance or complete layouts.
// The inline manager accessor produces retail's JE/LEA/JMP/XOR null
// branch; directly converting an inferred secondary-base pointer emitted
// NEG/SBB/AND instead. The complete search, exclusion and output-id logic
// is native; no donor type or relationship is asserted here.
// First key is an opaque four-byte value forwarded to queue vslot11.
// Its original type is unproved. Existing provider4E0625 returns a raw
// word typed int; retail consumes it as the virtual queue receiver.
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
struct Rva002E118ERegionGroup
{
 unsigned char pad[0x2C]; Rva002E118ERegionCollection collection;
};
struct Rva002E118ERegionManager
{
    unsigned char m_pad00[8];
    Rva002E118ERegionGroup *m_group;
 __forceinline Rva002E118ERegionCollection *getCollection() const { if (m_group) return &m_group->collection; return 0; }
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
    Rva002E118ERegionCollection *collection =
        reinterpret_cast<Rva002E118ELogicView *>(TheLivingWorldLogic)->m_regionManager->getCollection();
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
