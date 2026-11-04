// cl: /GX /MD

// PartitionManager world-to-cell X converter, retail 0x008F7480, 44 bytes.
// Twin of the Y converter at 0x008F74B0: both floor a world coordinate
// relative to an origin and scaled by the cell-size reciprocal, then
// truncate with a bare fistp. Same floor-import plus __asm truncation
// idiom as the matched TaintManagerImpl helpers in Bfme5SeventySix.cpp; the
// X half reads the origin at +0x04, the Y half the origin at +0x08, and
// both share the scale at +0x20 with the converted bounds-checked cell
// lookup ?bfmeAt@Gen_008F7CD0@@QBEPAVBfmeCellFD@@HH@Z at 0x008F7CD0.

typedef float Real;

#include <math.h>

__forceinline Real bfmeFloatFloorFD(Real value)
{
	return (Real)floor((double)value);
}

__forceinline long bfmeFloatToLongFD(Real value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

// The partition cell grid: origins +4/+8, cell-size reciprocal +0x20 and
// row-major 0xA8-byte cells (bfmeAt); one view for the whole TU.
class BfmeCellFD;
struct FloatRect0073CE30;

class Gen_008F7CD0
{
public:
	BfmeCellFD *bfmeAt(int x, int y) const;
	void rva0073A2A0(BfmeCellFD **first, BfmeCellFD **last, int firstColumn, int lastColumn, int scanRow);
	int bfmeCellX(float value) const;
	int bfmeCellY(float value) const;
	int bfmeCellExtent8F74E0(float value) const;
	void rva0073CC60(FloatRect0073CE30 *rect, int extra, unsigned int mask);
	void rva0073CE30(FloatRect0073CE30 *rect, int extra, unsigned int mask);

	char m_pad00[4];				// +0x00
	float m_originX;				// +0x04
	float m_originY;				// +0x08
	char m_pad0C[20];				// +0x0C
	float m_scale;					// +0x20
	int m_bfmeWidth;				// +0x24
	int m_bfmeHeight;				// +0x28
	BfmeCellFD *m_bfmeCells;			// +0x2C
};

// ?bfmeCellX@Gen_008F7CD0@@QBEHM@Z
int Gen_008F7CD0::bfmeCellX(Real value) const
{
	return bfmeFloatToLongFD(bfmeFloatFloorFD(
		(value - m_originX) * m_scale));
}
