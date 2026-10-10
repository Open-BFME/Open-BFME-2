// cl: /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/moduledata /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// ?getLocation@Team@@UBE?AVCoord3D@@XZ retail 0x0039D7DB / 101 bytes.
// Target identity: WorldBuilder 0x00EF4A30 names Team::getLocation in
// Team.cpp:2083..2096. It first loads the prototype, then the owner record's
// target chooser, and returns the chooser result's three floats or zero.
// Target layout: TeamCtor 0x003A39A7 installs secondary vtable 0x00C1AEB8
// at +4 after the 0x2C-byte Rva0055B0CC base. Its slot 13 is this body;
// getControllingPlayer receives the complete Team pointer (secondary this-4).
// Retail and WB prove prototype +0x30 (secondary +0x2C), target id +0x2C4,
// owner-record chooser +0x164 and result location +0x0C. Original names of
// the chooser record and id field remain unknown.
// Donor: BFME1 575ba2b04743f190f069805fbdc59936123c45da WWMath
// coord3d.h supplies the full inherited three-float Coord3D declaration.
// The class return spelling and inline scalar copy are structural inferences
// from the hidden-result ABI and retail FLD/FSTP plus two integer copies;
// WB's function identity does not independently prove the aggregate type name.
// All three callees resolve to existing owned bodies. No new callee pins.
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &v) { x=v.x;y=v.y;z=v.z; }
inline Coord3D::Coord3D(float xv,float yv,float zv) { x=xv;y=yv;z=zv; }

#include "Common/Snapshot.h"
class Player;
struct Rva002C5FBAResult { char pad[12]; Coord3D location; };
class Rva002C5FBA { public: void *rva002C5FBA(int); };
struct Rva002A8AB1Record { char pad[0x164]; Rva002C5FBA *target; };
class Rva002A8F24 { public: Rva002A8AB1Record *rva002A8AB1(void *); };
extern Rva002A8F24 *g_00DFEEF8;
struct Prototype { char pad[0x2c4]; int targetId; };
class Rva0055B0CC { public: virtual ~Rva0055B0CC();
virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();
virtual void slot7();virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();virtual void slot12();
virtual Coord3D getLocation() const; private: char pad[0x28]; };
class Team : public Snapshot, public Rva0055B0CC { public: Player *getControllingPlayer() const; virtual Coord3D getLocation() const; private: Prototype *proto; };
Coord3D Team::getLocation() const
{
 Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(getControllingPlayer());
 if(record) {
  Prototype *prototype = proto;
  Rva002C5FBA *target = record->target;
  Rva002C5FBAResult *result = (Rva002C5FBAResult *)target->rva002C5FBA(prototype->targetId);
  if(result) { return result->location; }
 }
 return Coord3D(0.0f,0.0f,0.0f);
}
