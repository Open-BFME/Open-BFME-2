// Cold-slice xor-eax zero returners without vtable carriage (twin-free TU).
//
// Same discipline as ConstIntGetters5.cpp (opaque address-derived names for
// unclaimed leaves with no callers, no branch sources and no .rdata vtable
// slot) but for the 3-byte shape (xor eax,eax / ret). Each follows a ret
// (prev C3) and is followed by a function prologue, so the boundary is
// proven. Kept in a fresh TU to avoid contending with hot getter files.
// No // cl: line (defaults match the frameless 3-byte shape).

// ?Rva00075692Get@@YAHXZ @ 0x00075692 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00075692Get(void)
{
	return 0;
}

// ?Rva0017FB0CGet@@YAHXZ @ 0x0017fb0c (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0017FB0CGet(void)
{
	return 0;
}

// ?Rva001E38B6Get@@YAHXZ @ 0x001e38b6 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva001E38B6Get(void)
{
	return 0;
}

// ?Rva001E4012Get@@YAHXZ @ 0x001e4012 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva001E4012Get(void)
{
	return 0;
}

// ?Rva001F53FEGet@@YAHXZ @ 0x001f53fe (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva001F53FEGet(void)
{
	return 0;
}

// ?Rva002221A6Get@@YAHXZ @ 0x002221a6 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002221A6Get(void)
{
	return 0;
}

// ?Rva0023C921Get@@YAHXZ @ 0x0023c921 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0023C921Get(void)
{
	return 0;
}

// ?Rva0025DD45Get@@YAHXZ @ 0x0025dd45 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0025DD45Get(void)
{
	return 0;
}

// ?Rva00271776Get@@YAHXZ @ 0x00271776 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00271776Get(void)
{
	return 0;
}

// ?Rva0028B3A3Get@@YAHXZ @ 0x0028b3a3 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0028B3A3Get(void)
{
	return 0;
}

// ?Rva0028D4DDGet@@YAHXZ @ 0x0028d4dd (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0028D4DDGet(void)
{
	return 0;
}

// ?Rva002B2CC3Get@@YAHXZ @ 0x002b2cc3 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002B2CC3Get(void)
{
	return 0;
}

// ?Rva002B3635Get@@YAHXZ @ 0x002b3635 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002B3635Get(void)
{
	return 0;
}

// ?Rva002B3EF7Get@@YAHXZ @ 0x002b3ef7 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002B3EF7Get(void)
{
	return 0;
}

// ?Rva002D6BFFGet@@YAHXZ @ 0x002d6bff (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002D6BFFGet(void)
{
	return 0;
}

// ?Rva00301B51Get@@YAHXZ @ 0x00301b51 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00301B51Get(void)
{
	return 0;
}

// ?Rva003427A6Get@@YAHXZ @ 0x003427a6 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva003427A6Get(void)
{
	return 0;
}

// ?Rva003956E5Get@@YAHXZ @ 0x003956e5 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva003956E5Get(void)
{
	return 0;
}

// ?Rva003E46B1Get@@YAHXZ @ 0x003e46b1 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva003E46B1Get(void)
{
	return 0;
}

// ?Rva003FE25AGet@@YAHXZ @ 0x003fe25a (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva003FE25AGet(void)
{
	return 0;
}

// ?Rva00406E1FGet@@YAHXZ @ 0x00406e1f (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00406E1FGet(void)
{
	return 0;
}

// ?Rva004110D9Get@@YAHXZ @ 0x004110d9 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004110D9Get(void)
{
	return 0;
}

// ?Rva00418BF8Get@@YAHXZ @ 0x00418bf8 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00418BF8Get(void)
{
	return 0;
}

// ?Rva0043287BGet@@YAHXZ @ 0x0043287b (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0043287BGet(void)
{
	return 0;
}

// ?Rva00444506Get@@YAHXZ @ 0x00444506 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00444506Get(void)
{
	return 0;
}

// ?Rva00449A26Get@@YAHXZ @ 0x00449a26 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00449A26Get(void)
{
	return 0;
}

// ?Rva004524E2Get@@YAHXZ @ 0x004524e2 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004524E2Get(void)
{
	return 0;
}

// ?Rva004697DEGet@@YAHXZ @ 0x004697de (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004697DEGet(void)
{
	return 0;
}

// ?Rva0047E4FCGet@@YAHXZ @ 0x0047e4fc (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0047E4FCGet(void)
{
	return 0;
}

// ?Rva004C30D5Get@@YAHXZ @ 0x004c30d5 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004C30D5Get(void)
{
	return 0;
}

// ?Rva004D8D7CGet@@YAHXZ @ 0x004d8d7c (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004D8D7CGet(void)
{
	return 0;
}

// ?Rva004DD655Get@@YAHXZ @ 0x004dd655 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004DD655Get(void)
{
	return 0;
}

// ?Rva00523F1FGet@@YAHXZ @ 0x00523f1f (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00523F1FGet(void)
{
	return 0;
}

// ?Rva0052B23AGet@@YAHXZ @ 0x0052b23a (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0052B23AGet(void)
{
	return 0;
}

// ?Rva005312BBGet@@YAHXZ @ 0x005312bb (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005312BBGet(void)
{
	return 0;
}

// ?Rva0055D3F2Get@@YAHXZ @ 0x0055d3f2 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0055D3F2Get(void)
{
	return 0;
}

// ?Rva005CCAC7Get@@YAHXZ @ 0x005ccac7 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005CCAC7Get(void)
{
	return 0;
}

// ?Rva005EB88CGet@@YAHXZ @ 0x005eb88c (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005EB88CGet(void)
{
	return 0;
}

// ?Rva005EEA1DGet@@YAHXZ @ 0x005eea1d (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005EEA1DGet(void)
{
	return 0;
}

// ?Rva005F0233Get@@YAHXZ @ 0x005f0233 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005F0233Get(void)
{
	return 0;
}

// ?Rva005F88F1Get@@YAHXZ @ 0x005f88f1 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005F88F1Get(void)
{
	return 0;
}

// ?Rva0060B883Get@@YAHXZ @ 0x0060b883 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0060B883Get(void)
{
	return 0;
}

// ?Rva00740A5DGet@@YAHXZ @ 0x00740a5d (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00740A5DGet(void)
{
	return 0;
}

// ?Rva00021736Get@@YAHXZ @ 0x00021736 (3B): returns 0.
// Follows a ret (prev C3), padded (CC) before next function, no .rdata
// vtable slot, no direct callers, no branch sources. Opaque name.
int Rva00021736Get(void)
{
	return 0;
}

// ?Rva00030514Get@@YAHXZ @ 0x00030514 (3B): returns 0.
// Follows a ret (prev C3), padded (CC) before next function, no .rdata
// vtable slot, no direct callers, no branch sources. Opaque name.
int Rva00030514Get(void)
{
	return 0;
}

// ?Rva000310EBGet@@YAHXZ @ 0x000310eb (3B): returns 0.
// Follows a ret (prev C3), padded (CC) before next function, no .rdata
// vtable slot, no direct callers, no branch sources. Opaque name.
int Rva000310EBGet(void)
{
	return 0;
}

// ?Rva001499A5Get@@YAHXZ @ 0x001499a5 (3B): returns 0.
// Follows a ret (prev C3), padded (CC) before next function, no .rdata
// vtable slot, no direct callers, no branch sources. Opaque name.
int Rva001499A5Get(void)
{
	return 0;
}
// ?Rva00042FF5Get@@YAHXZ @ 0x00042ff5 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00042FF5Get(void)
{
	return 0;
}

// ?Rva00094BEFGet@@YAHXZ @ 0x00094bef (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00094BEFGet(void)
{
	return 0;
}

// ?Rva00149A6CGet@@YAHXZ @ 0x00149a6c (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00149A6CGet(void)
{
	return 0;
}

// ?Rva00179930Get@@YAHXZ @ 0x00179930 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00179930Get(void)
{
	return 0;
}

// ?Rva00202028Get@@YAHXZ @ 0x00202028 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00202028Get(void)
{
	return 0;
}

// ?Rva0028B83FGet@@YAHXZ @ 0x0028b83f (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0028B83FGet(void)
{
	return 0;
}

// ?Rva002B256BGet@@YAHXZ @ 0x002b256b (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002B256BGet(void)
{
	return 0;
}

// ?Rva002D9580Get@@YAHXZ @ 0x002d9580 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002D9580Get(void)
{
	return 0;
}

// ?Rva002E6C8AGet@@YAHXZ @ 0x002e6c8a (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002E6C8AGet(void)
{
	return 0;
}

// ?Rva0035B1C0Get@@YAHXZ @ 0x0035b1c0 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0035B1C0Get(void)
{
	return 0;
}

// ?Rva00411128Get@@YAHXZ @ 0x00411128 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00411128Get(void)
{
	return 0;
}

// ?Rva004A9911Get@@YAHXZ @ 0x004a9911 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004A9911Get(void)
{
	return 0;
}

// ?Rva00538D14Get@@YAHXZ @ 0x00538d14 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00538D14Get(void)
{
	return 0;
}

// ?Rva0059F379Get@@YAHXZ @ 0x0059f379 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0059F379Get(void)
{
	return 0;
}

// ?Rva0065EC9AGet@@YAHXZ @ 0x0065ec9a (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0065EC9AGet(void)
{
	return 0;
}

// ?Rva006C6490Get@@YAHXZ @ 0x006c6490 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva006C6490Get(void)
{
	return 0;
}

// ?Rva00050D50Get@@YAHXZ @ 0x00050d50 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00050D50Get(void)
{
	return 0;
}

// ?Rva000B19F8Get@@YAHXZ @ 0x000b19f8 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva000B19F8Get(void)
{
	return 0;
}

// ?Rva00149A8CGet@@YAHXZ @ 0x00149a8c (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00149A8CGet(void)
{
	return 0;
}

// ?Rva0017EF80Get@@YAHXZ @ 0x0017ef80 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0017EF80Get(void)
{
	return 0;
}

// ?Rva00215EE9Get@@YAHXZ @ 0x00215ee9 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00215EE9Get(void)
{
	return 0;
}

// ?Rva0028B872Get@@YAHXZ @ 0x0028b872 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0028B872Get(void)
{
	return 0;
}

// ?Rva002C0A0CGet@@YAHXZ @ 0x002c0a0c (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002C0A0CGet(void)
{
	return 0;
}

// ?Rva002D95A9Get@@YAHXZ @ 0x002d95a9 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002D95A9Get(void)
{
	return 0;
}

// ?Rva002E6E9CGet@@YAHXZ @ 0x002e6e9c (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002E6E9CGet(void)
{
	return 0;
}

// ?Rva0035BD7BGet@@YAHXZ @ 0x0035bd7b (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0035BD7BGet(void)
{
	return 0;
}

// ?Rva0042D6D3Get@@YAHXZ @ 0x0042d6d3 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0042D6D3Get(void)
{
	return 0;
}

// ?Rva004B0D49Get@@YAHXZ @ 0x004b0d49 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004B0D49Get(void)
{
	return 0;
}

// ?Rva0053EC1EGet@@YAHXZ @ 0x0053ec1e (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0053EC1EGet(void)
{
	return 0;
}

// ?Rva005A671AGet@@YAHXZ @ 0x005a671a (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005A671AGet(void)
{
	return 0;
}

// ?Rva00661618Get@@YAHXZ @ 0x00661618 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00661618Get(void)
{
	return 0;
}

// ?Rva006C64F5Get@@YAHXZ @ 0x006c64f5 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva006C64F5Get(void)
{
	return 0;
}

// ?Rva00050D5DGet@@YAHXZ @ 0x00050d5d (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00050D5DGet(void)
{
	return 0;
}

// ?Rva000B2CE2Get@@YAHXZ @ 0x000b2ce2 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva000B2CE2Get(void)
{
	return 0;
}

// ?Rva0014A07FGet@@YAHXZ @ 0x0014a07f (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0014A07FGet(void)
{
	return 0;
}

// ?Rva0017EFC0Get@@YAHXZ @ 0x0017efc0 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0017EFC0Get(void)
{
	return 0;
}

// ?Rva00219837Get@@YAHXZ @ 0x00219837 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00219837Get(void)
{
	return 0;
}

// ?Rva0028B8A3Get@@YAHXZ @ 0x0028b8a3 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0028B8A3Get(void)
{
	return 0;
}

// ?Rva002C5FD6Get@@YAHXZ @ 0x002c5fd6 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002C5FD6Get(void)
{
	return 0;
}

// ?Rva002D95D2Get@@YAHXZ @ 0x002d95d2 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002D95D2Get(void)
{
	return 0;
}

// ?Rva0030BD05Get@@YAHXZ @ 0x0030bd05 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0030BD05Get(void)
{
	return 0;
}

// ?Rva003626AAGet@@YAHXZ @ 0x003626aa (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva003626AAGet(void)
{
	return 0;
}

// ?Rva0042D6E3Get@@YAHXZ @ 0x0042d6e3 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0042D6E3Get(void)
{
	return 0;
}

// ?Rva004C576FGet@@YAHXZ @ 0x004c576f (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004C576FGet(void)
{
	return 0;
}

// ?Rva0055C425Get@@YAHXZ @ 0x0055c425 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0055C425Get(void)
{
	return 0;
}

// ?Rva005E7604Get@@YAHXZ @ 0x005e7604 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005E7604Get(void)
{
	return 0;
}

// ?Rva00661F63Get@@YAHXZ @ 0x00661f63 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00661F63Get(void)
{
	return 0;
}

// ?Rva006CD9DFGet@@YAHXZ @ 0x006cd9df (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva006CD9DFGet(void)
{
	return 0;
}
// ?Rva00050DEDGet@@YAHXZ @ 0x00050ded (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00050DEDGet(void)
{
	return 0;
}

// ?Rva000B3148Get@@YAHXZ @ 0x000b3148 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva000B3148Get(void)
{
	return 0;
}

// ?Rva0014A0C6Get@@YAHXZ @ 0x0014a0c6 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0014A0C6Get(void)
{
	return 0;
}

// ?Rva0017F000Get@@YAHXZ @ 0x0017f000 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0017F000Get(void)
{
	return 0;
}

// ?Rva0025DE73Get@@YAHXZ @ 0x0025de73 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0025DE73Get(void)
{
	return 0;
}

// ?Rva0029A351Get@@YAHXZ @ 0x0029a351 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0029A351Get(void)
{
	return 0;
}

// ?Rva002D2553Get@@YAHXZ @ 0x002d2553 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002D2553Get(void)
{
	return 0;
}

// ?Rva002E6ADEGet@@YAHXZ @ 0x002e6ade (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002E6ADEGet(void)
{
	return 0;
}

// ?Rva003143B6Get@@YAHXZ @ 0x003143b6 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva003143B6Get(void)
{
	return 0;
}

// ?Rva00377610Get@@YAHXZ @ 0x00377610 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00377610Get(void)
{
	return 0;
}

// ?Rva0042E8BEGet@@YAHXZ @ 0x0042e8be (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0042E8BEGet(void)
{
	return 0;
}

// ?Rva004D8DE7Get@@YAHXZ @ 0x004d8de7 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004D8DE7Get(void)
{
	return 0;
}

// ?Rva0056777FGet@@YAHXZ @ 0x0056777f (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0056777FGet(void)
{
	return 0;
}

// ?Rva006026D0Get@@YAHXZ @ 0x006026d0 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva006026D0Get(void)
{
	return 0;
}

// ?Rva006694AAGet@@YAHXZ @ 0x006694aa (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva006694AAGet(void)
{
	return 0;
}

// ?Rva0006CEEBGet@@YAHXZ @ 0x0006ceeb (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0006CEEBGet(void)
{
	return 0;
}

// ?Rva000FBA47Get@@YAHXZ @ 0x000fba47 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva000FBA47Get(void)
{
	return 0;
}

// ?Rva001542C3Get@@YAHXZ @ 0x001542c3 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva001542C3Get(void)
{
	return 0;
}

// ?Rva00181242Get@@YAHXZ @ 0x00181242 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00181242Get(void)
{
	return 0;
}

// ?Rva002632C4Get@@YAHXZ @ 0x002632c4 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002632C4Get(void)
{
	return 0;
}

// ?Rva0029A35FGet@@YAHXZ @ 0x0029a35f (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0029A35FGet(void)
{
	return 0;
}

// ?Rva002D25B7Get@@YAHXZ @ 0x002d25b7 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002D25B7Get(void)
{
	return 0;
}

// ?Rva002E6B03Get@@YAHXZ @ 0x002e6b03 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002E6B03Get(void)
{
	return 0;
}

// ?Rva00318D60Get@@YAHXZ @ 0x00318d60 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00318D60Get(void)
{
	return 0;
}

// ?Rva0037DC81Get@@YAHXZ @ 0x0037dc81 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0037DC81Get(void)
{
	return 0;
}

// ?Rva004318C3Get@@YAHXZ @ 0x004318c3 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004318C3Get(void)
{
	return 0;
}

// ?Rva004E0602Get@@YAHXZ @ 0x004e0602 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004E0602Get(void)
{
	return 0;
}

// ?Rva0056DA35Get@@YAHXZ @ 0x0056da35 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0056DA35Get(void)
{
	return 0;
}

// ?Rva00602820Get@@YAHXZ @ 0x00602820 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00602820Get(void)
{
	return 0;
}

// ?Rva0066CA0CGet@@YAHXZ @ 0x0066ca0c (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0066CA0CGet(void)
{
	return 0;
}

// ?Rva0007B716Get@@YAHXZ @ 0x0007b716 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0007B716Get(void)
{
	return 0;
}

// ?Rva000FC943Get@@YAHXZ @ 0x000fc943 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva000FC943Get(void)
{
	return 0;
}

// ?Rva0016ABD1Get@@YAHXZ @ 0x0016abd1 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0016ABD1Get(void)
{
	return 0;
}

// ?Rva001D909EGet@@YAHXZ @ 0x001d909e (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva001D909EGet(void)
{
	return 0;
}

// ?Rva002632DEGet@@YAHXZ @ 0x002632de (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002632DEGet(void)
{
	return 0;
}

// ?Rva002AA254Get@@YAHXZ @ 0x002aa254 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002AA254Get(void)
{
	return 0;
}

// ?Rva002D2C31Get@@YAHXZ @ 0x002d2c31 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002D2C31Get(void)
{
	return 0;
}

// ?Rva002E6B16Get@@YAHXZ @ 0x002e6b16 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002E6B16Get(void)
{
	return 0;
}

// ?Rva00327DF3Get@@YAHXZ @ 0x00327df3 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00327DF3Get(void)
{
	return 0;
}

// ?Rva00388F36Get@@YAHXZ @ 0x00388f36 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00388F36Get(void)
{
	return 0;
}

// ?Rva004319EFGet@@YAHXZ @ 0x004319ef (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004319EFGet(void)
{
	return 0;
}

// ?Rva004EABE7Get@@YAHXZ @ 0x004eabe7 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004EABE7Get(void)
{
	return 0;
}

// ?Rva0057AAFDGet@@YAHXZ @ 0x0057aafd (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0057AAFDGet(void)
{
	return 0;
}

// ?Rva00602860Get@@YAHXZ @ 0x00602860 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00602860Get(void)
{
	return 0;
}

// ?Rva006C5FBAGet@@YAHXZ @ 0x006c5fba (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva006C5FBAGet(void)
{
	return 0;
}

// ?Rva0007E3AEGet@@YAHXZ @ 0x0007e3ae (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0007E3AEGet(void)
{
	return 0;
}

// ?Rva00104076Get@@YAHXZ @ 0x00104076 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00104076Get(void)
{
	return 0;
}

// ?Rva0016ABF1Get@@YAHXZ @ 0x0016abf1 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0016ABF1Get(void)
{
	return 0;
}

// ?Rva001E35C7Get@@YAHXZ @ 0x001e35c7 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva001E35C7Get(void)
{
	return 0;
}

// ?Rva0027175CGet@@YAHXZ @ 0x0027175c (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0027175CGet(void)
{
	return 0;
}

// ?Rva002AAD99Get@@YAHXZ @ 0x002aad99 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002AAD99Get(void)
{
	return 0;
}

// ?Rva002D36F2Get@@YAHXZ @ 0x002d36f2 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002D36F2Get(void)
{
	return 0;
}

// ?Rva002E6B3AGet@@YAHXZ @ 0x002e6b3a (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002E6B3AGet(void)
{
	return 0;
}

// ?Rva0033F259Get@@YAHXZ @ 0x0033f259 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0033F259Get(void)
{
	return 0;
}

// ?Rva003F3F94Get@@YAHXZ @ 0x003f3f94 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva003F3F94Get(void)
{
	return 0;
}

// ?Rva00462589Get@@YAHXZ @ 0x00462589 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00462589Get(void)
{
	return 0;
}

// ?Rva004FC217Get@@YAHXZ @ 0x004fc217 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004FC217Get(void)
{
	return 0;
}

// ?Rva0057B990Get@@YAHXZ @ 0x0057b990 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0057B990Get(void)
{
	return 0;
}

// ?Rva00658147Get@@YAHXZ @ 0x00658147 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00658147Get(void)
{
	return 0;
}

// ?Rva006C5FD3Get@@YAHXZ @ 0x006c5fd3 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva006C5FD3Get(void)
{
	return 0;
}

// ?Rva0008BBDDGet@@YAHXZ @ 0x0008bbdd (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0008BBDDGet(void)
{
	return 0;
}

// ?Rva0010615FGet@@YAHXZ @ 0x0010615f (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0010615FGet(void)
{
	return 0;
}

// ?Rva00176D69Get@@YAHXZ @ 0x00176d69 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00176D69Get(void)
{
	return 0;
}

// ?Rva001E368BGet@@YAHXZ @ 0x001e368b (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva001E368BGet(void)
{
	return 0;
}

// ?Rva0028AF94Get@@YAHXZ @ 0x0028af94 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0028AF94Get(void)
{
	return 0;
}

// ?Rva002B225DGet@@YAHXZ @ 0x002b225d (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002B225DGet(void)
{
	return 0;
}

// ?Rva002D9557Get@@YAHXZ @ 0x002d9557 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002D9557Get(void)
{
	return 0;
}

// ?Rva002E6C5DGet@@YAHXZ @ 0x002e6c5d (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002E6C5DGet(void)
{
	return 0;
}

// ?Rva0033F514Get@@YAHXZ @ 0x0033f514 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0033F514Get(void)
{
	return 0;
}

// ?Rva00407702Get@@YAHXZ @ 0x00407702 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00407702Get(void)
{
	return 0;
}

// ?Rva004A3A1DGet@@YAHXZ @ 0x004a3a1d (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004A3A1DGet(void)
{
	return 0;
}

// ?Rva0050DBE3Get@@YAHXZ @ 0x0050dbe3 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0050DBE3Get(void)
{
	return 0;
}

// ?Rva0059E10CGet@@YAHXZ @ 0x0059e10c (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0059E10CGet(void)
{
	return 0;
}

// ?Rva0065E7CAGet@@YAHXZ @ 0x0065e7ca (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0065E7CAGet(void)
{
	return 0;
}

// ?Rva006C5FF3Get@@YAHXZ @ 0x006c5ff3 (3B): returns 0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva006C5FF3Get(void)
{
	return 0;
}

