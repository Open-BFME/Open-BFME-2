// cl: /MD
// ?rva005E3B25@Rva005E3B25@@QAEXH@Z @0x005E3B25 8B: ptr-chase tail-jmp into rowed rva005E3AAA 0x005E3AAA via +0x10. Evidence: rowed callee plus caller 0x005E6ACF plus gap between 0x005E3B1A and 0x005E3B2D plus unlock lane.
class Rva005E39AE
{
public:
    void rva005E3AAA(int v);
};
class Rva005E3B25
{
    char m_pad[0x10];
    Rva005E39AE *m_10;
public:
    void rva005E3B25(int v);
};
void Rva005E3B25::rva005E3B25(int v)
{
    m_10->rva005E3AAA(v);
}
