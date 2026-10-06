// cl: /MD
// ??0Rva00431920@@QAE@PAXHPAUICoord2D@@HH@Z @0x00431920 53B: ctor storing vtable g_00C3C994 plus 5 args with 8B struct copy to +0xc. Evidence: unlock lane unblocks 0x00431AEC; caller passes outer+4; g_00C3C994.
struct ICoord2D
{
	int m_x;
	int m_y;
};

extern const void *const g_00C3C994[];

class Rva00431920
{
	void *m_00;
	void *m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
public:
	Rva00431920(void *a, int b, ICoord2D *c, int d, int e);
};

Rva00431920::Rva00431920(void *a, int b, ICoord2D *c, int d, int e)
{
	m_04 = a;
	m_08 = b;
	m_00 = (void *)g_00C3C994;
	m_0C = c->m_x;
	m_10 = c->m_y;
	m_14 = d;
	m_18 = e;
}
