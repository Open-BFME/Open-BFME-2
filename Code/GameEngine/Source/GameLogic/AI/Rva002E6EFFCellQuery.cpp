// cl: /O1 /G7 /Oy- /MD
// Native 002E6EFF..002E6F8B, framed ECX member, RET 8 and Bool result.
// Target evidence establishes a column grid +70, width +78, height +7C,
// 20-byte cells, and a nonzero unsigned word +6. The second argument is
// unread by this body. Original owner, method and field meanings are unknown.
// BFME1 ba7ddda7e8 PathfinderRva003DF250.cpp and ZH AIPathfind.cpp supply
// the rounding lead: floor a cell coordinate, narrow to float, then convert
// to int using the x87 rounding path. The first pure C++ /QIfist trial
// instead emits a qword FISTP and removes the float narrowing. This two-
// instruction helper is the donor's established x87 codegen blocker.
extern "C" __declspec(dllimport) double __cdecl floor(double);

static __forceinline long fast_float2long_round(float value)
{
    long result;
    __asm {
        fld [value]
        fistp [result]
    }
    return result;
}

struct Rva002E6EFFPosition { float x, y; };
struct Rva002E6EFFCell
{
    unsigned char prefix06[6];
    unsigned short value06;
    unsigned char suffix08[12];
};
class Rva002E6EFFGrid
{
public:
    bool rva002E6EFF(const Rva002E6EFFPosition *position, unsigned int unused);
    unsigned int rva00285860(const Rva002E6EFFPosition *position);
private:
    unsigned char prefix70[0x70];
    Rva002E6EFFCell **columns;
    unsigned int unknown74;
    int width, height;
};

// ?rva002E6EFF@Rva002E6EFFGrid@@QAE_NPBURva002E6EFFPosition@@I@Z
bool Rva002E6EFFGrid::rva002E6EFF(const Rva002E6EFFPosition *position,
    unsigned int unused)
{
    int x = fast_float2long_round((float)floor((position->x + 0.5f) * 0.1f));
    int y = fast_float2long_round((float)floor((position->y + 0.5f) * 0.1f));
    if (x < 0 || x >= width || y < 0 || y >= height)
        return false;
    return columns[x][y].value06 > 0;
}

// Native 00285860..002858E5 shares the exact rounding path and grid accesses
// with 002E6EFF, but returns the zero-extended cell word and consumes one
// stack argument (RET 4). This establishes the same structural grid view;
// the original class and method names remain unknown.
unsigned int Rva002E6EFFGrid::rva00285860(const Rva002E6EFFPosition *position)
{
    int x = fast_float2long_round((float)floor((position->x + 0.5f) * 0.1f));
    int y = fast_float2long_round((float)floor((position->y + 0.5f) * 0.1f));
    if (x < 0 || x >= width || y < 0 || y >= height)
        return 0;
    return columns[x][y].value06;
}
