// cl: /MD
// ?Rva002EBBFBIsOdd@@YAEPAX@Z @0x002EBBFB 25B
// Free __cdecl unsigned char (void*) wrapping ?Rva002E9B31Get@@YAHPAX@Z parity test.
// Evidence: 12 callers pass single pointer and use result as bool for WorldToCell;
// retail cdq/idiv 2 plus dec/neg/sbb/inc is (Get(p)%2)==1; unblocks 0x002EBC14 etc.
int __cdecl Rva002E9B31Get(void *p);
unsigned char __cdecl Rva002EBBFBIsOdd(void *p)
{
	int v = Rva002E9B31Get(p) % 2;
	return (unsigned char)(v == 1 ? 1 : 0);
}
// ?Rva002EBCA7Split@@YAXPAXPAHPAE@Z @0x002EBCA7 47B
// Free __cdecl void (void* int* uchar*) splitting Get(p) into half and odd bit.
// Evidence: caller 0x002ED7B6 passes p plus [esi+0xC] int and [esi+0x8] byte and ignores eax;
// retail stores Get then (rem==1) byte then v/2 via cdq/sub/sar; unblocks 0x002ECD63 etc.
void __cdecl Rva002EBCA7Split(void *p, int *outHalf, unsigned char *outOdd)
{
	int v = Rva002E9B31Get(p);
	*outHalf = v;
	*outOdd = (v % 2 == 1);
	*outHalf /= 2;
}
