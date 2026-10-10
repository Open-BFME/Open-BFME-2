// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// ?Rva005E4817Partition@@YAPAHPAH0VRva005E4300Cmp@@H@Z
// stlport

// ?Rva005E4817Partition@@YAPAHPAHVRva005E4300Cmp@@H@Z 0x005E4817 75B partition with stateful cmp
// Evidence: two out-of-line calls to pinned 0x005E4300, same family as 0x005E459F __unguarded_partition; caller 0x005E49FD.
class Rva005E4300Cmp
{
public:
	bool operator()(int a, int b) const;
};

int *__cdecl Rva005E4817Partition(int *first, int *last, Rva005E4300Cmp comp, int pivot)
{
loop:
	if ((first?first:first) == last)
		return first;
	if (comp(*first, pivot))
	{
		++first;
		goto loop;
	}
	do
	{
		--last;
		if (first == last)
			return first;
	} while (!comp(*last, pivot));
	int tmp = *first;
	*first = *last;
	*last = tmp;
	++first;
	goto loop;
}
