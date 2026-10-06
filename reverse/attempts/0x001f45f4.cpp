// ?rva001F45F4@ParticleSystem@@QAEX_N@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
//
// ?rva001F45F4@ParticleSystem@@QAEX_N@Z @0x001F45F4 56B.
// Slave-chain flag setter (ParticleSystem neighbourhood: Make001FCBD7 rowed
// factory returns the chain node type; 0x001F4646 destroy nearby): stamps
// the bool param into this+0x1A6, returns if +0x15C is null, else walks the
// +0x15C chain creating via Make001FCBD7 when a link is missing, stamping
// each link and stopping after the first link with null next. The cursor
// reuses ecx (this dead after entry, so no save). Strict chain semantics
// unproven; node type is ParticleSystem per the factory signature.
class ParticleSystem
{
public:
	void rva001F45F4(bool flag);
private:
	char m_pad00[0x15C];
public:
	ParticleSystem *m_next15C;
private:
	char m_pad160[0x46];
public:
	bool m_flag1A6;
};

extern ParticleSystem *Make001FCBD7(void);

void ParticleSystem::rva001F45F4(bool flag)
{
	m_flag1A6 = flag;
	if (m_next15C == 0)
		return;
	ParticleSystem *cur = this;
	ParticleSystem *nxt;
	do
	{
		nxt = cur->m_next15C;
		if (nxt == 0)
			nxt = Make001FCBD7();
		nxt->m_flag1A6 = flag;
		cur = nxt;
	} while (nxt->m_next15C != 0);
}
