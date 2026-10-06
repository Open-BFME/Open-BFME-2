// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005F2CBA@Rva005F2FEF@@QAEXM@Z @0x005F2CBA 135B
// Evidence: Apt rank progress float at +0x50 flag 4 at +0x58 via rowed Fire 0x00527925 AptCall 0x005FB5E6 strings SetMemberRankProgress SetMemberRankProgressBarState _show globals 0x009FE4CC 0x007BAC1C caller 0x005F2F49.
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];

int __cdecl Rva00527925Fire(void *target, void *level, const char *prefix, const char *function, const float *val);
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

struct Rva005F2FEFTeam
{
	char m_pad[8];
	char m_name[1];
};

class Rva005F2FEF
{
public:
	void rva005F2CBA(float progress);
private:
	char m_pad00[8];
	void *m_level08;
	Rva005F2FEFTeam *m_team0C;
	char m_pad10[0x50 - 0x10];
	float m_progress50;
	char m_pad54[4];
	unsigned char m_flags58;
};

void Rva005F2FEF::rva005F2CBA(float progress)
{
	if (progress != m_progress50) {
		const char *team = m_team0C ? m_team0C->m_name : g_Rva0107301CEmptyString;
		Rva00527925Fire(TheRva00222A8BTarget, m_level08, team, "SetMemberRankProgress", &progress);
		m_progress50 = progress;
	}
	if (!(m_flags58 & 4)) {
		const char *team = m_team0C ? m_team0C->m_name : g_Rva0107301CEmptyString;
		Rva005FB5E6AptCall(TheRva00222A8BTarget, m_level08, team, "SetMemberRankProgressBarState", "_show");
		m_flags58 |= 4;
	}
}
