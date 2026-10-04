// ?allow@Rva002617E8Filter@@QAE_NPAVObject@@@Z
// partial score=0.9 date=2026-10-04
// cl: /O1 /arch:SSE /DNDEBUG /MD
struct Coord3D
{
	float x, y, z;
};
class Object
{
public:
	float getShroudClearingRange() const;
	const Coord3D *getPosition() const { return &m_pos; }
	float getB8() const { return m_b8; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_pos;			// +0x38
	unsigned char m_pad44[0xB8 - 0x44];
	float m_b8;			// +0xB8
};
class Rva002617E8Filter
{
public:
	bool allow(Object *obj);
private:
	void *m_vptr;
	void *m_next;
	Coord3D m_pos;			// +0x08
	float m_range;			// +0x14
	bool m_inside;			// +0x18
};
bool Rva002617E8Filter::allow(Object *obj)
{
	float radius = obj->getShroudClearingRange();
	if (0.0f < radius) {
		float dx = obj->getPosition()->x - m_pos.x;
		float dy = obj->getPosition()->y - m_pos.y;
		float range = m_range + radius + obj->getB8();
		if (range * range > dx * dx + dy * dy)
			return m_inside;
	}
	return !m_inside;
}
