// cl: /O1 /arch:SSE /G7 /MD
// Ghidra FUN_00775a73, 116 bytes, RET12. Query initialization is slot 2;
// valid24, sample18 and the three-word output48 are proven by the native body.
// The registration at 0x0022F47E names global 0x00A0095C TheSplineService.
// The query's class and the helper's original method name remain unknown.

struct Rva00375A73Position { float x, y, z; };
class Rva00375A73Query
{
public:
    virtual void slot0() = 0;
    virtual void slot1() = 0;
    virtual void initialize(int kind, int duration, float a, float b, int c, int d) = 0;
    char unknown04[0x18 - 4];
    float sample;
    char unknown1c[0x24 - 0x1c];
    bool valid;
    char unknown25[0x48 - 0x25];
    Rva00375A73Position position;
};

class Rva0022B3F6Subsystem;
extern Rva0022B3F6Subsystem *TheSplineService;
class Rva00311974
{
public:
    bool rva00311974(Rva00375A73Query *query, bool flag, float *extraOutput);
};

// ?Rva00375A73@@YG_NPAVRva00375A73Query@@MPAURva00375A73Position@@@Z
bool __stdcall Rva00375A73(Rva00375A73Query *query, float value,
                          Rva00375A73Position *output)
{
    if (value < 0.0f)
        return false;
    query->initialize(1, 4000, 1000.0f, 1000.0f, 0, 0);
    if (!query->valid)
        return false;
    query->sample = value;
    if (!reinterpret_cast<Rva00311974 *>(TheSplineService)->rva00311974(query, false, 0))
        return false;
    *output = query->position;
    return true;
}
