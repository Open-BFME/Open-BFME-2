// cl: /DNDEBUG /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Bfme/Rva001B2DF0Predicate.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?predicate@Rva001B2DF0@@QBEHXZ 0x004DEAB0 (27B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

class Rva001B2DF0
{
public:
	int predicate() const;

private:
	unsigned char m_padding_00[0x3C];
	unsigned int m_field_3C;
	unsigned int m_field_40;
	unsigned char m_padding_44[0x10];
	unsigned int m_field_54;
};

int Rva001B2DF0::predicate() const
{
	if (m_field_54 == 0 && m_field_3C == 0 && m_field_40 == 0)
		return 0x3FFFFFFF;
	return 1;
}
