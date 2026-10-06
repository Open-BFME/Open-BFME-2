// cl: /Oy- /MD
//
// ?Rva002D3489Find@@YAPADPAD0ABD@Z retail 0x002D3489 89B.
// Free byte search over [first last) for value passed by reference.
// Evidence: caller 0x002D3978 pushes first last value-address plus local;
// 4x unrolled main loop via sar ecx 2 grouping with jle/jg shape; switch
// tail with dec-je chain and fallthrough checks for 3-2-1 leftovers.
// Flags match neighbour Rva002D352CMaxStore.cpp.

char *Rva002D3489Find(char *first, char *last, const char &value)
{
	int n = (last - first) >> 2;
	if (n > 0)
	{
		do
		{
			if (*first == value)
				return first;
			++first;
			if (*first == value)
				return first;
			++first;
			if (*first == value)
				return first;
			++first;
			if (*first == value)
				return first;
			++first;
			--n;
		} while (n > 0);
	}
	int rem = last - first;
	switch (rem)
	{
	case 3:
		if (*first == value)
			return first;
		++first;
	case 2:
		if (*first == value)
			return first;
		++first;
	case 1:
		if (*first == value)
			return first;
	default:
		return last;
	}
}
