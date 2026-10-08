// ?rva0020E4C8@Rva0020E794@@QAE_NXZ
// partial score=0.85 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /MD
// ?rva0020E794@Rva0020E794@@QAEPAVLivingWorldBattle@@XZ, retail 0x0020E794, 41 bytes.
// Pointer scan at +0x14/+0x18 over LivingWorldBattle pointers via rowed 0x003F4831
// returning first element with positive count else NULL. Caller at 0x0020EC21.

class LivingWorldLogic { public: void rva002BD64F(int value); };
extern LivingWorldLogic *TheLivingWorldLogic;

class LivingWorldBattle
{
public:
	int rva003F4831();
};

class Rva0020E794
{
public:
	LivingWorldBattle *rva0020E794();
	bool rva0020E4C8();

private:
	unsigned char m_pad[0x14];
	LivingWorldBattle **m_begin;
	LivingWorldBattle **m_end;
};

LivingWorldBattle *Rva0020E794::rva0020E794()
{
	LivingWorldBattle **begin = m_begin;
	LivingWorldBattle **end = m_end;
	for (; begin != end; ++begin) {
		LivingWorldBattle *elem = *begin;
		if (elem->rva003F4831() > 0)
			return elem;
	}
	return 0;
}

bool Rva0020E794::rva0020E4C8()
{
 bool changed = false;
restart:
 for (LivingWorldBattle **it = m_begin; it != m_end; ++it) {
  LivingWorldBattle *battle = *it;
  if (battle->rva003F4831() == 0) {
   TheLivingWorldLogic->rva002BD64F(reinterpret_cast<int>(battle));
   changed = true;
   goto restart;
  }
 }
 return changed;
}
