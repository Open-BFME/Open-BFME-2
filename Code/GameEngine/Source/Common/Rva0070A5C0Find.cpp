// cl: /MD
// ?rva0070A5C0@Rva0070A5C0@@..., retail 0x0070A5C0 (8B).
// +8 forwarder over embedded BfmeTab1034 tail-jumping to bfmeFind1034F at 0x0070B380.
// Evidence: add ecx 8 plus jmp; 21 callers pass one pointer/int arg and consume pointer return via vtable slot 0xC;
// same tail pattern as Rva8D0D80Result::rva006FBB90 over m_table at +8 (BfmeConv1034 proves BfmeTab1034::bfmeFind1034F signature).

class BfmeN1034
{
public:
    int bfmeVal1034();
};

class BfmeTab1034
{
public:
    BfmeN1034 *bfmeFind1034F(int k);
};

class Rva0070A5C0
{
    char m_pad[8];
    BfmeTab1034 m_tab; // +8
public:
    BfmeN1034 *rva0070A5C0(int k);
};

BfmeN1034 *Rva0070A5C0::rva0070A5C0(int k)
{
    return m_tab.bfmeFind1034F(k);
}
