// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?Rva002D0D5ECopy@@YAPADPAD00H@Z @0x002D0D5E 29B wrapper over counted copy 0x002D0BB8 stride 92.
// Evidence: calls 0x002D0BB8 ?Rva002D0BB8Copy@@YAPADPAD00@Z; callers 0x002D0FDC 0x002D0FFC pass 4 args; retail pushes 5 to callee.
char *__cdecl Rva002D0BB8Copy5(char *first, char *last, char *result, char *tmp, int zero);
char *__cdecl Rva002D0D5ECopy(char *first, char *last, char *result, int unused)
{
	char tmp;
	return Rva002D0BB8Copy5(first, last, result, &tmp, 0);
}
