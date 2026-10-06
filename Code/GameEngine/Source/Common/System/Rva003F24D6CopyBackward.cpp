// cl: /DNDEBUG /MD
// ?Rva003F24D6CopyBackward@@YAXPAD00@Z @0x003F24D6 29B:
// wrapper calling rowed 0x003F1F38 copy-backward with two extra ignored
// trailing args (local byte plus 0). Caller 0x003F365D. Sibling of
// Rva003F2460Copy 0x003F2460 (forward direction). Dedicated TU so the
// call stays external.
char *__cdecl Rva003F1F38CopyBackward(char *first, char *last, char *result);
typedef char *(__cdecl *Rva003F1F38CopyBackward5Fn)(char *, char *, char *, char *, int);
void __cdecl Rva003F24D6CopyBackward(char *first, char *last, char *result)
{
	char tmp;
	((Rva003F1F38CopyBackward5Fn)&Rva003F1F38CopyBackward)(first, last, result, &tmp, 0);
}
