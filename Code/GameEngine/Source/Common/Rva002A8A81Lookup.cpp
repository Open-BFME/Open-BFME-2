// cl: /MD
// ?rva002A8A81@Rva002A8A81@@QAEMPAX@Z @0x002A8A81 48B search int[16] at +4 for key=[[arg+4]+0x520] return float[16] at +0x44 else BfmeZeroRange caller 0x00357051
// The data ledger identifies the shared read-only operand as float +0.0.
struct Mid002A8A81 { char _pad[0x520]; int m_520; };
struct Arg002A8A81 { char _pad[4]; Mid002A8A81 *m_04; };
class Rva002A8A81
{
public:
    char _pad0[4];
    int m_04[16];
    float m_44[16];
    float rva002A8A81(void *arg);
};

float Rva002A8A81::rva002A8A81(void *arg)
{
    int key = ((Arg002A8A81 *)arg)->m_04->m_520;
    for (int i = 0; i < 16; ++i) {
        if (key == m_04[i])
            return m_44[i];
    }
    return 0.0f;
}
