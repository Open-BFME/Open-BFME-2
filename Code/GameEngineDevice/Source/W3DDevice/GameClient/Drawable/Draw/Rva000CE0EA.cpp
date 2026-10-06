// cl: /MD
// ?rva000CE0EA@W3DTankDraw@@QAEXXZ @0x000CE0EA 63B: enable debris emitters at +0x2E8/+0x2F4 via get-or-Make then rowed byte-one enable 0x1F3852; W3DTankDraw layout from ctor 0xCEA6C; volatile loads preserve Make chases like truck toss 0xCB5C3; unblocks 0xCE147
class Rva001F3852ByteOneSetter {
public:
	void enable();
};
class ParticleSystem;
ParticleSystem *Make001FCBD7();
struct BfmeParticleSystemHandle {
	ParticleSystem *volatile m_system;
	void *m_prev;
	void *m_next;
};
class W3DTankDraw {
public:
	void rva000CE0EA();
	char m_pad0[0x2E8];
	BfmeParticleSystemHandle m_emit1;
	BfmeParticleSystemHandle m_emit2;
};
void W3DTankDraw::rva000CE0EA()
{
	if (m_emit1.m_system) {
		ParticleSystem *p = m_emit1.m_system;
		if (!p)
			p = Make001FCBD7();
		((Rva001F3852ByteOneSetter *)p)->enable();
	}
	if (m_emit2.m_system) {
		ParticleSystem *q = m_emit2.m_system;
		if (!q)
			q = Make001FCBD7();
		((Rva001F3852ByteOneSetter *)q)->enable();
	}
}
