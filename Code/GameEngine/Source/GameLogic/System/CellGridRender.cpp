// cl: /O1 /G7 /arch:SSE /MD

// BFME1 donor9cbfb551fe20dae985f91f2319d8997287b6a705
// BfmeCellGridRva001B1AD0.cpp semantic source; target56C3EA..56C4D3
// fixes grid0/4/8/C/10/14 and0xA8 cells; original method identity unknown.
// The donor sweeps terrain-centred cells and supplies the structural lead.
// Target bytes independently establish the 0x1C-byte grid, 0xA8 cell stride,
// height*y+x index expression and the call to recovered cell body 40495D.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct Rva003FD060TerrainLogic
{
	virtual void bfmeSlot0VC();
	virtual void bfmeSlot1VC();
	virtual void bfmeSlot2VC();
	virtual void bfmeSlot3VC();
	virtual void bfmeSlot4VC();
	virtual void bfmeSlot5VC();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);
};

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

class Rva0040495D
{
public:
	void rva0040495D(const Coord3D *position, Real cellSize,
		Int index, void *parameters);

private:
	unsigned char m_data[0xA8];
};

class Rva0056C3EA
{
public:
	void rva0056C3EA(Int index, void *parameters);

private:
	Int m_width;
	Int m_height;
	UnsignedInt m_cellCount;
	Real m_cellSize;
	Real m_offset;
	Rva0040495D *m_cells;
	UnsignedInt *m_cellValues;
};

void Rva0056C3EA::rva0056C3EA(Int index, void *parameters)
{
	Real base = *(volatile Real *)&m_cellSize * 0.5f + m_offset;

	for (UnsignedInt y = 0; y < (UnsignedInt)m_height; ++y)
	{
		Coord3D position;
		position.x = base;
		position.y = (Real)y * m_cellSize + base;
		position.z = 0.0f;

		for (UnsignedInt x = 0; x < (UnsignedInt)m_width; ++x)
		{
			UnsignedInt cellIndex = (UnsignedInt)m_height * y + x;
			if (cellIndex < m_cellCount)
			{
				position.x = (Real)x * m_cellSize + base;
				position.z = ((Rva003FD060TerrainLogic *)TheTerrainLogic)->getGroundHeight(
					position.x, position.y, 0) + 0.5f;
				m_cells[cellIndex].rva0040495D(&position, m_cellSize,
					index, parameters);
			}
		}
	}
}
