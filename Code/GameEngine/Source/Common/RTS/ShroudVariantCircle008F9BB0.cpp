// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Native 0073A860..0073A8FB (155B) circle walker and
// 0073A9B0..0073AABA (266B) caller from the existing BfmeThingCDE family.
// Source lead: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameLogic/Object/PartitionData_doSmallFill.cpp.
// The donor calls this algorithm doSmallFill; the target's original name
// remains unresolved. Target updateCellsTouched at 0073AD90 calls this body,
// whose +0 grid and +1C/+20 coverage array/count agree with rowed CDE siblings.
// Retail proves origin +4/+8, scale +20, dimensions +24/+28, cells +2C,
// 0xA8-byte cells and 0x10-byte coverage records. The donor cells are 0x68.
// The caller reserves exactly 12 argument bytes for grid/current/end and
// the rowed span updater at 0073A650 consumes only those three words.
// This corrects the old four-word BfmeArgXO declaration without renaming
// either rowed callee or claiming the donor's class identity as target fact.

class Gen_008F7CD0;
class BfmeCoiSmallFill;

struct BfmeArgXO
{
    Gen_008F7CD0 *m_grid;
    BfmeCoiSmallFill *m_first;
    BfmeCoiSmallFill *m_next;
};

class BfmeShroudVRC
{
public:
	char bfmeUpdateVRC(int x, int y, int radius);

	Gen_008F7CD0 *m_grid;
	BfmeCoiSmallFill *m_first;
	BfmeCoiSmallFill *m_next;
};

bool __cdecl bfmeCallXO(int cellX, int cellY, int cellRadius, BfmeArgXO arg)
{
	int touched = 0;
	int currentRadius = cellRadius;
	int error = 2;
	error -= currentRadius * 2;
	int left = cellX;
	int right = cellX;

	for (;;)
	{
		if (error + currentRadius > 0)
		{
			if (currentRadius == 0 && cellRadius == 1)
			{
				++touched;
				++right;
				--left;
			}

			if (!reinterpret_cast<BfmeShroudVRC *>(&arg)->bfmeUpdateVRC(
				left, right, cellY + currentRadius))
				return false;

			if (currentRadius == 0)
				return true;

			if (!reinterpret_cast<BfmeShroudVRC *>(&arg)->bfmeUpdateVRC(
				left, right, cellY - currentRadius))
				return false;

			--currentRadius;
			error += 1 - currentRadius * 2;
		}

		if (touched > error)
		{
			++touched;
			++right;
			--left;
			error += touched * 2 + 1;
		}
	}
}



extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern "C" __declspec(dllimport) double __cdecl ceil(double value);

__forceinline Real bfmeFloatFloorSmallFill(Real value)
{
	return (Real)floor((double)value);
}

__forceinline Real bfmeFloatCeilSmallFill(Real value)
{
	return (Real)ceil((double)value);
}

// As in the already matched ShroudManagerImpl008FBA40.cpp, retail rounds
// through a float slot then converts with the current x87 control word.
// Keep the donor's two-instruction REAL_TO_INT helper: an ordinary cast uses
// compiler conversion machinery with a different rounding/stack shape.
__forceinline int bfmeFloatToIntSmallFill(Real value)
{
	int result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

class BfmeCoiSmallFill;

class BfmeCellFD
{
public:
	BfmeCoiSmallFill *m_first;
	int m_data[41];
};

class Gen_008F7CD0
{
public:
	void rva0073A2A0(BfmeCellFD **first, BfmeCellFD **last, int firstColumn, int lastColumn, int scanRow);

	char m_pad00[4];				// +0x00
	float m_originX;				// +0x04
	float m_originY;				// +0x08
	char m_pad0C[20];				// +0x0C
	float m_scale;					// +0x20
	int m_bfmeWidth;				// +0x24
	int m_bfmeHeight;				// +0x28
	BfmeCellFD *m_bfmeCells;			// +0x2C
};

__forceinline BfmeCellFD *bfmeCellAtSmallFill(Gen_008F7CD0 *grid, int x, int y)
{
	if (x < 0 || x >= grid->m_bfmeWidth || y < 0 || y >= grid->m_bfmeHeight)
		return 0;
	return &grid->m_bfmeCells[y * grid->m_bfmeWidth + x];
}

class BfmeCoiSmallFill
{
public:
	BfmeCellFD *m_cell;
	void *m_module;
	BfmeCellFD *m_prev;
	BfmeCoiSmallFill *m_next;

	__forceinline bool addCoverage(BfmeCellFD *cell)
	{
		m_cell = cell;
		BfmeCoiSmallFill *next = cell->m_first;
		m_next = next;
		if (next != 0)
			next->m_prev = (BfmeCellFD *)&m_next;
		m_prev = (BfmeCellFD *)cell;
		cell->m_first = this;
		return true;
	}
};

class BfmeThingCDE
{
private:
	bool rva0073A9B0(Real centerX, Real centerY, Real radius);

	void *m_owner;
	char m_prefix[0x18];
	void *m_array;
	int m_count;
};

bool BfmeThingCDE::rva0073A9B0(Real centerX, Real centerY, Real radius)
{
	int cellCenterX = bfmeFloatToIntSmallFill(bfmeFloatFloorSmallFill(
		(centerX - ((Gen_008F7CD0 *)m_owner)->m_originX) * ((Gen_008F7CD0 *)m_owner)->m_scale));
	int cellCenterY = bfmeFloatToIntSmallFill(bfmeFloatFloorSmallFill(
		(centerY - ((Gen_008F7CD0 *)m_owner)->m_originY) * ((Gen_008F7CD0 *)m_owner)->m_scale));
	int cellRadius = bfmeFloatToIntSmallFill(bfmeFloatCeilSmallFill(
		radius * ((Gen_008F7CD0 *)m_owner)->m_scale));

	--cellRadius;
	if (cellRadius < 1)
	{
		BfmeCellFD *cell = bfmeCellAtSmallFill((Gen_008F7CD0 *)m_owner, cellCenterX, cellCenterY);
		if (cell != 0)
		{
			BfmeCoiSmallFill *coi = (BfmeCoiSmallFill *)m_array;
			coi->addCoverage(cell);
		}
		return true;
	}
	else
	{
		BfmeArgXO range;
		range.m_grid = (Gen_008F7CD0 *)m_owner;
		range.m_first = (BfmeCoiSmallFill *)m_array;
		range.m_next = (BfmeCoiSmallFill *)m_array + m_count;
		if (!bfmeCallXO(cellCenterX, cellCenterY, cellRadius, range))
		{
			_ReadWriteBarrier();
			return false;
		}
		return true;
	}
}

template<class T> inline volatile T &__vref(T &x) { return *(volatile T *)&x; }

// ?bfmeUpdateVRC@BfmeShroudVRC@@QAEDHHH@Z @0x0073A650 (115 B): the span updater
// bfmeCallXO calls for each row of the circle. The grid's row-range helper
// 0x0073A2A0 returns the first and last cell of the span; each cell is then
// chained to the next free coverage record, failing when the records run out.
// Codegen: a compiler barrier follows the range fetch and the first cell is
// read through a volatile view (retail re-reads it for the first comparison).
char BfmeShroudVRC::bfmeUpdateVRC(int firstX, int lastX, int y)
{
	BfmeCellFD *first;
	BfmeCellFD *last;
	m_grid->rva0073A2A0(&first, &last, firstX, lastX, y);
	BfmeCellFD *cell = first;
	BfmeCellFD *end = last;
	_ReadWriteBarrier();
	if (__vref(cell) != end)
	{
		do
		{
			if (m_first >= m_next)
				return false;
			(m_first++)->addCoverage(cell++);
		} while (cell != end);
	}
	return true;
}
