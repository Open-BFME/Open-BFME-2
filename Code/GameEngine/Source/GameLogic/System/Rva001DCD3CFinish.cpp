// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /arch:SSE
// ?rva001DCD3C@Rva001DCD3C@@QAEXXZ @ 0x001DCD3C 80B
// Honest address name: __thiscall clearer beside GameLogicModeGateChecks.
// Target evidence: 80B retail, SSE movss/xorps, no calls, 5 callers
// (0x1DD238 0x1DEEA0 0x1DF1E8 0x1DF520 0x1DF78F); first two floats from
// global VA 0x00BBB9AC (-1.0f), rest zeroed through +0x30. Prev/next pin TU and flags.
extern float g_00BBB9AC;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva001DCD3C
{
public:
    void rva001DCD3C();
private:
    volatile float m_00;
    volatile float m_04;
    volatile float m_08;
    volatile float m_0C;
    volatile float m_10;
    volatile float m_14;
    volatile float m_18;
    volatile float m_1C;
    volatile unsigned char m_20;
    volatile unsigned char m_21;
    volatile unsigned char m_22;
    volatile unsigned char m_pad23;
    volatile float m_24;
    volatile float m_28;
    volatile float m_2C;
    volatile int m_30;
};
void Rva001DCD3C::rva001DCD3C()
{
    float v = g_00BBB9AC;
    float zero = 0.0f;
    m_00 = v;
    m_04 = v;
    _ReadWriteBarrier();
    m_20 = 0;
    m_08 = zero;
    m_0C = zero;
    m_10 = zero;
    m_21 = 0;
    m_14 = zero;
    m_18 = zero;
    m_1C = zero;
    m_22 = 0;
    m_24 = zero;
    m_28 = zero;
    m_2C = zero;
    m_30 = 0;
}
