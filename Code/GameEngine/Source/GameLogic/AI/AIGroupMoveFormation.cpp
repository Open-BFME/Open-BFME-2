// cl: /I. /O1 /G7 /EHs /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Donor semantic spine: f98983a7d ZH AIGroup::friend_moveFormationToPos.
// Native371166..371AE2 RET20 / WB EE0AF0 independently name BFME2 formation move.
// Visible getter, command/vector and coordinate helper definitions reproduce the C0 frame.
// Their emitted bodies also match the existing retail owner rows.
#include <list>
// vector<Coord3D>::_M_insert_overflow inlines max(size(), n), as the rowed
// retail copy 0x002CDF8A does; a file-static unsigned overload takes the call.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &leftValue, const unsigned int &rightValue) { return leftValue < rightValue ? rightValue : leftValue; }
}
#include <vector>

// Retail compares typed list nodes inline, as in NetPacket.cpp.
namespace _STL {
template <class T, class L, class R>
static __forceinline bool operator!=(const _List_iterator<T, L> &a, const _List_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
}

#include <math.h>
#include <stdlib.h>
#include "Coord3D.h"
inline float Coord3D::length() const { return (float)sqrt(x * x + y * y + z * z); }
inline float Coord3D::GetLength() const
{
    float xComponent = x, b = y, c = z;
    return (float)sqrt(xComponent * xComponent + b * b + c * c);
}
inline void Coord3D::normalize()
{
    float len = length();
    if (len != 0.0f)
    {
        float scale = 1.0f / len;
        x *= scale;
        y *= scale;
        z *= scale;
    }
}
struct Coord3DCopy : Coord3D
{
    Coord3DCopy() {}
    Coord3DCopy(const Coord3D &sourceCoord)
    {
        x = sourceCoord.x;
        y = sourceCoord.y;
        z = sourceCoord.z;
    }
    Coord3DCopy(const Coord3DCopy &coord3DCopy)
    {
        x = coord3DCopy.x;
        y = coord3DCopy.y;
        z = coord3DCopy.z;
    }
    ~Coord3DCopy() {}
    Coord3DCopy &operator=(const Coord3D &r)
    {
        static_cast<Coord3D &>(*this) = r;
        return *this;
    }
    Coord3DCopy &Sub(const Coord3D &subtrahend)
    {
        x -= subtrahend.x;
        y -= subtrahend.y;
        z -= subtrahend.z;
        return *this;
    }
    Coord3DCopy &Add(const Coord3D &addend)
    {
        x += addend.x;
        y += addend.y;
        z += addend.z;
        return *this;
    }
    Coord3DCopy &Scale(float s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
    float lengthSqr() const { return x * x + y * y + z * z; }
};
#include "Coord2D.h"
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
// bfme link decl-only end

enum CommandSourceType
{
    CMD_FROM_PLAYER = 0
};
enum PathfindLayerEnum
{
    LAYER_INVALID = 0,
    LAYER_GROUND = 1
};
float ACos(float);
class Object;
class LocomotorSet;
class Rva0035149F;

void Rva00030830GameFree(void *);
enum AICommandType
{
    AICMD_MOVE_TO_POSITION = 0
};

struct BfmeE12
{
    float x, y, z;
};
class Rva000E016A
{
  public:
    BfmeE12 *rva000E016A(unsigned, Coord3D *, Coord3D *);
};
namespace _STL
{
template <> __declspec(noinline) inline void _Construct(Coord3D *p, const Coord3D &r)
{
    if (p)
    {
        p->x = r.x;
        p->y = r.y;
        p->z = r.z;
    }
}
} // namespace _STL
// The retail copy worker takes the empty tag by const reference.
// Select that overload explicitly; the general STLport header uses a value tag.
// __uninitialized_copy stays visible: a declaration-only specialization makes
// _M_insert_overflow build a zeroed tag temporary that retail's copy lacks.
namespace _STL
{
template <class I, class O> O __copy_ptrs(I, I, O, const __false_type &);
} // namespace _STL
class Rva0035149F
{
  public:
    BfmeE12 *start, *finish, *end;
    Rva0035149F &rva0035149F(const Rva0035149F &);
};
struct AICommandParms
{
    AICommandParms(AICommandType, CommandSourceType);
    // Inline teardown frees through the C free, as SlavedUpdateRepair's rowed copies do.
    ~AICommandParms()
    {
        if (coords.start)
            free(coords.start);
    }
    int cmd, source;
    Coord3D pos;
    Object *target;
    char pad18[8];
    Rva0035149F coords;
    char pad2c[8];
    int maxShots;
    char pad38[0xc0 - 0x38];
};
class Rva00295A0FCommands
{
  public:
    virtual void aiDoCommand(const AICommandParms *);
    void Rva00295A0FCommand(void *, int, int);
};
class AICommandInterface
{
  public:
    virtual void aiDoCommand(const AICommandParms *);
    void aiMoveToPosition(const Coord3D *, CommandSourceType);
    void rva0036EE89(const Rva0035149F *, Object *, float, CommandSourceType);
    void rva0036EF09(const Rva0035149F *, Object *, float, CommandSourceType);
};
struct FormationLocomotorTemplate
{
    char pad0[0x78];
    int mode;
};
struct FormationLocomotor
{
    char pad0[4];
    FormationLocomotorTemplate *type;
};
class AIUpdateInterface
{
  public:
#define AIV(n) virtual void slot##n();
    AIV(0)
    AIV(1) AIV(2) AIV(3) AIV(4) AIV(5) AIV(6) AIV(7) AIV(8) AIV(9) AIV(10) AIV(11) AIV(12) AIV(13)
        AIV(14) AIV(15) AIV(16) AIV(17) AIV(18) AIV(19) AIV(20) AIV(21) AIV(22) AIV(23) AIV(24)
            AIV(25) AIV(26) AIV(27) AIV(28) AIV(29) AIV(30) AIV(31) AIV(32) AIV(33) AIV(34) AIV(35)
                AIV(36) AIV(37) AIV(38) AIV(39) AIV(40) AIV(41) AIV(42) AIV(43) AIV(44) AIV(45)
                    AIV(46) AIV(47) AIV(48) AIV(49) AIV(50) AIV(51) AIV(52) AIV(53) AIV(54) AIV(55)
                        AIV(56) AIV(57) AIV(58) AIV(59) AIV(60) AIV(61) AIV(62) AIV(63) AIV(64)
                            AIV(65) AIV(66) AIV(67) AIV(68) AIV(69) AIV(70) AIV(71) AIV(72) AIV(73)
                                AIV(74) AIV(75) AIV(76) AIV(77) AIV(78) AIV(79) AIV(80) AIV(81)
                                    AIV(82) AIV(83) AIV(84) AIV(85) AIV(86) AIV(87) AIV(88) AIV(89)
                                        AIV(90) AIV(91) AIV(92) AIV(93) AIV(94) AIV(95) AIV(96) AIV(
                                            97) AIV(98) AIV(99) AIV(100) AIV(101) AIV(102) AIV(103)
                                            AIV(104) AIV(105) AIV(106) AIV(107) AIV(108) AIV(109)
                                                AIV(110) AIV(111) AIV(112) AIV(113) AIV(114)
                                                    AIV(115) AIV(116) AIV(117) AIV(118) AIV(119)
                                                        AIV(120) AIV(121) AIV(122) AIV(123) AIV(124)
                                                            AIV(125) AIV(126) AIV(127) AIV(128)
                                                                AIV(129) AIV(130) AIV(131) AIV(132)
                                                                    AIV(133) AIV(134) AIV(135)
                                                                        AIV(136)
#undef AIV
                                                                            virtual bool slot137();
    __declspec(dllimport) __forceinline const LocomotorSet &getLocomotorSet() const
    {
        return *reinterpret_cast<const LocomotorSet *>(reinterpret_cast<const char *>(this) +
                                                       0x1CC);
    }
    void *surfaces() const { return m_surfaces; }
    char pad4[0x20 - 4];
    AICommandInterface commands;
    char pad21[0x1DC - 0x24];
    void *m_surfaces;
    char pad1E0[0x1F0 - 0x1E0];
    FormationLocomotor *locomotor;
};
class ThingTemplate
{
  public:
    char pad0[0x564];
    int formationRank;
    int getFormationRank() const { return formationRank; }
};
class Object
{
  public:
    int rva0028B511() const;
    bool isMobile() const;
    bool isDisabledByHeld() const { return held(); }
    AIUpdateInterface *getAIUpdateInterface() const { return ai; }
    bool rva0028C264(int *, int);
    bool isAbleToAttack() const;
    void rva0028ACEE(int, int);
    const Coord3D *getPosition() const { return &pos; }
    const ThingTemplate *getTemplate() const { return type; }
    bool held() const { return (disabled[0] & 8) != 0; }
    char pad0[4];
    const ThingTemplate *type;
    char pad8[0x38 - 8];
    Coord3D pos;
    char pad44[0x1C8 - 0x44];
    unsigned char disabled[0x258 - 0x1C8];
    AIUpdateInterface *ai;
    char pad25C[0x414 - 0x25C];
    Coord2D offset;
};
#include "../../../Include/GameLogic/PathNode.h"
#include "../../../Include/GameLogic/PathfindPath.h"
#include "../../../Include/GameLogic/AIPathfind.h"
struct FormationAIData
{
    char pad0[0xA4];
    float spacing;
    char padA8[4];
    float terrainSpacing;
};
class AI
{
  public:
    char pad0[0x10];
    Pathfinder *pathfinder;
    char pad14[4];
    FormationAIData *data;
    Pathfinder *getPathfinder() { return pathfinder; }
    const FormationAIData *getAiData() const { return data; }
};
extern AI *TheAI;
struct FormationExtent
{
    Coord3D lo, hi;
};
class TerrainLogic
{
  public:
#define TV(n) virtual void slot##n();
    TV(0) TV(1) TV(2) TV(3) TV(4) TV(5) TV(6) TV(7) virtual void slot8(FormationExtent *);
    TV(9)
    TV(10) TV(11) TV(12) TV(13) TV(14) TV(15) TV(16) TV(17) TV(18) TV(19) TV(20) TV(21) TV(22)
        TV(23) TV(24) TV(25) TV(26) TV(27) TV(28) TV(29) TV(30) TV(31) TV(32) TV(33) TV(34) TV(35)
            TV(36) TV(37) TV(38) TV(39) TV(40) TV(41) TV(42) TV(43) TV(44) TV(45) TV(46) TV(47)
                TV(48) TV(49)
#undef TV
                    virtual bool slot50(const Coord3D *);
};
extern TerrainLogic *TheTerrainLogic;

static const float &larger(const float &leftValue, const float &rightValue) { return leftValue > rightValue ? leftValue : rightValue; }
struct FormationOffset : Coord2D
{
    FormationOffset() {}
    FormationOffset(const FormationOffset &formationOffset)
    {
        x = formationOffset.x;
        y = formationOffset.y;
    }
    FormationOffset(const Coord2D &sourceOffset)
    {
        x = sourceOffset.x;
        y = sourceOffset.y;
    }
    ~FormationOffset() {}
    FormationOffset &Scale(float scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }
};
class AIGroup
{
  public:
    bool getCenter(Coord3D *);
    static void rotateOffset(const Coord3D *, const Coord3D *, Coord2D *);
    void moveFormationToPos(const Coord3D *, CommandSourceType, int, bool, bool);

  private:
    char pad0[4];
    std::list<Object *> members;
    char pad8[0x14 - 8];
    Path *groundPath;
};
void AIGroup::moveFormationToPos(const Coord3D *pos, CommandSourceType source, int mode,
                                 bool ground, bool keepFormation)
{
    Coord3D center;
    if (!getCenter(&center))
        return;
    PathNode *startNode = 0, *endNode = 0;
    Coord3DCopy endPoint = *pos;
    Coord3DCopy startPoint = center;
    Coord3DCopy moveStart = center;
    float startDistance = TheAI->getAiData()->spacing * 4.0f;
    float endDistance = TheAI->getAiData()->spacing * 2.0f;
    bool useMoveStart = false;
    if (members.empty())
        return;
    std::list<Object *>::iterator i;
    float spacing = 0.0f;
    bool wider = false;
    for (i = members.begin(); i != members.end(); ++i)
    {
        Object *obj = *i;
        FormationOffset offset;
        static_cast<Coord2D &>(offset) = obj->offset;
        float required =
            -offset.x + (float)obj->getTemplate()->getFormationRank() * TheAI->getAiData()->spacing;
        spacing = larger(spacing, required);
        int info;
        if (obj->rva0028C264(&info, 4))
            wider = true;
    }
    spacing += TheAI->getAiData()->spacing * 0.5f;
    startDistance = larger(startDistance, spacing);
    if (wider)
        startDistance *= 2.0f;
    if (groundPath)
    {
        static_cast<Coord3D &>(startPoint) = *groundPath->getFirstNode()->getPosition();
        float remaining = startDistance;
        Coord3DCopy delta;
        Coord3DCopy previous = startPoint;
        PathNode *node;
        for (node = groundPath->getFirstNode(); node; node = node->getNextOptimized())
        {
            delta = *node->getPosition();
            delta.Sub(previous);
            delta.z = 0.0f;
            if (delta.lengthSqr() > remaining * remaining)
            {
                useMoveStart = true;
                startNode = node;
                delta.normalize();
                delta.Scale(remaining);
                moveStart = previous;
                moveStart.Add(delta);
                break;
            }
            static_cast<Coord3D &>(previous) = *node->getPosition();
            remaining -= delta.GetLength();
        }
        static_cast<Coord3D &>(endPoint) = *groundPath->getLastNode()->getPosition();
        delta = endPoint;
        delta.Sub(moveStart);
        if (delta.lengthSqr() < endDistance * endDistance)
            useMoveStart = false;
        for (node = groundPath->getFirstNode(); node; node = node->getNextOptimized())
        {
            delta = *node->getPosition();
            delta.Sub(endPoint);
            delta.z = 0.0f;
            if (delta.lengthSqr() > endDistance * endDistance)
                endNode = node;
        }
        PathNode *pathNode = endNode;
        while (pathNode)
        {
            if (pathNode == startNode)
                endNode = 0;
            pathNode = pathNode->getNextOptimized();
        }
        if (!startNode || !endNode)
        {
            delete groundPath;
            groundPath = 0;
            startNode = 0;
            endNode = 0;
        }
    }
    Coord3DCopy facingStart = startPoint;
    Coord3DCopy facing = endPoint;
    if (endNode)
        static_cast<Coord3D &>(facingStart) = *endNode->getPosition();
    facing.Sub(facingStart);
    facing.normalize();
    float angle = ACos(facing.x);
    if (facing.y < 0.0f)
        angle = -angle;
    for (i = members.begin(); i != members.end(); ++i)
    {
        Object *unit = *i;
        if (unit->held())
            continue;
        AIUpdateInterface *ai = unit->getAIUpdateInterface();
        if (!ai)
            continue;
        FormationOffset offset;
        static_cast<Coord2D &>(offset) = unit->offset;
        bool pathClear = true;
        if (TheAI->getPathfinder()->IsLineBlocked(unit, unit->getAIUpdateInterface()->surfaces(),
                                                  (PathfindLayerEnum)unit->rva0028B511(),
                                                  unit->getPosition(), &startPoint))
        {
            pathClear = false;
            if (useMoveStart &&
                !TheAI->getPathfinder()->IsLineBlocked(
                    unit, unit->getAIUpdateInterface()->surfaces(),
                    (PathfindLayerEnum)unit->rva0028B511(), unit->getPosition(), &moveStart))
                pathClear = true;
        }
        std::vector<Coord3D> path;
        Coord3DCopy previous = startPoint;
        if (useMoveStart && pathClear)
        {
            FormationOffset rotated(offset);
            rotateOffset(&previous, &moveStart, &rotated);
            previous = moveStart;
            Coord3DCopy dest = moveStart;
            dest.x += rotated.x;
            dest.y += rotated.y;
            if (ground == true)
                TheAI->getPathfinder()->AdjustGroundPathPosition(&moveStart, &dest);
            path.push_back(dest);
        }
        if (startNode && pathClear)
        {
            for (PathNode *node = startNode; node;)
            {
                Coord3DCopy dest = *node->getPosition();
                FormationOffset rotated(offset);
                rotateOffset(&previous, &dest, &rotated);
                if (TheTerrainLogic->slot50(&dest))
                {
                    rotated.Scale(TheAI->getAiData()->terrainSpacing);
                }
                dest.x += rotated.x;
                dest.y += rotated.y;
                if (ground == true)
                    TheAI->getPathfinder()->AdjustGroundPathPosition(node->getPosition(), &dest);
                path.push_back(dest);
                if (node == endNode)
                    break;
                node = node->getNextOptimized();
                previous = dest;
            }
        }
        FormationOffset rotated(offset);
        rotateOffset(&previous, &endPoint, &rotated);
        if (TheTerrainLogic->slot50(&endPoint))
        {
            rotated.Scale(TheAI->getAiData()->terrainSpacing);
        }
        if (ai->locomotor && ai->locomotor->type->mode == 0 && !keepFormation)
        {
            rotated.Scale(0.0f);
        }
        Coord3DCopy dest = endPoint;
        dest.x += rotated.x;
        dest.y += rotated.y;
        if (ground == true)
            TheAI->getPathfinder()->AdjustGroundPathPosition(&endPoint, &dest);
        if (!TheAI->getPathfinder()->AdjustDestination(unit, ai->getLocomotorSet(), &dest, 0))
        {
            FormationExtent extent;
            TheTerrainLogic->slot8(&extent);
            if (!(dest.x > extent.lo.x && dest.x < extent.hi.x && dest.y > extent.lo.y &&
                  dest.y < extent.hi.y))
            {
                dest = endPoint;
                TheAI->getPathfinder()->AdjustDestination(unit, ai->getLocomotorSet(), &dest, 0);
            }
        }
        unit->rva0028ACEE((int)&dest, (int)LAYER_GROUND);
        path.push_back(dest);
        if (mode == 1 && unit->isAbleToAttack())
        {
            if (!ai->slot137())
                reinterpret_cast<Rva00295A0FCommands *>(&ai->commands)
                    ->Rva00295A0FCommand(&dest, 0x7fffffff, (int)source);
            else
                ai->commands.rva0036EF09(reinterpret_cast<const Rva0035149F *>(&path), 0, angle,
                                         source);
        }
        else
        {
            if (!ai->slot137())
                ai->commands.aiMoveToPosition(&dest, source);
            else
                ai->commands.rva0036EE89(reinterpret_cast<const Rva0035149F *>(&path), 0, angle,
                                         source);
        }
    }
}

inline bool AIGroup::getCenter(Coord3D *center)
{
    int count = 0;
    center->x = 0.0f;
    center->y = 0.0f;
    center->z = 0.0f;

    std::list<Object *>::iterator i;
    for (i = members.begin(); i != members.end(); ++i)
    {
        if ((*i)->isDisabledByHeld())
            continue; // don't bother counting riders in the center calculation
        if (!(*i)->isMobile())
            continue;
        AIUpdateInterface *ai = (*i)->getAIUpdateInterface();
        if (ai)
        {
            const Coord3D *objPos = (*i)->getPosition();
            center->x += objPos->x;
            center->y += objPos->y;
            center->z += objPos->z;
            ++count;
        }
    }

    if (count == 0 && !members.empty())
    {
        for (i = members.begin(); i != members.end(); ++i)
        {
            if ((*i)->isDisabledByHeld())
                continue; // don't bother counting riders in the center calculation
            const Coord3D *objPos = (*i)->getPosition();
            center->x = objPos->x + center->x;
            center->y += objPos->y;
            center->z += objPos->z;
            ++count;
        }
    }

    center->x /= count;
    center->y /= count;
    center->z /= count;
    return count > 0;
}

// Preserve the definition order of the offset components: it determines which
// normalized component MSVC keeps live in XMM1. This copy matches all 129 bytes.
inline void AIGroup::rotateOffset(const Coord3D *from, const Coord3D *to, Coord2D *offset)
{
    Coord3DCopy dir;
    dir.x = to->x;
    dir.y = to->y;
    dir.x -= from->x;
    dir.y -= from->y;
    dir.z = 0.0f;
    dir.normalize();
    FormationOffset perp;
    perp.x = -dir.y;
    float x = offset->x;
    float y = offset->y;
    perp.y = dir.x;
    dir.Scale(x);
    perp.Scale(y);
    offset->x = dir.x + perp.x;
    offset->y = perp.y + dir.y;
}

inline void AICommandInterface::aiMoveToPosition(const Coord3D *position, CommandSourceType source)
{
    AICommandParms parms((AICommandType)0, source);
    parms.pos = *position;
    aiDoCommand(&parms);
}
// Rva00295A0FCommands::Rva00295A0FCommand is defined in AICommandRva00295A0F.cpp.
inline void AICommandInterface::rva0036EE89(const Rva0035149F *path, Object *target, float angle,
                                            CommandSourceType source)
{
    AICommandParms parms((AICommandType)0x24, source);
    parms.coords.rva0035149F(*path);
    parms.target = target;
    parms.pos.x = angle;
    aiDoCommand(&parms);
}
inline void AICommandInterface::rva0036EF09(const Rva0035149F *path, Object *target, float angle,
                                            CommandSourceType source)
{
    AICommandParms parms((AICommandType)0x25, source);
    parms.coords.rva0035149F(*path);
    parms.target = target;
    parms.pos.x = angle;
    aiDoCommand(&parms);
}

inline Rva0035149F &Rva0035149F::rva0035149F(const Rva0035149F &other)
{
    _STL::__false_type tag;
    typedef BfmeE12 *(__cdecl * Copy)(const BfmeE12 *, const BfmeE12 *, BfmeE12 *,
                                      const _STL::__false_type &);
    Copy copy = &_STL::__copy_ptrs<const BfmeE12 *, BfmeE12 *>;
    if (&other == this)
        return *this;
    unsigned elementCount = other.finish - other.start, cap = end - start;
    if (elementCount > cap)
    {
        BfmeE12 *newStorage =
            ((Rva000E016A *)this)->rva000E016A(elementCount, (Coord3D *)other.start, (Coord3D *)other.finish);
        if (start)
            Rva00030830GameFree(start);
        start = newStorage;
        end = newStorage + elementCount;
    }
    else
    {
        unsigned currentSize = finish - start;
        if (currentSize >= elementCount)
        {
            copy((const BfmeE12 *)other.start, (const BfmeE12 *)other.finish, start, tag);
        }
        else
        {
            copy((const BfmeE12 *)other.start, (const BfmeE12 *)(other.start + currentSize), start, tag);
            _STL::__uninitialized_copy((Coord3D *)(other.start + (finish - start)),
                                       (Coord3D *)other.finish, (Coord3D *)finish, tag);
        }
    }
    finish = start + elementCount;
    return *this;
}
