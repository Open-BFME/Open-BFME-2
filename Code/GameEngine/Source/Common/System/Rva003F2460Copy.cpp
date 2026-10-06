// cl: /DNDEBUG /MD
// ?Rva003F2460Copy@@YAXPAD00@Z @0x003F2460 29B:
// wrapper calling rowed 0x003F1F06 copy with two extra ignored trailing
// args (local byte plus 0). Caller 0x003F316D unblocks 0x003F3159.
// Dedicated TU so the call stays external.
char *__cdecl Rva003F1F06Copy(char *first, char *last, char *result);
typedef char *(__cdecl *Rva003F1F06Copy5Fn)(char *, char *, char *, char *, int);
void __cdecl Rva003F2460Copy(char *first, char *last, char *result)
{
	char tmp;
	((Rva003F1F06Copy5Fn)&Rva003F1F06Copy)(first, last, result, &tmp, 0);
}
