// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva002C5AE6@Rva002C589B@@QAEMXZ @0x002C5AE6 96B via max array float plus m_28
// Evidence: pin QAEMXZ float no args; caller 0x00505383 matched plus 0x0059A1F0; this+0 m_00 via global g_00DFEEF8 to rowed rva002A8AB1 pin; rec+0x164 plus 0x20 bounds; elems float at +0x18 max from 0.0f; m_28 float at +0x28 max; SSE xorps movss comiss plus fld return; prev/next Rva002C589B same class
class Rva002A8F24;
struct Rva002A8AB1Record;
extern Rva002A8F24 *g_00DFEEF8;

struct Rva002A8AB1Record
{
	char _pad[0x164];
	void *m_164;
};

struct ArrayBounds002C5AE6
{
	void **m_start;
	void **m_end;
};

struct Elem002C5AE6
{
	char _pad[0x18];
	float m_18;
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *p);
};

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

class Rva003ECDB7Object
{
public:
	~Rva003ECDB7Object();
};

class Rva002C589B
{
public:
	float rva002C5AE6();
private:
	int m_00;
	unsigned int m_04;
	unsigned int m_08;
	Coord3DBase m_0C;
	bool m_18;
	bool m_19;
	char m_pad1A[2];
	int m_1C;
	int m_20;
	Rva003ECDB7Object *m_24;
	float m_28;
};

float Rva002C589B::rva002C5AE6()
{
	float vmax = 0.0f;
	Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(*(void **)this);
	ArrayBounds002C5AE6 *b = (ArrayBounds002C5AE6 *)((char *)rec->m_164 + 0x20);
	void **it = b->m_start;
	void **end = b->m_end;
	while (it != end) {
		Elem002C5AE6 *e = *(Elem002C5AE6 **)it;
		if (e->m_18 > vmax)
			vmax = e->m_18;
		it++;
	}
	return (vmax > m_28) ? vmax : m_28;
}
