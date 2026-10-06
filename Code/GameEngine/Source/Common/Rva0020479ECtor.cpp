// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva0020479E@@QAE@XZ @0x0020479E 43B, call sites 0x0020756E 0x0020A0B9
// 0x0020A936. Installs the vtable at 0x00BE3A90, zeroes +0x04..+0x10, then the
// +0x14..+0x20 block (0, -1, 0, -1), the +0x24 byte and +0x28.
// Structural inference: retail stores both -1s before both zeros of the
// +0x14 block; a 16-byte member sub-object with its own inline constructor
// reproduces that order (plain members put the or -1 first; the banked
// attempt also wrote the vtable as a literal address).
struct Rva0020479EQuad {
    int m_count0;
    int m_index0;
    int m_count1;
    int m_index1;
    Rva0020479EQuad() : m_count0(0), m_index0(-1), m_count1(0), m_index1(-1) {}
};
class Rva0020479E {
public:
    Rva0020479E();
    virtual ~Rva0020479E();
    int m_04;
    int m_08;
    int m_0c;
    int m_10;
    Rva0020479EQuad m_14;
    unsigned char m_24;
    int m_28;
};
Rva0020479E::Rva0020479E() : m_04(0), m_08(0), m_0c(0), m_10(0), m_24(0), m_28(0) {
}
