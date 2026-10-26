// cl: /MD
// ??0BfmePod60@@QAE@XZ @0x00587500 72B: default ctor of the 60-byte element.
// Stores: floats +0/+4/+8 zeroed via xorps+movss, byte +0xC set to 1,
// dword +0x10 zeroed, 4x8B block +0x14 constructed via ??_H then zeroed
// with an and-[m],0 pointer-walk loop, byte +0x39 zeroed. Dword +0x34
// and byte +0x38 left uninitialized, matching the Rva00587375 copy shape.
// Evidence: stack temp at caller 0x00588A81 passed by value to rowed
// vector<BfmePod60>::resize; ??_H immediate is the shared 3B empty ctor
// 0x0047A6A9 (ICF-folded Coord/Region/ICoord2D empty ctors).
// The 8-byte element is not Region3D (24 B) and its identity is unproven:
// canonical ICoord2D supplies the storage (two dwords, zeroed by integer
// and-[m],0 stores); the neutral adapter supplies the witnessed empty
// ordinary ctor, rowed as a gen-alias of the shared body. Canonical
// Region3D comes from Lib/ as Zero Hour's BaseType.h supplies it to game
// units; no private Region3D view remains.
// Neighbour next 0x00587599.
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/Region3D.h"

struct Rva00587500Block : ICoord2D
{
	Rva00587500Block();
};

Rva00587500Block::Rva00587500Block()
{
}

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
	Rva00587500Block m_arr14[4];
	int m_i34;
	unsigned char m_b38;
	unsigned char m_b39;
	unsigned char m_pad3A[2];
};

BfmePod60::BfmePod60() : m_b0C(1), m_i10(0)
{
	Rva00587500Block *block = m_arr14;
	int n = 4;
	m_b39 = 0;
	m_f08 = 0.0f;
	m_f04 = 0.0f;
	m_f00 = 0.0f;
	do
	{
		block->y = 0;
		block->x = 0;
		++block;
	} while (--n != 0);
}
