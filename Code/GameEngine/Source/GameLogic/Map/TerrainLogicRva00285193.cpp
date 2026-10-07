// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /ICode/Libraries/Include/Lib
#include "Coord3D.h"
class G00DFF080Obj;
extern G00DFF080Obj *g_00DFF080;
template<int N> class Rva00285193Slots : public Rva00285193Slots<N-1>
{
public:
    virtual void unused(char (*)[N]) = 0;
};
template<> class Rva00285193Slots<0> {};
class Object;
class TerrainLogic
{
public:
    void rva00285193(Object *argument);
    void rva00284DD2(const Coord3D *position, float orientation, const void *geometry,
        Object **object, bool optionA, bool optionB);
};
// Native00285193..00285202, 111B, RET4. Object+38/44/A8 and template
// bit positions108/109/11A are measured; preserve the existing signed-char
// layer query. Helper00284DD2's933B entry proves six-word RET18 ABI and
// the same receiver578/57C pointer range; original method meaning unknown.
class Object
{
public:
    char rva00294815();
};
struct Rva00285193TemplateView
{
    char unknown00[0x108];
    unsigned char flags108, flags109;
    char unknown10A[0x11A - 0x10A];
    unsigned char flags11A;
};
struct Rva00285193ObjectView
{
    void *unknown00;
    Rva00285193TemplateView *data;
    char unknown08[0x38 - 8];
    Coord3D position;
    float orientation;
    char unknown48[0xA8 - 0x48];
    char geometry;
};
class Rva00285193GlobalView : public Rva00285193Slots<27>
{
public:
    virtual void slot6C(Object *object) = 0;
};
void TerrainLogic::rva00285193(Object *argument)
{
    reinterpret_cast<Rva00285193GlobalView *>(g_00DFF080)->slot6C(argument);
    if (!(reinterpret_cast<Rva00285193ObjectView *>(argument)->data->flags108 & 4)
        && (argument->rva00294815() > 1
            || (reinterpret_cast<Rva00285193ObjectView *>(argument)->data->flags109 & 8))
        && !(reinterpret_cast<Rva00285193ObjectView *>(argument)->data->flags11A & 0x80))
    {
        float orientation = reinterpret_cast<Rva00285193ObjectView *>(argument)->orientation;
        Object *object = argument;
        Rva00285193ObjectView *view = reinterpret_cast<Rva00285193ObjectView *>(object);
        rva00284DD2(&view->position, orientation, &view->geometry, &object, true, false);
    }
}
