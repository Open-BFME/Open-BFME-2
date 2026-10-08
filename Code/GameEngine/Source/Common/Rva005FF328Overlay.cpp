// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva005FF328@Rva005FF328@@QAEX_N@Z @ 0x005FF328 101B
// Guarded SetSelectionOverlayState via rowed AptCall 0x0050E9FE with _show else _over or _hide.
// Evidence: caller jmp 0x005FF4D0; globals TheRva00222A8BTarget g_Rva0107301CEmptyString;
// strings SetSelectionOverlayState _show _over _hide; layout +4 level +8 team +0x3c flag +0x3d over;
// precedent Rva005F086E 0x005F086E and Rva005FF38D 0x005FF38D.
class Rva00222A8BTarget;

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

struct Rva005FF328Team
{
	char m_pad[8];
	char m_name[1];
};

class Rva005FF328
{
public:
	void rva005FF328(bool flag);
private:
	char m_pad0[4];
	void *m_level;
	Rva005FF328Team *m_team;
	char m_pad0C[48];
	bool m_flag3C;
	bool m_over3D;
};

void Rva005FF328::rva005FF328(bool flag)
{
	if (flag == m_flag3C)
		return;
	const char *state;
	if (flag)
		state = "_show";
	else
		state = m_over3D ? "_over" : "_hide";
	const char *prefix = m_team ? m_team->m_name : "";
	Rva0050E9FEAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level, prefix, "SetSelectionOverlayState", &state);
	m_flag3C = flag;
}
