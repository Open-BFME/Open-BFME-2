// cl: /DNDEBUG /MD /Ob2
// ?rva0056DCBF@Rva0056DCBF@@QAEX_N@Z @0x0056DCBF 83B. Window enabler: stores bool
// arg to +0xCE then winEnable(arg) on each non-null GameWindow at
// +0xA4 +0xA8 +0xAC +0xB0 via rowed winEnable 0x00313BEC. Evidence: four
// test-je-push-call sequences plus bool store, ret 4, callers 0x00570F41
// 0x005713AB 0x005719F5 0x00571D22 0x00571FF8 0x00572746 0x0057284F,
// neighbours ConstIntGetters4 and MinimizeCurrentThreadWindow.
class GameWindow
{
public:
	int winEnable(bool enabled);
};
class Rva0056DCBF
{
public:
	void rva0056DCBF(bool enabled);
private:
	char m_pad00[0xA4];
	GameWindow *m_a4;
	GameWindow *m_a8;
	GameWindow *m_ac;
	GameWindow *m_b0;
	char m_padB4[0x1A];
	bool m_ce;
};
void Rva0056DCBF::rva0056DCBF(bool enabled)
{
	m_ce = enabled;
	if (m_a4)
		m_a4->winEnable(enabled);
	if (m_a8)
		m_a8->winEnable(enabled);
	if (m_ac)
		m_ac->winEnable(enabled);
	if (m_b0)
		m_b0->winEnable(enabled);
}
