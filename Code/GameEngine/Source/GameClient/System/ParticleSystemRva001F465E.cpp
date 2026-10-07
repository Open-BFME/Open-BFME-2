// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
//
// ?rva001F465E@ParticleSystem@@QAEXPAX@Z, retail 0x001F465E, 56 bytes.
// ParticleSystem slave-chain setter for +0x98 with same +0x15C Make001FCBD7
// chain as neighbour ?rva001F45F4 (0x001F45F4 56B). Gap between destroy
// 0x001F462C and 0x001F4696; offsets from retail disassembly.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class ParticleSystem
{
public:
	void rva001F465E(void *val);
private:
	char m_pad00[0x98];
public:
	void *m_val98;
private:
	char m_pad9C[0x15C - 0x9C];
public:
	ParticleSystem *m_next15C;
};

extern ParticleSystem *Make001FCBD7(void);

void ParticleSystem::rva001F465E(void *val)
{
	m_val98 = val;
	if (m_next15C == 0)
		return;
	ParticleSystem *cur = this;
	ParticleSystem *nxt;
	do
	{
		nxt = cur->m_next15C;
		if (nxt == 0)
			nxt = Make001FCBD7();
		nxt->m_val98 = val;
		_ReadWriteBarrier();
		cur = nxt;
	} while (nxt->m_next15C != 0);
}
