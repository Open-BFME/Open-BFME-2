// ?rva002E1155@Rva002E112A@@QAE_NPAVRva00319CED@@@Z
// partial score=0.93 date=2026-10-06
// cl: /O1
// ?rva002E112A@Rva002E112A@@QAE_NPAVRva00319CED@@@Z @ 0x002E112A 43B.
// Unlock-lane __thiscall bool taking Rva00319CED*: sums this->rva002E0C68
// 0x002E0C68 plus arg->rva004E1755 0x004E1755 and compares against
// this->get 0x002E0CD4 via setle. Returns (a+b)<=c.
// Evidence: callees all rowed per packet; callers 0x002B65DE 0x004FAB57
// UNCLAIMED so owner honest Rva002E112A; this calls rowed get on itself.
class Rva002E0C68
{
public:
	int rva002E0C68();
};

class Rva00319CED
{
public:
	int rva004E1755();
};

class Rva002E0CD4
{
public:
	int get() const;
};

class Rva002E112A
{
public:
	bool rva002E112A(Rva00319CED *arg);
	bool rva002E1155(Rva00319CED *arg);
private:
	char m_pad[0x298];
	int m_298;
};

bool Rva002E112A::rva002E112A(Rva00319CED *arg)
{
	int a = ((Rva002E0C68 *)this)->rva002E0C68();
	a += arg->rva004E1755();
	int c = ((Rva002E0CD4 *)this)->get();
	return a <= c;
}
// ?rva002E1155@Rva002E112A@@QAE_NPAVRva00319CED@@@Z @ 0x002E1155 57B.
// Same shape as rva002E112A plus +0x298 member: (a+mem+b)<=c via setle.
// Evidence: same three rowed callees; caller 0x004FA8B5 UNCLAIMED.
// ?rva002E1155@Rva002E112A@@QAE_NPAVRva00319CED@@@Z present-unmatched
bool Rva002E112A::rva002E1155(Rva00319CED *arg)
{
	int a;
	int mem = m_298;
	int b;
	a = ((Rva002E0C68 *)this)->rva002E0C68();
	b = arg->rva004E1755();
	a += mem;
	b += a;
	int c = ((Rva002E0CD4 *)this)->get();
	return b <= c;
}
