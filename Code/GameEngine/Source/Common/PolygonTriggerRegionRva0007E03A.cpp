// cl: /MD
//
// ?rva0007E03A@PolygonTrigger@@QAE?AURegion2D@@XZ retail 0x0007E03A 19B
// PolygonTrigger region forwarder: returns m_shape (at +0x08) region via the
// rowed Rva0030B719Shape::rva0030B6E3 0x0030B6E3. Caller 0x002E3954 pins the
// PolygonTrigger class (its FloatRect copy takes this region); add ecx,8 is
// the m_shape member. Unblocks 0x002E3954 plus 3 more.

struct Region2D
{
	Region2D(const Region2D &that);
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

class Rva0030B719Shape
{
public:
	Region2D rva0030B6E3();
};

class PolygonTrigger
{
public:
	Region2D rva0007E03A();
	void rva002E3954(struct FloatRect0073CE30 *rect);
private:
	unsigned char m_pad00[0x08];
	Rva0030B719Shape m_shape; // +0x08
};

Region2D PolygonTrigger::rva0007E03A()
{
	return m_shape.rva0030B6E3();
}

struct FloatRect0073CE30
{
	float x1;
	float y1;
	float x2;
	float y2;
};

// ?rva002E3954@PolygonTrigger@@QAEXPAUFloatRect0073CE30@@@Z @ 0x002E3954 (36B). PolygonTrigger rect copy: if out is null return; else take region via rowed rva0007E03A 0x0007E03A and copy 16B to out. Callers 0x0035784F 0x00357912 0x003C0169 name it; LINK 2 files 306B. Honest pin name.
void PolygonTrigger::rva002E3954(FloatRect0073CE30 *rect)
{
	if (!rect)
		return;
	*(Region2D *)rect = rva0007E03A();
}
