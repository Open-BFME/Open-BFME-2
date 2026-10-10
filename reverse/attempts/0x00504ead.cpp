// ?set@Rva00504EADCurve@@QAE_NMMMM@Z
// partial score=0.98 date=2026-10-10
// ?set@Rva00504EADCurve@@QAE_NMMMM@Z
// partial score=0.94 date=2026-10-06
// cl: /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7

// ?set@Rva00504EADCurve@@QAE_NMMMM@Z @0x00504EAD (92B).
// Target calls the tree insertion helper on the four incoming floats; class
// layout is inferred from the target's this+8 helper call and this+0x18 store.
struct Rva00504EADKeyTail
{
	Rva00504EADKeyTail(float v,float i,float o):m_value(v),m_inTangent(i),m_outTangent(o){}
	float m_value;
	float m_inTangent;
	float m_outTangent;
};

struct Rva00504EADKey
{
	Rva00504EADKey(float t,const Rva00504EADKeyTail&v):m_time(t),m_tail(v){}
	float m_time;
	Rva00504EADKeyTail m_tail;
};

struct Rva00504E6DResult
{
	Rva00504E6DResult(void *node, bool inserted)
		: m_node(node), m_inserted(inserted) {}

	void *m_node;
	bool m_inserted;
};

class Rva00504DF8
{
public:
	Rva00504E6DResult rva00504E6D(const void *value);
	void *m_begin;
	void *m_finish;
	void *m_capacity;
};

class Rva00504EADCurve
{
public:
	bool set(float time, float value, float inTangent, float outTangent);

private:
	char m_pad00[8];
	Rva00504DF8 m_tree;
	char m_pad14[4];
	void *m_lastNode;
};

bool Rva00504EADCurve::set(float time, float value, float inTangent, float outTangent)
{
	Rva00504EADKey key(time,Rva00504EADKeyTail(value,inTangent,outTangent));
	bool inserted = m_tree.rva00504E6D(&key).m_inserted;
	m_lastNode = m_tree.m_finish;
	return inserted;
}
