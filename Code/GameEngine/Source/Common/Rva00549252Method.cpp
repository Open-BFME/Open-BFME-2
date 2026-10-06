// cl: /DNDEBUG /MD
// ?rva00549252@Rva00549252@@QAEXXZ, RVA 0x00549252, 243B
// Zero slot counts at +8 stride 0x1c then nested loops over +0x120 array
// with 0x258/0x1f0/0x78 gate plus leaf 0x568 accumulate and bfmePush.
// Evidence: prev same flags, callee rowed bfmePush 0x00548FC0, caller
// 0x00549434, offsets 0x120/0x124/0x1B4/0x1B8 and count>=10 plus k<13 gate.
class Gen_0015A260 {
public:
	void bfmePush(int value) throw();
	int m_count;
	int m_items[6];
};

struct Leaf00549252 {
	char m_pad[0x568];
	int m_0568;
};

struct Gate00549252 {
	char m_pad[0x78];
	int m_0078;
};

struct Inner200549252 {
	int m_00;
	Gate00549252 *m_04;
};

struct Inner100549252 {
	char m_pad[0x1F0];
	Inner200549252 *m_01F0;
};

struct Mid00549252 {
	int m_00;
	Leaf00549252 *m_04;
	char m_pad08[0x250];
	Inner100549252 *m_0258;
};

class Rva00549252 {
public:
	int m_00;
	int m_04;
	Gen_0015A260 m_slots08[10];
	int m_0120;
	Mid00549252 *m_array124[1];
	char m_pad128[0x1B4 - 0x128];
	int m_01B4;
	unsigned char m_01B8;
	void rva00549252();
};

void Rva00549252::rva00549252()
{
	int acc = 0;
	int i = 0;
	m_01B4 = 0;
	if (m_00 > 0) {
		Gen_0015A260 *slot = m_slots08;
		do {
			slot->m_count = 0;
			++i;
			slot++;
		} while (i < m_00);
	}
	m_00 = 0;
	int k = 0;
	if (m_00 >= 10)
		return;
	while (k < 13) {
		if (m_00 >= 10)
			break;
		int j = 0;
		if (m_0120 > 0) {
			Mid00549252 **pp = m_array124;
			do {
				Mid00549252 *elem = *pp;
				Inner100549252 *s1 = elem->m_0258;
				if (s1 != 0) {
					Inner200549252 *s2 = s1->m_01F0;
					if (s2 != 0) {
						Gate00549252 *g = s2->m_04;
						if (g->m_0078 == k) {
							acc += elem->m_04->m_0568;
							if (acc > m_04) {
								++m_00;
								if (m_00 >= 10)
									break;
								acc = elem->m_04->m_0568;
							}
							m_slots08[m_00].bfmePush((int)elem);
							if (m_01B4 < acc)
								m_01B4 = acc;
						}
					}
				}
				++j;
				++pp;
			} while (j < m_0120);
		}
		if (k == 3 || k == 6 || k == 0 || k == 9 || k == 12) {
			if (acc > 0)
				++m_00;
			acc = 0;
		}
		++k;
	}
	m_01B8 = 1;
}
