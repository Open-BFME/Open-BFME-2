// Cold-slice B8-imm32 const-int returners (second twin-free TU).
//
// Same 6-byte shape as ConstIntGetters9.cpp (mov eax,<IMM32> / ret) for
// range-free bodies (no matched row contains the address). Every entry was
// vetted: unclaimed, unpinned, xref-empty, absent from re_attempts.log and
// deleted_rows.csv, exact-disx confirms mov/ret, and no short-jcc in the
// preceding 16B targets the mov (je-into-mov arms, jump-table case clusters
// and mid-fn fragments screened out). Opaque address-derived names witness
// only the address and the returned constant.
// No // cl: line (defaults match the frameless 6-byte shape).

// ?Rva002DF99DGet@@YAHXZ @ 0x002df99d (6B): returns 0x00c04310.
int Rva002DF99DGet(void)
{
	return 0x00c04310;
}

// ?Rva00318B39Get@@YAHXZ @ 0x00318b39 (6B): returns 0x00de0878.
int Rva00318B39Get(void)
{
	return 0x00de0878;
}
