// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0051E458PowFloat@@YAMHH@Z @0x0051E458 25B: float wrapper over rowed int pow; fild converts to FPU return
int Rva0051E3F8Pow(int base, int exp);
float Rva0051E458PowFloat(int base, int exp)
{
	return (float)Rva0051E3F8Pow(base, exp);
}
