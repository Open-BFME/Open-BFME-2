// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeTwoHundredFortyThree.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeCopyOA@@YAPAUBfmeVecOA@@PBU1@0PAU1@@Z 0x002C97AC (60B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// A counted run of triples copied across, each of the three words in turn, with
// the advanced destination handed back.

struct BfmeVecOA
{
	int m_bfmeAcross;			// 0x0
	int m_bfmeUp;				// 0x4
	int m_bfmeAlong;			// 0x8
};

BfmeVecOA *bfmeCopyOA(const BfmeVecOA *first, const BfmeVecOA *last, BfmeVecOA *out)
{
	int count = (int)(last - first);

	while (count > 0)
	{
		out->m_bfmeAcross = first->m_bfmeAcross;
		out->m_bfmeUp = first->m_bfmeUp;
		out->m_bfmeAlong = first->m_bfmeAlong;

		++first;
		++out;
		--count;
	}

	return out;
}
