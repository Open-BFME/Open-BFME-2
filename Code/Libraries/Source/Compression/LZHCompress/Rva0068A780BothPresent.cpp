// cl: /DNDEBUG /MD /EHsc
// BFME1 donor at 0x0081EB30; the body was ICF-folded with a second BFME1 helper.
// Keep an RVA-derived target name; retail at 0x0068A780 tests both arguments.
bool __cdecl Rva0068A780BothPresent(const void *first, const void *second)
{
    if (first != 0 && second != 0)
        return true;
    return false;
}
