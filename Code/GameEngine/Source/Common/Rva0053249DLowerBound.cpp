// cl: /MD
//
// ?Rva0053249DLowerBound@@YAPAHPAH0PAG@Z retail 0x0053249D 59B.
// Binary lower bound over dword array with word key: count from byte delta
// then halve and compare low word, plain ret.
// Evidence: retail rdtsc-free EBP frame sar jae loop; callers 0x00532803 0x00532C75 0x00532DF6.
int * __cdecl Rva0053249DLowerBound(int *first, int *last, unsigned short *value);

int * __cdecl Rva0053249DLowerBound(int *first, int *last, unsigned short *value)
{
	int count = ((char *)last - (char *)first) >> 2;
	if (count <= 0)
		return first;
	unsigned short key = *value;
	while (count > 0) {
		int half = count >> 1;
		int *mid = first + half;
		if ((unsigned short)*mid < key) {
			first = mid + 1;
			count -= half + 1;
		} else {
			count = half;
		}
	}
	return first;
}
