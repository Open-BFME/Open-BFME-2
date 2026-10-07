// cl: /O1 /arch:SSE /G7 /MD
// Native 00375A73..00375AE7, RET 12 and AL result. No incoming ECX
// value is read: __stdcall is a view of the three measured stack inputs,
// not a claim about the original declaration. It invokes input slot +8
// with (1, 4000, 1000, 1000, 0, 0), checks input byte +24, stores the
// float input at +18 and queries TheSplineService before copying +48 XYZ.
// The named global's decorated type is read from the verified GameEngine
// init relocation at +4502. Its 00311974 member is RET 12 with AL result.
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

// ?rva00375A73@@YG_NPAVRva00375A73Context@@MPAURva00375A73Coord@@@Z
bool __stdcall rva00375A73(Rva00375A73Context *context, float value,
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
