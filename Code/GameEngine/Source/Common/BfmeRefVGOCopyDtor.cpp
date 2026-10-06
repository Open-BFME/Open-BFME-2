// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BfmeRefVGO copy constructor, retail 0x000A9806 (28B). The BFME1 donor
// (BfmeConv1355.cpp) only carries bfmeAssignVGO; the copy is the same
// single-pointer acquire through the shared VGO refcount helpers: copy the
// pointer, then increment when non-null. Callee resolves through the
// existing bfmeIncVGO pin at 0x006CFDE0.

unsigned __cdecl bfmeIncVGO(unsigned *p);
unsigned __cdecl bfmeDecVGO(unsigned *p);
void __cdecl bfmeDropVGO(void *p);

class BfmeRefVGO
{
public:
    BfmeRefVGO(const BfmeRefVGO &other);
    ~BfmeRefVGO();

private:
    unsigned *m_bfmeP;
};

// ??0BfmeRefVGO@@QAE@ABV0@@Z
BfmeRefVGO::BfmeRefVGO(const BfmeRefVGO &other)
{
    m_bfmeP = other.m_bfmeP;
    if (m_bfmeP)
        bfmeIncVGO(m_bfmeP);
}

// ??1BfmeRefVGO@@QAE@XZ, retail 0x000A9822 (30B). Mirror of the release half
// of bfmeAssignVGO in BfmeConv1355.cpp: decrement, dropping the shared block
// when the count reaches zero. Dec resolves through the rowed Rva006CFDF0DecRef
// leaf, drop through the bfmeDropVGO pin at 0x006D0440.
BfmeRefVGO::~BfmeRefVGO()
{
    if (m_bfmeP && bfmeDecVGO(m_bfmeP) == 0)
        bfmeDropVGO(m_bfmeP);
}
