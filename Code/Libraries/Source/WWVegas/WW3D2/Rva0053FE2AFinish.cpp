// ??0Rva0053FDE6@@QAE@PAUS12@@PAUS16@@MH@Z
// cl: /Ob0
// ??0Rva0053FDE6@@QAE@PAUS12@@PAUS16@@MH@Z @0x0053FE2A 58B
// Four-arg constructor of the camera frame Rva0053FDE6: dword arg4 to +0, three
// dwords from arg1 to +4/+8/+0xC, 16 bytes from arg2 to +0x10 via movsd x4, float
// arg3 to +0x20. Retail leaves `this` in eax at the return (constructor return).
// The by-value evaluator 0x0053FE64 builds its result slot through it directly.
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
class Rva0053FDE6
{
public:
	Rva0053FDE6(S12 *source, S16 *a2, float f, int d);
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	S16 m_10;
	float m_20;
};
Rva0053FDE6::Rva0053FDE6(S12 *source, S16 *a2, float f, int d)
{
	m_00 = d;
	int *dst = &m_04;
	const int *src = &source->a;
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	m_10 = *a2;
	m_20 = f;
}
