// ?getLocation@Team@@UBE?AVVector3@@XZ
// partial score=0.976685 date=2026-10-09
// cl: /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/moduledata /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
#include "vector3.h"

#include "Common/Snapshot.h"
class Player;
struct Rva002C5FBAResult { char pad[12]; Vector3 location; };
class Rva002C5FBA { public: void *rva002C5FBA(int); };
struct Rva002A8AB1Record { char pad[0x164]; Rva002C5FBA *target; };
class Rva002A8F24 { public: Rva002A8AB1Record *rva002A8AB1(void *); };
extern Rva002A8F24 *g_00DFEEF8;
struct Prototype { char pad[0x2c4]; int targetId; };
class Rva0055B0CC { public: virtual ~Rva0055B0CC();
virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();
virtual void slot7();virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();virtual void slot12();
virtual Vector3 getLocation() const; private: char pad[0x28]; };
class Team : public Snapshot, public Rva0055B0CC { public: Player *getControllingPlayer() const; virtual Vector3 getLocation() const; private: Prototype *proto; };
Vector3 Team::getLocation() const
{
 Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(getControllingPlayer());
 if(record) {
  Rva002C5FBAResult *result=(Rva002C5FBAResult *)record->target->rva002C5FBA(proto->targetId);
  if(result) { return result->location; }
 }
 return Vector3(0.0f,0.0f,0.0f);
}
