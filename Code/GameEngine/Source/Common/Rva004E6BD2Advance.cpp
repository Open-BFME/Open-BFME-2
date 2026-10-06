// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004E6BD2@Rva004E6BD2@@QAEXI@Z @0x004E6BD2 36B.
// State advance when m_8 holds 4: run the rowed 0x00524021 sweep on the
// +0x30 member, flip m_8 to 1, then run the rowed 0x004E6A1D clear on the
// +0x44 member. The +0x44 address is taken before the m_8 store, which is
// what emits lea-44 ahead of the dword store in retail.
class Rva00524021
{
public:
	void rva00524021();
private:
	void *m_begin;
	void *m_end;
};

class Rva004E6A1D
{
public:
	void clear();
private:
	void *m_ptr;
};

class Rva004E6BD2
{
public:
	void rva004E6BD2(unsigned int flags);
private:
	char m_pad[8];
	int m_8;
	char m_pad0C[0x30 - 0x0C];
	Rva00524021 m_30;
	char m_pad38[0x44 - 0x38];
	Rva004E6A1D m_44;
};

void Rva004E6BD2::rva004E6BD2(unsigned int flags)
{
	(void)flags;
	if (m_8 == 4) {
		m_30.rva00524021();
		Rva004E6A1D *target = &m_44;
		m_8 = 1;
		target->clear();
	}
}
