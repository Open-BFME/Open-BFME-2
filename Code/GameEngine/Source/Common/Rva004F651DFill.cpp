// cl: /DNDEBUG /MD
// ?Rva004F651DFill@@YAPAUTreeHintRef00217D4C@@PAU1@HPBU1@@Z, retail 0x004F651D, 37 bytes.
// Uninitialized_fill_n over 4-byte TreeHintRef slots via rowed Rva00087A5CCopy
// at 0x00087A5C, returning the end pointer. Same 37B recipe as Rva004F6BB3Fill
// at 0x004F6BB3 (stride 0xC via Rva004F6B69Construct); here stride 4.
// Evidence: push esi/edi plus test edi jle plus push-push-call pop add dec
// pop jne plus mov eax esi; caller at 0x004F6CEE in FUN_008f6cdd.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
};

void __cdecl Rva00087A5CCopy(void **dst, void **src);

TreeHintRef00217D4C *Rva004F651DFill(TreeHintRef00217D4C *dst, int count, const TreeHintRef00217D4C *src)
{
	TreeHintRef00217D4C *p = dst;
	int n = count;
	for (; n > 0; --n) {
		Rva00087A5CCopy((void **)p, (void **)src);
		p = (TreeHintRef00217D4C *)((char *)p + 4);
	}
	return p;
}
