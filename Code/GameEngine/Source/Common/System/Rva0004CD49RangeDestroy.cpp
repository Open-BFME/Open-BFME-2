// cl: /DNDEBUG /MD
// ?Rva0004CD49Destroy@@YAXPAVRva0004CCFF@@0@Z @0x0004CD49 27B
// Range destroy over 12-byte Rva0004CCFF handles via rowed destroyDelete 0x0004CCFF.
// Evidence: unlock lane unblocks 0x0004CD64; step 0xC; flags 0; caller 0x0004CD72.
class Rva0004CCFF
{
public:
	void *destroyDelete(unsigned int flags);
};

struct Rva0004CD49Elem
{
	char m_pad[0xC];
};

void __cdecl Rva0004CD49Destroy(Rva0004CCFF *first, Rva0004CCFF *last)
{
	for (Rva0004CCFF *p = first; p != last; p = (Rva0004CCFF *)((char *)p + 0xC))
		p->destroyDelete(0);
}
