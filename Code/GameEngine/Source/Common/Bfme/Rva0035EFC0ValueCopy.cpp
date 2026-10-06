// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Bfme/Rva0035EFC0ValueCopy.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?copyValue@Rva0035EFC0Owner@@QAE?AURva0035EFC0Value@@XZ 0x0054293F (20B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Open-BFME: address-derived reconstruction of retail RVA 0x0035EFC0.
// The complete member body returns the five-dword value at the start of its
// owner through MSVC's hidden structure-return pointer.  No authoritative
// class or method identity is currently available.

struct Rva0035EFC0Value
{
    unsigned word0;
    unsigned word1;
    unsigned word2;
    unsigned word3;
    unsigned word4;
};

class Rva0035EFC0Owner
{
public:
    Rva0035EFC0Value copyValue();

private:
    Rva0035EFC0Value value_;
};

Rva0035EFC0Value Rva0035EFC0Owner::copyValue()
{
    return value_;
}
