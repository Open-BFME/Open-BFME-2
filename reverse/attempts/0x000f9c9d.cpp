// ?rva000F9C9D@Rva000F9C9D@@QAE_NPA_NPAH@Z
// partial score=0.9 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD
// Native Ghidra 000F9C9D..000F9D94, 247B, RET8. Output byte is
// cleared; a zero pass counter is changed to six. The receiver supplies
// size18 and render surface4C; a six-word parameter block goes to the
// 394B cdecl helper 000780BC (two reference/pointer arguments; RET0).
// Global DFE758+D34 is saved at receiver1C then cleared before the rowed
// DX8 target/clear calls. Original receiver and method names are unknown.
struct Rva000F9C9DParameters
{
    int count;
    int length;
    float first;
    float second;
    float third;
    float fourth;
};
void Rva000780BC(void *holder, const Rva000F9C9DParameters &parameters);
extern void *g_00DFE758;
struct Rva000F9C9DFlags
{
    char unknown00[0xD34];
    bool flag;
};
struct IDirect3DSurface8;
class Vector3
{
public:
    float X, Y, Z;
    Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
};
class DX8Wrapper
{
public:
    static void Set_Render_Target(IDirect3DSurface8 *surface, bool defaultDepth);
    static void Clear(bool color, bool depth, bool stencil,
        const Vector3 &value, float alpha, float z, unsigned int stencilValue);
};
class Rva000F9C9D
{
public:
    bool rva000F9C9D(bool *output, int *passes);
private:
    char unknown00[0x14];
    float value;
    int size;
    bool savedFlag;
    char unknown1D[0x30 - 0x1D];
    bool active;
    char unknown31[3];
    char holder[0x18];
    IDirect3DSurface8 *surface;
};

// ?rva000F9C9D@Rva000F9C9D@@QAE_NPA_NPAH@Z present-unmatched
bool Rva000F9C9D::rva000F9C9D(bool *output, int *passes)
{
    *output = false;
    if (*passes != 0)
        return false;
    *passes = 6;
    float ratio = 18.0f / size;
    Rva000F9C9DParameters parameters;
    parameters.fourth = ratio * 0.11f;
    parameters.second = ratio * 0.06f;
    parameters.length = size * 2;
    parameters.first = 0.18f;
    parameters.third = 4.5f;
    parameters.count = 2;
    value = 0.8f;
    Rva000780BC(holder, parameters);
    savedFlag = reinterpret_cast<Rva000F9C9DFlags *>(g_00DFE758)->flag;
    reinterpret_cast<Rva000F9C9DFlags *>(g_00DFE758)->flag = false;
    DX8Wrapper::Set_Render_Target(surface, true);
    DX8Wrapper::Clear(true, false, false, Vector3(0.0f, 0.0f, 0.0f),
        0.0f, 1.0f, 0);
    active = true;
    return true;
}
