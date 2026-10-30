// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG
// Small bodies from .text gaps no Ghidra function covers (forty-seventh
// batch; see GapBodiesGE01.cpp), all from /O2 /arch:SSE /G7 retail regions
// between 0x001541E0 and 0x0019FFFF (reverse/retail_inventory/
// flag_regions.csv). Each begins after its neighbour's padding or ret and
// ends in its own ret. Retail bytes establish every shape; owning classes are
// not recovered, so each keeps an address-derived name and a view of only
// the members it touches.

// --- 0x0015F560 (48B): four floats, returning this; 0x0015F590 (46B): set
// them.
class Rva0015F560
{
public:
	Rva0015F560(float a, float b, float c, float d);
	void rva0015F590(float a, float b, float c, float d);
private:
	float m_a;
	float m_b;
	float m_c;
	float m_d;
};

Rva0015F560::Rva0015F560(float a, float b, float c, float d) : m_a(a), m_b(b), m_c(c), m_d(d)
{
}

void Rva0015F560::rva0015F590(float a, float b, float c, float d)
{
	m_a = a;
	m_b = b;
	m_c = c;
	m_d = d;
}

// --- 0x0015F920 (57B): an identity rotation (when asked) and a zero
// translation; 0x0015F9A0 (56B): a four-word rotation and a three-word
// translation copied in.
struct GapVec3;
struct GapQuat
{
 GapQuat() {}
 GapQuat(float ax,float ay,float az,float aw):x(ax),y(ay),z(az),w(aw) {}
 void assign(const GapQuat&v) {x=v.x;y=v.y;z=v.z;w=v.w;}

	float x;
	float y;
	float z;
	float w;
 void Rotate(const GapVec3&v,GapVec3*out) const;
};

struct GapVec3
{
 GapVec3() {}
 GapVec3(float ax,float ay,float az):x(ax),y(ay),z(az) {}
 GapVec3& operator=(const GapVec3&v) {x=v.x;y=v.y;z=v.z;return *this;}
 GapVec3& operator+=(const GapVec3&v) {x+=v.x;y+=v.y;z+=v.z;return *this;}

	float x;
	float y;
	float z;
};

class Rva0015F920
{
public:
	Rva0015F920(bool identity);
	Rva0015F920(const GapQuat &rotation, const GapVec3 &translation);
	static void rva0015F9E0(const Rva0015F920 &,const Rva0015F920 &,Rva0015F920 *);
	void rva0015FE80(const GapVec3 &v);
private:
	GapQuat m_q;
	GapVec3 m_t;
};

Rva0015F920::Rva0015F920(bool identity)
{
	if (identity)
	{
		m_q.x = 0.0f;
		m_q.y = 0.0f;
		m_q.z = 0.0f;
		m_q.w = 1.0f;
	}
	m_t.x = 0.0f;
	m_t.y = 0.0f;
	m_t.z = 0.0f;
}

Rva0015F920::Rva0015F920(const GapQuat &rotation, const GapVec3 &translation)
{
	m_q = rotation;
	m_t.x = translation.x;
	m_t.y = translation.y;
	m_t.z = translation.z;
}

// --- 0x00167E04 (24B): copy a three-word value into +0x0C.
struct GapWords3
{
	int a;
	int b;
	int c;
};

class Rva00167E04
{
public:
	void rva00167E04(const GapWords3 &value);
private:
	char m_pad00[0x0C];
	int m_0C;
	int m_10;
	int m_14;
};

void Rva00167E04::rva00167E04(const GapWords3 &value)
{
	m_0C = value.a;
	m_10 = value.b;
	m_14 = value.c;
}

// --- 0x0016EB50 (29B): the +0xA8 item i with a reference added.
struct GapRefItem
{
	int m_00;
	int m_refs;												// +0x04
};

class Rva0016EB50
{
public:
	GapRefItem *rva0016EB50(int i);
private:
	char m_pad00[0xA8];
	GapRefItem *m_items[4];									// +0xA8
};

GapRefItem *Rva0016EB50::rva0016EB50(int i)
{
	GapRefItem *item = m_items[i];
	if (item)
		item->m_refs += 1;
	return m_items[i];
}

// --- 0x00189400 (33B): slot 2 (+8) of the object embedded at +0x23C, then
// the +0x240 word.
class GapSlot2View
{
public:
	virtual void v00();
	virtual void v01();
	virtual void slot2(int value);
};

class Rva00189400
{
public:
	int rva00189400(int value);
private:
	char m_pad00[0x23C];
	GapSlot2View m_23C;
	int m_240;
};

int Rva00189400::rva00189400(int value)
{
	GapSlot2View *target = &m_23C;
	target->slot2(value);
	return m_240;
}

// --- 0x0019AF00 (20B): three zero floats, returning this.
class Rva0019AF00
{
public:
	Rva0019AF00();
private:
	float m_x;
	float m_y;
	float m_z;
};

Rva0019AF00::Rva0019AF00()
{
	m_z = 0.0f;
	m_y = 0.0f;
	m_x = 0.0f;
}


// --- 0x0015F9E0 (567B, static): compose two rotation+translation pairs:
// out.t = a.q rotating b.t, plus a.t; out.q = a.q * b.q. The expansion is
// WWMath quat.h's result-pointer Rotate_Vector and the quaternion product in
// the term order of the rowed neighbours 0x0015F6D0 / 0x0015F810 / 0x0015FC20
// (donor shape; owner class and names unknown).
// ?GapQuat::Rotate absent-from-retail
inline void GapQuat::Rotate(const GapVec3&v,GapVec3*result) const {
	float rx = w*v.x + (y*v.z - v.y*z);
	float ry = w*v.y - (x*v.z - v.x*z);
	float rz = w*v.z + (x*v.y - v.x*y);
	float rw = -(x*v.x + y*v.y + z*v.z);
	result->x = w*rx - rw*x + (y*rz - ry*z);
	result->y = w*ry - rw*y - (x*rz - rx*z);
	result->z = w*rz - rw*z + (x*ry - y*rx);
}
// ?GapVec3::operator+ absent-from-retail
inline GapVec3 operator+(const GapVec3&a,const GapVec3&b) {return GapVec3(a.x+b.x,a.y+b.y,a.z+b.z);}
// ?GapQuat::operator* absent-from-retail
inline GapQuat operator*(const GapQuat&saved,const GapQuat&other) {
	return GapQuat(other.w*saved.x + (saved.y*other.z - other.y*saved.z) + saved.w*other.x,
		other.w*saved.y + saved.w*other.y - (saved.x*other.z - other.x*saved.z),
		(saved.x*other.y - other.x*saved.y) + other.w*saved.z + saved.w*other.z,
		other.w*saved.w - (other.z*saved.z + other.y*saved.y + other.x*saved.x));
}

void Rva0015F920::rva0015F9E0(const Rva0015F920&a,const Rva0015F920&b,Rva0015F920*out) {GapVec3 t; a.m_q.Rotate(b.m_t,&t);out->m_t=t+a.m_t;out->m_q.assign(a.m_q*b.m_q);}

// --- 0x0015FE80 (322B): translate by v in the local frame: the rotation
// applied to v (same Rotate_Vector spelling as the compose above) is added
// to the translation.
void Rva0015F920::rva0015FE80(const GapVec3 &v)
{
	GapVec3 t;
	m_q.Rotate(v, &t);
	m_t += t;
}
