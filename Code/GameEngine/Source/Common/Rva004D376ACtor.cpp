// cl: /MD
// ??0Rva004D376A@@QAE@XZ 0x004D376A 177 ctor with 8x8 grid and parallel arrays, vtable 0x00C601DC

struct Rva004D376AGridElem
{
	unsigned char flag;
	unsigned char pad[3];
	int value;
};

class Rva004D376A
{
public:
	Rva004D376A();
	virtual ~Rva004D376A();
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14[7];
	Rva004D376AGridElem m_grid[8][8];
	int m_230[8];
	unsigned char m_250[8];
	int m_258[6];
	unsigned char m_270;
	unsigned char _pad271;
	unsigned short m_272[8];
	unsigned char m_282[8];
	unsigned char _pad28a[2];
};

Rva004D376A::Rva004D376A()
{
	m_04 = 0;
	m_08 = 0;
	m_0c = 0;
	m_10 = 0;
	m_258[0] = 0;
	m_258[1] = 0;
	m_258[2] = 0;
	m_258[3] = 0;
	m_258[4] = 0;
	m_258[5] = 0;
	m_270 = 0;
	for (int k = 0; k < 7; k++)
		m_14[k] = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_grid[i][j].flag = 0;
			m_grid[i][j].value = 0;
		}
		m_230[i] = 0;
		m_250[i] = 0;
		m_272[i] = 0;
		m_282[i] = 0;
	}
}

// ??1Rva004D376A@@UAE@XZ @0x004D381B 7B: the empty dtor, restoring the vtable (the
// deleting dtor still expands it inline).
Rva004D376A::~Rva004D376A()
{
}
