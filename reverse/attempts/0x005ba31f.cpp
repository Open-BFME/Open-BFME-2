// ?rva005BA31F@Rva005BA31F@@QAEHXZ
// partial score=0.93 date=2026-10-04
// cl: /O2 /GX-
// ?rva005BA31F@Rva005BA31F@@QAEHXZ @0x005BA31F 31B via expiry check with timeGetTime
// Evidence: this+0x968 dword time vs timeGetTime via IAT winmm; zero-guard then unsigned jae; xor-inc 1 else xor 0; caller 0x005BB79C; prev/next getters same page
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class Rva005BA31F
{
public:
	int rva005BA31F();
private:
	char _pad[0x968];
	unsigned long m_968;
};

// ?rva005BA31F@Rva005BA31F@@QAEHXZ present-unmatched
int Rva005BA31F::rva005BA31F()
{
	unsigned long *p = &m_968;
	if (*p == 0)
		return 0;
	unsigned long t = timeGetTime();
	if (*p < t)
		return 1;
	return 0;
}
