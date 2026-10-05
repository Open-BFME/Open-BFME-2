// ?setFrom@Rva0040D82FHost@@QAIXHPAURva0040D82FArg@@@Z
// partial score=0.95 date=2026-10-05
// cl: /O1 /MD
//
// Change-detecting setter at retail 0x0040D82F (57B). Reads a candidate int
// out of the argument's +0x1C through a 3-arg cdecl helper, compares it with
// the host's +0x18 field, and when different stores it through the +0x14
// subobject's __stdcall set. Names are address-derived.
class Rva0040D82FSub
{
public:
	int set(int v); // pinned retail 0x0025BF5D (RVA form; VA 0x0065BF5D) thiscall: this in ECX, callee cleans

	int m_first;
};

int rva0060E873(int a, int b, int *out); // pinned retail 0x0060E873

struct Rva0040D82FArg
{
	char m_00[0x1C];
	int m_1C;
};

class Rva0040D82FHost
{
public:
	void __fastcall setFrom(int unused, Rva0040D82FArg *arg); // retail 0x0040D82F

private:
	char m_00[0x14];
	Rva0040D82FSub m_14; // +0x14
	int m_18; // +0x18 current value
};

void __fastcall Rva0040D82FHost::setFrom(int unused, Rva0040D82FArg *arg)
{
	if (arg != 0) {
		int cur = m_18;
		int tmp = arg->m_1C;
		int r = rva0060E873(m_14.m_first, cur, &tmp);
		if (r != cur) {
			m_14.set(r);
		}
	}
}
