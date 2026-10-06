// ?rva005C7636@Rva005C76C0@@QAEXXZ
// partial score=0.93 date=2026-10-01
// cl: /MD
// ?rva005C7636@Rva005C76C0@@QAEXXZ, retail 0x005C7636 138B.
// Accumulator on Rva005C76C0::m_38[4]: m_38[i] += m_38[i+1] for i 0..2
// plus ++m_00. Evidence: 9 movss/addss triples 0x38+=0x44 etc plus inc
// [ecx]; layout from Rva005C76C0Ctor m_38[4] at +0x38; caller 0x0055A853.
class Coord3D
{
public:
	float x;
	float y;
	float z;
};

class Rva0055A246
{
public:
	Rva0055A246();
	Coord3D m_arr[4];
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva005C76C0
{
public:
	Rva005C76C0();
	Rva005C76C0(int count, const Rva0055A246 *source);
	void rva005C7636();
	void rva005C74B1();
	int m_00;
	int m_04;
	Rva0055A246 m_08;
	Coord3D m_38[4];
};

void Rva005C76C0::rva005C7636()
{
	float t0 = m_38[1].x;
	t0 += m_38[0].x;
	m_38[0].x = t0;
	float t1 = m_38[1].y;
	t1 += m_38[0].y;
	m_38[0].y = t1;
	float t2 = m_38[1].z;
	t2 += m_38[0].z;
	m_38[0].z = t2;
	float t3 = m_38[2].x;
	t3 += m_38[1].x;
	m_38[1].x = t3;
	float t4 = m_38[2].y;
	t4 += m_38[1].y;
	m_38[1].y = t4;
	float t5 = m_38[2].z;
	t5 += m_38[1].z;
	m_38[1].z = t5;
	float t6 = m_38[3].x;
	t6 += m_38[2].x;
	m_38[2].x = t6;
	float t7 = m_38[3].y;
	t7 += m_38[2].y;
	m_38[2].y = t7;
	float t8 = m_38[3].z;
	t8 += m_38[2].z;
	m_38[2].z = t8;
	_ReadWriteBarrier();
	++m_00;
}
