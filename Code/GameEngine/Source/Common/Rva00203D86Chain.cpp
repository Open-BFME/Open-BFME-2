// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00203D86Chain@@YAXPAVRva00203D86A@@PAX@Z at retail 0x00203D86 (28B).
// Sibling of Rva00203D6AChain (0x00203D6A): free __cdecl chain with slot
// 0x78 (slot 30) twice: mid = a->slot30(b); mid->slot30((char*)b+4).
// Target evidence: same 28B shape as 0x00203D6A except [eax+0x78] for the
// first call. Callers at 0x0020698C/0x002069D2 pass __cdecl args.

class Rva00203D86Mid
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
	virtual void s30(void *p);
};

class Rva00203D86A
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
	virtual Rva00203D86Mid *s30(void *p);
};

void Rva00203D86Chain(Rva00203D86A *a, void *b)
{
	Rva00203D86Mid *mid = a->s30(b);
	mid->s30((char *)b + 4);
}
