// cl: /MD
//
// ?rva00330C0F@Rva00330C0F@@QAE?AURegion2D@@XZ retail 0x00330C0F 19B
// this-adjusting Region2D forwarder: this-0x3C then Region2D return via the
// rowed PolygonTrigger::rva0007E03A 0x0007E03A. Same family as the 0x00330BDB
// this-0x34 float forwarder and the pinned 0x00330C22 this-0x3C center
// forwarder. Honest address names.

struct Region2D
{
	Region2D(const Region2D &that);
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

class PolygonTrigger
{
public:
	Region2D rva0007E03A();
};

class Rva00330C0F
{
public:
	Region2D rva00330C0F();
};

Region2D Rva00330C0F::rva00330C0F()
{
	PolygonTrigger *trigger = (PolygonTrigger *)((char *)this - 0x3C);
	return trigger->rva0007E03A();
}
