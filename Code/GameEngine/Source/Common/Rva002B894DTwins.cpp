// cl: /O1 /MD
// ?rva002B894D@Rva002B894DHost@@QAEXH@Z @0x002B894D 55B and ?rva002B8984@Rva002B894DHost@@QAEXH@Z @0x002B8984 55B: adjacent twins.
// Backwards index loop over +0x8C/+0x90 pointer vector (count via ptr-diff sar), elem +0x34 vs int arg;
// call pinned 0x2B7DE6 on == (0x2B894D) vs != (0x2B8984). Evidence: retail push esi/edi, mov edi,ecx,
// mov esi,[edi+0x90]/sub/sar/jmp-dec-jns shape, cmp [esp+0xC] with jne/je flip, shared pops epilogue.
// Boundary: 55B each, adjacent (0x894D+55=0x8984); prev/next prologues. Names address-derived except pinned callee.
class Rva002B894DElem
{
public:
	char m_pad[0x34];
	int m34;
};
// The removal 0x002B7DE6 is the LivingWorldLogic::RemovePlayer row (same host object).
class LivingWorldPlayer;
class LivingWorldLogic
{
public:
	void RemovePlayer(LivingWorldPlayer *player);
};
class Rva002B894DHost
{
public:
	void rva002B894D(int arg);
	void rva002B8984(int arg);
private:
	char m_pad[0x8C];
	Rva002B894DElem **m_begin8C;
	Rva002B894DElem **m_end90;
};
void Rva002B894DHost::rva002B894D(int arg)
{
	int n = (int)(m_end90 - m_begin8C);
	for (int i = n - 1; i >= 0; --i)
	{
		Rva002B894DElem *e = m_begin8C[i];
		if (e->m34 == arg)
			((LivingWorldLogic *)this)->RemovePlayer((LivingWorldPlayer *)e);
	}
}
void Rva002B894DHost::rva002B8984(int arg)
{
	int n = (int)(m_end90 - m_begin8C);
	for (int i = n - 1; i >= 0; --i)
	{
		Rva002B894DElem *e = m_begin8C[i];
		if (e->m34 != arg)
			((LivingWorldLogic *)this)->RemovePlayer((LivingWorldPlayer *)e);
	}
}
