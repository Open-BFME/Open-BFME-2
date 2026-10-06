// cl: /GX- /Oy-
// ?Rva004E44C9Check@@YGHHEE@Z @0x004E44C9 50B.
// Chain lane on 0x004E40A6 (Rva0050E9D3Enable.cpp neighbour): when the int
// is 0x15 and the byte is 1, 0xF or 0x1C (switch-lowered dec/sub chain),
// call the guarded enabler if the low bit of the third byte is set, then
// report true; else false. __stdcall for the ret 0xC cleanup. Own TU
// because the EBP frame needs /Oy- while the enable family's frameless
// bodies share /O1 /GX-. No callers rowed yet.
typedef unsigned char UnsignedByte;
void __stdcall Rva004E40A6Enable(int unused);
int __stdcall Rva004E44C9Check(int code, UnsignedByte kind, UnsignedByte flags)
{
	if (code != 0x15)
		return 0;
	switch (kind)
	{
	case 1:
	case 0xF:
	case 0x1C:
		break;
	default:
		return 0;
	}
	if (flags & 1)
		Rva004E40A6Enable(0);
	return 1;
}
