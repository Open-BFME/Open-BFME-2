// ?rva00051038@Rva0005F279Elem@@QAE_NXZ
// partial score=0.88 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc /Oi-
// ?rva00051017@Rva00051017@@QAEXH@Z @ 0x00051017 33B
// Evidence: IAT AIL_set_3D_sample_loop_count at 0x00BBAAA0 vs AIL_set_sample_loop_count at 0x00BBAAA4; guard byte +2 selects handle +4 (3D) or +8 (2D); caller 0x0005EFE9; neighbour GetEnvironmentName TU flags.
typedef void *HSAMPLE;

extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_loop_count(HSAMPLE s, int count);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_loop_count(HSAMPLE s, int count);

class Rva00051017
{
public:
	void rva00051017(int count);

private:
	char m_pad0[2];
	unsigned char m_is3D;
	char m_pad3;
	HSAMPLE m_sample3D;
	HSAMPLE m_sample2D;
};

void Rva00051017::rva00051017(int count)
{
	if (m_is3D)
		AIL_set_3D_sample_loop_count(m_sample3D, count);
	else
		AIL_set_sample_loop_count(m_sample2D, count);
}

// 0x00051038..0x0005106A: nullable 3D/2D Miles sample status check.
// Native IAT entries and the debug build establish both imported operations;
// byte +2 selects handle +4 or +8. Keep the existing caller-owned RVA name:
// the original containing class and method name are not established.
extern "C" __declspec(dllimport) int __stdcall AIL_3D_sample_status(HSAMPLE sample);
extern "C" __declspec(dllimport) int __stdcall AIL_sample_status(HSAMPLE sample);

class Rva0005F279Elem
{
public:
    bool rva00051038();
private:
    unsigned char m_byte0;
    unsigned char m_byte1;
    unsigned char m_is3D;
    unsigned char m_byte3;
    HSAMPLE m_sample3D;
    HSAMPLE m_sample2D;
    unsigned char m_unknown0C[4];
    unsigned char m_byte10;
};

bool Rva0005F279Elem::rva00051038()
{
    if (m_is3D)
    {
        if (!m_sample3D)
            return true;
        return AIL_3D_sample_status(m_sample3D) != 4;
    }
    if (!m_sample2D)
        return true;
    return AIL_sample_status(m_sample2D) != 4;
}
