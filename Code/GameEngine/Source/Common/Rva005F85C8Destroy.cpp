// cl: /MD
// ?Rva005F85C8Destroy@@YAXPAURva005F8447@@0@Z 0x005F85C8 25B: stride-8 destroy loop over Rva005F8447 via rowed dtor 0x005F8447.
// Evidence: callers at 0x005F85FB 0x005F863F 0x005F865B expect first-last range; prev copy 0x005F8573 same stride-8; callee rowed dtor.
struct Rva005F8447
{
	char m_pad[8];
	~Rva005F8447();
};
void __cdecl Rva005F85C8Destroy(Rva005F8447 *first, Rva005F8447 *last)
{
	for (; first != last; ++first)
		first->~Rva005F8447();
}
