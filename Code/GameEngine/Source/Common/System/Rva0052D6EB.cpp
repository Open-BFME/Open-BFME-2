// cl: /DNDEBUG /MD
// ?Rva0052D6EBCopy@@YAPAVRva0056616B@@PAV1@00@Z @0x0052D6EB 47B
// Array uninitialized_copy helper calling 0x0052D6BE Construct stepping 0xB8.
// Evidence: chain from 0x0052D6BE; compares src vs end and returns dst end in eax.
class Rva0056616B
{
public:
	Rva0056616B(const Rva0056616B &other);
	~Rva0056616B();
	char m_pad[0xB8];
};
void __cdecl Rva0052D6BEConstruct(Rva0056616B *dst, const Rva0056616B &src);
Rva0056616B *__cdecl Rva0052D6EBCopy(Rva0056616B *first, Rva0056616B *last, Rva0056616B *dest)
{
	Rva0056616B *cur_first = first;
	Rva0056616B *cur_dest = dest;
	for (; cur_first != last; ++cur_first, ++cur_dest)
		Rva0052D6BEConstruct(cur_dest, *cur_first);
	return cur_dest;
}
