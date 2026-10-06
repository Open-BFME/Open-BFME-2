// cl: /MD
//
// ?rva000E76B8@Rva000E76B8@@QAEXXZ, retail 0x000E76B8, 99 bytes.
// Loop over byte flags at +0x199C (stride 0xA0) calling rowed predicate
// ?rva000E488F@Rva000E488F@@QAE_NPAX@Z on the payload at +4, storing the
// inverted result and setting dirty at +0x4FB5C when it changes; count at
// +0x4FB58, step at +0x51278, cleared flag at +0x4FB5E.
// Evidence: retail lea/imultri plus neg/sbb/inc invert plus caller at 0x000E8AA0.

class Rva000E488F
{
public:
	bool rva000E488F(void *arg);
	void *m_begin;
	void *m_end;
};

struct Rva000E76B8Elem
{
	unsigned char flag;
	unsigned char pad[3];
	unsigned char data[0x9C];
};

class Rva000E76B8
{
public:
	void rva000E76B8();
	unsigned char m_pad0[0x199C];
	Rva000E76B8Elem m_elems[1999];
	unsigned char m_gap[0x5C];
	int m_count;
	unsigned char m_dirty;
	unsigned char m_pad1;
	unsigned char m_cleared;
	unsigned char m_pad2;
	Rva000E488F m_checker;
	unsigned char m_pad3[0x1710];
	int m_step;
};

void Rva000E76B8::rva000E76B8()
{
	for (int i = 0; i < m_count; i += m_step) {
		unsigned char v = m_checker.rva000E488F(m_elems[i].data) ? 0 : 1;
		if (v != m_elems[i].flag) {
			m_elems[i].flag = v;
			m_dirty = 1;
		}
	}
	m_cleared = 0;
}
