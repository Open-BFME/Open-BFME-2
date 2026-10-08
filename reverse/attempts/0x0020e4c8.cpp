// ?rva0020E4C8@Rva0020E794@@QAE_NXZ
// partial score=0.5 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /MD
class LivingWorldLogic { public: void rva002BD64F(int value); };
extern LivingWorldLogic *TheLivingWorldLogic;
class LivingWorldBattle { public: int rva003F4831(); };
class Rva0020E794 {
public:
	bool rva0020E4C8();
private:
	unsigned char m_pad[0x14];
	LivingWorldBattle **m_begin;
	LivingWorldBattle **m_end;
};
bool Rva0020E794::rva0020E4C8()
{
	bool changed = false;
	for (;;) {
		LivingWorldBattle **it = m_begin;
		for (; it != m_end; ++it) {
			LivingWorldBattle *battle = *it;
			if (battle->rva003F4831() == 0) {
				TheLivingWorldLogic->rva002BD64F(reinterpret_cast<int>(battle));
				changed = true;
				break;
			}
		}
		if (it == m_end)
			return changed;
	}
}
