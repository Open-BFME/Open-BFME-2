// cl: /Ob0
// ?rva0025C6E2@BfmeStrVM0@@QAEXHHMMMM@Z @0x0025C6E2 74B evidence: same TU class BfmeStrVM0 as neighbours rva0025C46E rva0025D10F in BfmeConv1435.cpp; array at +0x68 element 24B bounds 3; 6 stack args ret 0x18; unblocks 0x00356724 0x00356889
// ?rva0025C72C@BfmeStrVM0@@QAEXHHMMMM@Z @0x0025C72C 74B twin with const 2 at +0x14 via same array bounds and G7 imul; unblocks 0x0023958B 0x0035C566

struct Rva0025C6E2Elem
{
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
	float m_10;
	int m_14;
};

class BfmeStrVM0
{
public:
	virtual ~BfmeStrVM0();
	void rva0025C6E2(int v0, int idx, float f0, float f1, float f2, float f3);
	void rva0025C72C(int v0, int idx, float f0, float f1, float f2, float f3);
private:
	char m_pad04[0x64];
	Rva0025C6E2Elem m_arr[3];
};

void BfmeStrVM0::rva0025C6E2(int v0, int idx, float f0, float f1, float f2, float f3)
{
	if (idx >= 3)
		return;
	Rva0025C6E2Elem &e = m_arr[idx];
	e.m_04 = f0;
	e.m_08 = f1;
	e.m_0c = f2;
	e.m_00 = v0;
	e.m_10 = f3;
	e.m_14 = 1;
}

void BfmeStrVM0::rva0025C72C(int v0, int idx, float f0, float f1, float f2, float f3)
{
	if (idx >= 3)
		return;
	Rva0025C6E2Elem &e = m_arr[idx];
	e.m_04 = f0;
	e.m_08 = f1;
	e.m_0c = f2;
	e.m_00 = v0;
	e.m_10 = f3;
	e.m_14 = 2;
}
