/* Target facts (retail RVAs): 0x0073D477 allocates 0x11C bytes before calling the constructor at 0x00739E60; that constructor stores an owner pointer at +0, initializes +4/+8 and the links at +0x0C/+0x10/+0x14/+0x18, and installs no vptr. The teardown at 0x0073A900 also installs no vptr. PartitionData has no virtual functions or base subobject; Zero Hour's MemoryPoolObject inheritance does not describe this target.
   0x0073A0E0 and 0x0073A0F0 call the owner at +0; 0x0073B2A0 and 0x0073B250 prove the pointer-to-link at +0x14 and next pointer at +0x18. 0x0073B250 tail-calls ShroudManager::Data::UpdateCellsTouched at 0x0073AD90 on the same receiver. 0x00739EE0 initializes twenty dwords at +0x24/+0x74 and twenty bytes at +0xC4; 0x0073A6D0 proves those shroud caches, seen flags, COI pointer +0x1C and count +0x20. 0x00739E86..0x00739F01 and 0x0073AD90 prove coordinates +0xD8/+0xDC, radius triples +0xE0/+0xF4, mask +0xEC, rotation +0xF0, change masks +0x100 and amounts +0x10C; 0x0073A102 writes byte +0x118.
   The ledger names maybePrepend (0x0073A0E0), makeDirty (0x0073A0F0), friend_updateCellsTouched (0x0073B250) and getShroudedStatus (0x0073A6D0); the existing unlink pin names 0x0073A0A0. All remain out of line. Zero Hour PartitionManager.h supplies the shroud-cache, seen-flag, COI-count and dirty-link names; unknown owner-interface and master-list fields retain neutral names. */
#ifndef BFME2_PARTITIONDATA_H
#define BFME2_PARTITIONDATA_H

class PartitionDirtyListOwner;
struct CellAndObjectIntersection;
enum ObjectShroudStatus;

class PartitionData
{
public:
    void maybePrepend();
    void makeDirty();
    void unlink();
    void friend_updateCellsTouched();
    ObjectShroudStatus getShroudedStatus(int playerIndex);

    PartitionDirtyListOwner *m_owner;
    void *m_field04;
    void *m_field08;
    PartitionData **m_field0C;
    PartitionData *m_field10;
    PartitionData **m_prevDirty;
    PartitionData *m_nextDirty;
    CellAndObjectIntersection *m_coiArray;
    int m_coiInUseCount;
    int m_shroudedness[20];
    int m_shroudednessPrevious[20];
    unsigned char m_everSeenByPlayer[20];
    int m_fieldD8;
    int m_fieldDC;
    int m_fieldE0[3];
    unsigned int m_fieldEC;
    float m_fieldF0;
    int m_fieldF4[3];
    unsigned int m_field100[3];
    int m_field10C[3];
    unsigned char m_isDirty;
};

#endif
