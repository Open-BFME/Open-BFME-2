// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?SetPlayerHealth@Impl@DynamicAutoResolvePlayerPanelMovieClip@StrategicHUD@@QAEXM@Z @ 0x005FB8B4 79B: float health setter via rowed Fire 0x00527925 with SetPlayerHealth plus EmptyString fallback. Evidence: ucomiss float at +0x34 plus rowed Fire plus TheRva00222A8BTarget 0x009FE4CC plus g_Rva0107301CEmptyString 0x007BAC1C plus SetPlayerHealth literal plus gap between AptPlayerNameSet rows.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
extern "C" float kF7C;

int __cdecl Rva00527925Fire(void *target, void *level, const char *prefix, const char *function, const float *val);

struct Rva005FB770Team
{
	char m_pad[8];
	char m_name[1];
};

namespace StrategicHUD {
class DynamicAutoResolvePlayerPanelMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl
{
public:
	void SetPlayerHealth(float v);
	void PlayHitAnim(float v);
	void PlayReinforceAnim(float v);
private:
	char m_pad00[4];
	void *m_level04;
	Rva005FB770Team *m_team08;
	char m_pad0C[0x34 - 0x0C];
	float m_float34;
	char m_pad38[0x4C - 0x38];
	bool m_flag4C;
	bool m_flag4D;
};

void StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl::SetPlayerHealth(float v)
{
	if (v != m_float34) {
		const char *team = m_team08 ? m_team08->m_name : "";
		Rva00527925Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, team, "SetPlayerHealth", &v);
		m_float34 = v;
	}
}

void StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl::PlayHitAnim(float v)
{
	float *pHealth = &m_float34;
	float *p = pHealth;
	if (!(v > *pHealth))
		p = &v;
	v = *p;
	const char *team = m_team08 ? m_team08->m_name : "";
	Rva00527925Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, team, "PlayHitAnim", &v);
	*pHealth -= v;
	m_flag4C = true;
}

void StrategicHUD::DynamicAutoResolvePlayerPanelMovieClip::Impl::PlayReinforceAnim(float v)
{
	float cap = kF7C - m_float34;
	float *p = &cap;
	if (!(v > cap))
		p = &v;
	v = *p;
	const char *team = m_team08 ? m_team08->m_name : "";
	Rva00527925Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, team, "PlayReinforceAnim", &v);
	m_flag4D = true;
	m_float34 += v;
}
