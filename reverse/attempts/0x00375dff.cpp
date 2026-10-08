// ?rva00375DFF@AerialPathfinder@@QAE_NPAVObject@@PAVRva00375A73Context@@MM@Z
// partial score=0.95 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /MD
struct Rva00375A73Coord { float x, y, z; };
class Rva00375A73Context
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void prepare(int mode, int amount, float a, float b,
        unsigned int c, unsigned int d);
    unsigned char prefix04[0x14];
    float value18;
    unsigned char padding1C[8];
    bool valid24;
    unsigned char padding25[0x23];
    Rva00375A73Coord position48;
};
class Rva0022B3F6Subsystem
{
public:
    bool rva00311974(Rva00375A73Context *context, unsigned int a, unsigned int b);
};
extern Rva0022B3F6Subsystem *TheSplineService;
class Object
{
public:
    unsigned char pad00[0x258];
    void *m_258;
};
class TerrainLogic
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual float getGroundHeight(float x, float y, Rva00375A73Coord *normal) const;
};
extern TerrainLogic *TheTerrainLogic;
static const float g_00C18564 = 0.5f;
class AerialPathfinder
{
public:
    bool rva00375A73(Rva00375A73Context *context, float value, Rva00375A73Coord *output);
    bool rva00375DFF(Object *obj, Rva00375A73Context *context, float distance, float clearance);
    bool rva00375C28(Object *obj, Rva00375A73Coord *pos, float *a, Rva00375A73Coord *b);
};
extern AerialPathfinder *TheAerialPathfinder;

bool AerialPathfinder::rva00375A73(Rva00375A73Context *context, float value,
    Rva00375A73Coord *output)
{
    if (0.0f > value)
        return false;
    context->prepare(1, 4000, 1000.0f, 1000.0f, 0, 0);
    if (!context->valid24)
        return false;
    context->value18 = value;
    if (!TheSplineService->rva00311974(context, 0, 0))
        return false;
    *output = context->position48;
    return true;
}

bool AerialPathfinder::rva00375DFF(Object *obj, Rva00375A73Context *context, float distance, float clearance)
{
    if (obj->m_258 && context->valid24)
    {
        Rva00375A73Coord pos;
        if (rva00375A73(context, distance, &pos))
        {
            pos.z -= clearance * g_00C18564;
            bool above = false;
            bool hit = false;
            float t = TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0);
            if (pos.z > t)
                above = true;
            t = 0.0f;
            Rva00375A73Coord where;
            where.x = 0.0f;
            where.y = 0.0f;
            where.z = 0.0f;
            if (TheAerialPathfinder->rva00375C28(obj, &pos, &t, &where))
                hit = true;
            return above == true && hit == true;
        }
    }
    return true;
}
