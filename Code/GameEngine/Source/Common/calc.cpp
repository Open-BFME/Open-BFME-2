// cl: /DNDEBUG /MD /EHs-c-
// ?Rva00503D8EEvaluate@@YAMMMMMM@Z @0x00503D8E 93B: Catmull-Rom scalar evaluate(p0 p1 p2 p3 t).
// Donor: reference/open-bfme-1/Code/GameEngine/Source/Common/calc.cpp (Rva00064410Catmull::evaluate stub)
// and BfmeConv1266.cpp bfmeSpline1266 formula. Callers at 0x00503F61 0x00503F8B 0x00503FB1 0x00504477
// 0x005C718B 0x005C735C 0x005C7386 0x005C73AE. Constants 3.0 5.0 4.0 0.5 in .rdata.
// ?Rva00503F2CCalc@@YAXPAURva00503F2CPoint@@PBU1@111M@Z @0x00503F2C 165B: Catmull-Rom 3D wrapper, 3 evaluate calls.
// ?Rva00503D26Evaluate@@YAMMMMM@Z @0x00503D26 40B, ?rva00503DEB@Rva00503DEB@@QAEMXZ @0x00503DEB 44B,
// ?Rva00503D4ECubic@@YAMMMMMM@Z @0x00503D4E 64B and ?rva00503E17@Rva00503E17@@QAEMXZ @0x00503E17 56B:
// the Bezier ease helpers, moved here from Rva00503D26Bezier.cpp and Rva00503E17BezierCall.cpp
// because the curve lookup 0x005042F2 keeps a value in EDX across 0x00503DEB, which only a
// caller that sees all four helpers' bodies does (with any one of them out of the unit it does
// not); they compile unchanged here, so retail built them in one unit with that caller.
// g_Va00863BF8 came along (its old file held nothing else); g_Va00863BFC stays
// defined in Rva00503E17BezierCall.cpp.

struct Rva00503F2CPoint
{
	float x;
	float y;
	float z;
};

float __cdecl Rva00503D8EEvaluate(float p0, float p1, float p2, float p3, float t)
{
	return ((((p1 * 3.0f - p0 - p2 * 3.0f + p3) * t + (p0 + p0 - p1 * 5.0f + p2 * 4.0f - p3)) * t + (p2 - p0)) * t + (p1 + p1)) * 0.5f;
}

void __cdecl Rva00503F2CCalc(Rva00503F2CPoint *out, const Rva00503F2CPoint *p0, const Rva00503F2CPoint *p1, const Rva00503F2CPoint *p2, const Rva00503F2CPoint *p3, float t)
{
	volatile float z = Rva00503D8EEvaluate(p0->z, p1->z, p2->z, p3->z, t);
	volatile float y = Rva00503D8EEvaluate(p0->y, p1->y, p2->y, p3->y, t);
	float x = Rva00503D8EEvaluate(p0->x, p1->x, p2->x, p3->x, t);
	out->x = x;
	out->y = y;
	out->z = z;
}

// Quadratic Bezier scalar evaluate(a b c t) = (1-t)^2*a + 2*(1-t)*t*b + t^2*c.
// Pure x87, EBP frame. Callers 0x00503E0E 0x00503E46.
float __cdecl Rva00503D26Evaluate(float a, float b, float c, float t)
{
	float u = 1 - t;
	float s = a * u + 2 * b * t;
	s = s * u + c * t * t;
	return s;
}
// g_Va00863BF8: matched references place it at VA 0xc63bf8 (retail .rdata value 0.5833333f).
float g_Va00863BF8 = 0.5833333f;

struct Rva00503DEB
{
	char m_pad[0x10];
	float m_10;
	float rva00503DEB();
};
float Rva00503DEB::rva00503DEB()
{
	return Rva00503D26Evaluate(0.5f, g_Va00863BF8, 1.0f, m_10);
}
float __cdecl Rva00503D4ECubic(float a, float b, float c, float d, float t)
{
	float u = 1 - t;
	float s = a * u + b * t * 3.0f;
	s = s * u + c * t * t * 3.0f;
	s = s * u + d * t * t * t;
	return s;
}

// ?rva005042F2@Rva005042F2@@QAE_NIPAURva005042F2Key@@@Z @0x005042F2 415B.
// Retail 005042F2..00504491, RET8: time-keyed Catmull-Rom curve lookup over
// an ordered set of seven-dword control points (STLport _Rb_tree header at
// +0, node count at +4; node value at +0x10, key time at value+0x18). WB
// 12CAC30 is the unnamed debug twin. Target facts: an empty set returns
// false; a time at or before the first key, at or after the last, or whose
// lower bound is the first or end copies that whole point and returns false;
// otherwise the four neighbours p0..p3 around the lower bound p2 give the
// eased parameter (cubic 0x00503D4E over p1/p2 ease helpers 0x00503E17 and
// 0x00503DEB), Catmull-Rom position 0x00503F2C and scalar 0x00503D8E, and
// the result stores the requested time. Callees are their rowed views.
// It shares this unit with its helpers: retail keeps the out pointer in EAX
// across 0x00503D8E and a value in EDX across 0x00503DEB, which only a
// caller that sees those bodies may do. 0x00503F2C returns its out pointer in EAX (retail
// copies through it); its rowed spelling is void, so the call goes through
// a pointer-returning cast of the same function.

struct Rva005042F2Key
{
	float x, y, z;		// +0x00
	float w;		// +0x0C
	float m_10, m_14;	// +0x10
	unsigned int time;	// +0x18
};

namespace _STL
{
struct _Rb_tree_node_base;
template <class _Dummy> class _Rb_global
{
public:
	static _Rb_tree_node_base *_M_decrement(_Rb_tree_node_base *);
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}

typedef Rva00503F2CPoint *(__cdecl *Rva00503F2CCalcRet)(Rva00503F2CPoint *, const Rva00503F2CPoint *, const Rva00503F2CPoint *, const Rva00503F2CPoint *, const Rva00503F2CPoint *, float);

// Evaluate(0.0 g_863BFC 0.5 g_7BB8D8 minus m_14): SSE for t, x87 for args; caller 0x005043DF.
// g_Va00863BFC (VA 0xc63bfc, retail .rdata 0.41666666f) is defined in Rva00503E17BezierCall.cpp.
extern float g_Va00863BFC;
struct Rva00503E17
{
	char m_pad[0x14];
	float m_14;
	float rva00503E17();
};
float Rva00503E17::rva00503E17()
{
	return Rva00503D26Evaluate(0.0f, g_Va00863BFC, 0.5f, 1.0f - m_14);
}
struct Rva002BE7DBValue { float x, y, z; };
class Rva002BE7DB { public: Rva002BE7DBValue &rva002BE7DB(Rva002BE7DBValue &out) const; };
class Rva000643C0Value { public: Rva000643C0Value(void *); private: char m_data[0x1C]; };
class Rva00504112 { public: void *rva00504112(void *rec); };

struct Rva005042F2Node
{
	int m_color;
	Rva005042F2Node *m_parent;
	Rva005042F2Node *m_left;
	Rva005042F2Node *m_right;
	Rva005042F2Key m_value;
};

static inline Rva005042F2Node *prevNode(Rva005042F2Node *node)
{
	return (Rva005042F2Node *)_STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)node);
}
static inline Rva005042F2Node *nextNode(Rva005042F2Node *node)
{
	return (Rva005042F2Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)node);
}
static inline const Rva002BE7DB *pointOf(const Rva005042F2Node *node)
{
	return (const Rva002BE7DB *)&node->m_value;
}

class Rva005042F2
{
public:
	bool rva005042F2(unsigned int time, Rva005042F2Key *out);
private:
	Rva005042F2Node *m_header;
	unsigned int m_count;
};

bool Rva005042F2::rva005042F2(unsigned int time, Rva005042F2Key *out)
{
	if (m_count == 0)
		return false;
	Rva005042F2Node *first = m_header->m_left;
	if (time <= first->m_value.time) {
		*out = first->m_value;
		return false;
	}
	Rva005042F2Node *last = prevNode(m_header);
	if (time > last->m_value.time) {
		*out = last->m_value;
		return false;
	}
	Rva000643C0Value key((void *)time);
	Rva005042F2Node *p1 = (Rva005042F2Node *)((Rva00504112 *)this)->rva00504112(&key);
	if (p1 == first) {
		*out = first->m_value;
		return false;
	}
	if (p1 == m_header) {
		*out = last->m_value;
		return false;
	}
	Rva005042F2Node *p2 = p1;
	p1 = prevNode(p1);
	Rva005042F2Node *p0 = p1;
	if (p1 != first)
		p0 = prevNode(p0);
	Rva005042F2Node *p3 = p2;
	if (p2 != last)
		p3 = nextNode(p3);
	float t = (float)(time - p1->m_value.time) / (float)(p2->m_value.time - p1->m_value.time);
	float s = Rva00503D4ECubic(0.0f, ((Rva00503E17 *)&p1->m_value)->rva00503E17(), ((Rva00503DEB *)&p2->m_value)->rva00503DEB(), 1.0f, t);
	Rva002BE7DBValue a, b, c, d;
	Rva00503F2CPoint pos;
	Rva00503F2CPoint *res = ((Rva00503F2CCalcRet)&Rva00503F2CCalc)(&pos,
		(const Rva00503F2CPoint *)&pointOf(p0)->rva002BE7DB(a),
		(const Rva00503F2CPoint *)&pointOf(p1)->rva002BE7DB(b),
		(const Rva00503F2CPoint *)&pointOf(p2)->rva002BE7DB(c),
		(const Rva00503F2CPoint *)&pointOf(p3)->rva002BE7DB(d), s);
	*(Rva00503F2CPoint *)out = *res;
	out->w = Rva00503D8EEvaluate(p0->m_value.w, p1->m_value.w, p2->m_value.w, p3->m_value.w, s);
	out->time = time;
	return true;
}
