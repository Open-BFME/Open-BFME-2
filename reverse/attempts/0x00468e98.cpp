// ?rva00468E98@Rva00468E98@@QAEAAVVector2@@AAV2@MM@Z
// partial score=0.9 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// Native Ghidra 00468E98..00468F0F, 119B, RET12. Caller 00472620
// supplies an output address and two float words copied from Vector2;
// EAX returns the output address. Source-level grouping and hidden versus
// explicit result are unknown; this neutral interface states the ABI words.
// Angle comes from receiver +8 -> +44. Vector2 copy follows BFME1
// ba7ddda7e8 vector2.h; class identity and method name are unresolved.
// Retain the bank's established x87 fsincos codegen blocker: the CRT
// sin/cos calls precede its two rounded float results in retail.
extern "C" double __cdecl sin(double angle);
extern "C" double __cdecl cos(double angle);

class Vector2
{
public:
    float X, Y;
    Vector2() {}
    Vector2(const Vector2 &other) { X = other.X; Y = other.Y; }
    Vector2(float x, float y) { X = x; Y = y; }
    Vector2 &operator=(const Vector2 &other)
    { X = other.X; Y = other.Y; return *this; }
};
struct Rva00468E98Outer
{
    char unknown00[0x44];
    float angle;
};
class Rva00468E98
{
public:
    Vector2 &rva00468E98(Vector2 &output, float a, float b);
    char unknown00[8];
    Rva00468E98Outer *outer;
};

// ?rva00468E98@Rva00468E98@@QAEAAVVector2@@AAV2@MM@Z present-unmatched
Vector2 &Rva00468E98::rva00468E98(Vector2 &output, float a, float b)
{
    float angle = outer->angle;
    struct Trig { volatile float cosine; volatile float sine; } trig;
    trig.sine = (float)sin(angle);
    trig.cosine = (float)cos(angle);
    __asm {
        fld angle
        fsincos
        fstp trig.cosine
        fstp trig.sine
    }
    float x = reinterpret_cast<const volatile float &>(a);
    float cosine = trig.cosine;
    float sine = trig.sine;
    output.X = x * cosine - b * sine;
    output.Y = x * sine + b * cosine;
    return output;
}
