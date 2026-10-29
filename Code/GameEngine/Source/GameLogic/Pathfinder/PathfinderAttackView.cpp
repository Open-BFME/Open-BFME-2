// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native 002F314A..002F336A RET16; WB D3D500 names this attack-view query.
// BFME1 575ba2b04 PathfinderIsAttackViewBlockedByObstacle.cpp supplies the
// semantic guide; target kind bits, AI+18/67 and the five-unit end offset
// are BFME2 facts. The word accessor's integer Boolean result preserves the
// native EDI-before-ESI reload after the bridge-layer branch.
// class-gate: allow Coord3D WB's memberwise copy and empty destructor produce the verified 544-byte body and 0x38 frame; this 12-byte view also declares the existing Normalize2D owner, absent from the canonical header.
struct Coord3DBase { float x, y, z; };
struct Coord3D : Coord3DBase {
    Coord3D() {}
    Coord3D(const Coord3D &v) { x = v.x; y = v.y; z = v.z; }
    ~Coord3D() {}
    void assign(const Coord3D &v) { x = v.x; y = v.y; z = v.z; }
    Coord3D &operator-=(const Coord3DBase &v) {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    float Normalize2D();
};
typedef char AttackCoordinateSizeCheck[sizeof(Coord3D) == 12 ? 1 : -1];

enum PathfindLayerEnum { LAYER_GROUND = 1 };
enum WeaponSlotType;
enum AttackViewKind { AttackViewKind2 = 2, AttackViewKind59 = 59, AttackViewKind214 = 214 };
struct AttackViewTemplate {
    char padding[0x108];
    unsigned int bits[7];
    __forceinline unsigned int test(AttackViewKind bit) const {
        return (bits[bit >> 5] & (1u << (bit & 31))) != 0;
    }
};
class Weapon;
class Object {
public:
    void *vtable;
    AttackViewTemplate *definition;
    const Weapon *getCurrentWeapon(WeaponSlotType *) const;
    int rva0028B511() const;
};
class Rva002C9400ByteField;
class Weapon
{
public:
	bool isWithinAttackRange(Object *source, const Coord3D *pos, Object *victim, const Coord3D *victimPos, float bonus, bool checkMinimum);
	float getAttackRange(const Object *) const;
	bool isWithinAttackRange(const Object *,const Object *,float,int) const;
	bool isClearGoalFiringLineOfSightTerrain(const Object *, const Coord3D &, const Coord3D &) const;
	int isClearGoalFiringLineOfSightTerrain(const Object *, const Coord3D *, const Object *);
	void *m_00; // +0x00
	Rva002C9400ByteField *m_definition; // +0x04
};
struct AttackAiData { char pad[0x67]; unsigned char useLOS; };
class AI;
extern AI *TheAI;
struct AttackAIView { char pad[0x18]; AttackAiData *data; };
class TerrainLogic {
public:
    PathfindLayerEnum getLayerForDestination(Object *, const Coord3D *);
};
extern TerrainLogic *TheTerrainLogic;
class Rva002E73D4
{
public:
	Rva002E73D4(int a, int b, int c);
	int m_00; // +0x00
	int m_04; // +0x04
	int m_08; // +0x08
	int m_0C; // +0x0C
	bool m_10; // +0x10
	char m_pad11[0x3];
	int m_14; // +0x14
	int m_18; // +0x18
};
struct Rva002F18D4Info;
int isGroundOrBridgeLayer(int);
class Pathfinder {
public:
    bool isAttackViewBlockedByObstacle(const Object *, const Coord3D &, const Object *, const Coord3D &);
    void *rva001E3647Pos(int, const Coord3D *);
    int iterateCellsAlongLine(const Coord3D *, const Coord3D *, PathfindLayerEnum, Rva002F18D4Info *);
};

bool Pathfinder::isAttackViewBlockedByObstacle(const Object *attacker, const Coord3D &attackerPos,
    const Object *victim, const Coord3D &victimPos)
{
    if (!((AttackAIView *)TheAI)->data->useLOS)
        return false;
    if (!victim || (!attacker->definition->test(AttackViewKind59) && !attacker->definition->test(AttackViewKind214)))
        return false;
    {
        Weapon *weapon = (Weapon *)attacker->getCurrentWeapon(0);
        if (attacker->definition->test(AttackViewKind2))
            weapon = 0;
        if (weapon) {
            bool blocked;
            if (victim)
                blocked = !(unsigned char)weapon->isClearGoalFiringLineOfSightTerrain(attacker, &attackerPos, victim);
            else
                blocked = !weapon->isClearGoalFiringLineOfSightTerrain(attacker, attackerPos, victimPos);
            if (blocked)
                return true;
        }
        Coord3D pos;
        int attackerLayer = attacker->rva0028B511();
        PathfindLayerEnum layer = LAYER_GROUND;
        if (victim) {
            layer = (PathfindLayerEnum)victim->rva0028B511();
            if (attackerLayer != layer) {
                if ((attackerLayer >= 2 && attackerLayer <= 15) || (layer >= 2 && layer <= 15)) {
                    float z = attackerPos.z;
                    if (victimPos.z > z)
                        z = victimPos.z;
                    pos.assign(attackerPos);
                    pos.z = z;
                    PathfindLayerEnum attackerTerrainLayer = TheTerrainLogic->getLayerForDestination(0, &pos);
                    pos = victimPos;
                    pos.z = z;
                    PathfindLayerEnum victimTerrainLayer = TheTerrainLogic->getLayerForDestination(0, &pos);
                    if (attackerTerrainLayer == victimTerrainLayer)
                        return true;
                }
            }
        }
        Rva002E73D4 info((int)attacker, (int)victim, (int)rva001E3647Pos(layer, &victimPos));
        if (!(unsigned char)isGroundOrBridgeLayer(attacker->rva0028B511())) {
            info.m_0C = 3;
            if (layer == LAYER_GROUND)
                layer = (PathfindLayerEnum)attacker->rva0028B511();
        }
        pos.assign(attackerPos);
        pos -= victimPos;
        pos.Normalize2D();
        pos.x *= 5.0f;
        pos.y *= 5.0f;
        pos.z *= 5.0f;
        pos.x = victimPos.x + pos.x;
        pos.y = victimPos.y + pos.y;
        pos.z = victimPos.z + pos.z;
        return iterateCellsAlongLine(&attackerPos, &pos, layer, (Rva002F18D4Info *)&info) != 0;
    }
    return false;
}
