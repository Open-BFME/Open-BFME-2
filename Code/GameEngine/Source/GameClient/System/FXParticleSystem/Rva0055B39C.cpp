// cl: /MD /O1 /arch:SSE /G7
// ?rva0055B39C@Rva0055B39C@@QAEXXZ @0x0055B39C 61B
// FX interpolation between keyframes at +4 with result at +0x54.
// Evidence: thiscall 0 args ret void; xorps/movss zero path plus fld/fsub/fild/fadd/fdivp;
// caller 0x0055B489 passes ecx=esi and compares index at +0x58 against 8;
// neighbours 0x0055B367 and 0x0055B44D same FXParticleSystem subsystem.
class ParticleSystem;
ParticleSystem *Make001FCBD7();

struct AlphaSystemView489
{
    char unknown00[8];
    int state;
};

struct AlphaHandle489
{
    void *system;
    void *prev, *next;

    AlphaSystemView489 *operator->() const
    {
        if (!system)
            return (AlphaSystemView489 *)Make001FCBD7();
        return (AlphaSystemView489 *)system;
    }
};

struct AlphaParticleView489
{
    char unknown00[0x34];
    unsigned lifetime;
    char unknown38[4];
    AlphaHandle489 system;
    char unknown48[0xC];
    unsigned remaining;

    const AlphaHandle489 &getSystem() const { return system; }
    unsigned age() const { return lifetime - remaining; }
};

struct Rva0055B39CPair
{
	unsigned int frame;
	float value;
};

class Rva0055B39C
{
public:
	void rva0055B39C();
	void rva0055B489();
private:
	char m_pad0[4];
	// Two views of the same retail interpolation storage. The key view
	// includes the terminal slots inspected by the existing helper.
	union
	{
		Rva0055B39CPair m_pairs[11];
		struct
		{
			AlphaParticleView489 *particle;
			char unknown08[0x48];
			float m_time;
			float m_result;
			unsigned m_index;
		};
	};
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

// Native 0x0055B489..0x0055B52E: skip states 1/2, advance the alpha
// key interpolation, then clamp to 0..1. The call uses the same receiver
// and fields as the already verified helper at 0x0055B39C.
void Rva0055B39C::rva0055B489()
{
    if (particle->getSystem()->state == 1 || particle->getSystem()->state == 2)
        return;
    m_time += m_result;
    if ((int)m_index < 8 && m_pairs[m_index + 2].frame)
    {
        if (particle->age() >= m_pairs[m_index + 2].frame)
        {
            m_time = m_pairs[m_index + 1].value;
            ++m_index;
            rva0055B39C();
        }
    }
    else
        m_result = 0.0f;
    if (m_time < 0.0f)
        m_time = 0.0f;
    else if (m_time > 1.0f)
        m_time = 1.0f;
}
