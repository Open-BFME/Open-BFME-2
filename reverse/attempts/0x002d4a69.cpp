// ?d_002d4a69@@YAXXZ
// partial score=0.98 date=2026-10-07
// cl: /O1 /G7 /arch:SSE /Oy- /Op /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Native2D4A69..2D4AEF RET0. CreateRadarPing/MoveRadarPing strings and
// rowed2D43EF establish the callback ABI. +18 is its int parameter, +10 an
// AsciiString, +1C/+20 normalized coordinates; virtual40 returns two floats.
// Original receiver and method names unresolved; retain an address view.
#include "ascii_string.h"
struct Rva002D4A69Scale { float x, y; };
class Rva00222A8BTarget
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual Rva002D4A69Scale *slot16();
};
int Rva002D43EFFire(Rva00222A8BTarget *, void *, const char *, int *, const AsciiString *);
int Rva002D4464Fire(Rva00222A8BTarget *, void *, const char *, int *, float *, float *);
extern int g_00DFE4CC;
struct Rva002D4A69Owner
{
    char prefix[0x5C];
    void *level;
};
class Rva002D4A69
{
public:
    void rva002D4A69();
private:
    char prefix[8];
    Rva002D4A69Owner *owner;
    char pad0C[4];
    AsciiString text;
    bool initialized;
    char pad15[3];
    int id;
    float x, y;
};
void Rva002D4A69::rva002D4A69()
{
    if (initialized)
        return;
    if (owner)
    {
        Rva002D43EFFire(reinterpret_cast<Rva00222A8BTarget *>(g_00DFE4CC),
                        owner->level, "CreateRadarPing", &id, &text);
        Rva002D4A69Scale *scale =
            reinterpret_cast<Rva00222A8BTarget *>(g_00DFE4CC)->slot16();
        float scaledY = y * scale->y;
        float scaledX = x * scale->x;
        Rva002D4464Fire(reinterpret_cast<Rva00222A8BTarget *>(g_00DFE4CC),
                        owner->level, "MoveRadarPing", &id, &scaledX, &scaledY);
    }
    initialized = true;
}
