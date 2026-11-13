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
 GapQuat(float xComponent,float yComponent,float zComponent,float wComponent):x(xComponent),y(yComponent),z(zComponent),w(wComponent) {}
 void assign(const GapQuat&quaternion) {x=quaternion.x;y=quaternion.y;z=quaternion.z;w=quaternion.w;}

	float x;
	float y;
	float z;
	float w;
 void Rotate(const GapVec3&vector,GapVec3*out) const;
};

struct GapVec3
{
 GapVec3() {}
 GapVec3(float xComponent,float yComponent,float zComponent):x(xComponent),y(yComponent),z(zComponent) {}
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
	void rva0015FE80(const GapVec3 &localTranslation);
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
#include "../../Include/Common/GapWords3.h"

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
	GapRefItem *rva0016EB50(int itemIndex);
private:
	char m_pad00[0xA8];
	GapRefItem *m_items[4];									// +0xA8
};

GapRefItem *Rva0016EB50::rva0016EB50(int itemIndex)
{
	GapRefItem *item = m_items[itemIndex];
	if (item)
		item->m_refs += 1;
	return m_items[itemIndex];
}

// --- 0x00189400 (33B): slot 2 (+8) of the object embedded at +0x23C, then
// the +0x240 word.
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
inline void GapQuat::Rotate(const GapVec3&vector,GapVec3*result) const {
	float rx = w*vector.x + (y*vector.z - vector.y*z);
	float ry = w*vector.y - (x*vector.z - vector.x*z);
	float rz = w*vector.z + (x*vector.y - vector.x*y);
	float rw = -(x*vector.x + y*vector.y + z*vector.z);
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

void Rva0015F920::rva0015F9E0(const Rva0015F920&firstTransform,const Rva0015F920&secondTransform,Rva0015F920*composedTransform) {GapVec3 rotatedTranslation; firstTransform.m_q.Rotate(secondTransform.m_t,&rotatedTranslation);composedTransform->m_t=rotatedTranslation+firstTransform.m_t;composedTransform->m_q.assign(firstTransform.m_q*secondTransform.m_q);}

// --- 0x0015FE80 (322B): translate by v in the local frame: the rotation
// applied to v (same Rotate_Vector spelling as the compose above) is added
// to the translation.
void Rva0015F920::rva0015FE80(const GapVec3 &localTranslation)
{
	GapVec3 rotatedTranslation;
	m_q.Rotate(localTranslation, &rotatedTranslation);
	m_t += rotatedTranslation;
}
