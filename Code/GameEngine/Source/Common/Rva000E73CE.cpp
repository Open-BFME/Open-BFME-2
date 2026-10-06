// cl: /MD
// ?rva000E73CE@Rva000E73CE@@QAEXXZ 0x000E73CE 46B
// Fill byte-flag dword at +0x19F4 stride 0xA0 with (TheShroudManager==0),
// bounded by count at +0x4FB58. Same array base +0x199C stride 0xA0 count
// +0x4FB58 as Rva000E7016/Rva000E76B8 neighbours.
// Evidence: global TheShroudManager 0x009FE74C; caller jmp at 0x000683F9.

class PartitionManager;
extern PartitionManager *TheShroudManager;

struct E73Elem
{
	char _0[0x58];
	int m_val;
	char _1[0xA0 - 0x5C];
};

class Rva000E73CE
{
public:
	void rva000E73CE();
private:
	char _pad0[0x199C];
	E73Elem m_elems[1999];
	char _gap[0x5C];
	int m_count;
};

void Rva000E73CE::rva000E73CE()
{
	for (int i = 0; i < m_count; ++i)
		m_elems[i].m_val = (TheShroudManager == 0);
}
