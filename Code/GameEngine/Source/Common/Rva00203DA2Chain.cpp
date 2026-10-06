// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00203DA2Chain@@YAXPAVRva00203DA2A@@PAX@Z at retail 0x00203DA2 (28B).
// Sibling of Rva00203D86Chain (0x00203D86): free __cdecl chain with slot
// 0x6c (slot 27) then 0x60 (slot 24): mid = a->slot27(b); mid->slot24((char*)b+4).
// Target evidence: same 28B shape as 0x00203D86 except [eax+0x6c] then [edx+0x60].
// Callers at 0x0020814A/0x00208190 pass __cdecl args.

class Rva00203DA2Mid
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(void *p);
};

class Rva00203DA2A
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual Rva00203DA2Mid *s27(void *p);
};

void Rva00203DA2Chain(Rva00203DA2A *a, void *b)
{
	Rva00203DA2Mid *mid = a->s27(b);
	mid->s24((char *)b + 4);
}
