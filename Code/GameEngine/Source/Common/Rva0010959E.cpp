// cl: /DNDEBUG /MD
// ?rva0010959E@Rva0010959E@@QAEXXZ @0x0010959E 20B
// Calls rowed W3DProjectedShadow::rva00108951 at +0x58 then tail-jmps it at
// +0x5C; caller at 0x0010BA18; chain from 0x00108951.
class W3DProjectedShadow
{
public:
	void rva00108951();
};
class Rva0010959E
{
public:
	void rva0010959E();
private:
	char m_pad0[4];
	unsigned char m_4;
	unsigned char m_5;
	char m_pad6[2];
	float m_8;
	float m_C;
	float m_10;
	char m_pad14[12];
	float m_20;
	char m_pad24[52];
	W3DProjectedShadow *m_58;
	W3DProjectedShadow *m_5c;
	int m_60;
};
void Rva0010959E::rva0010959E()
{
	m_58->rva00108951();
	return m_5c->rva00108951();
}

struct Node : public Rva0010959E
{
	Node *m_next64;
};
class Rva0010B9E5
{
public:
	void rva0010B9E5(Node *arg);
private:
	char m_pad[0x14];
	Node *m_head14;
	Node *m_tail18;
};
void Rva0010B9E5::rva0010B9E5(Node *arg)
{
	Node *cur = m_head14;
	Node *prev = 0;
	while (cur != 0) {
		if (cur == arg) {
			if (prev != 0)
				prev->m_next64 = arg->m_next64;
			else
				m_head14 = arg->m_next64;
			Node *tail = m_tail18;
			arg->m_next64 = tail;
			m_tail18 = arg;
			arg->rva0010959E();
		}
		prev = cur;
		cur = cur->m_next64;
	}
}
