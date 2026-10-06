// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??1Rva004F69C3@@QAE@XZ, retail 0x004F69C3, 19 bytes.
// Holder dtor releasing TargetRef at +0xAC of pointee at +4 via rowed
// fastcall 0x0007DEEF. Same shape as Rva002B2F97 holder with int pad at +0.
// Evidence: tail-jmp to Release; callers at 0x0040D05E 0x0040DC49 0x0040DCFA
// 0x0040DF22 0x0040EDE8 plus tail-jmp callers incl Unwind funclets.

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva004F69C3Target
{
	char m_pad[0xAC];
	TargetRef00217D4C m_ac;
};

struct Rva004F69C3
{
	int m_00;
	Rva004F69C3Target *m_04;
	~Rva004F69C3();
};

Rva004F69C3::~Rva004F69C3()
{
	if (m_04)
		ReleaseTreeHintRef00217D4C(&m_04->m_ac);
}

// ??1Rva0040D8B0@@QAE@XZ @0x0040D8B0 8B holder dtor forwarder to
// rowed ??1Rva004F69C3@@QAE@XZ (0x004F69C3). No callers. Honest address name.
class Rva0040D8B0
{
public:
	~Rva0040D8B0();
private:
	char m_pad[4];
	Rva004F69C3 *m_member;
};
Rva0040D8B0::~Rva0040D8B0()
{
	m_member->~Rva004F69C3();
}
