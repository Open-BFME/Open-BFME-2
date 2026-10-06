// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0030BF0CEqual@@YA_NPBM00@Z retail 0x0030BF0C 90B: float array equal with NaN fail.
// Evidence: movss ucomiss lahf test jp times 4 plus add 10 loop; caller 0x0030BFE8 pushes 3 args with add esp C.

bool __cdecl Rva0030BF0CEqual(const float *first1, const float *last1, const float *first2)
{
	while (first1 != last1)
	{
		if (first1[0] != first2[0])
			return false;
		if (first1[1] != first2[1])
			return false;
		if (first1[2] != first2[2])
			return false;
		if (first1[3] != first2[3])
			return false;
		first1 += 4;
		first2 += 4;
	}
	return true;
}
