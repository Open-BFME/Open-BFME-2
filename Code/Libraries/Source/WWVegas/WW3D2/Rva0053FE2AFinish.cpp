// ?rva0053FE2A@Rva0053FE2A@@QAEAAV1@PAUS12@@PAUS16@@MH@Z
// partial score=0.94 date=2026-10-04
// cl: /Ob0
// ?rva0053FE2A@Rva0053FE2A@@QAEAAV1@PAUS12@@PAUS16@@MH@Z @0x0053FE2A 58B
// Four-arg reference-returning setter: dword arg4 to +0, three dwords from arg1
// to +4/+8/+0xC, 16 bytes from arg2 to +0x10 via movsd x4, float arg3 to +0x20.
// Retail leaves `this` in eax at the return, so the function returns *this.
// Evidence: ret 0x10 four stack args; movss xmm0 early plus movsd x4;
// caller at 0x0053FF10; follows the rowed Rva0053FDE6 ctor (0x53FDE6+0x44).
//
// The three dword stores go through int* locals rather than member syntax:
// that is what pushes the /O1 save-register pair (push esi / mov esi,[esp+0xc])
// past the first store, where retail schedules it.
struct S12
{
	int a;
	int b;
	int c;
};
struct S16
{
	int a;
	int b;
	int c;
	int d;
};
class Rva0053FE2A
{
public:
	Rva0053FE2A &rva0053FE2A(S12 *a1, S16 *a2, float f, int d);
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	S16 m_10;
	float m_20;
};
Rva0053FE2A &Rva0053FE2A::rva0053FE2A(S12 *a1, S16 *a2, float f, int d)
{
	m_00 = d;
	int *dst = &m_04;
	const int *src = &a1->a;
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	m_10 = *a2;
	m_20 = f;
	return *this;
}
