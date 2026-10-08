// ?rva00739F50@Rva00739F50@@QAEXXZ
// partial score=0.9 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc
// ?rva00739F50@Rva00739F50@@QAEXXZ 0x00739F50 133B. Two-phase slot pump on the
// object at +0x00: a one-shot call on the first slot (+0xE0, then set to -1), then
// three slots at +0xF4 with a nonzero count at +0x18 each call the second helper
// (0x0073CE90) and are retired by setting their first word to -1.
class Gen_008F7CD0
{
public:
	void rva0073E500(int a, int b, int *c, int d, int e);
	void rva0073CE90(int a, int b, int c, int d, int e, int f);
};

class Rva00739F50
{
public:
	void rva00739F50();
private:
	Gen_008F7CD0 *m_obj; // +0x00
	unsigned char m_pad04[0xD8 - 0x04];
	int m_d8; // +0xD8
	int m_dc; // +0xDC
	int m_e0; // +0xE0
	unsigned char m_pad0E4[0xEC - 0xE4];
	int m_ec; // +0xEC
	int m_f0; // +0xF0
	int m_f4[3]; // +0xF4
};

void Rva00739F50::rva00739F50()
{
	if (m_e0 >= 0)
	{
		m_obj->rva0073E500(m_d8, m_dc, &m_e0, m_f0, m_ec);
		m_e0 = -1;
	}
	for (int i = 0; i < 3; ++i)
	{
		int *slot = &m_f4[i];
		if (slot[0] >= 0 && (unsigned int)slot[6] != 0)
		{
			m_obj->rva0073CE90(m_d8, m_dc, slot[0], i, -slot[6], slot[3]);
			slot[0] = -1;
		}
	}
}
