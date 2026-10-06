// cl: /MD
// ?Rva00600665Set@@YAXPAD@Z @0x00600665 17B free cdecl copy into g_00DD509C ("English" buffer).
// Retail push arg; push global; call _mbscpy via 0x00629176; pop ecx twice; ret.
// Evidence: sibling Rva00600777Set copies to TheLangDir via same _mbscpy; data xref 0x009D509C
// read by 0x00600E3A 0x00600FC9 0x00600665 0x00600C34 0x00600D7D; callee rowed ji_00629176 (_mbscpy).
extern char g_00DD509C[];
extern "C" char *__cdecl _mbscpy(char *dst, const char *src);
void __cdecl Rva00600665Set(char *src)
{
	_mbscpy(g_00DD509C, src);
}
