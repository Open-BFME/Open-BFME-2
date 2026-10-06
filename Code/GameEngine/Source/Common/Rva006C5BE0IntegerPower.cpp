// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva006C5BE0IntegerPower.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?Rva006C5BE0@@YANNH@Z 0x000664BE (49B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Retail @ 0x006C5BE0, integer exponentiation for a double base.

static const double g_rva006C5BE0One = 1.0;

double Rva006C5BE0(double value, int exponent)
{
	int magnitude = exponent;
	if (magnitude < 0)
		magnitude = -magnitude;

	double result = g_rva006C5BE0One;
	do
	{
		if (magnitude & 1)
			result *= value;
		magnitude = (int)((unsigned int)magnitude >> 1);
		if (magnitude != 0)
			value *= value;
	} while (magnitude != 0);

	if (exponent < 0)
		result = g_rva006C5BE0One / result;
	return result;
}
