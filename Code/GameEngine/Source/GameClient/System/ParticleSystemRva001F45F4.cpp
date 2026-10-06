// cl: /O1 /DNDEBUG /MD
//
// ?rva001F45F4@ParticleSystem@@QAEX_N@Z @0x001F45F4 56B.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
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
		_ReadWriteBarrier();
		cur = nxt;
	} while (nxt->m_next15C != 0);
}
