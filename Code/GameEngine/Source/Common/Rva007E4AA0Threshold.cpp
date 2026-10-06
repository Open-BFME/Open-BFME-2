// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva007E4AA0Threshold.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?isBelowTransformed@Rva007E4AA0Threshold@@QBE_NH@Z 0x0009116F (26B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Open-BFME5: clean C++ conversion of the transformed-threshold comparison.

int __stdcall rva000190ABTransform(int value);

class Rva007E4AA0Threshold
{
public:
	bool isBelowTransformed(int value) const;

private:
	char m_pad00[0x4C];
	int m_threshold;
};

bool Rva007E4AA0Threshold::isBelowTransformed(int value) const
{
	return m_threshold < rva000190ABTransform(value);
}
