// cl: /O1 /MD
// ?rva005E3266@Rva005E3266@@QAEXXZ @0x005E3266 8B: ptr-chase tail-jmp into rowed rva005E31EE 0x005E31EE via +0x04. Evidence: rowed callee plus caller 0x005CC7DF plus gap between 0x005E3258 and 0x005E326E same flags.
class Rva005E31EE
{
public:
    void rva005E31EE();
};
class Rva005E3266
{
    char m_pad[4];
    Rva005E31EE *m_04;
public:
    void rva005E3266();
};
void Rva005E3266::rva005E3266()
{
    m_04->rva005E31EE();
}
