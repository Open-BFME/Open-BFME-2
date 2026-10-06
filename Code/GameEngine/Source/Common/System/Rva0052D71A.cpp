// cl: /DNDEBUG /MD
// ?Rva0052D71AFillN@@YAPAVRva0056616B@@PAV1@IABV1@@Z @0x0052D71A 40B
// Array fill_n helper calling 0x0052D6BE Construct in a 0xB8-stride loop with count.
// Evidence: chain from 0x0052D6BE; caller 0x0052D742 pushes (dst count src); returns end pointer in eax.
class Rva0056616B
{
public:
	Rva0056616B(const Rva0056616B &other);
	~Rva0056616B();
	char m_pad[0xB8];
};
void __cdecl Rva0052D6BEConstruct(Rva0056616B *dst, const Rva0056616B &src);
Rva0056616B *__cdecl Rva0052D71AFillN(Rva0056616B *first, unsigned int n, const Rva0056616B &x)
{
	Rva0056616B *cur = first;
	for (; n > 0; --n, ++cur)
		Rva0052D6BEConstruct(cur, x);
	return cur;
}
