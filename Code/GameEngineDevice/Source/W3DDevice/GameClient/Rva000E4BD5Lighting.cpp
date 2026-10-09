// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /Oy- /ICode/Libraries/Include
#include "Lib/Coord3D.h"
// Semantic guide: Zero Hour W3DTreeBuffer lighting through BFME1. Target
// E4BD5..E4F20 owns all offsets, globals, weather and terrain virtual slots.
// Original target method/class name is unproven; retain address-derived identity.
// MSVC7.1 needs references for R/G accumulators to reproduce both RGB reloads.
class GlobalData;extern GlobalData *TheWritableGlobalData;
struct LightingGlobals {char p[0x49];bool skipFirst;char p4A[0x944-0x4A];float red,green,blue;};
class Rva0027070CGlobal;extern Rva0027070CGlobal *g_00DFE1E4;
struct LightingWeatherDispatch {virtual void p0();virtual void p1();virtual void p2();virtual void p3();virtual void p4();virtual void p5();virtual void p6();virtual void p7();virtual void p8();virtual void p9();virtual void p10();virtual void p11();virtual void p12();virtual void p13();virtual void p14();virtual bool enabled();virtual void p16();virtual void p17();virtual Coord3D color();};
class BaseHeightMapRenderObjClass;extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
struct LightingTerrainDispatch {virtual void p0();virtual void p1();virtual void p2();virtual void p3();virtual void p4();virtual void p5();virtual void p6();virtual void p7();virtual void p8();virtual void p9();virtual void p10();virtual void p11();virtual void p12();virtual void p13();virtual void p14();virtual void p15();virtual void p16();virtual void p17();virtual void p18();virtual void p19();virtual void p20();virtual void p21();virtual void p22();virtual void p23();virtual void p24();virtual void p25();virtual void p26();virtual void p27();virtual void p28();virtual void p29();virtual void p30();virtual void p31();virtual void p32();virtual void p33();virtual void p34();virtual void p35();virtual void p36();virtual void p37();virtual void p38();virtual void p39();virtual void p40();virtual void p41();virtual void p42();virtual void p43();virtual void p44();virtual void p45();virtual void p46();virtual void p47();virtual void p48();virtual void p49();virtual void p50();virtual void p51();virtual void p52();virtual void p53();virtual void p54();virtual void p55();virtual void p56();virtual void p57();virtual void p58();virtual void p59();virtual void p60();virtual void p61();virtual void p62();virtual void p63();virtual void p64();virtual void p65();virtual void p66();virtual void p67();virtual void p68();virtual void p69();virtual void p70();virtual void p71();virtual void p72();virtual void p73();virtual void p74();virtual void p75();virtual void p76();virtual void p77();virtual void p78();virtual void p79();virtual void p80();virtual void p81();virtual void p82();virtual void p83();virtual void p84();virtual void p85();virtual void p86();virtual void p87();virtual void p88();virtual void p89();virtual void p90();virtual void p91();virtual void p92();virtual void p93();virtual void p94();virtual void p95();virtual void p96();virtual void p97();virtual void p98();virtual void p99();virtual void p100();virtual void p101();virtual void p102();virtual void p103();virtual void p104();virtual void p105();virtual void p106();virtual void p107();virtual void p108();virtual void p109();virtual void p110();virtual void p111();virtual void p112();virtual void p113();virtual void p114();virtual void p115();virtual void p116();virtual void p117();virtual void p118();virtual void p119();virtual void p120();virtual void p121();virtual void p122();virtual void p123();virtual void p124();virtual void p125();virtual void p126();virtual void p127();virtual void p128();virtual void p129();virtual void p130();virtual void p131();virtual void p132();virtual void p133();virtual void p134();virtual void p135();virtual void p136();virtual void p137();virtual void p138();virtual void p139();virtual void p140();virtual void p141();virtual void p142();virtual void p143();virtual void p144();virtual void p145();virtual void p146();virtual int mode();};
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#define Rva006F7DA0ZeroRange 0.0f
#define Rva006F7DA0One 1.0f
#define Rva006F7DA0Uint32Scale 4294967296.0f
#define Rva006F7DA0OneOver255 (1.0f / 255.0f)
#define Rva006F7DA0OneDouble 1.0
#define Rva006F7DA0Scale255 255.0f

struct Coord3D;

class WWMath {
public:
    static Real __fastcall Inv_Sqrt(Real value);
};

extern "C" long __ftol2(double value);

class Vector3 {
public:
    Real X;
    Real Y;
    Real Z;

    Vector3(Real x, Real y, Real z) : X(x), Y(y), Z(z) {}

    __forceinline void Normalize(void)
    {
        Real lengthSquared = X * X + Y * Y + Z * Z;

        if (lengthSquared != 0.0f) {
            Real inverseLength = WWMath::Inv_Sqrt(lengthSquared);
            X *= inverseLength;
            Y *= inverseLength;
            Z *= inverseLength;
        }
    }
};

struct BfmeLighting36 {
    struct RGBColor {
        Real red;
        Real green;
        Real blue;
    } ambient;
    RGBColor diffuse;
    Coord3D lightPos;
};

static Real Rva006F7DA0Fabs(Real value)
{
    union {
        Real realValue;
        UnsignedInt bits;
    } converted;

    converted.realValue = value;
    converted.bits &= 0x7FFFFFFF;
    return converted.realValue;
}

class Rva000E4BD5Lighting {
public:
    static UnsignedInt __stdcall doLighting(const BfmeLighting36 *objectLighting,
                                             const Coord3D *emissive,
                                             UnsignedInt vertDiffuse,
                                             Real scale,
                                             UnsignedInt alpha);
};

// ?doLighting@Rva000E4BD5Lighting@@SGIPBUBfmeLighting36@@PBUCoord3D@@IMI@Z
UnsignedInt __stdcall Rva000E4BD5Lighting::doLighting(
    const BfmeLighting36 *objectLighting,
    const Coord3D *emissive,
    UnsignedInt vertDiffuse,
    Real scale,
    UnsignedInt alpha)
{
    Real _shadeR; Real &shadeR = _shadeR;
    Real _shadeG; Real &shadeG = _shadeG;
    Real shadeB;
    Real shade;
    Int i;

    shadeR = objectLighting[0].ambient.red + emissive->x;
    shadeG = objectLighting[0].ambient.green + emissive->y;
    shadeB = objectLighting[0].ambient.blue + emissive->z;

    i = 0; if (((LightingGlobals*)TheWritableGlobalData)->skipFirst) i = 1; for (; i < 3; ++i) {
        Vector3 lightDirection(objectLighting[i].lightPos.x,
                               objectLighting[i].lightPos.y,
                               objectLighting[i].lightPos.z);
        lightDirection.Normalize();
        shade = Rva006F7DA0Fabs(-lightDirection.Z);

        if (shade > 1.0f) {
            shade = 1.0f;
        }

        shadeR += shade * objectLighting[i].diffuse.red;
        shadeG += shade * objectLighting[i].diffuse.green;
        shadeB += shade * objectLighting[i].diffuse.blue;
    }

    if(g_00DFE1E4 && ((LightingWeatherDispatch*)g_00DFE1E4)->enabled()) {
        shadeR *= 1.0f - ((LightingWeatherDispatch*)g_00DFE1E4)->color().x;
        shadeG *= 1.0f - ((LightingWeatherDispatch*)g_00DFE1E4)->color().y;
        shadeB *= 1.0f - ((LightingWeatherDispatch*)g_00DFE1E4)->color().z;
    }
    if(((LightingTerrainDispatch*)TheTerrainRenderObject)->mode()<1) {
        shadeR *= ((LightingGlobals*)TheWritableGlobalData)->red;
        shadeG *= ((LightingGlobals*)TheWritableGlobalData)->green;
        shadeB *= ((LightingGlobals*)TheWritableGlobalData)->blue;
    }
    if (vertDiffuse != 0xFFFFFFFF) {
        shade = (Real)(vertDiffuse & 0xFF);
        shadeB *= shade / 255.0f;
        shade = (Real)((vertDiffuse >> 8) & 0xFF);
        shadeG *= shade / 255.0f;
        shade = (Real)((vertDiffuse >> 16) & 0xFF);
        shadeR *= shade / 255.0f;
    }

    shadeR *= scale;
    shadeG *= scale;
    shadeB *= scale;

    if (shadeR > 1.0) shadeR = 1.0;
    if (shadeR < 0.0f) shadeR = 0.0f;
    if (shadeG > 1.0) shadeG = 1.0;
    if (shadeG < 0.0f) shadeG = 0.0f;
    if (shadeB > 1.0) shadeB = 1.0;
    if (shadeB < 0.0f) shadeB = 0.0f;

    return (UnsignedInt)(shadeB * Rva006F7DA0Scale255)
        | ((UnsignedInt)(shadeG * Rva006F7DA0Scale255) << 8)
        | ((UnsignedInt)(shadeR * Rva006F7DA0Scale255) << 16)
        | (alpha << 24);
}
