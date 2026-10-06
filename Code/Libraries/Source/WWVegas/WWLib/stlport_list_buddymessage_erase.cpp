// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?Rva004168D3Erase@@YGXPAPAXPAUBuddyEraseNode@@@Z @0x004168D3 42B
// List unlink plus BuddyMessage destroy plus free. Unlinks node via Next at
// +0 and Prev at +4; destroys BuddyMessage at +8 via rowed 0x0038215B;
// frees node via rowed _free 0x00030830; stores Next into *out.
// Caller 0x00416939; prev list insert 0x004168AE.
class BuddyMessage
{
public:
	~BuddyMessage();
};

struct BuddyEraseNode
{
	void *m_next;
	void *m_prev;
	BuddyMessage m_msg;
};

extern "C" void __cdecl free(void *block);

void __stdcall Rva004168D3Erase(void **out, BuddyEraseNode *pos)
{
	void *next = pos->m_next;
	void *prev = pos->m_prev;
	*(void **)prev = next;
	*(void **)((char *)next + 4) = prev;
	pos->m_msg.~BuddyMessage();
	free(pos);
	*out = next;
}
