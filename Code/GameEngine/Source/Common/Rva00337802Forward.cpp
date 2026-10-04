// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?Rva00337802Forward@@YAXPAX00@Z retail 0x00337802 23 bytes.
// Forwards to 0x003377BC ?gen002EADF0@@YAXPAX0H0@Z with 0 as third arg and own third as fourth.
// Callees rowed; caller 0x0033788F passes 3 args; unblocks 0x0033788F.
// Identity honest address name free function.
void __cdecl gen002EADF0(void *a, void *b, int c, void *d);
void __cdecl Rva00337802Forward(void *a, void *b, void *c)
{
	gen002EADF0(a, b, 0, c);
}
