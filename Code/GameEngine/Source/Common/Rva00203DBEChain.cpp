// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00203DBEChain@@YAXPAVRva00203DBEA@@PAX@Z at retail 0x00203DBE (28B).
// Sibling of Rva00203D86Chain (0x00203D86) and Rva00203DA2Chain (0x00203DA2):
// free __cdecl chain with slot 0x78 (slot 30) then 0x60 (slot 24).
// Target evidence: same 28B shape except [eax+0x78] then [edx+0x60].
// Callers at 0x00206A57/0x00206A9F pass __cdecl args.

class Rva00203DBEMid
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

class Rva00203DBEA
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29();
	virtual Rva00203DBEMid *s30(void *p);
};

void Rva00203DBEChain(Rva00203DBEA *a, void *b)
{
	Rva00203DBEMid *mid = a->s30(b);
	mid->s24((char *)b + 4);
}
