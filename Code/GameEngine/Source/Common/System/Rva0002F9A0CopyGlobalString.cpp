// cl: /DNDEBUG /MD /EHsc
// BFME1 donor at 0x009C8680; its bytes were ICF-folded across five BFME1 names.
// Keep the target address name because BFME2-side evidence does not choose one alias.
// The exact body copies its input to the buffer at retail 0x00DE01D0.

extern "C" char *__cdecl strcpy(char *, const char *);
#pragma intrinsic(strcpy)

void __cdecl Rva0002F9A0CopyGlobalString(const char *source)
{
    strcpy((char *)0x00DE01D0, source);
}
