// cl: /O1 /EHsc /MD
// ?rva0044BF77@Rva0044BF77@@QAEPAU1@URva0051732A@@@Z @0x0044BF77 59B
// EH setter-twin of rowed Rva00517547Set (0x00517547 59B): forward the by-value
// holder at [ebp+8] as const ref to the rowed twin setter Rva0044BEE6::
// rva0044BEE6 (0x0044BEE6, same shape as rowed 0x005173CB), then Release the
// input pointer via rowed fastcall 0x0007DEEF, return this. Model and flags
// mirror Code/GameEngine/Source/Common/Rva00517547Set.cpp; holder layout
// mirrors Code/GameEngine/Source/Common/Rva005173CBSet.cpp. Caller 0x0044C0A8
// (MessageBoxOk pin); landing this unblocks 0x0044C0A8.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva0051732A
{
	TargetRef00217D4C *m_ptr;
	~Rva0051732A() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

struct Rva0044BDA2
{
	void *m_vtbl;
	int m_04;
	TargetRef00217D4C *m_08;
	Rva0044BDA2(const Rva0051732A &other);
};

struct Rva0044BEE6
{
	Rva0044BDA2 *m_ptr;
	Rva0044BEE6 *rva0044BEE6(const Rva0051732A &arg);
};

struct Rva0044BF77 : Rva0044BEE6
{
	Rva0044BF77 *rva0044BF77(Rva0051732A arg);
};

Rva0044BF77 *Rva0044BF77::rva0044BF77(Rva0051732A arg)
{
	rva0044BEE6(arg);
	return this;
}
