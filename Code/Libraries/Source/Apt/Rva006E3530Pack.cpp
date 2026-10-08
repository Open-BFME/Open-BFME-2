// cl: /MD
//
// ?rva006E3530@Rva006E34D0@@QAEXHHH@Z @0x006E3530 77B
// Packs three ints into one append value and passes it to rva006E34D0 through
// the same ecx (this is not moved): when the third argument is 1 the value is
// ((a<<7 | b&0x7F) << 10) | 5; otherwise ((((a<<7 | b&0x7F) << 8) | c&0xFF) << 2) | 1.
// Evidence: retail stdcall-style ret 0xC after pushing one dword to 0x6E34D0.
// Address-derived names: the meaning of the fields is not proven.
class Rva006E34D0
{
public:
	void rva006E34D0(int v);
	void rva006E3530(int a, int b, int c);
};

void Rva006E34D0::rva006E3530(int a, int b, int c)
{
	int packed;
	if (c == 1)
		packed = ((((a << 7) | (b & 0x7f)) << 10) | 5);
	else
		packed = ((((((a << 7) | (b & 0x7f)) << 8) | (c & 0xff))) << 2) | 1;
	rva006E34D0(packed);
}
