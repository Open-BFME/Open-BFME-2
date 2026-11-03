// cl: /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva0010E4D4@Rva0010E4D4@@QAEXXZ at 0x0010E4D4 (34B).
// Make-unique loop over VertexMaterialClass array at +0x0C with count at +0x18.
// Evidence: retail push ebx esi edi; mov ebx [esi+0x18]; test jle; loop mov eax [esi+0x0C];
// mov ecx [eax+edi*4]; call ?Make_Unique@VertexMaterialClass@@QAEXXZ at 0x0013C970;
// callers at 0x0010E52A 0x00135FA7 0x00186D38.
#include "../../../Libraries/Source/WWVegas/WW3D2/VertexMaterialClass.h"

class Rva0010E4D4
{
public:
	void rva0010E4D4();
private:
	char m_pad0[0x0C];
	VertexMaterialClass **m_arr0C;
	char m_pad10[8];
	int m_count18;
};

void Rva0010E4D4::rva0010E4D4()
{
	int n = m_count18;
	for (int i = 0; i < n; ++i)
		m_arr0C[i]->Make_Unique();
}
