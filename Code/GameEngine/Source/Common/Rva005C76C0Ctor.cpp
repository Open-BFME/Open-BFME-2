// cl: /O1 /G7 /arch:SSE /MD /Ireference/shims/sweep
// platformsdk
// dxsdk
// ??0Rva005C76C0@@QAE@XZ @ 0x005C76C0, 85 bytes.
// Ctor: zero ints at +0x00 +0x04 init Rva0055A246 at +0x08 zero 12 floats at +0x38.
// Evidence: retail and [esi] 0 and [esi+4] 0 lea ecx [esi+8] call 0x55A246 xorps movss x12; chain from 0x55A246.
typedef float Real;
// Use the defining unit's DX8 matrix type so the shared basis has one COFF name.
#include "d3dx8math.h"
extern const D3DXMATRIX g_Rva009D2398Basis;
extern "C" D3DXVECTOR4* __stdcall rva0062AF4AD3DXVec4Transform(D3DXVECTOR4*,const D3DXVECTOR4*,const D3DXMATRIX*);

#include "../../../Libraries/Include/Lib/Coord3D.h"

// TU-local donor zero operation preserves inline call scheduling.
static __forceinline void rva005C7448Zero(Coord3D &pos) { pos.x = 0.0f; pos.y = 0.0f; pos.z = 0.0f; }

class Rva0055A246
{
public:
	Rva0055A246();
	Coord3D m_arr[4];
};

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

Rva005C76C0::Rva005C76C0() : m_00(0), m_04(0)
{
	m_38[0].x = 0.0f;
	m_38[0].y = 0.0f;
	m_38[0].z = 0.0f;
	m_38[3].x = 0.0f;
	m_38[3].y = 0.0f;
	m_38[3].z = 0.0f;
	m_38[2].x = 0.0f;
	m_38[2].y = 0.0f;
	m_38[2].z = 0.0f;
	m_38[1].x = 0.0f;
	m_38[1].y = 0.0f;
	m_38[1].z = 0.0f;
}

// Clean BFME1 6d9434269164392c5ba62aaa7c15a86b5b020d76 BezFwdIterator.cpp,
// /O1 /G7 /arch:SSE /MD, original TU header directory first.
// Target Ghidra105B/RET8 at5C7448 ends exactly at5C74B1. Default holder
// atthis+8 calls55A246; twelve state floats at38/5C/50/44 are zeroed,
// count goes to+4, then twelveDWORDs are copied from the second argument.
// Donor supplies forward-difference purpose; original target names, full
// object identity and reachability remain unknown. No reference ABI guessed.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the donor.
Rva005C76C0::Rva005C76C0(int count, const Rva0055A246 *source) : m_00(0)
{
	rva005C7448Zero(m_38[0]);
	rva005C7448Zero(m_38[3]);
	rva005C7448Zero(m_38[2]);
	rva005C7448Zero(m_38[1]);
	m_04 = count;
	m_08 = *source;
}

// Same clean donor supplies forward differences. Target Ghidra389B at5C74B1
// ends exactly at the existing138B advance5C7636. Three typed12B-argument
// transform calls reach62AF4A, the shared64B basis atVA DD2398, and updates
// use the same four12B state triples at38/44/50/5C. Original names unknown.
void Rva005C76C0::rva005C74B1(void)
{
	m_00 = 0;

	if (m_04 <= 1)
		return;

	float parameterStep	 = 1.0f / (m_04 - 1);
	float parameterStepSquared = parameterStep * parameterStep;
	float parameterStepCubed = parameterStep * parameterStepSquared;

	D3DXVECTOR4 xControlPoints(m_08.m_arr[0].x, m_08.m_arr[1].x, m_08.m_arr[2].x, m_08.m_arr[3].x);
	D3DXVECTOR4 yControlPoints(m_08.m_arr[0].y, m_08.m_arr[1].y, m_08.m_arr[2].y, m_08.m_arr[3].y);
	D3DXVECTOR4 zControlPoints(m_08.m_arr[0].z, m_08.m_arr[1].z, m_08.m_arr[2].z, m_08.m_arr[3].z);

	D3DXVECTOR4 polynomialCoefficients[3];
	rva0062AF4AD3DXVec4Transform(&polynomialCoefficients[0], &xControlPoints, &g_Rva009D2398Basis);
	rva0062AF4AD3DXVec4Transform(&polynomialCoefficients[1], &yControlPoints, &g_Rva009D2398Basis);
	rva0062AF4AD3DXVec4Transform(&polynomialCoefficients[2], &zControlPoints, &g_Rva009D2398Basis);

	m_38[0] = m_08.m_arr[0];

	int axisIndex = 3;
	while (axisIndex--) {
		float cubicCoefficient = polynomialCoefficients[axisIndex].x;
		float quadraticCoefficient = polynomialCoefficients[axisIndex].y;
		float linearCoefficient = polynomialCoefficients[axisIndex].z;

		float *firstDifference, *secondDifference, *thirdDifference;

		if (axisIndex == 2) {
			firstDifference = &m_38[1].z;
			secondDifference = &m_38[2].z;
			thirdDifference = &m_38[3].z;
		} else if (axisIndex == 1) {
			firstDifference = &m_38[1].y;
			secondDifference = &m_38[2].y;
			thirdDifference = &m_38[3].y;
		} else if (axisIndex == 0) {
			firstDifference = &m_38[1].x;
			secondDifference = &m_38[2].x;
			thirdDifference = &m_38[3].x;
		}

		(*firstDifference) = cubicCoefficient * parameterStepCubed + quadraticCoefficient * parameterStepSquared + linearCoefficient * parameterStep;
		(*secondDifference) = 6 * cubicCoefficient * parameterStepCubed + 2 * quadraticCoefficient * parameterStepSquared;
		(*thirdDifference) = 6 * cubicCoefficient * parameterStepCubed;
	}
}
