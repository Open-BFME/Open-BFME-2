// ??0Rva00142EE0@@QAE@H@Z
// partial score=0.9525 date=2026-10-06
// ??0Rva00142EE0@@QAE@H@Z
// partial score=0.95 date=2026-10-05
// ??0Rva00142EE0@@QAE@H@Z
// partial score=0.92 date=2026-09-30
// cl: /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// 0x00142EE0 256B ctor taking int, 0x148-byte WW3D-side record.
// Evidence: sole init of the 0x148 record callers construct on stack
// (0x00118660 sub esp,0x148 then lea ecx,[esp+8] plus int arg); float 1.0
// via g_Va00BBB8D8; indexed m_b8[m_138] store with m_138==0.

extern float g_Va00BBB8D8;
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class Rva00142EE0
{
public:
	Rva00142EE0(int v);

private:
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	float m_14;
	float m_18;
	float m_1c;
	float m_20;
	float m_24;
	int m_28;
	int m_2c;
	int m_30[32];
	int m_b0;
	int m_b4;
	int m_b8[32];
	volatile int m_138;
	int m_13c;
	int m_140;
	int m_144;
};

// ??0Rva00142EE0@@QAE@H@Z present-unmatched
Rva00142EE0::Rva00142EE0(int v)
{
	m_00 = v;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_0c = 0.0f;
	m_10 = 0.0f;
	m_14 = 0.0f;
	m_18 = 0.0f;
	_ReadWriteBarrier();
	m_138 = 0;
	float one = g_Va00BBB8D8;
	m_1c = one;
	m_20 = one;
	m_24 = one;
	m_28 = 0;
	m_2c = 0;
	m_b0 = 0;
	m_b4 = 0;
	m_13c = 0;
	m_140 = 0;
	m_144 = 0;
	_ReadWriteBarrier();
	m_b8[m_138] = 0;
	for (int i = 0; i < 32; ++i) {
		m_30[i] = 0;
	}
}
