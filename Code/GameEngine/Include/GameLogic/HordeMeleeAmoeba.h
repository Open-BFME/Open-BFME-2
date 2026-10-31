#pragma once
// BFME2 retail ABI projection. See reverse/attempt_support/hordeamoeba-canonical-qc10-20261031/.
#include <vector>
#include "../../../Libraries/Include/Lib/Coord3DBase.h"
class Object;
class Xfer;
struct Coord3D;
struct BfmePod60 {
 BfmePod60();
 Coord3DBase position;
 bool needsPosition;char opaque0d[3];int index;
 int values[8];int opaque34;unsigned char opaque38;bool loaded39;char opaque3a[2];
};

// The native 005D6FCC owner establishes vptr+held (8 bytes), not Snapshot.
// Only its consumed lifetime surface is declared here; its other methods remain unrecovered.
class Rva005D6FCC {
public:
 Rva005D6FCC(void *);
 virtual ~Rva005D6FCC();
 void *held;
};
class HordeMeleeAmoeba : public Rva005D6FCC {
public:
 HordeMeleeAmoeba(void *,void *);
 virtual ~HordeMeleeAmoeba(); // slot 0
private:
 // Opaque private positions preserve the independently bounded native table.
 // Their void spelling grants no callable signature or recovered provider identity.
 virtual void _bfme_slot1();
 virtual void _bfme_slot2();
public:
 virtual void startMeleeAttack(Object *); // 3
private:
 virtual void _bfme_slot4();
public:
 virtual void updateMeleeAttack(Object *); // 5
 virtual void notifyOfMemberDeath(Object *); // 6
private:
 virtual void _bfme_slot7();
 virtual void _bfme_slot8();
 virtual void _bfme_slot9();
 virtual void _bfme_slot10();
 virtual void _bfme_slot11();
public:
 virtual void setUnitNeedsNewAttackPos(void *,int); // 12
 virtual bool rva0058776E(int,Coord3D *); // 13
private:
 virtual void _bfme_slot14();
public:
 virtual void xfer(Xfer *); // 15, native table C6FF38+3C
 // The existing row has a nonvirtual spelling; slot 14 points to this same body.
 // Do not claim a new virtual provider name without reconciling that identity.
 bool rva005879C8(Object *);
 void AttackUnit(Object *,Object *);
 _STL::vector<BfmePod60> slots; // +8, native 60-byte records
 bool flag14;
 void *other; // +18; native factory allocates 1C bytes
};
