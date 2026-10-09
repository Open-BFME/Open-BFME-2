// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva003FBB99@Rva003FBA58@@QAEXXZ retail 0x003FBB99..0x003FBC4D (180
// bytes ret 0). Same receiver as the rowed Rva003FBA58 siblings (vtable
// 0x008747B8: +0x08 child +0x4C mode). WorldBuilder twin 0x01071050 (vtable
// evidence) shows the source shape: when the +0x58 enable byte is set and
// the mode is non-zero it runs the child's vtable +0x50 update and reads
// the current position through 0x003FB793. A copy of the +0x68 vector less
// the +0x5C vector is scaled by the +0x74 rate (mode 1) or its negation
// (mode 2) then added to the position and handed to vtable +0x1C. The two
// inline scale calls tail-merge into retail's single multiply block (the
// MOVAPS pair on x comes from that). Names are inferred; the class and
// method stay address-derived like the siblings.
struct Vec3
{
	float x, y, z;
	Vec3() {}
	Vec3(const Vec3 &v) : x(v.x), y(v.y), z(v.z) {}
	void sub(const Vec3 &o) { x -= o.x; y -= o.y; z -= o.z; }
	void add(const Vec3 &o) { x += o.x; y += o.y; z += o.z; }
	void scale(float s) { x *= s; y *= s; z *= s; }
};

class Rva003F936EHost
{
public:
	void rva003FB793(Vec3 *out);
};

class Rva003FBB99Child
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void update(); // +0x50
};

class Rva003FBA58
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06();
	virtual void setPosition(const Vec3 *pos); // +0x1C
	void rva003FBB99();

private:
	char m_pad04[4];
	Rva003FBB99Child *m_child; // +0x08
	char m_pad0C[0x4C - 0x0C];
	int m_mode; // +0x4C
	char m_pad50[0x58 - 0x50];
	bool m_enabled; // +0x58
	Vec3 m_from; // +0x5C
	Vec3 m_to; // +0x68
	float m_rate; // +0x74
};

void Rva003FBA58::rva003FBB99()
{
	if (!m_enabled || m_mode == 0)
		return;
	m_child->update();
	Vec3 pos;
	reinterpret_cast<Rva003F936EHost *>(this)->rva003FB793(&pos);
	Vec3 delta = m_to;
	delta.sub(m_from);
	if (m_mode == 1)
		delta.scale(m_rate);
	else if (m_mode == 2)
		delta.scale(-m_rate);
	delta.add(pos);
	setPosition(&delta);
}

