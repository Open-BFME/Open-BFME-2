// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0030B395Equal@@YA_NPBM00@Z @0x0030B395 60B
// Float-pair array equal with NaN fail.
// Evidence: movss ucomiss lahf test jp x2 plus add 8 loop; caller 0x0030B6CD; prev copy_backward_ptrs BfmeE8.
// Precedent Rva0030BF0CEqual 90B same pattern with 4 floats.
bool __cdecl Rva0030B395Equal(const float *first1, const float *last1, const float *first2)
{
	while (first1 != last1)
	{
		if (first1[0] != first2[0])
			return false;
		if (first1[1] != first2[1])
			return false;
		first1 += 2;
		first2 += 2;
	}
	return true;
}
