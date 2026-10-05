// ?rva004F68B8@Rva004F68B8@@QAEXHH@Z
// partial score=0.9 date=2026-10-05
// ?rva004F68B8@Rva004F68B8@@QAEXHH@Z
// partial score=0.9 date=2026-10-05
// cl: /O1
//
// ?rva004F68B8@Rva004F68B8@@QAEXHH@Z @0x004F68B8 68B.
// Indexed twin-table dispatch: when the +0x48 entry and the +0x00 table's
// +0x24 slot at the index are both set, resolve through rowed 0x00413FC1 on
// the slot with the entry's +0x1C value into the +0x54 table; otherwise
// clear the +0x54 slot. The second argument is unused.
class Rva00413FC1
{
public:
	int *rva00413FC1(int v);
};

struct Rva004F68B8Rec34
{
	char m_pad[0x24];
	Rva00413FC1 *m_24;
	char m_pad28[0x34 - 0x28];
};

struct Rva004F68B8Entry
{
	char m_pad[0x1C];
	int m_1C;
};

class Rva004F68B8
{
public:
	void rva004F68B8(int idx, int flags);
private:
	Rva004F68B8Rec34 *m_0;
	char m_pad04[0x48 - 0x04];
	Rva004F68B8Entry **m_48;
	char m_pad4C[0x54 - 0x4C];
	int **m_54;
};

void Rva004F68B8::rva004F68B8(int idx, int flags)
{
	(void)flags;
	Rva004F68B8Entry *e = m_48[idx];
	if (e) {
		Rva00413FC1 *o = m_0[idx].m_24;
		if (o) {
			int **table = m_54;
			table[idx] = o->rva00413FC1(e->m_1C);
			goto END;
		}
	}
	m_54[idx] = 0;
END:
	;
}
