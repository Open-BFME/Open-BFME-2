// ?rva002153C7@Rva002153C7@@QAE?AURva002153C7Point@@XZ
// partial score=0.9 date=2026-10-07
// ?rva002153C7@Rva002153C7@@QAE?AURva002153C7Point@@XZ
// cl: /O1 /arch:SSE /DNDEBUG /MD /Oy- /ICode/Libraries/Include/Lib
// Native 002153C7..0021545C, 149B. ECX receiver and one output-home word
// at EBP+8; RET4/EAX returns that home. A three-float result view is measured.
// Nontrivial point copy is a source-shape inference for result elision;
// only the three-float output ABI is independently measured.
// The random helper is rowed WWMath::Random_Float. Helper002152BD is 266B,
// cdecl hidden-result-compatible: three words (result, float, float), RET0.
// Original receiver/method/result type identities remain unproven.
struct Rva002153C7Point
{
    float x, y, z;
    Rva002153C7Point() {}
    Rva002153C7Point(const Rva002153C7Point &p) : x(p.x), y(p.y), z(p.z) {}
    Rva002153C7Point(float a, float b, float c) : x(a), y(b), z(c) {}
};
class WWMath
{
public:
    static float Random_Float();
};
Rva002153C7Point Rva002152BD(float a, float b);
class Rva002153C7
{
public:
    Rva002153C7Point rva002153C7();
private:
    char unknown00[0x94];
    float a0, b0, a1, b1, a2, b2;
};
Rva002153C7Point Rva002153C7::rva002153C7()
{
    int choice = static_cast<int>(WWMath::Random_Float() * 100.0f) % 3;
    if (choice == 0)
        return Rva002152BD(a0, b0);
    else if (choice == 1)
        return Rva002152BD(a1, b1);
    else if (choice == 2)
        return Rva002152BD(a2, b2);
    else
        return Rva002153C7Point(1000.0f, 1000.0f, 1000.0f);
}
