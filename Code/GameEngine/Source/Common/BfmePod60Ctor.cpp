// cl: /MD
// ??0BfmePod60@@QAE@XZ @0x00587500 72B: default ctor of the 60-byte element.
// Stores: floats +0/+4/+8 zeroed via xorps+movss, byte +0xC set to 1,
// dword +0x10 zeroed, 4x8B block +0x14 constructed via ??_H then zeroed
// with an and-[m],0 pointer-walk loop, byte +0x39 zeroed. Dword +0x34
// and byte +0x38 left uninitialized, matching the Rva00587375 copy shape.
// Evidence: stack temp at caller 0x00588A81 passed by value to rowed
// vector<BfmePod60>::resize; ??_H immediate is rowed 0x0047A6A9 (3B empty
// ctor shared by Region3D/IRegion3D); element true identity unproven so
// the 8-byte element reuses the rowed Region3D name for gate resolution.
// Neighbour next 0x00587599.
class Region3D
{
public:
	Region3D();
	int m_v0;
	int m_v1;
};

struct BfmePod60
{
public:
	BfmePod60();
	float m_f00;
	float m_f04;
	float m_f08;
	unsigned char m_b0C;
	unsigned char m_pad0D[3];
	int m_i10;
	Region3D m_arr14[4];
	int m_i34;
	unsigned char m_b38;
	unsigned char m_b39;
	unsigned char m_pad3A[2];
};

BfmePod60::BfmePod60() : m_b0C(1), m_i10(0)
{
	Region3D *p = m_arr14;
	int n = 4;
	m_b39 = 0;
	m_f08 = 0.0f;
	m_f04 = 0.0f;
	m_f00 = 0.0f;
	do
	{
		p->m_v1 = 0;
		p->m_v0 = 0;
		++p;
	} while (--n != 0);
}
