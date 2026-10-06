// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003E40AFGet@@YGHH@Z @0x003E40AF 35B switch 0 to 1 plus 1 to 2 plus 2 to 4 else minus 1.
// Evidence: unlock lane no callees; callers 0x003E56FC plus 0x003E687D; push pop plus or minus 1 plus xor inc.
int __stdcall Rva003E40AFGet(int v)
{
	switch (v)
	{
	case 0:
		return 1;
	case 2:
		return 4;
	case 1:
		return 2;
	default:
		return -1;
	}
}
