// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva0037A810SignPredicate.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?isNonNegative@Rva0037A810Object@@QAE_NH@Z 0x004DC5EF (20B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Open-BFME: signed arithmetic predicate reconstructed from retail RVA 0x0037A810.

class Rva0037A810Object
{
public:
    bool isNonNegative(int value);

private:
    char m_pad0[0x1C];
    int m_factor;
    int m_offset;
};

bool Rva0037A810Object::isNonNegative(int value)
{
    return m_factor * value + m_offset >= 0;
}
