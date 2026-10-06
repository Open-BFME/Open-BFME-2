// ?Rva003BD46ESum@@YAHPAX@Z
// partial score=0.95 date=2026-09-29
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BD46ESum@@YAHPAX@Z @0x003BD46E 23B.
// Sum ints over a begin/end pointer pair: mov edx,[esp+4] mov ecx,[edx]
// mov edx,[edx+4] xor eax jmp check add eax,[ecx] add ecx,4 cmp ecx,edx jne.
// Callers at 0x003C5FEC 0x003E9890 0x003E9D47 0x003E9F98; plain ret so
// __cdecl int(void*). Tried while/for/no-r/ref/G7: all give mov eax base
// instead of mov edx base with destructive mov edx,[edx+4].
int __cdecl Rva003BD46ESum(void *range)
{
	struct Range { int *begin; int *end; };
	int sum = 0;
	Range *r = (Range *)range;
	int *p = r->begin;
	int *e = r->end;
	while (p != e)
	{
		sum += *p;
		++p;
	}
	return sum;
}
