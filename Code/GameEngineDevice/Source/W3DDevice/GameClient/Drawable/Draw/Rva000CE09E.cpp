// cl: /MD
// ?rva000CE09E@W3DTankDraw@@QAEXXZ @0x000CE09E 76B: disable debris emitters at +0x2E8/+0x2F4 via get-or-Make then rowed byte-zero disable 0x1F384A guarded by +0x8 rva00270260; W3DTankDraw layout from ctor 0xCEA6C and sibling Rva000CE0EA; volatile loads preserve Make chases; caller 0xCE4B0
class Rva00270260 {
public:
	bool rva00270260();
};
class Rva001F384AByteZeroSetter {
public:
	void disable();
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
	void rva000CE09E();
	char m_pad0[8];
	Rva00270260 *m_guard;
	char m_pad1[0x2DC];
	BfmeParticleSystemHandle m_emit1;
	BfmeParticleSystemHandle m_emit2;
};
void W3DTankDraw::rva000CE09E()
{
	if (m_guard->rva00270260())
		return;
	if (m_emit1.m_system) {
		ParticleSystem *p = m_emit1.m_system;
		if (!p)
			p = Make001FCBD7();
		((Rva001F384AByteZeroSetter *)p)->disable();
	}
	if (m_emit2.m_system) {
		ParticleSystem *q = m_emit2.m_system;
		if (!q)
			q = Make001FCBD7();
		((Rva001F384AByteZeroSetter *)q)->disable();
	}
}
