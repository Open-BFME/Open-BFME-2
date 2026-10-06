// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00203D6AChain@@YAXPAVRva00203D6AA@@PAX@Z at retail 0x00203D6A (28B).
// Free __cdecl chain: mid = a->slot27(b); mid->slot30((char*)b+4).
// Target evidence: mov ecx,[esp+4]; mov eax,[ecx]; push esi;
// mov esi,[esp+0xC]; push esi; call [eax+0x6C]; mov edx,[eax];
// add esi,4; push esi; mov ecx,eax; call [edx+0x78]. Callers at
// 0x00208001/0x0020804A pass __cdecl (esi, &field+8). Slots 27/30 are the
// same pair as the 0x00203E11/0x00203E2C Xfer helpers; hosts are honest
// address names.

class Rva00203D6AMid
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

class Rva00203D6AA
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual Rva00203D6AMid *s27(void *p);
};

void Rva00203D6AChain(Rva00203D6AA *a, void *b)
{
	Rva00203D6AMid *mid = a->s27(b);
	mid->s30((char *)b + 4);
}
