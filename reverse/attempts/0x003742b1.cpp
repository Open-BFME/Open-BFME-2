// ?rva003742B1@Rva003742B1@@QAEXXZ
// partial score=0.6667 date=2026-10-04
// cl: /O1 /G7 /GX- /MD
// Native3742B1/50 zero-stack-argument wrapper; served StealthUpdate name false.
// Owner8 uses rowed Object::rva002931F5(false), then passes positions38.
// The856-byte helper373F59 returns bool; original module identity unknown.
struct Coord3D { float x,y,z; };
class Object { public:Object *rva002931F5(bool); };
struct ObjectPositionView { unsigned char prefix[0x38];Coord3D position; };
class Rva003742B1 { public:void rva003742B1();bool updatePositions(const Coord3D *,const Coord3D *);unsigned char prefix[8];Object *owner; };
void Rva003742B1::rva003742B1() {
 Object *container=owner->rva002931F5(false);
 if(!container)
  updatePositions(&((ObjectPositionView*)owner)->position,&((ObjectPositionView*)owner)->position);
 else updatePositions(&((ObjectPositionView*)owner)->position,&((ObjectPositionView*)container)->position);
}
