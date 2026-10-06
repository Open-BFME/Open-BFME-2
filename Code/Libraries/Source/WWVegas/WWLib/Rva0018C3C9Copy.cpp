// cl: /Ireference/shims/bfmelist /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ?Rva0018C3C9Copy@@YAPAFPAURva0018C2E7Node@@0PAF@Z @0x0018C3C9 29B
// Chain wrapper for just-landed Rva0018C2E7Copy: passes through first/last/
// result with tag1 as local byte and tag2 0, returning copy result. Evidence:
// rowed Rva0018C2E7Copy 0x0018C2E7 five-arg __cdecl shape, neighbours
// Rva0018C262 same flags, callers 0x0018C533 plus 0x0018C705 plus 0x0018C73C.
struct Rva0018C2E7Node {
	int m_00;
	void *m_04;
	void *m_08;
	void *m_0C;
	short m_10;
};
short *__cdecl Rva0018C2E7Copy(Rva0018C2E7Node *first, Rva0018C2E7Node *last, short *result, void *tag1, int tag2);
short *__cdecl Rva0018C3C9Copy(Rva0018C2E7Node *first, Rva0018C2E7Node *last, short *result)
{
	char tag1;
	return Rva0018C2E7Copy(first, last, result, &tag1, 0);
}
