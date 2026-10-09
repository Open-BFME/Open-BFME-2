// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?rva0073CE30@Gen_008F7CD0@@QAEXPAUFloatRect0073CE30@@HI@Z 96B @0x0073CE30: rect wrapper building derived updater (base vtable 0x008F139C then derived 0x008F13A4) with grid=this mask&0xFFFFF extra then 4 ftol2 y2 y1 x2 x1 then rowed Fill. Layout base 12 plus derived +0xC. Evidence: dual vtable stores plus rowed Fill at 0x0073C7C0 plus ftol2 calls plus caller at 0x00739D78.
class BfmeCellFD;

class Gen_008F7CD0
{
public:
	void rva0073A2A0(BfmeCellFD **first, BfmeCellFD **last, int x1, int x2, int y);
	void rva0073CE30(struct FloatRect0073CE30 *rect, int extra, unsigned int mask);
	void rva0073CC60(struct FloatRect0073CE30 *rect, int extra, unsigned int mask);
};

class Rva0073BAA0Base
{
public:
	virtual char testFunc(int x, int y);
	Rva0073BAA0Base(Gen_008F7CD0 *grid, unsigned int mask) : m_grid(grid) { m_mask = mask & 0xFFFFF; }
private:
	Gen_008F7CD0 *m_grid;
	unsigned int m_mask;
};

class Rva0073BB40 : public Rva0073BAA0Base
{
public:
	Rva0073BB40(Gen_008F7CD0 *grid, unsigned int mask, int extra) : Rva0073BAA0Base(grid, mask), m_extra(extra) {}
private:
	int m_extra;
};

// Derived updater of the raster 0x0073C350 (vtable 0x00CF13A0): same layout as Rva0073BB40, kept under the name the
// raster callee's by-value parameter carries.
class Rva0073BAA0 : public Rva0073BAA0Base
{
public:
	Rva0073BAA0(Gen_008F7CD0 *grid, unsigned int mask, int extra) : Rva0073BAA0Base(grid, mask), m_extra(extra) {}
private:
	int m_extra;
};

struct FloatRect0073CE30
{
	float x1;
	float y1;
	float x2;
	float y2;
};

char __cdecl Rva0073C7C0Fill(int x1, int x2, int y1, int y2, Rva0073BB40 updater);

void Gen_008F7CD0::rva0073CE30(FloatRect0073CE30 *rect, int extra, unsigned int mask)
{
	if (mask != 0)
		Rva0073C7C0Fill((int)rect->x1, (int)rect->x2, (int)rect->y1, (int)rect->y2, Rva0073BB40(this, mask, extra));
}

char __cdecl Rva0073C350Raster(int x1, int x2, int y1, int y2, Rva0073BAA0 updater);

// ?rva0073CC60@Gen_008F7CD0@@QAEXPAUFloatRect0073CE30@@HI@Z 96B @0x0073CC60: sibling of rva0073CE30 with the raster
// callee 0x0073C350 and its own derived updater (vtable 0x00CF13A0). Target evidence: retail body read byte for byte;
// both vtable stores (base 0x00CF139C then derived) and the 16-byte by-value argument.
void Gen_008F7CD0::rva0073CC60(FloatRect0073CE30 *rect, int extra, unsigned int mask)
{
	if (mask != 0)
		Rva0073C350Raster((int)rect->x1, (int)rect->x2, (int)rect->y1, (int)rect->y2, Rva0073BAA0(this, mask, extra));
}
