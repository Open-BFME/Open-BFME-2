// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva004E7B6EErase@@YGXPAPAXPAURva004E7B6ENode@@@Z @0x004E7B6E 42B
// List unlink plus Rva004E7A76 destroy plus free. Unlinks node via Next at
// +0 and Prev at +4; destroys value at +8 via rowed 0x004E7A76;
// frees node via rowed _free 0x00030830; stores Next into *out.
// Callers 0x004E7B98 and 0x004E7FCA; prev list insert 0x004E7B49.
class Rva004E7A76
{
public:
	void rva004E7A76();
};

struct Rva004E7B6ENode
{
	void *m_next;
	void *m_prev;
	Rva004E7A76 m_msg;
};

extern "C" void __cdecl free(void *block);

void __stdcall Rva004E7B6EErase(void **out, Rva004E7B6ENode *pos)
{
	void *next = pos->m_next;
	void *prev = pos->m_prev;
	*(void **)prev = next;
	*(void **)((char *)next + 4) = prev;
	pos->m_msg.rva004E7A76();
	free(pos);
	*out = next;
}
