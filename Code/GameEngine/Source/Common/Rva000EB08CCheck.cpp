// cl: /MD
//
// ?rva000EB08C@Rva000EB08C@@QAEXH_N@Z @0x000EB08C 90B. Index plus flag store.
// Evidence: __thiscall ret 8 with int plus bool, TheWritableGlobalData row
// plus 0x40 gate, count at +0x44540 with 0xE8 stride array at +0x600 holding
// id at +0 plus value at +0xA4, second array at +0x44578 stride 0x5C holding
// pointer plus target int at +0x5C, dirty flag at +0x45C64. Caller 0x000EB2AC.
// Honest address name.
// ?rva000EB21D@Rva000EB08C@@QAEXXZ @0x000EB21D 98B. Loop over E8 array with
// checker at +0x44548, flag byte at elem +4, arg at elem +8, step at +0x45C60,
// set +0x44544 on change, clear +0x44546. Caller 0x000EDB60. Honest name.
// ??0Rva000EB08C@@QAE@XZ @0x000EB27F 45B. Default ctor with Region2D[3] at
// +0x10 and +0x90 via vector ctor iterator 0x1423 with folded empty ctor
// 0x47A6A9. Caller 0x000ED667. Honest name.
class GlobalData
{
public:
	char m_pad00[0x40];
	unsigned char m_40;
};

extern GlobalData *TheWritableGlobalData;

class Rva000E488F
{
public:
	bool rva000E488F(void *arg);
	void *m_begin;
	void *m_end;
};

class Region2D
{
public:
	Region2D();
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

class Rva000EB08C
{
public:
	Rva000EB08C();
	void rva000EB08C(int index, bool flag);
	bool rva000EB2AC(int id, bool flag);
	void rva000EB21D();
private:
	struct Elem1
	{
		int id1;
		unsigned char flag04;
		char m_pad05[3];
		int m_08;
		char m_pad0C[0x18 - 0x0C];
		int id2;
		char m_pad1C[0xA4 - 0x18 - 4];
		int value;
		char m_padA8[0xE8 - 0xA4 - 4];
	};
	struct Elem2Target
	{
		char m_pad00[0x5C];
		int value;
	};
	struct Elem2
	{
		Elem2Target *ptr;
		char m_pad04[0x5C - 4];
	};
	char m_pad00[0x10];
	Region2D m_10[3];
	char m_pad40[0x90 - 0x40];
	Region2D m_90[3];
	char m_padC0[0x600 - 0xC0];
	Elem1 m_elems[1];
	char m_pad01[0x44540 - 0x600 - 0xE8];
	int m_count;
	unsigned char m_44544;
	char m_pad44545;
	unsigned char m_44546;
	char m_pad44547;
	Rva000E488F m_checker;
	char m_pad44550[0x44578 - 0x44548 - 8];
	Elem2 m_array2[1];
	char m_pad03[0x45C60 - 0x44578 - 0x5C];
	int m_step;
	unsigned char m_dirty;
};

void Rva000EB08C::rva000EB08C(int index, bool flag)
{
	if (TheWritableGlobalData->m_40 == 0)
		return;
	if (index >= m_count)
		return;
	int id = m_elems[index].id1;
	if (id < 0)
		return;
	if (flag) {
		int val = m_array2[id].ptr->value;
		m_elems[index].value = val;
	} else {
		m_elems[index].value = 0xFF;
	}
	m_dirty = 1;
}

bool Rva000EB08C::rva000EB2AC(int id, bool flag)
{
	if (id == 0)
		return false;
	int n = m_count;
	for (int i = 0; i < n; ++i) {
		if (m_elems[i].id2 == id) {
			rva000EB08C(i, flag);
			return true;
		}
	}
	return false;
}

void Rva000EB08C::rva000EB21D()
{
	for (int i = 0; i < m_count; i += m_step) {
		bool v = !m_checker.rva000E488F(&m_elems[i].m_08);
		unsigned char *pf = &m_elems[i].flag04;
		if (v != *pf) {
			*pf = v;
			m_44544 = 1;
		}
	}
	m_44546 = 0;
}

Rva000EB08C::Rva000EB08C()
{
}
