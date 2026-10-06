// cl: /DNDEBUG /MD /EHsc
// ??0Rva002E7DF5@@QAE@HABU_Rva002E7DF5Cell@@@Z @0x002E7DF5 49B
// Ctor copying one int plus a 3-int cell then float global and false flag; caller at 0x002EE8C2.

extern float g_Va00BBB8E0;

struct _Rva002E7DF5Cell
{
	int x;
	int y;
	int z;
};

class Rva002E7DF5
{
public:
	Rva002E7DF5(int a, const _Rva002E7DF5Cell &cell);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	float m_1C;
	bool m_20;
};

Rva002E7DF5::Rva002E7DF5(int a, const _Rva002E7DF5Cell &cell)
{
	float f = g_Va00BBB8E0;
	m_00 = a;
	m_04 = cell.x;
	m_08 = cell.y;
	m_0C = cell.z;
	m_1C = f;
	m_20 = false;
}
