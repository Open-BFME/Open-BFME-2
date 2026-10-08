// cl: /MD
// ?rva0027D244@Rva0027D244@@QAEPAV1@H@Z, retail 0x0027D244, 50 bytes.
// Thiscall init of a 0x1C-byte struct: zeroes floats at +0/+4/+8, zeroes
// dwords at +0xC/+0x14, copies global float VA 0x00BC876C to +0x10, stores
// the int arg at +0x18. Caller 0x0027F13C builds the 0x1C struct on the
// stack. Same Common family as neighbours Rva0027D1A4Forward/Rva0027D347.
// No donor: honest address name.
//
// ?rva0027D1EF@Rva0027D244@@QAEXPAV1@0@Z, retail 0x0027D1EF, 85 bytes, the
// method right before it in the same TU: "keep the nearer of two" -- squared
// 2D distance from b's position to a's; unless this record is already taken
// (+0xC) and its stored distance (+0x10) is not greater, copy a's slot, its
// position (three movsd), the distance and a itself (+0x14). Retail loads both
// of b's floats before touching a and reuses eax for both pointers: that is a
// copy of b's position through a user-defined memberwise copy ctor (float
// loads, not a block move), which the Vec12 type carries; plain float locals,
// a by-value helper or a struct without the ctor interleave the loads or copy
// with movsd (reverse/re_attempts.log).
class Rva0027D244
{
public:
	struct Vec12
	{
		Vec12() {}
		Vec12(const Vec12 &o) : x(o.x), y(o.y), z(o.z) {}
		float x, y, z;
	};
	Rva0027D244 *rva0027D244(int v);
	void rva0027D1EF(Rva0027D244 *a, Rva0027D244 *b);
	void rva0027D276(Rva0027D244 *a, Rva0027D244 *b);
private:
	Vec12 m_pos00;
	int m_0C;
	float m_10;
	int m_14;
	int m_18;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object
{
public:
	unsigned char _pad[0x38];
	Coord3D m_38;
};

class Pathfinder
{
public:
	bool QuickDoesPathExist(class Object *obj, const struct Coord3D *from, const struct Coord3D *to, int v);
	bool IsGroundLineOnly(const struct Coord3D *a, const struct Coord3D *b);
};

class AI
{
public:
	unsigned char _pad[0x10];
	Pathfinder *m_10;
};

extern class AI *TheAI;

Rva0027D244 *Rva0027D244::rva0027D244(int v)
{
	float t = 10000000.0f;
	Rva0027D244 *s = this;
	int u = v;
	s->m_0C = 0;
	s->m_14 = 0;
	s->m_10 = t;
	s->m_18 = u;
	s->m_pos00.x = 0.0f;
	s->m_pos00.y = 0.0f;
	s->m_pos00.z = 0.0f;
	return s;
}

void Rva0027D244::rva0027D1EF(Rva0027D244 *a, Rva0027D244 *b)
{
	Vec12 p = b->m_pos00;
	float dx = p.x - a->m_pos00.x;
	float dy = p.y - a->m_pos00.y;
	float d2 = dx * dx + dy * dy;
	if (m_0C != 0 && !(m_10 > d2))
		return;
	m_0C = a->m_0C;
	m_pos00 = a->m_pos00;
	m_10 = d2;
	m_14 = (int)a;
}

void Rva0027D244::rva0027D276(Rva0027D244 *a, Rva0027D244 *b)
{
	Vec12 p = b->m_pos00;
	float dx = p.x - a->m_pos00.x;
	float dy = p.y - a->m_pos00.y;
	float d2 = dx * dx + dy * dy;
	if (m_0C != 0 && d2 >= m_10)
		return;
	Pathfinder *pf = TheAI->m_10;
	Object *obj = (Object *)m_18;
	if (!pf->QuickDoesPathExist(obj, &obj->m_38, (const Coord3D *)a, 0))
		return;
	pf = TheAI->m_10;
	obj = (Object *)m_18;
	if (!pf->IsGroundLineOnly(&obj->m_38, (const Coord3D *)a))
		return;
	m_0C = a->m_0C;
	m_pos00 = a->m_pos00;
	m_10 = d2;
	m_14 = (int)a;
}
