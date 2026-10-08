// ?bfmeUpdateVRC@BfmeShroudVRC@@QAEDHHH@Z
// partial score=0.8 date=2026-10-08
// cl: /O2 /arch:SSE
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
	char m_head[4];
	Real m_originX;
	Real m_originY;
	char m_middle[20];
	Real m_scale;
	int m_width;
	int m_height;
	BfmeCellFD *m_cells;

	void rva0073A2A0(BfmeCellFD **first, BfmeCellFD **last, int x1, int x2, int y);

    BfmeCellFD *getCellAt(int x, int y)
	{
		if (x < 0 || x >= m_width || y < 0 || y >= m_height)
			return 0;
		return &m_cells[y * m_width + x];
	}
};

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

	Gen_008F7CD0 *m_grid;
	char m_prefix[0x18];
	BfmeCoiSmallFill *m_coiArray;
	int m_coiInUseCount;
};

bool BfmeThingCDE::rva0073A9B0(Real centerX, Real centerY, Real radius)
{
	int cellCenterX = bfmeFloatToIntSmallFill(bfmeFloatFloorSmallFill(
		(centerX - m_grid->m_originX) * m_grid->m_scale));
	int cellCenterY = bfmeFloatToIntSmallFill(bfmeFloatFloorSmallFill(
		(centerY - m_grid->m_originY) * m_grid->m_scale));
	int cellRadius = bfmeFloatToIntSmallFill(bfmeFloatCeilSmallFill(
		radius * m_grid->m_scale));

	--cellRadius;
	if (cellRadius < 1)
	{
		BfmeCellFD *cell = m_grid->getCellAt(cellCenterX, cellCenterY);
		if (cell != 0)
		{
			BfmeCoiSmallFill *coi = m_coiArray;
			coi->addCoverage(cell);
		}
		return true;
	}
	else
	{
		BfmeArgXO range;
		range.m_grid = m_grid;
		range.m_first = m_coiArray;
		range.m_next = m_coiArray + m_coiInUseCount;
		if (!bfmeCallXO(cellCenterX, cellCenterY, cellRadius, range))
		{
			_ReadWriteBarrier();
			return false;
		}
		return true;
	}
}

char BfmeShroudVRC::bfmeUpdateVRC(int firstX, int lastX, int y)
{
    BfmeCellFD *first;
    BfmeCellFD *last;
    m_grid->rva0073A2A0(&first, &last, firstX, lastX, y);
    BfmeCellFD *cell = first;
    BfmeCellFD *end = last;
    if (cell != end)
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
