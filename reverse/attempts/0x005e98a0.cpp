// ?rva005E98A0@Rva005E98A0@@QAEXXZ
// partial score=0.85 date=2026-10-05
// cl: /O1 /MD /EHsc
// ?rva005E98A0@Rva005E98A0@@QAEXXZ, RVA 0x005E98A0, 65 bytes.
// Calls rowed clear 0x005E9705 on member +0x18 twice with rowed unload 0x0057C2CC via pointer +4 in between.
// Evidence: callees rowed in Rva005E971FAssign.cpp and Rva0057C236UnloadContent.cpp; neighbours 0x005E982C 0x005E9FC1; callers 0x005E98E1 0x005E9E27.
struct Rva005E971F
{
	void rva005E9705();
};
struct Rva0057C2CC
{
	void rva0057C2CC();
};
class Rva005E98A0
{
public:
	void rva005E98A0();
private:
	char m_pad0[4]; // +0
	Rva0057C2CC *m_4; // +4
	char m_pad8[16]; // +8..+0x17
	Rva005E971F m_18; // +0x18
};
// ?rva005E98A0@Rva005E98A0@@QAEXXZ present-unmatched
void Rva005E98A0::rva005E98A0()
{
	try {
		m_18.rva005E9705();
		m_4->rva0057C2CC();
		m_18.rva005E9705();
	} catch (...) {}
}
