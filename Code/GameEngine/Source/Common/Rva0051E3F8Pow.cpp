// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0051E3F8Pow@@YAHHH@Z @0x0051E3F8 51B: int pow by squaring with negative-exp reciprocal; caller 0x0051E458 converts to float
int Rva0051E3F8Pow(int base, int exp)
{
	unsigned int n = exp < 0 ? (unsigned int)-exp : (unsigned int)exp;
	int result = 1;
	for (;;)
	{
		if ((n & 1) != 0)
			result *= base;
		n >>= 1;
		if (n == 0)
			break;
		base *= base;
	}
	if (exp < 0)
		return 1 / result;
	return result;
}
