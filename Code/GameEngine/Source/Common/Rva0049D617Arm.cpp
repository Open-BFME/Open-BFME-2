// cl: /O1 /DNDEBUG /MD
//
// ?rva0049D617@Rva0049D617@@QAEXHE@Z @0x0049D617 104B ret 8.
// Index 0..3 stores the flag in the 0x10-stride record at +0x1C. A set flag
// with three zero dwords records TheGameLogic+0x40, ORs the table bit into
// the words at +0xA8, and sets +0xF4.

class GameLogic
{
public:
	char m_pad[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;
extern unsigned int g_00C51304[];

struct Rva0049D617Rec
{
	unsigned int m_a;
	unsigned int m_b;
	unsigned int m_c;
	unsigned char m_flag;
	char m_pad[3];
};

class Rva0049D617
{
public:
	void rva0049D617(int index, unsigned char flag);

private:
	char m_pad[0x1C];
	Rva0049D617Rec m_recs[4];
	char m_pad5C[0xA8 - 0x5C];
	unsigned int m_bits[19];
	unsigned char m_f4;
};

void Rva0049D617::rva0049D617(int index, unsigned char flag)
{
	if (index < 0 || index >= 4)
		return;
	Rva0049D617Rec *rec = &m_recs[index];
	rec->m_flag = flag;
	if (flag == 0)
		return;
	if (rec->m_a != 0 || rec->m_b != 0 || rec->m_c != 0)
		return;
	rec->m_a = TheGameLogic->m_frame;
	unsigned int bit = g_00C51304[index];
	m_bits[bit >> 5] |= 1u << (bit & 31);
	m_f4 = 1;
}
