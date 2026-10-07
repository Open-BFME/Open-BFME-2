// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
//
// ?rva001F4A22@Rva001F4A22@@QAEXXZ, retail 0x001F4A22, 21 bytes.
// Clears the BfmeParticleSystemHandle at +0x78 when its system is set.
// Same handle-dtor row as Rva002115C5 precedent plus the clear store.
// Evidence: rowed ??1BfmeParticleSystemHandle@@QAE@XZ callee and caller
// at 0x001FBD17 range; class unproven so honest address name.
struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle();
	void *m_system;
	void *m_prev;
	void *m_next;
};

struct Rva001F4A22
{
	void rva001F4A22();
	BfmeParticleSystemHandle *handle78();
private:
	char m_pad00[0x78];
public:
	BfmeParticleSystemHandle m_handle78;
};

void Rva001F4A22::rva001F4A22()
{
	if (m_handle78.m_system)
	{
		m_handle78.~BfmeParticleSystemHandle();
		m_handle78.m_system = 0;
	}
}
