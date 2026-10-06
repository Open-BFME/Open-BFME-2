// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Small03cHalfCopy.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?copyFrom@Rva0093C9A0Box@@QAEPAV1@PBURva0093C9A0Src@@PBH@Z 0x004CFB14 (24B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
struct Rva0093C9A0Src
{
	unsigned short m_half;
	char m_gap[2];
	int m_word;
};
class Rva0093C9A0Box
{
public:
	Rva0093C9A0Box *copyFrom(const Rva0093C9A0Src *a, const int *b);
	unsigned short m_half;
	char m_gap[2];
	int m_word;
};
// mov eax,ecx / halfword copy / word copy off the second pointer.
Rva0093C9A0Box *Rva0093C9A0Box::copyFrom(const Rva0093C9A0Src *a, const int *b)
{
	m_half = a->m_half;
	m_word = *b;
	return this;
}
