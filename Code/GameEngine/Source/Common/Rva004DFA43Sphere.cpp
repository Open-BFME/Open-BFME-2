// cl: /MD
// ?rva004DFA43@Rva004DFA43@@QAE_NPAX0@Z, RVA 0x004DFA43, 112 bytes.
// __thiscall sphere test: radius m_04-m_14 vs distance from center
// m_08/m_0C/m_10 to the point returned by the __cdecl getter in the second
// arg called with the first arg. Evidence: EBP frame plus push [ebp+8] call
// [ebp+C] plus movss/subss/mulss/addss/comiss plus ret8 plus callers at
// 0x002829FE and 0x004DFD27. Neighbours are /O1 /MD; SSE for movss.
// Structural inference: the test is written d2 <= r * r, which evaluates d2
// first, loads r late and keeps r*r first in comiss with jb to false.
struct Vec3
{
	float x;
	float y;
	float z;
	Vec3() {}
	Vec3(const Vec3 &other) : x(other.x), y(other.y), z(other.z) {}
};

class Rva004DFA43
{
public:
	bool rva004DFA43(void *ctx, void *fn);

private:
	float m_00;
	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
};

bool Rva004DFA43::rva004DFA43(void *ctx, void *fn)
{
	float r = m_04 - m_14;
	Vec3 *p = ((Vec3 *(__cdecl *)(void *))fn)(ctx);
	float dx = p->x - m_08;
	float dy = p->y - m_0C;
	float dz = p->z - m_10;
	if (dz * dz + dy * dy + dx * dx <= r * r)
		return true;
	return false;
}

// Native 0x004DFAB3..0x004DFB55: compare two positions supplied by the
// receiver's callback at +0x20 against twice the squared value returned by
// virtual slot 0. Both explicit arguments are passed separately to that
// cdecl callback. The first three-float copy is kept on the stack across the
// second callback; the explicit copy constructor gives retail's three SSE
// loads for the second copy. The radius term must be evaluated first for
// the strict comparison, including retail's unordered/NaN false branch.
// Callers include 0x00282B26 and 0x004DFE4F. This partial receiver view and
// method retain address-derived names; no original application type is inferred.
class Rva004DFAB3
{
public:
    virtual float radius();
    bool rva004DFAB3(void *a, void *b);
private:
    char unknown04[0x1c];
    Vec3 *(__cdecl *position)(void *);
};

bool Rva004DFAB3::rva004DFAB3(void *a, void *b)
{
    float r = radius();
    Vec3 p = *position(a);
    Vec3 q = *position(b);
    float dx = p.x - q.x;
    float dy = p.y - q.y;
    float dz = p.z - q.z;
    if (r * r * 2.0f > dz * dz + dy * dy + dx * dx)
        return true;
    return false;
}
