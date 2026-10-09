// ?rva002D4A69@Rva002D4A69@@QAEXXZ
// partial score=0.98 date=2026-10-09
// ?rva002D4A69@Rva002D4A69@@QAEXXZ
// cl: /O1 /G7 /arch:SSE /Oy- /Op /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Native 2D4A69..2D4AEF RET0, 134B; CreateRadarPing/MoveRadarPing
// strings and real117B/205B callback helpers establish input/lifetime ABI.
// +10 AsciiString, +14 initialized flag, +18 int, +1C/+20 normalized XY,
// owner +8 has level at +5C. Virtual40 returns two scale floats.
// Existing provisional Apt manager global supplies canonical link identity;
// its exact original class/method names remain unresolved target facts.
// Emits134B with all relocations bound. Only remaining hot mismatch is
// +68 MOVSS scaled-X store versus owner PUSH ordering (two instructions).
// Pair grouping leaves identical gap; no new pin or fake register barrier.
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
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
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
        Rva002D43EFFire(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager),
                        owner->level, "CreateRadarPing", &id, &text);
        Rva002D4A69Scale *scale =
            reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->slot16();
        float scaledY = y * scale->y;
        float scaledX = x * scale->x;
        Rva002D4464Fire(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager),
                        owner->level, "MoveRadarPing", &id, &scaledX, &scaledY);
    }
    initialized = true;
}
