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

// Native boundary 0x00051038..0x0005106A, RET0. The IAT and the
// WorldBuilder counterpart independently establish the two Miles imports.
// Target accesses prove only the flag at +2 and handles at +4/+8; the
// original owner name and its complete layout remain unknown. Keep the
// address-derived spelling already used by the existing caller pin.
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
};

bool Rva0005F279Elem::rva00051038()
{
	if (m_is3D)
	{
		if (!m_sample3D)
			return true;
		else
			return AIL_3D_sample_status(m_sample3D) != 4;
	}
	else
	{
		if (!m_sample2D)
			return true;
		else
			return AIL_sample_status(m_sample2D) != 4;
	}
}
