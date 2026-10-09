// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
// ?rva0010082F@Rva0010082F@@QAEXXZ, retail 0x0010082F, 338 bytes (ends RET at 0x100980).
// Per-frame update of a water render object (water cluster beside W3DWaterDepthShader getter
// 0x00100981, same object family): elapsed milliseconds from a function-local static
// timeGetTime stamp, converted through unsigned->float; the GlobalData (0x00DFE758) byte at
// +0xD45 replaces the measured time with 33.333332 ms; scaled to seconds and passed to slot 1
// of every object in two pointer ranges (+0x108..+0x10C, +0x118..+0x11C); then two texture
// scroll offsets (+0x12C, +0x130) advance by 8.25e-5 / 1.65e-4 and wrap into [-1, 1].
// Identity of the owning class is not established; the name is address-derived.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class GlobalData { public: char pad[0xD45]; bool m_D45; };
extern GlobalData *TheWritableGlobalData; // 0x00DFE758

class Rva0010082FPart { public: virtual void slot0(); virtual void Update(float); };

class Rva0010082F {
public:
    void rva0010082F();
    char pad0[0x108];
    Rva0010082FPart **begin1, **end1;
    char pad1[0x118 - 0x110];
    Rva0010082FPart **begin2, **end2;
    char pad2[0x12C - 0x120];
    float u, v;
};

void Rva0010082F::rva0010082F()
{
    static unsigned long last = timeGetTime();
    unsigned long now = timeGetTime();
    float step = (float)(now - last);
    if (TheWritableGlobalData->m_D45)
        step = 33.333332f;
    last = now;
    float seconds = step * 0.001f;
    Rva0010082FPart **p = begin1;
    for (; p != end1; ++p)
        (*p)->Update(seconds);
    for (p = begin2; p != end2; ++p)
        (*p)->Update(seconds);
    u = u + 8.25e-5f;
    v = v + 1.65e-4f;
    if (u > 1.0f)
        u = u - 1.0f;
    if (v > 1.0f)
        v = v - 1.0f;
    if (-1.0f > u)
        u = u + 1.0f;
    if (-1.0f > v)
        v = v + 1.0f;
}
