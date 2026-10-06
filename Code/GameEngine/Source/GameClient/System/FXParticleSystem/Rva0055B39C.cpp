// cl: /MD
// ?rva0055B39C@Rva0055B39C@@QAEXXZ @0x0055B39C 61B
// FX interpolation between keyframes at +4 with result at +0x54.
// Evidence: thiscall 0 args ret void; xorps/movss zero path plus fld/fsub/fild/fadd/fdivp;
// caller 0x0055B489 passes ecx=esi and compares index at +0x58 against 8;
// neighbours 0x0055B367 and 0x0055B44D same FXParticleSystem subsystem.
struct Rva0055B39CPair
{
	unsigned int frame;
	float value;
};

class Rva0055B39C
{
public:
	void rva0055B39C();
private:
	char m_pad0[4];
	Rva0055B39CPair m_pairs[8];
	char m_pad1[12];
	float m_time;
	float m_result;
	unsigned int m_index;
};

void Rva0055B39C::rva0055B39C()
{
	unsigned int idx = m_index;
	unsigned int next = m_pairs[idx + 2].frame;
	if (next == 0)
	{
		m_result = 0.0f;
		return;
	}
	float v = m_pairs[idx + 1].value;
	unsigned int prev = m_pairs[idx + 1].frame;
	unsigned int delta = next - prev;
	float f = v - m_time;
	float d = (float)delta;
	m_result = f / d;
}
