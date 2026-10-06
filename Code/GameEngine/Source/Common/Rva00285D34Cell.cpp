// cl: /DNDEBUG /MD
// ?rva00285D34@Rva00285D34@@QAEHHH@Z @0x00285D34 (145B):
// Grid cell-type lookup: null grid returns 0, else each coordinate is
// divided by the 10-unit tile, biased by g_Va007C26F0 and floored to a row
// and column that are bounds-checked against +0x78/+0x7C, returning the
// leading int of the 20-byte cell. Evidence: this+0x70 row-pointer table
// with row/col counts, imul 0x14 stride, IAT floor twice, caller 0x00098573
// comparing the result against 1 and 2; owner unproven so honest Rva class.
typedef int Int;

extern "C" __declspec(dllimport) double __cdecl floor(double);

extern float g_Va007C26F0;

// float-to-int must stay inline fld/fistp: a C cast emits an out-of-line
// _ftol call plus qword traffic (see GlobalLanguageAdjustFontSize precedent).
__forceinline long FloatToLong(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

class Rva00285D34
{
public:
	Int rva00285D34(Int x, Int y);
private:
	struct Cell
	{
		Int m_type;
		char m_pad[16];
	};
	char m_pad[0x70];
	Cell **m_cells;
	Int m_pad74;
	Int m_numRows;
	Int m_numCols;
};

Int Rva00285D34::rva00285D34(Int x, Int y)
{
	Int result = 0;
	if (m_cells != 0) {
		double dx = floor((double)(x / 10) + g_Va007C26F0);
		Int row = FloatToLong((float)dx);
		double dy = floor((double)(y / 10) + g_Va007C26F0);
		Int col = FloatToLong((float)dy);
		if (row >= 0 && row < m_numRows && col >= 0 && col < m_numCols) {
			Int off = col * 20;
			result = *(const Int *)((const char *)m_cells[row] + off);
		}
	}
	return result;
}
