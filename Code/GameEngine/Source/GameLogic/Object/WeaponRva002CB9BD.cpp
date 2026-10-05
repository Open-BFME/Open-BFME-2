// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX- /arch:SSE
typedef int Int;
typedef float Real;
struct ICoord2D { Int x; Int y; };
struct Coord3D { Real x; Real y; Real z; };
enum PathfindLayerEnum { LAYER_INVALID = 0 };
class Object {
public:
    void *m_vtable;
    void *m_unk4;
};
struct FlagBlock { char m_pad[0x10f]; unsigned char m_flags; };
class WeaponTemplate;
class AI;
class Pathfinder;
class TerrainLogic;
class Weapon {
public:
    int rva002CB9BD(const Object *source, const Coord3D *pos, const Object *victim);
protected:
    void getFiringLineOfSightOrigin(const Object *shooter, Coord3D &origin) const;
public:
    Coord3D bfmeGetLOSVictimPos(const Object *source, const Object *victim, int weaponSlot) const;
};
struct Rva002ED01EInfo { Int cellCallback(void *a, void *b, Int x, Int y); };
ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);
class AI {
public:
    char m_pad[0x10];
    Pathfinder *m_pathfinder;
};
extern AI *g_Va009FF0F8;
class Pathfinder {
public:
    int rva002EE96B(Coord3D *a, const Coord3D *b);
};
class TerrainLogic {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual int v15(Coord3D *a, Coord3D *b);
};
extern TerrainLogic *TheTerrainLogic;
int Weapon::rva002CB9BD(const Object *source, const Coord3D *pos, const Object *victim)
{
    Coord3D firingOrigin;
    firingOrigin.x = pos->x;
    firingOrigin.y = pos->y;
    firingOrigin.z = pos->z;
    const Object *v = victim;
    Coord3D adjustedVictim;
    getFiringLineOfSightOrigin(source, firingOrigin);
    adjustedVictim = bfmeGetLOSVictimPos(source, v, 0);
    if (v != 0) {
        FlagBlock *blk = *(FlagBlock **)((char *)v + 4);
        if ((blk->m_flags & 0x10) != 0) {
            AI *ai = g_Va009FF0F8;
            if (ai != 0) {
                Pathfinder *pf = ai->m_pathfinder;
                if (pf != 0) {
                    pf->rva002EE96B(&adjustedVictim, &firingOrigin);
                }
            }
        }
    }
    return TheTerrainLogic->v15(&firingOrigin, &adjustedVictim);
}
