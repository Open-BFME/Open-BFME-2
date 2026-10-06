// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva005FF38D@Rva005FF38D@@QAEX_N@Z @ 0x005FF38D 92B
// Guarded SetSelectionOverlayState via rowed AptCall 0x0050E9FE with _over else _rollOut.
// Evidence: caller jmp 0x005FF4D8; globals TheRva00222A8BTarget g_Rva0107301CEmptyString;
// strings SetSelectionOverlayState _over _rollOut; layout +4 level +8 team +0x3c guard +0x3d flag;
// precedent Rva005F086E 0x005F086E.
class Rva00222A8BTarget;

extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];

int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

struct Rva005FF38DTeam
{
	char m_pad[8];
	char m_name[1];
};

class Rva005FF38D
{
public:
	void rva005FF38D(bool flag);
private:
	char m_pad0[4];
	void *m_level;
	Rva005FF38DTeam *m_team;
	char m_pad0C[48];
	bool m_guard3C;
	bool m_flag3D;
};

void Rva005FF38D::rva005FF38D(bool flag)
{
	if (flag == m_flag3D)
		return;
	if (!m_guard3C) {
		const char *state = flag ? "_over" : "_rollOut";
		const char *prefix = m_team ? m_team->m_name : g_Rva0107301CEmptyString;
		Rva0050E9FEAptCall(TheRva00222A8BTarget, m_level, prefix, "SetSelectionOverlayState", &state);
	}
	m_flag3D = flag;
}
