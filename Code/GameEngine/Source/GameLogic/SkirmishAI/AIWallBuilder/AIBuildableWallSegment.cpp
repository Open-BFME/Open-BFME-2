// cl: /O1 /G7 /arch:SSE /MD /EHsc
// WorldBuilder names 0x1538510 AIBuildableWallSegment::build. The paired
// retail body 0x00596D99..0x00596E13 preserves its base-build fallback,
// start-node lookup, virtual wall construction and terminal-hub ID update.
// Target offsets differ from WB: Object position +0x38 and ID +0x74;
// produced ID +0x24 and start-node ID +0x4C are observed in retail.
// Unrecovered virtual slots and class extents remain opaque.
#include "../../../Common/GameLogicObjectLookupView.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
    char m_unrecovered00[0x38];
    Coord3D m_position;
    char m_unrecovered44[0x74 - 0x44];
    ObjectID m_id;
};

class Player;
extern GameLogic *TheGameLogic;

class BuildAssistant
{
public:
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual bool buildWall(Object *startNode, const Coord3D *startPosition,
                           const Coord3D &endPosition, Player *player,
                           bool option, Object **terminalHub);
};
extern BuildAssistant *g_00A027B8;

class Rva0055ADD8
{
public:
    int rva0055ADD8(int ignored);
};

class AIBuildableStructure
{
public:
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12();
    virtual Coord3D getWorldPosition(); // slot 13, hidden result pointer
    bool build(Player *player); // WB 0x1506950; retail REL32 0x00573C7C
protected:
    char m_unrecovered04[0x24 - 4];
    ObjectID m_producedObjectID;
    char m_unrecovered28[0x4C - 0x28];
};

class AIBuildableWallSegment : public AIBuildableStructure
{
public:
    bool build(Player *player);
private:
    ObjectID m_startNodeID;
};

bool AIBuildableWallSegment::build(Player *player)
{
    if (m_startNodeID == INVALID_OBJECT_ID)
        return AIBuildableStructure::build(player);
    Object *startNode = TheGameLogic->findObjectByID(m_startNodeID);
    Object *terminalHub = 0;
    if (g_00A027B8->buildWall(startNode, &startNode->m_position,
                            getWorldPosition(), player, false, &terminalHub))
    {
        m_producedObjectID = terminalHub->m_id;
        return true;
    }
    ((Rva0055ADD8 *)this)->rva0055ADD8((int)player);
    return false;
}
