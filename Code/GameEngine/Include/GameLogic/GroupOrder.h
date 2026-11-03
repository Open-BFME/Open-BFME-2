// Target facts (addresses are RVAs unless prefixed VA): constructors 0x005488C5,
// 0x005488E9 and 0x00548A25 install VA 0x00C6A520 at +0; destructor 0x00548948
// installs that table, frees the +4 buffer, then restores Snapshot VA 0x00BBB554.
// The base extent is 0x18: the constructors write dwords +0x10/+0x14, and the
// derived constructor 0x00546AEF writes its first member at +0x18. Factory
// 0x00354EFC allocates 0x1C for that derived type. The +4 vector occupies 12 bytes;
// 0x005488E9 calls the folded four-byte-element copy 0x0054878E, and 0x00548A25
// builds it through 0x00211E58. Its element type is not established by that fold.
// 0x00211E58 and its proxy 0x0014F3C4 clear its three pointer words; 0x00546A78
// iterates four-byte words from +4 up to +8. Copy helper 0x004F62A4 sets the
// +0x0C storage limit to begin + count * 4.
// 0x005488E9 and 0x00548A25 generate +0x10 from VA 0x00E05F74, skipping zero,
// and clear +0x14. Transfer 0x00548AC2 visits +4, +0x10 and +0x14 in that order.
// VA 0x00C6A520 has fourteen code pointers followed by text: slot 0 is deleting
// destructor 0x00548A09; 1 is empty 0x000B3FD0; 2,4,5,6,8,11,12,13 are purecall
// 0x0003B810; 3 is xfer 0x00548AC2; 7 is ret-4 0x0047A69C; 9 returns false and
// pops four bytes (0x005CB9FF); 10 returns -1 without arguments (0x0036CC7A).
// Snapshot owns slots 0-3. Factory 0x00354EFC calls slot 12 for the NameKeyType;
// derived ledger rows 0x005474B9/0x00547A77 name getClassKey/clone at slots 12/13.
// Derived ledger rows 0x005471DF/0x0054719D/0x005471A3/0x005471E6 establish slots
// 7/8/9/11 and their declarations below. Slot 4/5 dispatchers 0x005478B5 and
// 0x00547368 take ObjectID; 0x00548984 passes the same ID word to slot 6.

#pragma once

#ifndef __BFME2_GROUPORDER_H_
#define __BFME2_GROUPORDER_H_

#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva0036E346;
struct Coord3D;
struct GroupOrderCommand;
enum ObjectID;
enum NameKeyType;

class GroupOrder : public Snapshot
{
public:
    GroupOrder();
    GroupOrder(const GroupOrder &other);
    GroupOrder(Rva0036E346 *holder);
    virtual ~GroupOrder();

    virtual void loadPostProcess() {}
    virtual void xfer(Xfer *xfer);
    virtual void slot04(ObjectID id) = 0;
    virtual bool slot05(ObjectID id) = 0;
    virtual void slot06(ObjectID id) = 0;
    virtual void slot07Set(int unused) {}
    virtual Coord3D *getDestination(int unused) = 0;
    virtual bool isNearDestination(const Coord3D *position) { return false; }
    virtual int slot10() { return -1; }
    virtual bool slot11Command(int *outType, GroupOrderCommand *command) = 0;
    virtual NameKeyType getClassKey() = 0;
    virtual GroupOrder *clone() = 0;

public:
    int *m_field04;
    int *m_field08;
    void *m_field0C;
    unsigned int m_field10;
    unsigned int m_field14;
};

#endif
