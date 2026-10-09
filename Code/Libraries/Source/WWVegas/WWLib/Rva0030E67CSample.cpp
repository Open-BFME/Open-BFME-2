// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva0030E67C@Rva0030E7D0@@QAEMMM@Z retail 0x0030E67C (340 bytes, RET 8).
// Bilinear/triangle sample of the float grid whose constructor is rowed at
// 0x0030E7D0 (vector at +0, width +0xC, height +0x10, cell scale +0x14,
// border cells +0x18, valid byte +0x1C; helpers 0x0030E7FE fill_insert,
// 0x0030E8DF clear, 0x0030E910 resize). Target evidence: the border is
// scaled by 10.0f (the map cell size), coordinates are divided by the cell
// scale and floored through the CRT, clamped to the grid, and the last cell
// row/column returns the sample itself; otherwise the cell is split along
// its diagonal like Zero Hour's BaseHeightMap::getHeightMapHeight, selecting
// the triangle by fy > fx. The method name is a placeholder for the address.
extern "C" { static float __cdecl floorf(float); }
#include <math.h>

#define MAP_XY_FACTOR 10.0f

class Rva0030E7D0
{
public:
    float rva0030E67C(float x, float y);
private:
    float *m_data;
    int m_04;
    int m_08;
    int m_width;
    int m_height;
    float m_cellScale;
    int m_border;
    bool m_valid;
};

static __forceinline float fast_float_floor(float f)
{
    return floorf(f);
}

static __forceinline long fast_float2long_round(float f)
{
    long i;
    __asm {
        fld [f]
        fistp [i]
    }
    return i;
}

float Rva0030E7D0::rva0030E67C(float x, float y)
{
    if (!m_valid)
        return 0.0f;

    float border = (float)m_border * MAP_XY_FACTOR;
    float inverse = 1.0f / m_cellScale;
    x = (x + border) * inverse;
    y = (y + border) * inverse;
    int ix = fast_float2long_round(fast_float_floor(x));
    int iy = fast_float2long_round(fast_float_floor(y));
    float fx = x - (float)ix;
    float fy = y - (float)iy;
    if (ix < 0)
        ix = 0;
    if (iy < 0)
        iy = 0;
    if (ix > m_width - 1)
        ix = m_width - 1;
    if (iy > m_height - 1)
        iy = m_height - 1;
    if (ix > m_width - 2 || iy > m_height - 2)
        return m_data[iy * m_width + ix];

    int base = iy * m_width + ix;
    const float *data = m_data;
    float p00 = data[base];
    float p11 = data[base + m_width + 1];
    float h;
    if (fy > fx)
    {
        float c = data[base + m_width];
        h = (p00 - c) * (1.0f - fy) + (p11 - c) * fx + c;
    }
    else
    {
        float c = data[base + 1];
        h = (p00 - c) * (1.0f - fx) + (p11 - c) * fy + c;
    }
    return h;
}
