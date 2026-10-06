// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva001F63C9Erase@@YGXPAPAXPAURva001F63C9Node@@@Z @0x001F63C9 44B
// Evidence: unlink via Next at +0 Prev at +4 destroys 12B value at +8 via rowed destroyDelete 0x0004CCFF with flags 0 frees node via rowed _free 0x00030830 stores Next into *out; caller 0x001F8144 passes list plus node; shape from Rva004168D3Erase plus EraseTargetListNode0073EFFC.
class Rva0004CCFF
{
public:
	void *destroyDelete(unsigned int flags);
};

struct Rva001F63C9Node
{
	void *m_next;
	void *m_prev;
	Rva0004CCFF m_value;
};

extern "C" void __cdecl free(void *block);

void __stdcall Rva001F63C9Erase(void **out, Rva001F63C9Node *pos)
{
	void *next = pos->m_next;
	void *prev = pos->m_prev;
	*(void **)prev = next;
	*(void **)((char *)next + 4) = prev;
	pos->m_value.destroyDelete(0);
	free(pos);
	*out = next;
}
