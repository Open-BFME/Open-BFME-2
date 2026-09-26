// cl: /O1
//
// ?rva00133DA0Set@CameraClass@@QAEXABUMatrix4@@@Z, retail 0x00133DA0, 150 bytes.
// CameraClass AdditionalTransform setter (second Matrix4 at +0x38C, BFME2
// addition per bfmecamera shim; setter at RVA 0x133DA0 writes all 16 floats).
// Gap between Get_Aspect_Ratio 0x133D90/7 and Convert_Old 0x133E40/55 in
// camera.cpp; new file beside it (minimal /O1 with 16 explicit dword stores
// gives the unrolled movs with last via eax saving 3B; struct-copy = would
// give rep movsd 22B, not retail). Identity is address-derived honest name
// (CameraClass proven by neighbours + shim + copy ctor/operator= copying
// AdditionalTransform; 64B Matrix4 copy + sole caller 0x7F7E1). No fallback
// paths.

struct Matrix4
{
	int m[16];
};

class CameraClass
{
public:
	void rva00133DA0Set(const Matrix4 &src);

private:
	char m_lead[0x38C];
	Matrix4 m_38C;
};

// ?rva00133DA0Set@CameraClass@@QAEXABUMatrix4@@@Z @0x00133DA0
void CameraClass::rva00133DA0Set(const Matrix4 &src)
{
	m_38C.m[0] = src.m[0];
	m_38C.m[1] = src.m[1];
	m_38C.m[2] = src.m[2];
	m_38C.m[3] = src.m[3];
	m_38C.m[4] = src.m[4];
	m_38C.m[5] = src.m[5];
	m_38C.m[6] = src.m[6];
	m_38C.m[7] = src.m[7];
	m_38C.m[8] = src.m[8];
	m_38C.m[9] = src.m[9];
	m_38C.m[10] = src.m[10];
	m_38C.m[11] = src.m[11];
	m_38C.m[12] = src.m[12];
	m_38C.m[13] = src.m[13];
	m_38C.m[14] = src.m[14];
	m_38C.m[15] = src.m[15];
}
