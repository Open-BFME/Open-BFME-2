// cl: /MD
// ?rva005D4B6E@Rva005D4B6E@@QAEXM@Z @0x005D4B6E 64B: float pos firer via rowed Fire 0x00527925 with SetPos plus EmptyString fallback no store. Evidence: ucomiss float at +0x20 plus rowed Fire plus TheRva00222A8BTarget 0x009FE4CC plus g_Rva0107301CEmptyString 0x007BAC1C plus SetPos literal plus unblocks 0x005D4BD4 caller 0x005D4BDF siblings 0x005D4B1F 0x005D4AD0.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00527925Fire(void *target, void *level, const char *prefix, const char *function, const float *val);

struct Rva005D4B6ETeam
{
	char m_pad[8];
	char m_name[1];
};

class Rva005D4B6E
{
public:
	void rva005D4B6E(float v);
private:
	char m_pad00[4];
	void *m_level04;
	Rva005D4B6ETeam *m_team08;
	char m_pad0C[0x20 - 0x0C];
	float m_float20;
};

void Rva005D4B6E::rva005D4B6E(float v)
{
	if (v != m_float20) {
		const char *team = m_team08 ? m_team08->m_name : "";
		Rva00527925Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, team, "SetPos", &v);
	}
}
