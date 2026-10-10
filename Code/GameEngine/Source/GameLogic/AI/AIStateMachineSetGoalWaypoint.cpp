// cl: /DNDEBUG /MD
// Native 0x003E3BFB..0x003E3C05: store the argument at +0x48; RET4.
// AIUpdate team/waypoint callers pass null or a Waypoint pointer here.
// ZH AI/AIStates.cpp setGoalWaypoint supplies the semantic source; BFME2's
// member offset is established independently by the native setter and callers
// 0x0026BA33 and 0x0026D478. This supersedes a gen-alias that used
// RenderObjClass::Set_ObjectScale; its kept copy uses SSE float stores at +0x48.
class Waypoint;
class AIStateMachine {
    char prefix[0x48];
    const Waypoint *goalWaypoint;
public:
    void setGoalWaypoint(const Waypoint *);
};
void AIStateMachine::setGoalWaypoint(const Waypoint *waypoint)
{
    goalWaypoint = waypoint;
}
// ?rva003E3BFB@Pathfinder@@QAEXW4ObjectID@@@Z @0x003E3BFB (10B): the same
// 10-byte store serves Pathfinder callers with obstacle IDs (retail
// computeAttackPath 0x00266AA2 calls 0x003E3BFB three times where sources
// call pathfinder()->rva003E3BFB; doPathfind/DerivedOnExit likewise), so
// the setter folds here. Defined over a minimal Pathfinder view; the enum
// keeps the W4ObjectID mangling the callers reference.
enum ObjectID
{
    INVALID_OBJECT_ID = 0
};
class Pathfinder {
    char prefix[0x48];
    ObjectID ignoredObstacleID;
public:
    void rva003E3BFB(ObjectID);
};
void Pathfinder::rva003E3BFB(ObjectID id)
{
    ignoredObstacleID = id;
}
