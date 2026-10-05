// cl: /O1 /MD
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
private:
	unsigned char m_pad00[0x08];
	Rva0030B719Shape m_shape; // +0x08
};

Region2D PolygonTrigger::rva0007E03A()
{
	return m_shape.rva0030B6E3();
}
