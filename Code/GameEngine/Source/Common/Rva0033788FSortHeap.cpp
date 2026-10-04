// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?Rva0033788FSortHeap@@YAXPAX00@Z retail 0x0033788F 65 bytes.
// Calls 0x00337802 Forward in a sort_heap loop decrementing by 0x14.
// Caller 0x003379F0 passes 3 args; unblocks 0x00337999.
// Identity honest address name free function.
void __cdecl Rva00337802Forward(void *first, void *last, void *comp);
void __cdecl Rva0033788FSortHeap(void *first, void *last, void *comp)
{
	int count = ((char *)last - (char *)first) / 0x14;
	if (count <= 1)
		return;
	do
	{
		Rva00337802Forward(first, last, comp);
		last = (char *)last - 0x14;
		count = ((char *)last - (char *)first) / 0x14;
	} while (count > 1);
}
