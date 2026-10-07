// ?rva00285193@TerrainLogic@@QAEXPAVObject@@@Z
// partial score=0.93 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /ICode/Libraries/Include/Lib
// Native00283CE7..00283D70, 137B, RET4. TerrainLogic receiver from rowed
// sibling query00283D70 and its callers. Pointer range578/57C, child584,
// stamp1910 and record key+C are measured; original member names unknown.
#include "Coord3D.h"
class Object;
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva00283CE7FrameView { char unknown00[0x40]; unsigned int frame; };
class Rva0027D098
{
public:
    void rva0027D098();
};
struct Rva00283CE7RecordView { char unknown00[12]; unsigned int key; };
class Rva002872BA
{
public:
    void rva0028641F(unsigned int key, Rva0027D098 *record);
};
extern Rva002872BA *TheTriggerManager;
class G00DFF080Obj;
extern G00DFF080Obj *g_00DFF080;
template<int N> class Rva00283CE7Slots : public Rva00283CE7Slots<N-1>
{
public:
    virtual void unused(char (*)[N]) = 0;
};
template<> class Rva00283CE7Slots<0> {};
class Rva00283CE7GlobalView : public Rva00283CE7Slots<22>
{
public:
    virtual void slot58(unsigned int key) = 0;
};
class Rva00283CB3
{
public:
    void rva00283CB3(Rva0027D098 *record);
};
class TerrainLogic
{
public:
    void rva00283CE7(unsigned int key);
    void rva00285193(Object *argument);
    void rva00284DD2(const Coord3D *position, float orientation, const void *geometry,
        Object **object, bool optionA, bool optionB);
private:
    char unknown00[0x578];
    Rva0027D098 **first, **last, **limit;
    Rva00283CB3 *child;
    char unknown588[0x1910 - 0x588];
    unsigned int stamp;
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
class Rva00285193GlobalView : public Rva00283CE7Slots<27>
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
        Object *object = argument;
        Rva00285193ObjectView *view = reinterpret_cast<Rva00285193ObjectView *>(object);
        rva00284DD2(&view->position, view->orientation, &view->geometry, &object, true, false);
    }
}
