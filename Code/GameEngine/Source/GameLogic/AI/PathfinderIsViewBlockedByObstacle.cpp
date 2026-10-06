// cl: /DNDEBUG /MD
// Target: 0x002F3B6B, 49 bytes; Ghidra boundary FUN_006f3b6b.
// Target evidence: its callee at 0x0030ADDC takes ECX=this, pushes 0.0f,
// calls 0x0030AD8B and returns the boolean; the latter reads object flags and
// compares height against terrain. The next call is Pathfinder at 0x002F314A,
// with Object pointers and each Object's Coord3D at +0x38.
// Donor: BFME1 AIPathfind.cpp, Pathfinder::isViewBlockedByObstacle.
// Structural inference: this is the same forwarding helper; retail has no
// null check on objOther, unlike the donor's source-level guard.
struct Coord3D { float x, y, z; };
class Object
{
public:
    unsigned char pad[0x38];
    Coord3D position;
    bool isSignificantlyAboveTerrain(void) const;
    Coord3D const *getPosition(void) const { return &position; }
};
class Pathfinder
{
public:
    bool isViewBlockedByObstacle(Object const *, Object const *);
    bool isAttackViewBlockedByObstacle(Object const *, Coord3D const &, Object const *, Coord3D const &);
};
bool Pathfinder::isViewBlockedByObstacle(Object const *obj, Object const *objOther)
{
    if (objOther->isSignificantlyAboveTerrain()) return false;
    return isAttackViewBlockedByObstacle(obj, *obj->getPosition(), objOther, *objOther->getPosition());
}
