// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00203D4EChain@@YAXPAVRva00203D4EA@@PAX@Z at retail 0x00203D4E (28B).
// Free __cdecl chain: mid = a->slot27(b); mid->slot27((char*)b+4).
// Target evidence: mov ecx,[esp+4]; mov eax,[ecx]; push esi;
// mov esi,[esp+0xC]; push esi; call [eax+0x6C]; mov edx,[eax];
// add esi,4; push esi; mov ecx,eax; call [edx+0x6C]. Callers in
// UNCLAIMED FUN_0060a859. Same shape as neighbour 0x00203D6A which uses
// slots 27/30; here both calls are slot 27 (0x6C/4=27).

class Rva00203D4EMid
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual void s27(void *p);
};

class Rva00203D4EA
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual Rva00203D4EMid *s27(void *p);
};

void Rva00203D4EChain(Rva00203D4EA *a, void *b)
{
	Rva00203D4EMid *mid = a->s27(b);
	mid->s27((char *)b + 4);
}
