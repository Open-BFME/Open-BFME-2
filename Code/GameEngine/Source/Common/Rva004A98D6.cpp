// cl: /O1 /MD
// ?rva004A98D6@Rva004A98D6@@QAEHXZ @0x004A98D6 62B: thiscall predicate over two +0x4C0/+0x4C8 machines.
// Evidence: leaf lane; caller 0x004A99E4 (mov ecx esi; test al al) proves thiscall bool no-arg; true only when both chained vals == 1.
struct Mid2
{
	char m_pad[4];
	int m_val;
};

struct Mid1
{
	char m_pad[4];
	Mid2 *m_next;
};

class Rva004A98D6
{
public:
	char m_pad[0x4C0];
	Mid1 *m_p1;
	char m_gap[4];
	Mid1 *m_p2;
	int rva004A98D6();
};

int Rva004A98D6::rva004A98D6()
{
	int v1 = m_p1->m_next ? m_p1->m_next->m_val : 999999;
	if (v1 == 1) {
		Mid1 *p2 = m_p2;
		int v2 = p2->m_next ? p2->m_next->m_val : 999999;
		if (v2 == 1)
			return 1;
	}
	return 0;
}
