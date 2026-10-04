// ?rva004693D9@Rva004693D9@@QAEXXZ
// partial score=0.97 date=2026-10-04
// cl: /O1 /MD /arch:SSE
// ?rva004693D9@Rva004693D9@@QAEXXZ 0x004693D9 308B evidence: vector at holder+0x18c via AsciiString key through g_009FF000 row 0x002D06CA flag 0x109 bit 8 then float avg via g_Va00BBB8D8 caller 0x00474519
class AsciiString;
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern Rva002D06CA *g_009FF000;
extern float g_Va00BBB8D8;
struct Flag109
{
	unsigned char m_pad[0x109];
	unsigned char m_flags;
};
struct Item16
{
	char m_d[16];
};
struct SubEntry
{
	int m_00;
	int m_keyPlaceholder;
	Item16 *m_08Begin;
	Item16 *m_0CEnd;
};
struct Vec28
{
	int m_00;
	float m_04;
	float m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
};
struct SubVec
{
	SubEntry **m_beg;
	SubEntry **m_end;
};
struct Holder
{
	char m_pad[0x18C];
	SubVec m_vec;
};
class Rva004693D9
{
public:
	void rva004693D9();
private:
	char m_pad00[4];
	Holder *m_04;
	char m_pad08[0x180];
	Vec28 *m_188;
	Vec28 *m_18C;
};
// ?rva004693D9@Rva004693D9@@QAEXXZ present-unmatched
void Rva004693D9::rva004693D9()
{
	SubVec *v = &m_04->m_vec;
	int total = 0;
	int wanted = -1;
	if ((((char *)v->m_end - (char *)v->m_beg) >> 2) != 0) {
		unsigned i = 0;
		do {
			void *f = g_009FF000->rva002D06CA((const AsciiString *)((char *)v->m_beg[i] + 4));
			if (f != 0 && ((((Flag109 *)f)->m_flags) & 8) != 0) {
				wanted = total;
				break;
			}
			SubEntry *e = v->m_beg[i];
			total += (int)(e->m_0CEnd - e->m_08Begin);
			++i;
		} while (i < (unsigned)(((char *)v->m_end - (char *)v->m_beg) >> 2));
	}
	Vec28 *b2 = m_188;
	Vec28 *e2 = m_18C;
	float sx = 0.0f;
	float sy = 0.0f;
	int n = 0;
	total = 0;
	if (b2 != e2) {
		Vec28 *p = b2;
		do {
			sx += p->m_04;
			sy += p->m_08;
			++n;
			if (total == wanted) {
				int ix = *(int *)&p->m_04;
				int iy = *(int *)&p->m_08;
				sx = *(float *)&ix;
				sy = *(float *)&iy;
				n = 1;
				break;
			}
			++total;
			++p;
		} while (p != e2);
	}
	if (n != 0) {
		float inv = g_Va00BBB8D8 / (float)n;
		sx *= inv;
		sy *= inv;
	}
	if (b2 != e2) {
		for (Vec28 *p = b2; p != e2; ++p) {
			p->m_04 -= sx;
			p->m_08 -= sy;
			p->m_0C = *(int *)&p->m_04;
			p->m_10 = *(int *)&p->m_08;
		}
	}
}
