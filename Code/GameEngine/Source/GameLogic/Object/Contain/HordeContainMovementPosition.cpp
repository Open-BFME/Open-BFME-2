// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include /ICode/GameEngine/Source
// ?rva0046B05B@HordeContain@@QAEXPAVObject@@PAUCoord3D@@0@Z
// Native 0046B05B..0046B850 RET12; WB 010BD060 and transform 007E7310.
// The 0046E6EA caller takes this receiver's +0x11C interface; the final call
// to HordeContain::rva00468B24 establishes the containing class. The second
// argument is a mutable coordinate and the third an Object, not a coordinate.
// Method and unresolved field identities stay address-derived.
// Three-component point construction preserves the inline transform schedule.
// Binding saved z before scaling dir preserves native's initial SSE schedule.
#include <math.h>

#include "Lib/Coord3D.h"
#include "Common/GameLogicObjectLookupView.h"

struct MovementVector : Coord3D
{
    MovementVector()
    {
    }
    MovementVector(float xComponent, float yComponent, float zComponent)
    {
        x = xComponent;
        y = yComponent;
        z = zComponent;
    }
    MovementVector(const Coord3D &p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
    }
    MovementVector(const MovementVector &movementVector)
    {
        x = movementVector.x;
        y = movementVector.y;
        z = movementVector.z;
    }
    ~MovementVector()
    {
    }
    void sub(const Coord3D &p)
    {
        x -= p.x;
        y -= p.y;
        z -= p.z;
    }
    void add(const Coord3D &p)
    {
        x += p.x;
        y += p.y;
        z += p.z;
    }
    void scale(float s)
    {
        x = s * x;
        y = s * y;
        z = s * z;
    }
};

struct MovementPoint
{
    float x, y, z;
    MovementPoint()
    {
    }
    MovementPoint(float xComponent, float yComponent, float zComponent)
    {
        x = xComponent;
        y = yComponent;
        z = zComponent;
    }
    MovementPoint(const Coord3D &c)
    {
        x = c.x;
        y = c.y;
        z = c.z;
    }
};
class Matrix3D
{
  public:
    void Get_Orthogonal_Inverse(Matrix3D &set_inverse) const;
    float Row[3][4];
};

template <class T> __forceinline void Rva0046B05BTransform(const Matrix3D &matrix3D, T *point)
{
    float x = matrix3D.Row[0][0] * point->x + matrix3D.Row[0][1] * point->y + matrix3D.Row[0][2] * point->z + matrix3D.Row[0][3];
    float y = matrix3D.Row[1][0] * point->x + matrix3D.Row[1][1] * point->y + matrix3D.Row[1][2] * point->z + matrix3D.Row[1][3];
    float z = matrix3D.Row[2][0] * point->x + matrix3D.Row[2][1] * point->y + matrix3D.Row[2][2] * point->z + matrix3D.Row[2][3];
    point->x = x;
    point->y = y;
    point->z = z;
}

class GeometryInfo
{
  public:
    float getMaxHeightAbovePosition() const;
    // Local +0x24 geometry view; do not emit the generic accessor name used
    // by views with different layouts. The native movement body inlines this.
    float movementMajorRadius() const
    {
        return m_majorRadius;
    }
    char m_pad00[0x10];
    float m_10; // +0x10
    char m_pad14[0x24 - 0x14];
    float m_majorRadius; // +0x24
};

enum KindOfType
{
    KINDOF_67 = 0x67,
    KINDOF_69 = 0x69
};

struct Rva0046B05BTemplate
{
    char m_pad000[0x11A];
    unsigned short m_11A; // +0x11A
    unsigned char m_11C;  // +0x11C
    char m_pad11D[0x121 - 0x11D];
    unsigned char m_121; // +0x121
};

class Rva002627E8
{
  public:
    float rva002627E8() const;
};

class Object
{
  public:
    bool isKindOf(KindOfType t) const;
    bool isSignificantlyAboveTerrain() const;
    Coord3D *getPlanarDirectionTo(Coord3D *out, const Object *other) const;

    void *m_vtbl;
    const Rva0046B05BTemplate *m_template; // +0x04
    Matrix3D m_transform;                  // +0x08
    Coord3D m_position;                    // +0x38
    char m_pad44[0x74 - 0x44];
    ObjectID m_74; // +0x74
    char m_pad78[0xA8 - 0x78];
    GeometryInfo m_geometry; // +0xA8
    char m_padD4[0x258 - 0xA8 - sizeof(GeometryInfo)];
    Rva002627E8 *m_258; // +0x258
    char m_pad25C[0x438 - 0x25C];
    unsigned char m_438; // +0x438
};

enum PathfindLayerEnum
{
    LAYER_INVALID = 0
};

class TerrainLogic
{
  public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual float getGroundHeight(float x, float y, Coord3D *normal); // +0x18
    PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

class Pathfinder
{
  public:
    void *getObstacleID(int layer, int pos);
};

class AI
{
  public:
    Pathfinder *getPathfinder()
    {
        return m_pathfinder;
    }
    char m_pad00[0x10];
    Pathfinder *m_pathfinder; // +0x10
};

extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;
extern GameLogic *TheGameLogic;

class HordeContain
{
  public:
    void rva00468B24(float value);
    void rva0046B05B(Object *obj, Coord3D *pos, Object *other);
    char m_pad00[8];
    Object *m_object; // +0x08
    char m_pad0C[0x2F0 - 0x0C];
    ObjectID m_2F0; // +0x2F0
};

__forceinline Object *Rva0046B05BFindAt(PathfindLayerEnum layer, const Coord3D *pos)
{
    return TheGameLogic->findObjectByID(
        (ObjectID)(int)TheAI->getPathfinder()->getObstacleID(layer, (int)pos));
}

void HordeContain::rva0046B05B(Object *objArg, Coord3D *posArg, Object *otherArg)
{
    Coord3D *pos = posArg;
    Object *other = otherArg;
    Object *obj = objArg;

    bool far;
    float moveRadius;
    MovementVector start;
    MovementVector target;
    float dist;
    {
        MovementVector dir(pos->x, pos->y, pos->z);
        dir.sub(obj->m_position);
        dir.z = 0.0f;
        dist = dir.length();
        dir.normalize();
        far = dist > 2.0f * m_object->m_geometry.m_10;

        moveRadius = dist < other->m_258->rva002627E8() ? dist : other->m_258->rva002627E8();
        moveRadius *= 0.7f;
        moveRadius = moveRadius < 7.0f ? moveRadius : 7.0f;

        float clampedDistance;
        {
            Coord3D toward;
            obj->getPlanarDirectionTo(&toward, m_object);
            clampedDistance = toward.GetLengthEstimate();
        }
        if (200.0f < clampedDistance)
            clampedDistance = 200.0f;
        else if (clampedDistance <= 1.0f)
            clampedDistance = 1.0f;
        float t = (200.0f - clampedDistance) / 200.0f;
        moveRadius *= t * 0.8f + 0.2f;
        if (moveRadius > 10.0f)
            moveRadius = 10.0f;
        if (obj->m_template->m_11C & 0x10)
            moveRadius *= 0.8f;
        if (far)
            moveRadius = moveRadius > 9.0f ? moveRadius : 9.0f;

        // Preserve the starting height before advancing along the direction.
        float &zValue = start.z;
        zValue = obj->m_position.z;
        dir.scale(moveRadius);
        target.x = obj->m_position.x;
        target.y = obj->m_position.y;
        start.x = target.x;
        start.y = target.y;
        target.x += dir.x;
        target.y += dir.y;
        target.z = zValue + dir.z;
    }

    Object *object = Rva0046B05BFindAt(TheTerrainLogic->getLayerForDestination(obj, &target), &target);
    if (object == 0)
    {
        if (!obj->isKindOf(KINDOF_67) && !obj->isKindOf(KINDOF_69) &&
            !obj->isSignificantlyAboveTerrain())
        {
            MovementVector mid;
            mid.z = target.z;
            mid.x = (target.x + start.x) * 0.5f;
            mid.y = (target.y + start.y) * 0.5f;
            object = Rva0046B05BFindAt(TheTerrainLogic->getLayerForDestination(obj, &mid), &mid);
            if (object)
                target = mid;
        }
    }

    unsigned char raised = false;
    bool lowered = false;
    if (object && (object->m_template->m_121 & 2) && !(object->m_438 & 1))
    {
        if (object->m_74 != m_2F0)
        {
            Object *owner = TheGameLogic->findObjectByID(m_2F0);
            if (owner)
                object = owner;
        }
        MovementPoint local(target.x, target.y, target.z);
        Matrix3D inverse;
        object->m_transform.Get_Orthogonal_Inverse(inverse);
        Rva0046B05BTransform(inverse, &local);
        GeometryInfo *geom = &object->m_geometry;
        bool inside =
            fabs(local.x) <= geom->movementMajorRadius() && geom->getMaxHeightAbovePosition() >= local.z;
        if ((inside == 0) && !obj->isKindOf(KINDOF_67) && !obj->isKindOf(KINDOF_69) &&
            !obj->isSignificantlyAboveTerrain())
        {
            MovementPoint midpoint((target.x + start.x) * 0.5f, (target.y + start.y) * 0.5f,
                                   target.z);
            Rva0046B05BTransform(inverse, &midpoint);
            inside = fabs(midpoint.x) <= geom->movementMajorRadius() &&
                     geom->getMaxHeightAbovePosition() >= midpoint.z;
        }
        if (inside)
        {
            float top = geom->getMaxHeightAbovePosition();
            float baseZ = object->m_position.z;
            float topZ = baseZ + top;
            if (start.z < topZ)
            {
                MovementPoint startPoint(start.x, start.y, start.z);
                Rva0046B05BTransform(inverse, &startPoint);
                if (startPoint.x > geom->movementMajorRadius())
                    startPoint.x = geom->movementMajorRadius();
                else if (-geom->movementMajorRadius() > startPoint.x)
                    startPoint.x = -geom->movementMajorRadius();
                Rva0046B05BTransform(object->m_transform, &startPoint);
                start.x = startPoint.x;
                start.y = startPoint.y;
                start.z = startPoint.z;
                float half = obj->m_geometry.getMaxHeightAbovePosition() * 0.5f;
                if (half + baseZ > start.z)
                    start.z = baseZ + half;
                else if (far)
                    start.z = start.z + (moveRadius * 0.8f);
                else
                    start.z += moveRadius * 0.6f;
                if (start.z > topZ)
                    start.z = topZ;
                raised = true;
            }
        }
    }
    else
    {
        float ground = TheTerrainLogic->getGroundHeight(start.x, start.y, 0);
        if (start.z > ground)
        {
            if (far)
                start.z -= moveRadius * 0.8f;
            else
                start.z -= moveRadius * 0.6f;
            if (start.z < ground)
                start.z = ground;
            lowered = true;
        }
        else if (object && (object->m_template->m_11A & 0x1040) && object->m_74 != m_2F0)
        {
            Object *owner = TheGameLogic->findObjectByID(m_2F0);
            if (owner)
            {
                MovementVector a(owner->m_position);
                a.sub(obj->m_position);
                MovementVector b(obj->m_position);
                b.sub(object->m_position);
                b.scale(2.0f);
                a.add(b);
                a.normalize();
                a.scale(moveRadius);
                MovementVector c(obj->m_position);
                c.add(a);
                target = c;
            }
        }
    }
    if (!lowered && !raised)
        start = target;
    *pos = start;
    rva00468B24(dist);
}
