// Cold-slice B8-imm32 const-int returners without vtable carriage (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters4.cpp (mov eax,<IMM32> / ret) but for
// bodies with no .rdata vtable slot, no direct callers and no branch sources:
// each follows a ret-imm (C2-04-00) and is an unclaimed leaf, so the opaque
// address-derived name witnesses only the address and the returned constant.
// Kept in a fresh TU so this batch does not contend with the hot
// ConstIntGetters4 appends on origin/master. No // cl: line (defaults match
// the frameless 6-byte shape).

// ?Rva00062A52Get@@YAHXZ @ 0x00062a52 (6B): returns 0x0000ffff.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00062A52Get(void)
{
	return 0x0000ffff;
}

// ?Rva0028C77DGet@@YAHXZ @ 0x0028c77d (6B): returns 0x0000009a.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0028C77DGet(void)
{
	return 0x0000009a;
}

// ?Rva004CFAE5Get@@YAHXZ @ 0x004cfae5 (6B): returns 0x00010000.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004CFAE5Get(void)
{
	return 0x00010000;
}

// ?Rva00007450Get@@YAHXZ @ 0x00007450 (6B): returns -2.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00007450Get(void)
{
	return -2;
}

// ?Rva00018080Get@@YAHXZ @ 0x00018080 (6B): returns INT_MIN.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00018080Get(void)
{
	return (int)0x80000000;
}

// ?Rva00018610Get@@YAHXZ @ 0x00018610 (6B): returns INT_MAX.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00018610Get(void)
{
	return 0x7fffffff;
}

// ?Rva00019B50Get@@YAHXZ @ 0x00019b50 (6B): returns 0x7ffffffe.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00019B50Get(void)
{
	return 0x7ffffffe;
}

// ?Rva00030A40Get@@YAHXZ @ 0x00030a40 (6B): returns 16.
// Follows a ret tail, int3-padded after. No direct callers.
// Opaque address-derived name.
int Rva00030A40Get(void)
{
	return 16;
}

// ?Rva00051EA9Get@@YAHXZ @ 0x00051ea9 (6B): returns 1000000.
// Follows a ret tail. No direct callers. Opaque address-derived name.
int Rva00051EA9Get(void)
{
	return 1000000;
}

// ?Rva000454EDGet@@YAHXZ @ 0x000454ed (6B): returns 0x0000024f.
// Follows an idiv helper tail. No direct callers. Opaque address-derived
// name.
int Rva000454EDGet(void)
{
	return 0x0000024f;
}

// ?Rva0024A8D6Get@@YAHXZ @ 0x0024a8d6 (6B): returns 132.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024A8D6Get(void)
{
	return 132;
}

// ?Rva0024B43DGet@@YAHXZ @ 0x0024b43d (6B): returns 135.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024B43DGet(void)
{
	return 135;
}

// ?Rva0024B507Get@@YAHXZ @ 0x0024b507 (6B): returns 142.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024B507Get(void)
{
	return 142;
}

// ?Rva0024C32DGet@@YAHXZ @ 0x0024c32d (6B): returns 133.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024C32DGet(void)
{
	return 133;
}

// ?Rva0024C775Get@@YAHXZ @ 0x0024c775 (6B): returns 8192.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024C775Get(void)
{
	return 8192;
}

// ?Rva0024D51CGet@@YAHXZ @ 0x0024d51c (6B): returns 2048.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024D51CGet(void)
{
	return 2048;
}

// ?Rva0024DCDDGet@@YAHXZ @ 0x0024dcdd (6B): returns 256.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024DCDDGet(void)
{
	return 256;
}

// ?Rva0024DCE3Get@@YAHXZ @ 0x0024dce3 (6B): returns 257.
// Abuts the twin getter above. No direct callers. Opaque
// address-derived name.
int Rva0024DCE3Get(void)
{
	return 257;
}

// ?Rva0024FB41Get@@YAHXZ @ 0x0024fb41 (6B): returns 513.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024FB41Get(void)
{
	return 513;
}

// ?Rva00250722Get@@YAHXZ @ 0x00250722 (6B): returns 140.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva00250722Get(void)
{
	return 140;
}

// ?Rva002507ECGet@@YAHXZ @ 0x002507ec (6B): returns 131.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva002507ECGet(void)
{
	return 131;
}

// ?Rva00252165Get@@YAHXZ @ 0x00252165 (6B): returns 273.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva00252165Get(void)
{
	return 273;
}

// ?Rva00285B54Get@@YAHXZ @ 0x00285b54 (6B): returns 4095.
// Follows a lea plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00285B54Get(void)
{
	return 4095;
}

// ?Rva00285B5AGet@@YAHXZ @ 0x00285b5a (6B): returns 1023.
// Abuts the twin getter above. No direct callers. Opaque
// address-derived name.
int Rva00285B5AGet(void)
{
	return 1023;
}

// ?Rva00285B60Get@@YAHXZ @ 0x00285b60 (6B): returns 255.
// Abuts the twin getter above. No direct callers. Opaque
// address-derived name.
int Rva00285B60Get(void)
{
	return 255;
}

// ?Rva0028B04AGet@@YAHXZ @ 0x0028b04a (6B): returns -16777216.
// Follows a conditional mov plus ret tail (its je targets the ret, not
// this body). No direct callers. Opaque address-derived name.
int Rva0028B04AGet(void)
{
	return (int)0xff000000;
}

// ?Rva0028B074Get@@YAHXZ @ 0x0028b074 (6B): returns -16777216.
// Follows a conditional mov plus ret tail (its je targets the ret, not
// this body). No direct callers. Opaque address-derived name.
int Rva0028B074Get(void)
{
	return (int)0xff000000;
}

// ?Rva002AA2C9Get@@YAHXZ @ 0x002aa2c9 (6B): returns 218.
// Follows an idiv helper tail. No direct callers. Opaque
// address-derived name.
int Rva002AA2C9Get(void)
{
	return 218;
}

// ?Rva0041F286Get@@YAHXZ @ 0x0041f286 (6B): returns 0x00c3b000.
// Follows an x87-load plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0041F286Get(void)
{
	return 0x00c3b000;
}

// ?Rva004D949FGet@@YAHXZ @ 0x004d949f (6B): returns INT_MIN.
// Follows a byte-store plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva004D949FGet(void)
{
	return (int)0x80000000;
}

// ?Rva00619FF0Get@@YAHXZ @ 0x00619ff0 (6B): returns -17.
// Follows a ret-12 plus int3 run. No direct callers. Opaque
// address-derived name.
int Rva00619FF0Get(void)
{
	return -17;
}

// ?Rva00620170Get@@YAHXZ @ 0x00620170 (6B): returns 32.
// Follows a sar plus ret plus int3 run. No direct callers. Opaque
// address-derived name.
int Rva00620170Get(void)
{
	return 32;
}
