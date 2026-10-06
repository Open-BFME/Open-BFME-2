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
