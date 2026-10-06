// cl: /DNDEBUG /MD /EHsc
// ??0Rva002E7B02@@QAE@HHABU_Rva002E7B02Cell@@@Z @0x002E7B02 39B
// Ctor copying two ints plus a 3-int cell; caller at 0x002EDFD0 passes (esi, 4, [ebp+8]).

struct _Rva002E7B02Cell
{
	int x;
	int y;
	int z;
};

class Rva002E7B02
{
public:
	Rva002E7B02(int a, int b, const _Rva002E7B02Cell &cell);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};

Rva002E7B02::Rva002E7B02(int a, int b, const _Rva002E7B02Cell &cell)
	: m_00(a)
	, m_04(b)
	, m_08(cell.x)
	, m_0C(cell.y)
	, m_10(cell.z)
{
}
