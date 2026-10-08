// cl: /DNDEBUG /MD
// ?setTarget@AITarget@@QAEXPAVObject@@M@Z @0x002C5D8B 27B: forwards Object+0x38 position plus float plus Object+0x74 to 0x002C5CF7. Evidence pin REL32 at 0x005739CE in AITargetHeuristicBaseDefense slot 1 with 200.0 plus neighbours Rva002C589BXfer Dtor share flags.
#include "../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_38;
	char m_pad44[0x30];
	int m_74;
};

// Native 3ED0C4..3ED191 copies seventeen dwords into its hidden result
// pointer and returns that pointer in EAX (RET16). Only its first scalar is
// consumed here; the original result type remains unresolved.
struct Rva003ED0C4Result
{
    float values[17];
};
class Rva003ED0C4
{
public:
    Rva003ED0C4Result rva003ED0C4(void *owner, int mode, int player);
    char m_pad00[0x554];
    Coord3D m_position;
    float m_radius;
};
class Rva003ECB0BDwordClearer
{
public:
    void clear();
};
class Rva002C589B
{
public:
    void rva002C58B3();
};
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class AITarget
{
public:
	void rva002C5CF7(const struct Coord3D *pos, float radius, int id);
	void setTarget(Object *obj, float value);
    void markApproachHazard(const Coord3D *pos);
private:
    void *m_owner;
    unsigned int m_04;
    unsigned int m_frame;
    Coord3D m_position;
    char m_pad18[0x24 - 0x18];
    Rva003ED0C4 *m_table;
    float m_value;
    char m_pad2C[0x34 - 0x2C];
    int m_id;
};

void AITarget::setTarget(Object *obj, float value)
{
	rva002C5CF7(&obj->m_38, value, obj->m_74);
}

// Existing setTarget and the rowed heuristic caller identify this AITarget
// setter and its position/radius/id ABI. Native 2C5CF7..2C5D8B RET12 proves
// the offsets, helper calls, three-component snapshot and 68-byte result.
void AITarget::rva002C5CF7(const Coord3D *pos, float radius, int id)
{
    reinterpret_cast<Rva002C589B *>(this)->rva002C58B3();
    m_position = *pos;
    Rva003ED0C4 *table = m_table;
    m_id = id;
    m_frame = TheGameLogic->getFrame();
    Coord3D point;
    point.x = pos->x;
    point.y = pos->y;
    point.z = pos->z;
    table->m_position = point;
    m_table->m_radius = radius;
    reinterpret_cast<Rva003ECB0BDwordClearer *>(m_table)->clear();
    Rva003ED0C4Result result = m_table->rva003ED0C4(m_owner, 0, 0);
    m_value = result.values[0];
}

// Native 2C590F..2C59CE RET4. Trial position uses the same table as the
// position setter; keep it only when the first result scalar improves, and
// otherwise restore the three saved components. Original method name unknown.
void AITarget::markApproachHazard(const Coord3D *pos)
{
    struct PositionPair { Coord3D point; Coord3D oldPoint; } positions;
    positions.oldPoint.x = m_table->m_position.x;
    Coord3D *destination = &m_table->m_position;
    positions.oldPoint.y = destination->y;
    positions.oldPoint.z = destination->z;
    positions.point.x = pos->x;
    positions.point.y = pos->y;
    positions.point.z = pos->z;
    *destination = positions.point;
    reinterpret_cast<Rva003ECB0BDwordClearer *>(m_table)->clear();
    Rva003ED0C4Result result = m_table->rva003ED0C4(m_owner, 0, 0);
    if (result.values[0] > m_value)
        m_value = result.values[0];
    else
    {
        positions.point.x = positions.oldPoint.x;
        positions.point.y = positions.oldPoint.y;
        positions.point.z = positions.oldPoint.z;
        m_table->m_position = positions.point;
        reinterpret_cast<Rva003ECB0BDwordClearer *>(m_table)->clear();
    }
}
