// cl: /GX-
//
// ?Rva0059B036Copy@@YAPAXPAX0H@Z retail 0x0059B036 42B.
// 24-byte record build: copy the 20-byte head from src to stack tmp, store the
// tail, then copy the whole 24 bytes to dst and return dst. The returned
// destination is why retail materialises dst in eax and copies eax into edi for
// the rep movsd 6 (eax must survive as the return value); a void return drops
// that move. Evidence: retail 5/6 rep movsd, callers 0x00513ED1 0x0059B5A3
// 0x005E3753.
struct Rva0059B036Five
{
	int v[5];
};

struct Rva0059B036Six
{
	Rva0059B036Five head;
	int tail;
};

void *__cdecl Rva0059B036Copy(void *dst, void *src, int tail)
{
	Rva0059B036Six tmp;
	tmp.head = *(Rva0059B036Five *)src;
	tmp.tail = tail;
	*(Rva0059B036Six *)dst = tmp;
	return dst;
}
