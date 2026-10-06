// ?rva0027D483@Rva0027D483@@QAEXPAX0@Z
// partial score=0.8281 date=2026-10-05
// ?rva0027D483@Rva0027D483@@QAEXPAX0@Z
// partial score=0.9 date=2026-10-02
// cl: /O1 /MD /arch:SSE /G7
// ?rva0027D483@Rva0027D483@@QAEXPAX0@Z, retail 0x0027D483, 298 bytes.
// List walk via slot40 head, key at +0x60 vs arg+0x74; miss copies arg+0x38
// triple to both out triples; hit normalizes (top-base), lengths second
// segment, scales by g_Va007C26F0 and writes base+k*norm and top-k*norm.
// Evidence: rowed Coord3D normalize/length, slot 0xa0, callers 0x266CF3 etc.
extern float g_Va007C26F0;

class Coord3D
{
public:
	float x;
	float y;
	float z;
	float length() const;
	void normalize();
};

struct Rva0027D483Node
{
	char m_pad00[4];
	Rva0027D483Node *m_next;
	char m_pad08[4];
	float m_baseX;
	float m_baseY;
	float m_baseZ;
	float m_topX;
	float m_topY;
	float m_topZ;
	char m_pad24[4];
	float m_segBaseX;
	float m_segBaseY;
	float m_segBaseZ;
	float m_segTopX;
	float m_segTopY;
	float m_segTopZ;
	char m_pad40[0x60 - 0x40];
	int m_key;
};

struct Rva0027D483Arg
{
	char m_pad00[0x38];
	Coord3D m_triple;
	char m_pad44[0x74 - 0x44];
	int m_key;
};

struct Rva0027D483Out
{
	Coord3D m_first;
	Coord3D m_second;
};

class Rva0027D483
{
public:
	virtual void _slot00();
	virtual void _slot01();
	virtual void _slot02();
	virtual void _slot03();
	virtual void _slot04();
	virtual void _slot05();
	virtual void _slot06();
	virtual void _slot07();
	virtual void _slot08();
	virtual void _slot09();
	virtual void _slot10();
	virtual void _slot11();
	virtual void _slot12();
	virtual void _slot13();
	virtual void _slot14();
	virtual void _slot15();
	virtual void _slot16();
	virtual void _slot17();
	virtual void _slot18();
	virtual void _slot19();
	virtual void _slot20();
	virtual void _slot21();
	virtual void _slot22();
	virtual void _slot23();
	virtual void _slot24();
	virtual void _slot25();
	virtual void _slot26();
	virtual void _slot27();
	virtual void _slot28();
	virtual void _slot29();
	virtual void _slot30();
	virtual void _slot31();
	virtual void _slot32();
	virtual void _slot33();
	virtual void _slot34();
	virtual void _slot35();
	virtual void _slot36();
	virtual void _slot37();
	virtual void _slot38();
	virtual void _slot39();
	virtual Rva0027D483Node *_slot40();
	void rva0027D483(void *a, void *b);
};

// ?rva0027D483@Rva0027D483@@QAEXPAX0@Z present-unmatched
void Rva0027D483::rva0027D483(void *a, void *b)
{
	Rva0027D483Arg *arg = (Rva0027D483Arg *)a;
	Rva0027D483Out *out = (Rva0027D483Out *)b;
	Rva0027D483Node *cur = _slot40();
	int key = arg->m_key;
	while (cur != 0) {
		if (cur->m_key == key)
			break;
		cur = cur->m_next;
	}
	if (cur == 0) {
		out->m_first = arg->m_triple;
		out->m_second = arg->m_triple;
		return;
	}
	Coord3D dir;
	dir.x = cur->m_topX - cur->m_baseX;
	dir.y = cur->m_topY - cur->m_baseY;
	dir.z = cur->m_topZ - cur->m_baseZ;
	dir.normalize();
	Coord3D seg;
	seg.x = cur->m_segTopX - cur->m_segBaseX;
	seg.y = cur->m_segTopY - cur->m_segBaseY;
	seg.z = cur->m_segTopZ - cur->m_segBaseZ;
	float k = seg.length() * g_Va007C26F0;
	out->m_first.x = cur->m_baseX + k * dir.x;
	out->m_first.y = cur->m_baseY + k * dir.y;
	out->m_first.z = cur->m_baseZ + k * dir.z;
	out->m_second.x = cur->m_topX - k * dir.x;
	out->m_second.y = cur->m_topY - k * dir.y;
	out->m_second.z = cur->m_topZ - k * dir.z;
}
