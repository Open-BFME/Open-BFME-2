// ?rva0073BE00@Rva0073BEA0@@QAEXHH@Z
// partial score=0.8 date=2026-10-09
// cl: /O2 /G6 /MD /EHsc
// ?rva0073BEA0@Rva0073BEA0@@QAEXHH@Z, retail 0x0073BEA0, 106 bytes (RET 8).
// Address-derived name; layout is a view of the witnessed offsets. Native:
// converts integer cell coordinates (a, b) to the cell centre in the
// grid at this+4 (cell size at +0x1C, origins at +8 for the first and +4 for
// the second coordinate, centre = c * size + origin + size * 0.5, truncated),
// swaps them into a float pair (second, first) and reports it through slot 0
// of the sink at this+0xC. 0x0073BE00 is the same body with a guarded frame.
struct Rva0073BEA0Grid
{
	char m_pad0[4];
	float m_4;
	float m_8;
	char m_padC[0x1C - 0xC];
	float m_cellSize;
};

struct Rva0073BEA0Point
{
	float x;
	float y;
};

struct Rva0073BEA0Grid2 : Rva0073BEA0Grid
{
	int centreA(int c) const { return (int)((float)c * m_cellSize + m_8 + m_cellSize * 0.5); }
	int centreB(int c) const { return (int)((float)c * m_cellSize + m_4 + m_cellSize * 0.5); }
};

struct Rva0073BE00Point : Rva0073BEA0Point
{
	~Rva0073BE00Point() {}
};

class Rva0073BEA0Sink
{
public:
	virtual void slot0(const Rva0073BEA0Point *point);
};

class Rva0073BEA0
{
public:
	void rva0073BE00(int a, int b);
	void rva0073BEA0(int a, int b);
private:
	char m_pad0[4];
	Rva0073BEA0Grid2 *m_grid;
	char m_pad8[4];
	Rva0073BEA0Sink *m_sink;
};

void Rva0073BEA0::rva0073BEA0(int a, int b)
{
	int x = m_grid->centreA(b);
	int y = m_grid->centreB(a);
	Rva0073BEA0Point p;
	p.x = (float)y;
	p.y = (float)x;
	m_sink->slot0(&p);
}

// ?rva0073BE00@Rva0073BEA0@@QAEXHH@Z, retail 0x0073BE00, 146 bytes (RET 8, EH):
// the same conversion with a destructible point (native registers an unwind
// state around the sink call).
void Rva0073BEA0::rva0073BE00(int a, int b)
{
	int x = m_grid->centreA(b);
	int y = m_grid->centreB(a);
	Rva0073BE00Point p;
	p.x = (float)y;
	p.y = (float)x;
	m_sink->slot0(&p);
}
