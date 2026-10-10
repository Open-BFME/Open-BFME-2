// ?rva000AE234@Rva000AE234@@QAEDHH@Z
// cl: /O1 /DNDEBUG /MD
// Retail 0x000AE234, 65 bytes: bounds-checked byte read of a width x height
// grid (width +8, height +0xC) stored row-major in the byte vector whose
// begin/end sit at +0x8C/+0x90; out of range yields 0. Owner address-derived.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva000AE234Bytes
{
	char *m_begin;
	char *m_end;
	unsigned int size() const { return (unsigned int)(m_end - m_begin); }
};

class Rva000AE234
{
public:
	char rva000AE234(int x, int y);
	char m_pad[8];
	int m_width;
	int m_height;
	char m_pad2[0x8C - 0x10];
	Rva000AE234Bytes m_cells;
};

char Rva000AE234::rva000AE234(int x, int y)
{
	if (x < 0 || y < 0 || y >= m_height || x >= m_width)
		return 0;
	unsigned int i = y * m_width + x;
	Rva000AE234Bytes &c = m_cells;
	if (i < c.size())
	{
		_ReadWriteBarrier();
		return c.m_begin[i];
	}
	return 0;
}
