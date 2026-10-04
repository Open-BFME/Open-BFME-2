// ?rva002E6CFE@Rva002E6CFE@@QAEXHHH@Z
// partial score=0.96 date=2026-10-04
// cl: /O1
// ?rva002E6CFE@Rva002E6CFE@@QAEXHHH@Z @0x002E6CFE 49B
// Evidence: unlock lane; pure arithmetic triple-int setter with m_c at +8 always
// stored and scaled range at +4/+0 when positive; callers 12x 724B range users.
class Rva002E6CFE
{
    int m_00;
    int m_04;
    int m_08;
public:
    void rva002E6CFE(int a, int b, int c);
};

void Rva002E6CFE::rva002E6CFE(int a, int b, int c)
{
    m_08 = c;
    if (c > 0) {
        int q = ((b - a) << 8) / c;
        m_04 = q;
        m_00 = (a << 8) + q / 2;
    }
}
