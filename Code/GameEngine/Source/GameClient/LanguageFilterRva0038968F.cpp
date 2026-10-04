// cl: /O1 /MD
// ?Rva0038968FDup@@YGPAU_Rva0038766BNode@@PBU1@@Z retail 0x0038968F 30 bytes.
// Dups _Rva0038766BNode via rowed Alloc 0x0038766B then inits +0 +8 +0xC.
// Chain of 0x0038766B; no callers.
// Identity honest address free function __stdcall returns Node*.
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
struct _Rva0038766BNode
{
	char m_pad00[0x10];
	struct Rva0038768DData m_tail;
};
struct _Rva0038766BNode *__stdcall Rva0038766BAlloc(const struct Rva0038768DData *src);
struct _Rva0038766BNode *__stdcall Rva0038968FDup(const struct _Rva0038766BNode *src)
{
	struct _Rva0038766BNode *n = Rva0038766BAlloc(&src->m_tail);
	unsigned char b = *(const unsigned char *)src;
	*(int *)((char *)n + 8) = 0;
	*(int *)((char *)n + 0xc) = 0;
	*(unsigned char *)n = b;
	return n;
}
