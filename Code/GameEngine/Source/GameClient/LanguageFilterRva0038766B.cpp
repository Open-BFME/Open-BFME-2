// cl: /O1 /MD
// ?Rva0038766BAlloc@@YGPAU_Rva0038766BNode@@PBURva0038768DData@@@Z retail 0x0038766B 34 bytes.
// Chain of 0x0038768D: allocates 0x18 via 0x307F0 then copies tail at +0x10.
// Callers 0x3875DB 0x387717 0x38968F 0x5539DC init +0/+4/+8/+0xC themselves.
// Identity honest address name free function.
namespace _STL
{
template <typename T> class allocator;
template <> class allocator<char>
{
public:
	static char *allocate(unsigned int n, const void *hint);
};
}
struct Rva0038768DData
{
	unsigned char m_b;
	int m_x;
};
void __cdecl Rva0038768DCopy(struct Rva0038768DData *dest, const struct Rva0038768DData *src);
struct _Rva0038766BNode
{
	char m_pad00[0x10];
	struct Rva0038768DData m_tail;
};
struct _Rva0038766BNode *__stdcall Rva0038766BAlloc(const struct Rva0038768DData *src)
{
	struct _Rva0038766BNode *n = (struct _Rva0038766BNode *)_STL::allocator<char>::allocate(0x18, 0);
	Rva0038768DCopy(&n->m_tail, src);
	return n;
}
