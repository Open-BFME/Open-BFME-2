// cl: /O1 /Oi /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc
// Target evidence: game.dat 136F5B..137054; WB9B2CB0 PostLoad renderasset.cpp:302.
// Only observed virtual slots and field offsets are represented here.
#include "ascii_string.h"
// WWMath::Fabs from BFME1 34f59164f6: clear the IEEE-754 sign bit.
inline float renderAbs(float val) { int bits = *(int *)&val; bits &= 0x7fffffff; return *(float *)&bits; }
class RenderObjClass;
RenderObjClass *Create_Render_Obj(const char *);
void Rva00135F6CMakeUnique(void *);
struct Rva00136F5BRange { void *begin; void *end; void *capacity; bool empty() const { return begin == end; } };
void rva00136E95(RenderObjClass *, Rva00136F5BRange *, Rva00136F5BRange *, Rva00136F5BRange *);
extern bool g_Va00DB6218;
class Rva00136F5BRenderView {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void setName(const char *);
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual void slot85();
    virtual void slot86();
    virtual void slot87();
    virtual void slot88();
    virtual void slot89();
    virtual void slot90();
    virtual void slot91();
    virtual void scale(float);
    virtual void slot93();
    virtual void slot94();
    virtual void slot95();
    virtual void slot96();
    virtual void slot97();
    virtual void slot98();
    virtual void slot99();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual void slot114();
    virtual void slot115();
    virtual void slot116();
    virtual void slot117();
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void applyOptions(const void *);
};
struct Rva00136F5BOptions { unsigned color:3; unsigned unknown:27; unsigned enabled:1; unsigned reserved:1; unsigned extra[3]; bool enabledValue() const { return enabled != 0; } unsigned colorValue() const { return color; } };
namespace RenderAsset {
class ModifiedRenderFactory {
public:
    virtual const char *getName();
    void PostLoad();
    char unknown04[20];
    AsciiString baseName;
    Rva00136F5BRange first;
    Rva00136F5BRange textures;
    Rva00136F5BRange excluded;
    float scale;
    Rva00136F5BOptions options;
    RenderObjClass *rendObj;
};
void ModifiedRenderFactory::PostLoad()
{
    rendObj = Create_Render_Obj(baseName.str());
    if (!rendObj) return;
    ((Rva00136F5BRenderView *)rendObj)->setName(getName());
    bool scaled = renderAbs(scale - 1.0f) > 0.01f;
    bool colored = g_Va00DB6218 && (options.enabledValue() || options.colorValue() > 0);
    bool textured = !textures.empty();
    if (scaled || colored || textured) {
        if (scaled) ((Rva00136F5BRenderView *)rendObj)->scale(scale);
        if (textured) {
            Rva00135F6CMakeUnique(rendObj);
            rva00136E95(rendObj, &first, &textures, &excluded);
        }
        if (colored) {
            Rva00135F6CMakeUnique(rendObj);
            ((Rva00136F5BRenderView *)rendObj)->applyOptions(&options);
        }
    }
}
}



