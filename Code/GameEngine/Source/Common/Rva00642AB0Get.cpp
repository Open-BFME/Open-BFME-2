// cl: /Ob0
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva00642AB0Get.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?get@Rva00642AB0@@QAEHH@Z 0x003888A8 (27B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

class Rva00642AB0
{
	char m_pad[0x17C];
	int m_slots[8];

public:
	int get(int index);
};

int Rva00642AB0::get(int index)
{
	if (index < 0 || index >= 8)
		return 0;
	return m_slots[index];
}
