// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?Rva0055C0E1Write@@YAAAV?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@AAV12@ABURGBColor@@@Z at 0x0055C0E1 size 170
// Evidence: unlock lane; writes "R:"/"G:"/"B:" with int-scaled color components via
// _M_put_nowiden/_M_put_num/_M_put_char; caller 0x0055C263 writeINI; RGBColor layout red/green/blue floats.

#include <ostream>

struct RGBColor
{
    float red;
    float green;
    float blue;
};

extern float g_00BC2900;
// g_00BC2900: matched references place it at VA 0xbc2900 (retail .rdata value 255.0f).
float g_00BC2900 = 255.0f;
extern float g_Va007C26F0;

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva0055C0E1Write(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    const RGBColor &color)
{
    os << "R:" << (int)(color.red * g_00BC2900 + g_Va007C26F0) << ' ';
    os << "G:" << (int)(color.green * g_00BC2900 + g_Va007C26F0) << ' ';
    os << "B:" << (int)(color.blue * g_00BC2900 + g_Va007C26F0);
    return os;
}
