// cl: /MD
// ?Rva000AD8EBCopy@@YAPAHPAF0PAH@Z @0x000AD8EB 41B: sign-extending word to dword copy with dest stride 4 src stride 2 count from byte diff sar 1; caller 0x000ADF1B 29B; prev fill_n stlport_vector_s_o1 next deleting dtors OpaqueScalarDeletingDtors; no donor.

int *__cdecl Rva000AD8EBCopy(short *srcStart, short *srcEnd, int *dest)
{
	int count = (int)((char *)srcEnd - (char *)srcStart) >> 1;
	if (count > 0) {
		do {
			*dest = *srcStart;
			++srcStart;
			++dest;
			--count;
		} while (count != 0);
	}
	return dest;
}
