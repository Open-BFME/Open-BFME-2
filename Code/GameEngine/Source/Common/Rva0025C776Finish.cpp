// cl: /Ob0
// ?rva0025C776@BfmeStrVM0@@QAEXHMMMMHH@Z @0x0025C776 131B
// Third BfmeStrVM0 block setter, sibling of rva0025C6E2/rva0025C72C in
// Rva0025C6E2.cpp: same object model, the +0x110/+0x124/+0x138 scalar block.
// Seven stack args (ret 0x1c); the reciprocal stores
// 1.0f / (float)a20 at +0x11c and the same literal at +0x120, both read from
// the compiler literal pool at 0x00BBB8D8 (modelled as a private extern float).
// The stores are written through volatile lvalues so MSVC 2003's /O1 list
// scheduler keeps the retail store order (m_124, m_130, m_134, m_138, m_110)
// instead of sinking the +0x138 immediate past the divss into its latency slot;
// the volatile qualifier emits the identical mov/movss encodings and the
// function has no externally visible behaviour change.

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
	void rva0025C776(int a8, float fc, float f10, float f14, float f18, int a1c, int a20);
private:
	char m_pad04[0x64];
	Rva0025C6E2Elem m_arr[3];
	char m_padB0[0x60];
	int m_110;
	char m_pad114[4];
	int m_118;
	float m_11c;
	float m_120;
	int m_124;
	float m_128;
	float m_12c;
	float m_130;
	float m_134;
	int m_138;
};

extern float g_Va00BBB8D8;

// ?rva0025C776@BfmeStrVM0@@QAEXHMMMMHH@Z @0x0025C776
void BfmeStrVM0::rva0025C776(int a8, float fc, float f10, float f14, float f18, int a1c, int a20)
{
	m_128 = fc;
	m_12c = f10;
	*(volatile int *)&m_124 = a8;
	int t_a1c = a1c;
	*(volatile float *)&m_130 = f14;
	*(volatile float *)&m_134 = f18;
	float one = g_Va00BBB8D8;
	*(volatile int *)&m_138 = 1;
	*(volatile int *)&m_110 = t_a1c;
	float fdiv = one / (float)a20;
	m_118 = a20;
	m_11c = fdiv;
	m_120 = one;
}
